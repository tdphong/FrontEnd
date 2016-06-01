//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENREDRAWEVENTHANDLER_H
#define FRONTEND_SCREENREDRAWEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"

namespace UI
{
    class ScreenRedrawEventHandler : public BaseEventHandler
    {
        Screen& screen_;

    public:
        ScreenRedrawEventHandler(UI::Screen &s)
                : screen_( s )
        { }
        virtual void invoke()
        {
            screen_.draw();
        }
        virtual BaseEventHandler* clone() const
        {
            return new ScreenRedrawEventHandler(screen_);
        }
    };
}

#endif //FRONTEND_SCREENREDRAWEVENTHANDLER_H
