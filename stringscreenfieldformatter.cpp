//
// Created by phtran on 14/05/2016.
//

#include <sstream>
#include <iomanip>

#include "stringscreenfieldformatter.h"
#include "screenfield.h"
#include "terminal.h"

void UI::StringScreenFieldFormatter::draw(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (!f.readonly()) {
        drawFrame(f);
    }
    drawContent(f);
}

void UI::StringScreenFieldFormatter::drawForEdit(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (f.readonly()) {
        clearFrame(f);
    } else {
        drawFrame(f);
    }
    drawContentForEdit(f);
}

UI::StringScreenFieldFormatter* UI::StringScreenFieldFormatter::clone() const
{
    return new StringScreenFieldFormatter(*this);
}

void UI::StringScreenFieldFormatter::drawContent( const ScreenField &f ) const
{
    std::ostringstream s;
    s << std::left << std::setw(f.length()) << std::setfill(' ') << f.get();
    UI::terminal().gotoxy(f.xCoordinate(), f.yCoordinate());
    UI::terminal().startBold();
    UI::terminal().write(s.str());
}

void UI::StringScreenFieldFormatter::drawContentForEdit(const ScreenField& f) const
{
    std::ostringstream s;
    s << std::left << std::setw(f.length()) << std::setfill(' ') << f.get();
    UI::terminal().gotoxy(f.xCoordinate(), f.yCoordinate());
    UI::terminal().startBold();
    UI::terminal().write(s.str());
}


