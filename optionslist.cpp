//
// Created by phtran on 14/05/2016.
//

#include <algorithm>

#include "optionslist.h"
#include "terminal.h"
#include "event.h"
#include "baseeventhandler.h"

static const unsigned int START_ROW_DELTA(1);
static const std::string OPTION_GAP("  ");
static const std::string COMPONENT_NAME("OptionsList");


class DrawEventHandler : public BaseEventHandler
{
    UI::OptionsList& optionsList_;

public:
    DrawEventHandler(UI::OptionsList& l)
            : optionsList_(l)
    { }

    void invoke()
    {
        optionsList_.draw();
    }
    virtual DrawEventHandler* clone() const
    {
        return new DrawEventHandler( *this );
    }
};

class DrawOption
{
    unsigned int remainingLength_;

public:
    DrawOption(const std::list<std::string>& ov)
            : remainingLength_(0)
    {
        for ( std::list<std::string>::const_iterator i(ov.begin()); i != ov.end(); ++i ) {
            remainingLength_ += i->size() + OPTION_GAP.size();
        }
    }
    void operator() (const std::string&);
};

void DrawOption::operator()(const std::string& o)
{
    if (UI::terminal().xCoordinate() + o.size() > UI::terminal().width()) {
        if (UI::terminal().yCoordinate() >= UI::terminal().height()) {
            return;
        }
        UI::terminal().gotoxy(1, UI::terminal().height());
    }
    if ((remainingLength_ < UI::terminal().width())
        && (UI::terminal().yCoordinate() < UI::terminal().height())) {
        UI::terminal().gotoxy( 1, UI::terminal().height() );
    }
    bool bold(false);
    UI::terminal().endEnhanced();
    for (std::string::const_iterator c = o.begin(); c != o.end(); ++c) {
        if ((c + 1 != o.end()) && (*(c + 1) == ')')) {
            UI::terminal().startBold();
        }
        if (*c == ']') {
            UI::terminal().endEnhanced();
            bold = false;
        }
        UI::terminal().write( *c );
        if (*c == '[') {
            UI::terminal().startBold();
            bold = true;
        }
        if (!bold) {
            UI::terminal().endEnhanced();
        }
    }
    remainingLength_ -= o.size() - OPTION_GAP.size();
    if (UI::terminal().xCoordinate() + OPTION_GAP.size() < UI::terminal().width() ) {
        UI::terminal().write( OPTION_GAP );
    }
}

UI::OptionsList::OptionsList()
{
    resetEventHandlers();
}

UI::OptionsList::OptionsList(const std::string& m) : message_(m)
{
    resetEventHandlers();
}

std::string UI::OptionsList::name() const
{
    return COMPONENT_NAME;
}

void UI::OptionsList::addOption(const std::string& m)
{
    options_.push_back(m);
}

void UI::OptionsList::addOption(const std::string & m, const BaseEvent& e, const BaseEventHandler& h)
{
    addOption(m);
    addEventHandler(e, h);
}

void UI::OptionsList::draw() const
{
    if (hidden()) {
        return;
    }
    UI::terminal().gotoxy(1, UI::terminal().height() - START_ROW_DELTA);
    UI::terminal().eraseEos();
    if (!message_.empty()) {
        UI::terminal().endEnhanced();
        UI::terminal().write(message_);
        UI::terminal().gotoxy(1, UI::terminal().height());
    }
    std::for_each( options_.begin(), options_.end(), DrawOption(options_));
    UI::terminal().parkCursor();
}

void UI::OptionsList::clear()
{
    options_.clear();
    message_.clear();
    resetEventHandlers();
}

UI::OptionsList* UI::OptionsList::clone() const
{
    return new OptionsList(*this);
}

void UI::OptionsList::resetEventHandlers()
{
    clearEventHandlers();
    Component::assignEventHandlers();
    addEventHandler(DrawAllEvent(), DrawEventHandler(*this));
    addEventHandler(TerminalGeometryChangedEvent(), DrawEventHandler(*this));
}

