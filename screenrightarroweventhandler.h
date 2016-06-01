//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENRIGHTARROWEVENTHANDLER_H
#define FRONTEND_SCREENRIGHTARROWEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"
#include "screenfield.h"
#include "event.h"

namespace UI
{
    class ScreenRightArrowEventHandler : public BaseEventHandler
    {
        UI::Screen& screen_;

    public:
        ScreenRightArrowEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            if (screen_.focus() == screen_.end()) {
                return;
            }
            if (screen_.focus()->get()->cursorAtLast()) {
                screen_.notifyEvent(UI::StepFocusForwardEvent());
                return;
            }
            screen_.focus()->get()->notifyEvent(RightArrowEvent());
        }
        virtual ScreenRightArrowEventHandler* clone() const
        {
            return new ScreenRightArrowEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENRIGHTARROWEVENTHANDLER_H
