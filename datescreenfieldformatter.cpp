//
// Created by phtran on 15/05/2016.
//

#include <sstream>
#include <iomanip>

#include "datescreenfieldformatter.h"
#include "screenfield.h"
#include "terminal.h"

void UI::DateScreenFieldFormatter::draw(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (!f.readonly()) {
        drawFrame(f);
    }
    drawContent(f);
}

void
UI::DateScreenFieldFormatter::drawForEdit(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (!f.readonly()) {
        drawFrame(f);
    }
    drawContentForEdit(f);
}

UI::DateScreenFieldFormatter*
UI::DateScreenFieldFormatter::clone() const
{
    return new DateScreenFieldFormatter(*this);
}

void UI::DateScreenFieldFormatter::drawContent(const ScreenField& f) const
{
    std::ostringstream s;
    s << std::right << std::setw(f.length()) << std::setfill(' ') << f.get();
    UI::terminal().gotoxy(f.xCoordinate(), f.yCoordinate());
    UI::terminal().startBold();
    UI::terminal().write(s.str());
}

void UI::DateScreenFieldFormatter::drawContentForEdit(const ScreenField& f) const
{
    std::ostringstream s;
    s << std::right << std::setw(f.length()) << std::setfill(' ') << f.get();
    UI::terminal().gotoxy(f.xCoordinate(), f.yCoordinate());
    UI::terminal().startBold();
    UI::terminal().write(s.str());
}