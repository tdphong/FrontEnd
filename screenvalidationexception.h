//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENVALIDATIONEXCEPTION_H
#define FRONTEND_SCREENVALIDATIONEXCEPTION_H

#include "screen.h"
#include "sysexception.h"

namespace UI
{
    class Screen::ValidationException : public ApplicationException
    {
        Screen::iterator field_;

    public:
        ValidationException(const Screen::iterator& f)
                : ApplicationException()
                , field_(f)
        { }
        const Screen::iterator& field() const
        {
            return field_;
        }
    };
}

#endif //FRONTEND_SCREENVALIDATIONEXCEPTION_H
