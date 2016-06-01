//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_INTEGERSCREENFIELDVALIDATOR_H
#define FRONTEND_INTEGERSCREENFIELDVALIDATOR_H

#include "basescreenfieldvalidator.h"

namespace UI
{
    class IntegerScreenFieldValidator : public BaseScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField& f) const
        { }
        virtual IntegerScreenFieldValidator* clone() const
        {
            return new IntegerScreenFieldValidator(*this);
        }

    };

}

#endif //FRONTEND_INTEGERSCREENFIELDVALIDATOR_H
