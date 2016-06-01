//
// Created by phtran on 13/05/2016.
//

#include "topline.h"
#include "event.h"
#include "draweventhandler.h"
#include "terminal.h"

static unsigned int XCOORD( 1 );
static unsigned int YCOORD( 1 );

static const std::string DISABLED_TOPLINE( "*** PLEASE LOG OUT - USER "
                                                   "INTERFACE DISABLED ***" );

static const std::string COMPONENT_NAME( "TopLine" );

static std::string toplineContent()
{
    return std::string("Tran Duc Phong");
}

UI::TopLine::TopLine()
{
    addEventHandler(DrawAllEvent(), DrawEventHandler<TopLine>(*this));
}
void UI::TopLine::draw() const
{
    UI::terminal().gotoxy(XCOORD, YCOORD);
    UI::terminal().eraseEos();
    UI::terminal().endEnhanced();
    UI::terminal().startInverse();
    UI::terminal().write(toplineContent());
}
UI::TopLine* UI::TopLine::clone() const
{
    return new TopLine(*this);
}
std::string UI::TopLine::name() const
{
    return COMPONENT_NAME;
}