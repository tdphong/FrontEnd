//
// Created by phtran on 14/05/2016.
//

#include "editabandonoptionslist.h"
#include "container.h"
#include "event.h"

static const std::string EDIT_OPTION("E)dit");
static const std::string ABANDON_OPTION("A)bandon");

UI::EditAbandonOptionsList::EventHandler::EventHandler(BaseComponent& ol, const BaseEvent& e, BaseComponent& er)
    : optionsList_(ol)
    , eventRecipient_(er)
{ }

void UI::EditAbandonOptionsList::EventHandler::invoke()
{
    optionsList_.parent().removeComponent(optionsList_.id());
    eventRecipient_.notifyEvent(*event_);
}

UI::EditAbandonOptionsList::EventHandler*
UI::EditAbandonOptionsList::EventHandler::clone() const
{
    return new EventHandler(*this);
}

UI::EditAbandonOptionsList::EditAbandonOptionsList()
{ }

UI::EditAbandonOptionsList::EditAbandonOptionsList(const std::string& m, BaseComponent& c)
        : OptionsList(m)
{

    addOption( EDIT_OPTION, EKeyEvent(), EventHandler(*this, ContinueEditEvent(), c));
    addOption( ABANDON_OPTION, AKeyEvent(), EventHandler(*this, AbandonEvent(), c));

}

UI::EditAbandonOptionsList*
UI::EditAbandonOptionsList::clone() const
{
    return new EditAbandonOptionsList(*this);
}

