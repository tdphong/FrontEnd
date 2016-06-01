//
// Created by phtran on 15/05/2016.
//

#ifndef FRONTEND_MANDATORYSCREENFIELDVALIDATOR_H
#define FRONTEND_MANDATORYSCREENFIELDVALIDATOR_H

#include "basescreenfieldvalidator.h"
#include "screenfield.h"
#include "sysexception.h"

namespace UI
{
    class MandatoryScreenFieldValidator : public BaseScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField& f) const
        {
            if (f.isBlank()) {
                throw ValidationException();
            }
        }
        virtual MandatoryScreenFieldValidator* clone() const
        {
            return new MandatoryScreenFieldValidator(*this);
        }
    };
}


#endif //FRONTEND_MANDATORYSCREENFIELDVALIDATOR_H
