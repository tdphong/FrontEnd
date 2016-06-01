//
// Created by phtran on 14/05/2016.
//

#include <algorithm>
#include <iostream>

#include "screen.h"
#include "baseeventhandler.h"
#include "screenfield.h"
#include "baseevent.h"
#include "event.h"
#include "terminal.h"
#include "screenenduserinputeventhandler.h"
#include "screenredraweventhandler.h"
#include "screenterminalgeometrychangedeventhandler.h"
#include "screengainfocuseventhandler.h"
#include "screenstepfocusforwardeventhandler.h"
#include "screenstepfocusbackwardeventhandler.h"
#include "screenleftarroweventhandler.h"
#include "screenrightarroweventhandler.h"
#include "warningexception.h"
#include "sysfile.h"
#include "loadscreenfields.h"

static const int FIRST_DRAWABLE_ROW(3);

static const std::string COMPONENT_NAME("Screen");

namespace UI
{
    namespace ScreenEvent
    {
        class EndUserInputEventHandler : public BaseEventHandler
        {
            UI::Screen &screen_;

        public:
            EndUserInputEventHandler( Screen &s )
                    : screen_( s )
            { }
            virtual void invoke( )
            {
                if ( !screen_.endUserInputEventHandler().get( ) )
                {
                    return;
                }
                screen_.endUserInputEventHandler()->invoke( );
            }

            virtual EndUserInputEventHandler* clone( ) const
            {
                return new EndUserInputEventHandler( *this );
            }
        };
    }
}

class ScreenPrintEventHandler : public BaseEventHandler
{
    UI::Screen &screen_;

public:
    ScreenPrintEventHandler( UI::Screen &s )
            : screen_( s )
    { }
    virtual void invoke()
    {
        screen_.draw();
    }
    virtual ScreenPrintEventHandler* clone() const
    {
        return new ScreenPrintEventHandler( *this );
    }

};

static void drawField(const std::shared_ptr<UI::ScreenField>& f)
{
    f->draw();
}

static void clearField(UI::Screen::value_type& f)
{
    f->clear();
}

class ForwardEventToFocus : public BaseEventHandler
{
    UI::Screen& screen_;
    std::shared_ptr<BaseEvent> event_;

public:
    ForwardEventToFocus(UI::Screen& s, const BaseEvent& e)
            : screen_(s)
            , event_(e.clone())
    { }
    void invoke()
    {
        (*screen_.focus())->notifyEvent( *event_ );
    }
    ForwardEventToFocus* clone() const
    {
        return new ForwardEventToFocus(*this);
    }
};

class AddForwardEventToFocusEventHandler
{
    UI::Screen& screen_;

public:
    AddForwardEventToFocusEventHandler(UI::Screen& s) : screen_(s)
    { }
    void operator()(const char c)
    {
        screen_.addEventHandler(UI::PrintableKeyEvent(c)
                , ForwardEventToFocus(screen_, UI::PrintableKeyEvent(c)), true);
    }
};

static void addEventHandlers(UI::Screen& s)
{
    //@TODO: Uncomment out when code completes
    s.addEventHandler(UI::TerminalGeometryChangedEvent(), UI::ScreenTerminalGeometryChangedEventHandler(s));
    s.addEventHandler(UI::DrawAllEvent(), UI::ScreenRedrawEventHandler(s));
    s.addEventHandler(UI::GainFocusEvent(), UI::ScreenGainFocusEventHandler(s));
    s.addEventHandler(UI::StepFocusForwardEvent(), UI::ScreenStepFocusForwardEventHandler(s));
    s.addEventHandler(UI::StepFocusBackwardEvent(), UI::ScreenStepFocusBackwardEventHandler(s));
    s.addEventHandler(UI::EndUserInputEvent(), UI::ScreenEvent::EndUserInputEventHandler(s));
    s.addEventHandler(UI::EscEscEvent(), ForwardEventToFocus(s, UI::EscEscEvent()));
    s.addEventHandler(UI::BackSpaceEvent(), ForwardEventToFocus(s, UI::BackSpaceEvent()));
    s.addEventHandler(UI::DeleteEvent(), ForwardEventToFocus(s, UI::DeleteEvent()));
    s.addEventHandler(UI::EnterEvent(), UI::ScreenStepFocusForwardEventHandler(s));
    s.addEventHandler(UI::TabEvent(), UI::ScreenStepFocusForwardEventHandler(s));
    s.addEventHandler(UI::UpArrowEvent(), UI::ScreenStepFocusBackwardEventHandler(s));
    s.addEventHandler(UI::DownArrowEvent(), UI::ScreenStepFocusForwardEventHandler(s));
    s.addEventHandler(UI::LeftArrowEvent(), UI::ScreenLeftArrowEventHandler(s));
    s.addEventHandler(UI::RightArrowEvent(), UI::ScreenRightArrowEventHandler(s));
    std::list<char> l(UI::terminal().allPrintableCharacters());
    std::for_each(l.begin(), l.end(), AddForwardEventToFocusEventHandler(s));
}

static bool isEditable(const UI::ScreenField& f)
{
    if (f.readonly()) {
        return false;
    }
    if (f.xCoordinate() + f.length() > UI::terminal().width()) {
        return false;
    }
    return true;
}

static void decrement(UI::Screen& s, UI::Screen::iterator& i)
{
    if (i == s.begin()) {
        i = s.end();
    } else {
        --i;
    }
}

UI::Screen::Screen() : topLine_(std::make_shared<TopLine>())
{
    addEventHandlers(*this);
    focus_ = end();
}

UI::Screen::Screen(const std::string& n) : topLine_(std::make_shared<TopLine>())
{
    load(n);
    addEventHandlers(*this);
    focus_ = end();
}

std::shared_ptr<BaseEventHandler> UI::Screen::endUserInputEventHandler()
{
    return std::make_shared<ScreenEndUserInputEventHandler>(*this);
}

UI::ScreenField& UI::Screen::operator[](const unsigned int i)
{
    if (i >= fields_.size()) {
        throw InternalException();
    }
    return *fields_[ i ];
}

const UI::ScreenField& UI::Screen::operator[](const unsigned int i) const
{
    if (i >= fields_.size()) {
        throw InternalException();
    }
    return *fields_[ i ];
}

UI::Screen::iterator UI::Screen::stepForward()
{
    if (focus() == end()) {
        return end();
    }
    iterator before(focus());
    notifyNoRecurse(focus(), LooseFocusForwardEvent());
    if (focus() != before) {
        return focus();
    }
    iterator i(focus());
    ++i;
    for (; i != end() && ! isEditable(*(*i)); ++i) { }
    focus(i);
    notifyNoRecurse(focus(), GainFocusForwardEvent());
    if (focus() == end()) {
        UI::terminal().root().notifyEvent( UI::EndUserInputEvent() );
    }
    return focus();
}

UI::Screen::iterator UI::Screen::stepBackward()
{
    if (focus() == end()) {
        return end();
    }
    iterator before(focus());
    notifyNoRecurse(focus(), LooseFocusBackwardEvent());
    if (focus() != before) {
       return focus();
    }
    iterator i(focus());
    decrement( *this, i );
    for (; i != end() && ! isEditable(*(*i)); decrement(*this, i)) { }
    focus(i);
    notifyNoRecurse(focus(), GainFocusBackwardEvent());
    if (focus() == end()) {
        UI::terminal().root().notifyEvent(UI::EndUserInputEvent());
    }
    return focus();
}

UI::Screen::iterator UI::Screen::begin()
{
    return fields_.begin();
}

UI::Screen::iterator UI::Screen::end()
{
    return fields_.end();
}

UI::Screen::const_iterator UI::Screen::begin() const
{
    return fields_.begin();
}

UI::Screen::const_iterator UI::Screen::end() const
{
    return fields_.end();
}

UI::Screen::iterator UI::Screen::focus()
{
    return focus_;
}

UI::Screen::const_iterator UI::Screen::focus() const
{
    return focus_;
}

