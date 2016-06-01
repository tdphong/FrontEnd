//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_EDITABANDONSAVEOPTIONSLIST_H
#define FRONTEND_EDITABANDONSAVEOPTIONSLIST_H

#include "basecomponent.h"
#include "editabandonoptionslist.h"

namespace UI
{
    class EditAbandonSaveOptionsList : public EditAbandonOptionsList
    {
    public:
        EditAbandonSaveOptionsList(BaseComponent&);
        virtual EditAbandonSaveOptionsList* clone() const;
    };

}


#endif //FRONTEND_EDITABANDONSAVEOPTIONSLIST_H
