//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENSTEPFOCUSBACKWARDEVENTHANDLER_H
#define FRONTEND_SCREENSTEPFOCUSBACKWARDEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"

namespace UI
{
    class ScreenStepFocusBackwardEventHandler : public BaseEventHandler
    {
        UI::Screen& screen_;

    public:
        ScreenStepFocusBackwardEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            screen_.stepBackward();
        }
        virtual ScreenStepFocusBackwardEventHandler* clone() const
        {
            return new ScreenStepFocusBackwardEventHandler(*this);
        }
    };

}

#endif //FRONTEND_SCREENSTEPFOCUSBACKWARDEVENTHANDLER_H