UI::Screen::iterator UI::Screen::cursor()
{
    return cursor_;
}

UI::Screen::const_iterator UI::Screen::cursor() const
{
    return cursor_;
}

UI::Screen::iterator UI::Screen::focus(UI::Screen::iterator i)
{
    if ( focus_ == i ) {
        return focus_;
    }
    iterator before( focus_ );
    notifyNoRecurse(focus_, LooseFocusEvent());
    if (focus_ != before) {
        return focus_;
    }
    focus_ = i;
    if ( focus_ != end() ) {
        (*focus_)->notifyEvent(GainFocusEvent());
        cursor_ = focus_;
    }
    return focus_;
}

UI::Screen::iterator UI::Screen::firstEditable()
{
    iterator i( begin() );
    for (; i != end() && ! isEditable(*(*i)); ++i) { }
    return i;
}

void UI::Screen::title(const std::string& t)
{
    title_ = t;
}

const std::string& UI::Screen::title() const
{
    return title_;
}

void UI::Screen::clearFields()
{
    std::for_each(begin(), end(), clearField);
}

void UI::Screen::drawForm() const
{
    frameWork_.draw();
}

void UI::Screen::draw() const
{
    if (hidden()) {
        return;
    }
    UI::terminal().endEnhanced();
    topLine_->draw();
    drawForm();
    drawTitle();
    drawFields();

    if (focus() != end()){
        (*focus())->notifyEvent(GainFocusEvent());
    }
}

void UI::Screen::validate()
{
    validateFields();
    cursor(firstEditable());
    for (Validators::iterator i( validators_.begin() ); i != validators_.end(); ++i ) {
        (*i)->validate(*this);
    }

}

void UI::Screen::validateNoWarnings()
{
    cursor(firstEditable());
    WarningException we;
    for (Validators::iterator i(warningValidators_.begin());
          i != warningValidators_.end(); ++i) {
        try {
            (*i)->validate(*this);
        } catch (const std::exception& e) {
            we.addMessage(e.what());
        }
    }
    if (!we.messages().empty()) {
        throw we;
    }
}

void UI::Screen::addValidator(const BaseScreenValidator& v)
{
    validators_.push_back(ValidatorPtr(v.clone()));
}

void UI::Screen::addWarningValidator(const BaseScreenValidator& v)
{
    warningValidators_.push_back(ValidatorPtr(v.clone()));
}

std::string UI::Screen::name() const
{
    return COMPONENT_NAME;
}

void UI::Screen::drawFields() const
{
    std::for_each(begin(), end(), drawField);
}

void UI::Screen::load(const std::string& n) {
    if (fileExists(userInterfaceFormDataFilename(n))) {
        loadScreenFields(*this, fields_, userInterfaceFormDataFilename(n));
    }
    frameWork_.load(n);
}

void UI::Screen::validateFields()
{
    for ( iterator i( begin() ); i != end(); ++i ) {
        try {
            (*i)->validate();
        } catch (const ApplicationException& e) {
            cursor(i);
            throw ValidationException(i);
        }
    }
}

UI::Screen::iterator UI::Screen::cursor(UI::Screen::iterator i)
{
    return cursor_ = i;
}

void UI::Screen::drawTitle() const
{
    if (!title_.empty()) {
        UI::terminal().endEnhanced();
        UI::terminal().gotoxy( 1, 2 );
        UI::terminal().eraseEol();
        UI::terminal().write(title_);
    }
}

void UI::Screen::notifyNoRecurse(iterator f, const BaseEvent& e)
{
    if (f == end()) {
        return;
    }
    typedef std::map<std::string,unsigned int> RecursionDepthTable;
    static RecursionDepthTable recursionDepth;
    RecursionDepthTable::iterator i(recursionDepth.find(e.name()));
    if (i == recursionDepth.end()) {
        recursionDepth[e.name()] = 0;
        i = recursionDepth.find(e.name());
    }
    ++(i->second);
    if (i->second <= 1) {
        (*f)->notifyEvent(e);
    }
    i->second = 0;
}