//
// Created by phtran on 15/05/2016.
//

#ifndef FRONTEND_REALSCREENFIELDVALIDATOR_H
#define FRONTEND_REALSCREENFIELDVALIDATOR_H

#include "basescreenfieldvalidator.h"

namespace UI
{
    class RealScreenFieldValidator : public BaseScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField& f) const
        { }
        virtual RealScreenFieldValidator* clone() const
        {
            return new RealScreenFieldValidator(*this);
        }
    };
}

#endif //FRONTEND_REALSCREENFIELDVALIDATOR_H
