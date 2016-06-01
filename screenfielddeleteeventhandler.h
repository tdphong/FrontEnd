//
// Created by phtran on 25/05/2016.
//

#ifndef FRONTEND_SCREENFIELDDELETEEVENTHANDLER_H
#define FRONTEND_SCREENFIELDDELETEEVENTHANDLER_H

#include "baseeventhandler.h"
#include "screenfield.h"

namespace UI
{
    class ScreenFieldDeleteEventHandler : public BaseEventHandler
    {
        ScreenField& field_;

    public:
        ScreenFieldDeleteEventHandler(ScreenField& f) : field_(f)
        { }
        virtual void invoke()
        {
            field_.deleteCharacter();
        }
        virtual ScreenFieldDeleteEventHandler* clone() const
        {
            return new ScreenFieldDeleteEventHandler(*this);
        }
    };
}

#endif //FRONTEND_SCREENFIELDDELETEEVENTHANDLER_H
