//
// Created by phtran on 21/05/2016.
//

#ifndef FRONTEND_SCREENTERMINALGEOMETRYCHANGEDEVENTHANDLER_H
#define FRONTEND_SCREENTERMINALGEOMETRYCHANGEDEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screen.h"

namespace UI
{
    class ScreenTerminalGeometryChangedEventHandler : public BaseEventHandler
    {
        Screen& screen_;

    public:
        ScreenTerminalGeometryChangedEventHandler(Screen& s) : screen_(s)
        { }
        virtual void invoke()
        {
            screen_.draw();
        }
        virtual ScreenTerminalGeometryChangedEventHandler* clone() const
        {
            return new ScreenTerminalGeometryChangedEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENTERMINALGEOMETRYCHANGEDEVENTHANDLER_H
