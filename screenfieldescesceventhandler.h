//
// Created by phtran on 27/05/2016.
//

#ifndef FRONTEND_SCREENFIELDESCESCEVENTHANDLER_H
#define FRONTEND_SCREENFIELDESCESCEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldEscEscEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldEscEscEventHandler(ScreenField& f) : field_(f)
        { }
        virtual void invoke()
        {
            field_.escapeEscapePressed();
        }
        virtual ScreenFieldEscEscEventHandler* clone() const
        {
            return new ScreenFieldEscEscEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENFIELDESCESCEVENTHANDLER_H
