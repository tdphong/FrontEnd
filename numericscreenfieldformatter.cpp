//
// Created by phtran on 14/05/2016.
//

#include <sstream>
#include <iomanip>

#include "numericscreenfieldformatter.h"
#include "terminal.h"
#include "screenfield.h"

static const char FILL_CHARACTER( ' ' );

void UI::NumericScreenFieldFormatter::draw(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (!f.readonly()) {
        drawFrame(f);
    }
    drawContent(f);
}

void UI::NumericScreenFieldFormatter::drawForEdit(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (!f.readonly()) {
        drawFrame(f);
    }
    drawContentForEdit(f);
}

UI::NumericScreenFieldFormatter* UI::NumericScreenFieldFormatter::clone() const
{
    return new NumericScreenFieldFormatter(*this);
}

void UI::NumericScreenFieldFormatter::drawContent(const ScreenField& f) const
{
    std::ostringstream s;
    s << std::right << std::setw(f.length()) << std::setfill(fillCharacter()) << f.get();
    UI::terminal().gotoxy(f.xCoordinate(), f.yCoordinate());
    UI::terminal().startBold();
    UI::terminal().write(s.str());
}

void UI::NumericScreenFieldFormatter::drawContentForEdit(const ScreenField& f) const
{
    std::ostringstream s;
    s << std::left << std::setw(f.length()) << std::setfill(' ') << f.get();
    UI::terminal().gotoxy(f.xCoordinate(), f.yCoordinate());
    UI::terminal().startBold();
    UI::terminal().write(s.str());
}

char UI::NumericScreenFieldFormatter::fillCharacter() const
{
    return FILL_CHARACTER;
}

