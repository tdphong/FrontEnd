//
// Created by phtran on 25/05/2016.
//

#ifndef FRONTEND_SCREENFIELDLEFTARROWEVENTHANDLER_H
#define FRONTEND_SCREENFIELDLEFTARROWEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldLeftArrowEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldLeftArrowEventHandler(ScreenField& f) : field_(f)
        { }
        virtual void invoke()
        {
            field_.moveCursorLeft();
        }
        virtual ScreenFieldLeftArrowEventHandler* clone() const
        {
            return new ScreenFieldLeftArrowEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENFIELDLEFTARROWEVENTHANDLER_H
