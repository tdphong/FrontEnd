//
// Created by phtran on 27/05/2016.
//

#ifndef FRONTEND_SCREENFIELDRIGHTARROWEVENTHANDLER_H
#define FRONTEND_SCREENFIELDRIGHTARROWEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldRightArrowEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldRightArrowEventHandler(ScreenField& f) : field_(f)
        { }
        virtual void invoke()
        {
            field_.moveCursorRight();
        }
        virtual ScreenFieldRightArrowEventHandler* clone() const
        {
            return new ScreenFieldRightArrowEventHandler(*this);
        }

    };
}

#endif //FRONTEND_SCREENFIELDRIGHTARROWEVENTHANDLER_H
