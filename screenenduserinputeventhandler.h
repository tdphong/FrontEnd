//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENENDUSERINPUTEVENTHANDLER_H
#define FRONTEND_SCREENENDUSERINPUTEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"
#include "screenfield.h"
#include "event.h"
#include "optionslist.h"
#include "editabandonsaveoptionslist.h"
#include "screenvalidationexception.h"
#include "container.h"

namespace UI
{
    class ScreenEndUserInputEventHandler : public BaseEventHandler
    {
        UI::Screen& screen_;

    public:
        ScreenEndUserInputEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            if (screen_.focus() != screen_.end()) {
                (*screen_.focus())->notifyEvent(LooseFocusEvent());
            }

            using OLPtr = std::shared_ptr<UI::OptionsList> ;
            OLPtr h(OLPtr(new UI::EditAbandonSaveOptionsList(screen_)));

            try {
                screen_.validate();

            } catch(const ::ValidationException& e) {
                static const std::string prefix( "Error:  " );
                h = OLPtr(new UI::EditAbandonOptionsList(prefix + e.what(), screen_));
            } catch (const Screen::ValidationException& e) {
                static const std::string prefix( "Error:  " );
                h = OLPtr(new UI::EditAbandonOptionsList(prefix + e.what(), screen_));
            }
            screen_.parent().addComponent(*h);
            screen_.parent().focus(*h);
            h->notifyEvent(DrawAllEvent());
        }
        virtual ScreenEndUserInputEventHandler* clone() const
        {
            return new ScreenEndUserInputEventHandler(*this);
        }
    };

}

#endif //FRONTEND_SCREENENDUSERINPUTEVENTHANDLER_H
