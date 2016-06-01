//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_EDITABANDONOPTIONSLIST_H
#define FRONTEND_EDITABANDONOPTIONSLIST_H

#include "optionslist.h"
#include "baseeventhandler.h"

namespace UI
{
    class EditAbandonOptionsList : public OptionsList
    {
    protected:
        class EventHandler : public BaseEventHandler
        {
            BaseComponent& optionsList_;
            BaseComponent& eventRecipient_;
            std::shared_ptr<BaseEvent> event_;

        public:
            EventHandler(BaseComponent&, const BaseEvent&, BaseComponent&);
            virtual void invoke();
            virtual EventHandler* clone( ) const;
        };

    public:
        EditAbandonOptionsList();
        EditAbandonOptionsList(const std::string&, BaseComponent&);
        virtual EditAbandonOptionsList* clone() const;
    };
}

#endif //FRONTEND_EDITABANDONOPTIONSLIST_H
