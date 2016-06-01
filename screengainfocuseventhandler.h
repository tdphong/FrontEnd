//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENGAINFOCUSEVENTHANDLER_H
#define FRONTEND_SCREENGAINFOCUSEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"
#include "screenfield.h"
#include "event.h"

namespace UI
{
    class ScreenGainFocusEventHandler : public BaseEventHandler
    {
        Screen& screen_;

    public:
        ScreenGainFocusEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            if (screen_.focus() != screen_.end()) {
                screen_.focus()->get()->notifyEvent(GainFocusEvent());
            }
        }
        ScreenGainFocusEventHandler* clone() const
        {
            return new ScreenGainFocusEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENGAINFOCUSEVENTHANDLER_H
