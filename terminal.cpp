//
// Created by phtran on 13/05/2016.
//

#include <signal.h>
//#include <unistd.h>
//#include <stropts.h>
#include <stdio.h>
#include <errno.h>
#include <algorithm>
#include <iostream>

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdbool.h>



#include "terminal.h"
//#include "countedpointer.h"
#include "event.h"
#include "topline.h"
#include "errormessage.h"
#include "baseeventhandler.h"
#include "screen.h"

static const char LOWEST_PRINTABLE_ASCII( ' ' );
static const char HIGHEST_PRINTABLE_ASCII( '~' );

using KeyStrokeEventPtr = std::shared_ptr<UI::KeyStrokeEvent>;
using KeyStroke2EventTable = std::map<int, KeyStrokeEventPtr>;

const UI::Terminal::AttributeMask UI::Terminal::normal(0x0);
const UI::Terminal::AttributeMask UI::Terminal::dim(0x1);
const UI::Terminal::AttributeMask UI::Terminal::bold(0x2);
const UI::Terminal::AttributeMask UI::Terminal::blink(0x4);
const UI::Terminal::AttributeMask UI::Terminal::hidden(0x8);
const UI::Terminal::AttributeMask UI::Terminal::inverse(0x10);
const UI::Terminal::AttributeMask UI::Terminal::underline(0x20);
const UI::Terminal::AttributeMask UI::Terminal::graphics(0x40);

static const UI::Terminal::Colour DEFAULT_FOREGROUND(UI::Terminal::yellow);
static const UI::Terminal::Colour DEFAULT_BACKGROUND(UI::Terminal::black);

static const unsigned int DEFAULT_WIDTH(79);
static const unsigned int DEFAULT_HEIGHT(24);

UI::Terminal* UI::Terminal::singleTerm_(0);

static unsigned int DEFAULT_X_COORDINATE(1);
static unsigned int DEFAULT_Y_COORDINATE(1);

//static const char ESCAPE_SYMBOL( '^[' );
//static const char ESCAPE_SYMBOL( '\u001B' );
static const char ESCAPE_SYMBOL( '' );
//static const char BACKSPACE_SYMBOL( '^H' );
//static const char BACKSPACE_SYMBOL( '' );
static const char BACKSPACE_SYMBOL( '\b' );
//static const char DELETE_SYMBOL( '^?' );
static const char DELETE_SYMBOL( '\u007F' );
static const char TAB_SYMBOL( '\t' );

class ThrowTerminateException : public BaseEventHandler
{
public:
    void invoke()
    {
        throw TerminateException();
    }
    ThrowTerminateException* clone() const
    {
        return new ThrowTerminateException(*this);
    }
};

static void handleExceptionInMainLoop(const std::string& m)
{
    UI::terminal().root().clear();
    UI::TopLine tl;
    UI::terminal().root().addComponent(tl);
    UI::ErrorMessage em(m);
    em.addEventHandler(UI::RemoveComponentEvent(), ThrowTerminateException());
    UI::terminal().root().addComponent(em);
    UI::terminal().drawAll();
}

enum TerminalAttribute
{
    ta_normal = 0,
    ta_bright = 1,
    ta_dim,
    ta_underline = 4,
    ta_blink,
    ta_hidden,
    ta_reverse = 7
};

static int readKeyStroke()
{
    const int i(getchar());
    if ( i == EOF && ( errno == EIO || errno == ENXIO ) ) {
        throw AbortException();
    }
    return i;
}

static void sendEscapeCode(TerminalAttribute a, UI::Terminal::Colour fg, UI::Terminal::Colour bg)
{
    fprintf(stdout, "%c[%dm", 27, (int)a);
}

static void addEvent(KeyStroke2EventTable& t, const UI::KeyStrokeEvent& e)
{
    t[e.keyStroke()] = KeyStrokeEventPtr(e.clone());
}

class AddPrintableEvent
{
    KeyStroke2EventTable &table_;
public:
    AddPrintableEvent( KeyStroke2EventTable &t )
            : table_( t )
    { }
    void operator()( const char c )
    {
        addEvent( table_, UI::PrintableKeyEvent( c ) );
    }
};

static const KeyStroke2EventTable& keyStroke2EventTable()
{
    static KeyStroke2EventTable t;
    if (t.empty()) {
        addEvent( t, UI::QuestionEvent() );
        addEvent( t, UI::UpArrowEvent() );
        addEvent( t, UI::DownArrowEvent() );
        //@TODO: uncomment out when code complete
        addEvent( t, UI::LeftArrowEvent() );
        addEvent( t, UI::RightArrowEvent() );
        //addEvent( t, UI::PageUpEvent() );
        //addEvent( t, UI::PageDownEvent() );
        addEvent( t, UI::EscEscEvent() );
        //addEvent( t, UI::EscQEvent() );
        addEvent( t, UI::EnterEvent() );
        addEvent( t, UI::BackSpaceEvent() );
        addEvent( t, UI::DeleteEvent() );
        //addEvent( t, UI::F1Event() );
        //addEvent( t, UI::F2Event() );
        //addEvent( t, UI::F3Event() );
        //addEvent( t, UI::F4Event() );
        //addEvent( t, UI::F5Event() );
        //addEvent( t, UI::F6Event() );
        //addEvent( t, UI::F7Event() );
        //addEvent( t, UI::F8Event() );
        //addEvent( t, UI::F9Event() );
        //addEvent( t, UI::F10Event() );
        //addEvent( t, UI::F11Event() );
        //addEvent( t, UI::F12Event() );
        addEvent( t, UI::TabEvent() );
        //addEvent( t, UI::HomeKeyEvent() );
        //addEvent( t, UI::EndKeyEvent() );
        //addEvent( t, UI::ControlFKeyEvent() );
        //addEvent( t, UI::ControlFKeyEvent() );
        std::list<char> l( UI::terminal().allPrintableCharacters() );
        std::for_each( l.begin(), l.end(), AddPrintableEvent( t ) );
    }
    return t;
}

extern "C" {
static void windowChangeSignalHandler( int s )
{
    if (sigset(s, &windowChangeSignalHandler ) == SIG_ERR) {
        std::ostringstream m;
        m << "could not assign signal handler '" << s << "'";
        throw InternalException();
    }
    switch (s) {
        case SIGWINCH:
            UI::terminal().root().notifyEvent(UI::TerminalGeometryChangedEvent());
            break;
    }
}
}

namespace UI
{
    static void assignSignalHandlers()
    {
        if (sigset(SIGWINCH, &windowChangeSignalHandler) == SIG_ERR) {
            throw InternalException();
        }
    }
}

UI::Terminal& UI::terminal()
{
    return UI::Terminal::instance();
}

UI::Terminal& UI::Terminal::instance()
{
    if (!singleTerm_) {
        singleTerm_ = new Terminal;
        UI::assignSignalHandlers();
    }
    return *singleTerm_;
}

void UI::Terminal::startMainLoop()
{
    UI::Screen& screen = dynamic_cast<UI::Screen&>(*root_.begin()->get());
    for (;;) {
        const int k(getKey());
        KeyStroke2EventTable::const_iterator
                i(keyStroke2EventTable().find(k));
        if (i != keyStroke2EventTable().end()) {
            try {
                root_.notifyEvent(*i->second);
                dispose_.clear();
            } catch (const TerminateException&) {
                return;
            } catch (const std::exception &e) {
                handleExceptionInMainLoop(e.what());
            }
        }
    }
}

void UI::Terminal::eraseEol()
{
    std::cout << static_cast<char>(27) << "[K";
}

void UI::Terminal::eraseEos()
{
    std::cout << static_cast<char>(27) << "[J";
}

unsigned int UI::Terminal::xCoordinate() const
{
    return xCoordinate_;
}

unsigned int UI::Terminal::yCoordinate() const
{
    return yCoordinate_;
}

void UI::Terminal::saveCursorPosition()
{
    savedXCoordinate_ = xCoordinate();
    savedYCoordinate_ = yCoordinate();
}

void UI::Terminal::restoreCursorPosition()
{
    gotoxy(savedXCoordinate_, savedYCoordinate_);
}

void UI::Terminal::gotoxy(const unsigned int x, const unsigned int y)
{
    xCoordinate_ = x;
    yCoordinate_ = y;
    std::cout << static_cast<char>(27) << "["
    << yCoordinate_ << ";"
    << xCoordinate_ << "H";
}

void UI::Terminal::write(const std::string& s)
{
    if (static_cast<int>((width() - xCoordinate()) - 2) < 0) {
        xCoordinate_ += s.size();
        return;
    }
    std::cout << s.substr(0, width() - xCoordinate() + 1);
    xCoordinate_ += s.size();
}

void UI::Terminal::write(const char c)
{
    std::ostringstream s;
    s << c;
    write( s.str() );
}

unsigned int UI::Terminal::width() const
{
    struct winsize ws;
    if ( ioctl( 0, TIOCGWINSZ, &ws ) < 0 ) {
        return DEFAULT_WIDTH;
    }
    if ( ws.ws_col < 0 ) {
        return DEFAULT_WIDTH;
    }
    return ws.ws_col;
}

unsigned int UI::Terminal::height() const
{
    struct winsize ws;
    if ( ioctl( 0, TIOCGWINSZ, &ws ) < 0 ) {
        return DEFAULT_HEIGHT;
    }
    if ( ws.ws_row < 0 ) {
        return DEFAULT_HEIGHT;
    }
    return ws.ws_row;
}

UI::Container& UI::Terminal::root()
{
    return root_;
}

void UI::Terminal::drawAll()
{
    root().notifyEvent(UI::DrawAllEvent());
}

void UI::Terminal::endEnhanced()
{
    attributes(normal);
}

void UI::Terminal::startBold()
{
    attributes( bold );
}

void UI::Terminal::startInverse()
{
    attributes( inverse );
}

void UI::Terminal::startUnderline()
{
    attributes(underline);
}

void UI::Terminal::attributes(AttributeMask a)
{
    const AttributeMask origMask = attributeMask_;
    attributeMask_ |= a;
    if (a & Terminal::graphics) {
        fprintf( stdout, "%c(0", 27 );
    } else if (a == Terminal::normal) {
        attributeMask_ = Terminal::normal;
        if (origMask & Terminal::graphics) {
            fprintf( stdout, "%c(B", 27 );
        }
        sendEscapeCode(ta_normal, foreground_, background_);
        return;
    }
    if (a & Terminal::bold) {
        sendEscapeCode(ta_bright, foreground_, background_);
    }
    if (a & Terminal::underline) {
        sendEscapeCode(ta_underline, foreground_, background_);
    }
    if (a & Terminal::inverse) {
        sendEscapeCode(ta_reverse, foreground_, background_);
    }
}

void UI::Terminal::parkCursor()
{
    gotoxy(width(), height());
}

std::list<char> UI::Terminal::allPrintableCharacters() const
{
    std::list<char> l;
    for (char c(LOWEST_PRINTABLE_ASCII); c != HIGHEST_PRINTABLE_ASCII + 1; ++c) {
        l.push_back( c );
    }
    return l;
}

void UI::Terminal::dispose(ComponentPtr &c )
{

    if ( c.get() == 0 ) {
        return;
    }
    dispose_.push_back( c );
}

UI::Terminal::Terminal()
        : xCoordinate_(DEFAULT_X_COORDINATE)
        , yCoordinate_(DEFAULT_Y_COORDINATE)
        , attributeMask_(UI::Terminal::normal)
        , foreground_(DEFAULT_FOREGROUND)
        , background_(DEFAULT_BACKGROUND)
        , savedXCoordinate_(DEFAULT_X_COORDINATE)
        , savedYCoordinate_(DEFAULT_Y_COORDINATE)
{
    int STDIN = 0;
    struct termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN, TCSANOW, &term);
}

int UI::Terminal::getKey()
{
    int keyStroke( readKeyStroke() );
    if ( keyStroke == ESCAPE_SYMBOL ) {
        switch (readKeyStroke()) {
            case ESCAPE_SYMBOL:
                keyStroke = ESCESC;
                break;
            case '[':
                int key2;
                switch (readKeyStroke()) {
                    case 'A': keyStroke = UP_ARROW;    break;
                    case 'B': keyStroke = DOWN_ARROW;  break;
                    case 'C': keyStroke = RIGHT_ARROW; break;
                    case 'D': keyStroke = LEFT_ARROW;  break;
                    case '1':
                        switch (readKeyStroke()) {
                            case '2': key2 = FKEY_2; break;
                            case '3': key2 = FKEY_3; break;
                            case '4': key2 = FKEY_4; break;
                            case '5': key2 = FKEY_5; break;
                            case '7': key2 = FKEY_6; break;
                            case '8': key2 = FKEY_7; break;
                            case '9': key2 = FKEY_8; break;
                        }
                        if (keyStroke == '~')
                            keyStroke = key2;
                        break;
                    case '2':
                        switch (readKeyStroke()) {
                            case '0' : key2 = FKEY_9;  break;
                            case '1' : key2 = FKEY_10; break;
                            case '3' : key2 = FKEY_11; break;
                            case '4' : key2 = FKEY_12; break;
                        }
                        if (keyStroke == '~')
                            keyStroke = key2;
                        break;
                }
        }

    } else {
        switch (keyStroke) {
            case BACKSPACE_SYMBOL: keyStroke = BACK_SPACE;    break;
            case DELETE_SYMBOL:    keyStroke = DELETE;        break;
            case TAB_SYMBOL:       keyStroke = TAB_KEY;       break;
            case 10:               keyStroke = RETURN;        break;
            case 6:                keyStroke = CTRL_F;        break;
            case 16:               keyStroke = CTRL_P;        break;
        }
    }
    return keyStroke;
}
