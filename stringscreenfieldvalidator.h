//
// Created by phtran on 14/05/2016.
//


#ifndef FRONTEND_STRINGSCREENFIELDVALIDATOR_H
#define FRONTEND_STRINGSCREENFIELDVALIDATOR_H

#include "basescreenfieldvalidator.h"

namespace UI
{
    class StringScreenFieldValidator : public BaseScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField&) const;
        virtual StringScreenFieldValidator* clone() const;
    };
}

#endif //FRONTEND_STRINGSCREENFIELDVALIDATOR_H
