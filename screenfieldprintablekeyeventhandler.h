//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENFIELDPRINTABLEKEYEVENTHANDLER_H
#define FRONTEND_SCREENFIELDPRINTABLEKEYEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

#include <iostream>
namespace UI
{
    class ScreenFieldPrintableKeyEventHandler : public BaseEventHandler
    {
        ScreenField& field_;
        char keyStroke_;

    public:
        ScreenFieldPrintableKeyEventHandler(ScreenField& f, const char c)
                : field_(f)
                , keyStroke_(c)
        { }
        virtual void invoke()
        {
            field_.receiveKey(keyStroke_);
        }
        virtual ScreenFieldPrintableKeyEventHandler* clone() const
        {
            return new ScreenFieldPrintableKeyEventHandler(*this);
        }


    };
}

#endif //FRONTEND_SCREENFIELDPRINTABLEKEYEVENTHANDLER_H
