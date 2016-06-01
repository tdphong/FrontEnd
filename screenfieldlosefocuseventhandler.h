//
// Created by phtran on 22/05/2016.
//

#ifndef FRONTEND_SCREENFIELDLOSEFOCUSEVENTHANDLER_H
#define FRONTEND_SCREENFIELDLOSEFOCUSEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldLoseFocusEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldLoseFocusEventHandler(ScreenField& f) : field_(f)
        { }
        virtual void invoke()
        {
            field_.loseFocus();
        }
        virtual ScreenFieldLoseFocusEventHandler* clone() const
        {
            return new ScreenFieldLoseFocusEventHandler(*this);
        }
    };

}

#endif //FRONTEND_SCREENFIELDLOSEFOCUSEVENTHANDLER_H
