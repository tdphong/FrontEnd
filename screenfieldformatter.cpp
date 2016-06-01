//
// Created by phtran on 14/05/2016.
//

#include <string>

#include "screenfieldformatter.h"
#include "terminal.h"
#include "screenfield.h"

static const std::string FRAME_LEFT( "[" );
static const std::string FRAME_RIGHT( "]" );

void UI::ScreenFieldFormatter::drawFrame(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    UI::terminal().gotoxy(f.xCoordinate() - 1, f.yCoordinate());
    UI::terminal().write(FRAME_LEFT);
    UI::terminal().gotoxy(f.xCoordinate() + f.length(), f.yCoordinate());
    UI::terminal().write(FRAME_RIGHT);
}

void UI::ScreenFieldFormatter::clearFrame(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    UI::terminal().gotoxy(f.xCoordinate() - 1, f.yCoordinate());
    UI::terminal().write( ' ' );
    UI::terminal().gotoxy(f.xCoordinate() + f.length(), f.yCoordinate());
    UI::terminal().write(' ');
}

