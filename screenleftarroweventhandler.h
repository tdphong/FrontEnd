//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENLEFTARROWEVENTHANDLER_H
#define FRONTEND_SCREENLEFTARROWEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"
#include "screenfield.h"
#include "event.h"

namespace UI
{
    class ScreenLeftArrowEventHandler : public BaseEventHandler
    {
        UI::Screen& screen_;

    public:
        ScreenLeftArrowEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            if (screen_.focus() == screen_.end()) {
                return;
            }
            if (screen_.focus()->get()->cursorAtFirst()) {
                screen_.notifyEvent(UI::StepFocusBackwardEvent());
                return;
            }
            screen_.focus()->get()->notifyEvent(LeftArrowEvent());
        }
        virtual ScreenLeftArrowEventHandler* clone() const
        {
            return new ScreenLeftArrowEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENLEFTARROWEVENTHANDLER_H
