//
// Created by phtran on 14/05/2016.
//

#include "editabandonsaveoptionslist.h"
#include "event.h"

static const std::string SAVE_OPTION( "S)ave" );

UI::EditAbandonSaveOptionsList::EditAbandonSaveOptionsList(BaseComponent& c)
        : EditAbandonOptionsList(std::string(), c)
{
    addOption( SAVE_OPTION, SKeyEvent( ), EventHandler(*this, SaveRequestEvent(), c));
}

UI::EditAbandonSaveOptionsList* UI::EditAbandonSaveOptionsList::clone() const
{
    return new EditAbandonSaveOptionsList(*this);
}