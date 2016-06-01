//
// Created by phtran on 13/05/2016.
//

#include "acknowledgemessagedialogue.h"
#include "event.h"
#include "draweventhandler.h"
#include "terminal.h"

static const unsigned int XCOORD(1);
static const unsigned int YDELTA(1);
static const std::string PRESS_ANY_KEY("Press [ANY KEY] to continue.");

UI::AcknowledgeMessageDialogue::AcknowledgeMessageDialogue(const std::string& m)
{
    addEventHandler(DrawAllEvent(), DrawEventHandler<AcknowledgeMessageDialogue>(*this));
}
void UI::AcknowledgeMessageDialogue::drawMessage()
{
    UI::terminal().gotoxy(XCOORD, UI::terminal().height() - YDELTA);
    UI::terminal().eraseEos();
    UI::terminal().endEnhanced();
    UI::terminal().write(message());
}
void UI::AcknowledgeMessageDialogue::drawPressAnyKey()
{
    UI::terminal().gotoxy(XCOORD, UI::terminal().height() - YDELTA + 1);
    UI::terminal().write(PRESS_ANY_KEY);
}
void UI::AcknowledgeMessageDialogue::draw()
{
    drawMessage();
    drawPressAnyKey();
}
void UI::AcknowledgeMessageDialogue::notifyEvent(const BaseEvent& e)
{
    Component::notifyEvent(e);
    if (dynamic_cast<const KeyStrokeEvent*>(&e)) {
        parent().removeComponent(id());
        UI::terminal().drawAll();
    }
}