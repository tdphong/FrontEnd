//
// Created by phtran on 27/05/2016.
//

#ifndef FRONTEND_SCREENFIELDBACKSPACEEVENTHANDLER_H
#define FRONTEND_SCREENFIELDBACKSPACEEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldBackSpaceEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldBackSpaceEventHandler(ScreenField& f) : field_(f)
        { }
        virtual void invoke()
        {
            field_.backspaceCharacter();
        }
        virtual ScreenFieldBackSpaceEventHandler* clone() const
        {
            return new ScreenFieldBackSpaceEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENFIELDBACKSPACEEVENTHANDLER_H
