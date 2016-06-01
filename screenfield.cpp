//
// Created by phtran on 14/05/2016.
//

#include <list>
#include <algorithm>

#include "stringlib.h"
#include "terminal.h"
#include "event.h"
#include "screenfield.h"
#include "screenfieldprintablekeyeventhandler.h"
#include "screenfieldgainfocuseventhandler.h"
#include "screenfieldlosefocuseventhandler.h"
#include "screenfieldleftarroweventhandler.h"
#include "screenfieldrightarroweventhandler.h"
#include "screenfieldbackspaceeventhandler.h"
#include "screenfielddeleteeventhandler.h"
#include "screenfieldescesceventhandler.h"
#include "basescreenfieldvalidator.h"

static const unsigned int MESSAGE_Y_DELTA( 1 );

static std::string contentAfterEdit( const std::string &c )
{

    return strip(c);
}

class AddPrintableKeyEventHandler
{
    UI::ScreenField& field_;

public:
    AddPrintableKeyEventHandler(UI::ScreenField& f) : field_(f)
    { }
    void operator() (const char c)
    {
        field_.addEventHandler(UI::PrintableKeyEvent(c), UI::ScreenFieldPrintableKeyEventHandler(field_, c), true);
    }
};

static void addEventHandlers(UI::ScreenField& f)
{
    f.addEventHandler(UI::GainFocusEvent(), UI::ScreenFieldGainFocusEventHandler(f));
    f.addEventHandler(UI::EscEscEvent(), UI::ScreenFieldEscEscEventHandler(f));
    f.addEventHandler(UI::LooseFocusEvent(), UI::ScreenFieldLoseFocusEventHandler(f));
    f.addEventHandler(UI::LooseFocusForwardEvent(), UI::ScreenFieldLoseFocusEventHandler(f));
    f.addEventHandler(UI::LooseFocusBackwardEvent(), UI::ScreenFieldLoseFocusEventHandler(f));
    f.addEventHandler(UI::LeftArrowEvent(), UI::ScreenFieldLeftArrowEventHandler(f));
    f.addEventHandler(UI::RightArrowEvent(), UI::ScreenFieldRightArrowEventHandler(f));
    f.addEventHandler(UI::DeleteEvent(), UI::ScreenFieldDeleteEventHandler(f));
    f.addEventHandler(UI::BackSpaceEvent(), UI::ScreenFieldBackSpaceEventHandler(f));
    std::list<char> l(UI::terminal().allPrintableCharacters());
    std::for_each(l.begin(), l.end(), AddPrintableKeyEventHandler(f));
}

class Validate
{
    const UI::ScreenField& field_;

public:
    Validate(const UI::ScreenField& f) : field_(f)
    { }
    void operator() (const std::shared_ptr<UI::BaseScreenFieldValidator>& v)
    {
        v->validate(field_);
    }
};

UI::ScreenField::ScreenField()
    : xCoordinate_(0)
    , yCoordinate_(0)
    , length_(0)
    , decimalPlaces_(0)
    , isMandatory_( false )
    , isReadonly_( false )
    , hasOwnedInputFocus_( false )
{
    addEventHandlers(*this);
}

const std::string& UI::ScreenField::defaultValue() const
{
    return defaultValue_;
}

const std::string& UI::ScreenField::defaultValue(const std::string& v)
{
    return defaultValue_ = v;
}

std::string UI::ScreenField::setToDefaultValue()
{
    return set(defaultValue());
}

bool UI::ScreenField::isBlank() const
{
    return isBlank(get());
}

unsigned int UI::ScreenField::length() const
{
    return length_;
}

unsigned int UI::ScreenField::length(const unsigned int n)
{
    length_ = n;
    content_ = forceLength( content_, n );
    return length_;
}

void UI::ScreenField::gainFocus()
{
    if ( ! hasOwnedInputFocus_ ) {
        hasOwnedInputFocus_ = true;
        if (isBlank()) {
            setToDefaultValue();
        }
    }
    contentBeforeEdit_ = content_;
    content_ = forceLength( content_, length() );
    drawHintMessage();
    formatter().drawForEdit( *this );
    UI::terminal().gotoxy(xCoordinate(), yCoordinate());
}

void UI::ScreenField::loseFocus()
{
    content_ = contentAfterEdit(content_);
    formatter().draw( *this );
}

bool UI::ScreenField::contentHasChanged() const
{
    return strip( contentBeforeEdit() ) != contentAfterEdit( content_ );
}

bool UI::ScreenField::readonly() const
{
    return isReadonly_;
}

bool UI::ScreenField::readonly(const bool f)
{
    return isReadonly_ = f;
}

void UI::ScreenField::deleteCharacter()
{
    //@TODO: Revise the logic
    //cursorIndex() == length() - 1 ? content_.erase(cursorIndex(), 1) : content_.erase(cursorIndex() - 1, 1);
    if (cursorIndex() <= 0) {
        UI::terminal().saveCursorPosition();
        formatter().drawForEdit( *this );
        UI::terminal().restoreCursorPosition();
        return;
    }
        content_.erase(cursorIndex() - 1, 1);
        UI::terminal().gotoxy( UI::terminal().xCoordinate() - 1,
                               UI::terminal().yCoordinate() );
    content_ = content_ + " ";

    UI::terminal().saveCursorPosition();
    formatter().drawForEdit( *this );
    UI::terminal().restoreCursorPosition();
}

void UI::ScreenField::backspaceCharacter()
{
    if ( cursorIndex() == 0 ) {
        return;
    }
    moveCursorLeft();
    deleteCharacter();
}

char UI::ScreenField::receiveKey(const char c)
{
    if (hidden()) {
        return c;
    }
    //UI::terminal().write(c);
    //@TODO: Revise this logic
    /*
    UI::terminal().gotoxy(UI::terminal().xCoordinate() + 1, UI::terminal().yCoordinate());
    content_[cursorIndex() - 1] = c;
    if (cursorIndex() == length()) {
        moveCursorLeft();
    }
     */

    UI::terminal().write( c );
    content_[ cursorIndex() - 1 ] = c;
    if ( cursorIndex() == length() ) {
        moveCursorLeft();
    }
    return c;
}

const UI::BaseScreenFieldFormatter& UI::ScreenField::formatter() const
{
    if (!formatter_.get()) {
        throw InternalException();
    }
    return *formatter_;
}

const UI::BaseScreenFieldFormatter& UI::ScreenField::formatter(const BaseScreenFieldFormatter& f)
{
    formatter_ = FormatterPtr(f.clone());
    return formatter();
}

void UI::ScreenField::validate() const
{
    std::for_each(validators().begin(), validators().end(), Validate(*this));
}

void UI::ScreenField::draw() const
{
    if ( hidden() ) {
        return;
    }
    formatter().draw(*this);
}

void UI::ScreenField::addValidator(const BaseScreenFieldValidator& v)
{
    validators_.push_back(ValidatorPtr(v.clone()));

}

void UI::ScreenField::removeValidators()
{
    validators_.clear();
}

const UI::ScreenField::Validators& UI::ScreenField::validators() const
{
    return validators_;
}

const std::string& UI::ScreenField::set(const std::string& v)
{
    return content_ = strip(v).substr(0, length());
}

int UI::ScreenField::setInt(const int v)
{
    std::ostringstream s;
    s << v;
    set( s.str() );
    return v;
}

unsigned int UI::ScreenField::setUInt(const unsigned int v)
{
    std::ostringstream s;
    s << v;
    set( s.str() );
    return v;
}

double UI::ScreenField::setDouble(const double v)
{
    std::ostringstream s;
    s << v;
    set( s.str() );
    return v;
}

const std::string& UI::ScreenField::get() const
{
    return content_;
}

void UI::ScreenField::clear()
{
    content_.clear();
}

void UI::ScreenField::moveCursorLeft() const
{
    if ( cursorAtFirst() ) {
        return;
    }
    UI::terminal().gotoxy( UI::terminal().xCoordinate() - 1,
                           UI::terminal().yCoordinate() );
}

bool UI::ScreenField::cursorAtFirst() const
{
    return cursorIndex() == 0;
}

bool UI::ScreenField::cursorAtLast() const
{
    return cursorIndex() == length() - 1;
}

unsigned int UI::ScreenField::cursorIndex() const
{
    return UI::terminal().xCoordinate() - xCoordinate();
}

void UI::ScreenField::escapeEscapePressed() const
{
    if ( contentHasChanged() ) {
        UI::terminal().root().notifyEvent(UI::StepFocusForwardEvent());
    } else {
        UI::terminal().root().notifyEvent(UI::EndUserInputEvent());
    }
}

void UI::ScreenField::moveCursorRight() const
{
    if (cursorAtLast()) {
        return;
    }
    UI::terminal().gotoxy(UI::terminal().xCoordinate() + 1,
                          UI::terminal().yCoordinate());
}

void UI::ScreenField::clearField(UI::ScreenField* f)
{
    if ( ! f ) {
        return;
    }
    f->clear();
}

void UI::ScreenField::drawField(UI::ScreenField* f)
{
    if (!f) {
        return;
    }
    f->draw();
}

bool UI::ScreenField::isBlank(const std::string& c) const
{
    return strip(c).empty();
}

std::string UI::ScreenField::contentBeforeEdit() const
{
    return contentBeforeEdit_;
}

void UI::ScreenField::drawHintMessage() const
{
    if (yCoordinate() >= UI::terminal().height() - MESSAGE_Y_DELTA) {
        return;
    }
    UI::terminal().gotoxy(1, UI::terminal().height() - MESSAGE_Y_DELTA);
    UI::terminal().endEnhanced();
    UI::terminal().eraseEos();
    UI::terminal().gotoxy( 1, UI::terminal().height() );
    UI::terminal().write( hint() );
}
