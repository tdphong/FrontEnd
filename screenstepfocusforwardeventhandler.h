//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENSTEPFOCUSFORWARDEVENTHANDLER_H
#define FRONTEND_SCREENSTEPFOCUSFORWARDEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"

namespace UI
{
    class ScreenStepFocusForwardEventHandler : public BaseEventHandler
    {
        UI::Screen& screen_;

    public:
        ScreenStepFocusForwardEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            screen_.stepForward();
        }
        virtual ScreenStepFocusForwardEventHandler* clone() const
        {
            return new ScreenStepFocusForwardEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENSTEPFOCUSFORWARDEVENTHANDLER_H
