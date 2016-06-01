//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENFIELDGAINFOCUSEVENTHANDLER_H
#define FRONTEND_SCREENFIELDGAINFOCUSEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldGainFocusEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldGainFocusEventHandler(ScreenField& f)
                : field_( f )
        { }
        virtual void invoke()
        {
            field_.gainFocus();
        }
        virtual ScreenFieldGainFocusEventHandler* clone() const
        {
            return new ScreenFieldGainFocusEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENFIELDGAINFOCUSEVENTHANDLER_H
