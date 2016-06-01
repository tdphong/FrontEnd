//
// Created by phtran on 13/05/2016.
//

#include "baseeventhandler.h"

#ifndef FRONTEND_DRAWEVENTHANDLER_H
#define FRONTEND_DRAWEVENTHANDLER_H

namespace UI
{
    template <class T>
    class DrawEventHandler : public BaseEventHandler
    {
        T& component_;

    public:
        DrawEventHandler(T &c) : component_(c)
        { }
        void invoke()
        {
            component_.draw();
        }
        DrawEventHandler* clone() const
        {
            return new DrawEventHandler( *this );
        }
    };
}


#endif //FRONTEND_DRAWEVENTHANDLER_H
