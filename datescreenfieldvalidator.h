//
// Created by phtran on 15/05/2016.
//

#ifndef FRONTEND_DATESCREENFIELDVALIDATOR_H
#define FRONTEND_DATESCREENFIELDVALIDATOR_H

#include <stdlib.h>

#include "basescreenfieldvalidator.h"
#include "screenfield.h"
#include "date.h"

namespace UI
{
    class DateScreenFieldValidator : public BaseScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField& f) const
        {
            Date(atoi(f.get().c_str()));
        }
        virtual DateScreenFieldValidator* clone() const
        {
            return new DateScreenFieldValidator(*this);
        }
    };
}

#endif //FRONTEND_DATESCREENFIELDVALIDATOR_H
