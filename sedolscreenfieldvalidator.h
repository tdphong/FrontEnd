//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SEDOLSCREENFIELDVALIDATOR_H
#define FRONTEND_SEDOLSCREENFIELDVALIDATOR_H

#include "stringscreenfieldvalidator.h"

namespace UI
{
    class SedolScreenFieldValidator : public StringScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField&) const;
        virtual SedolScreenFieldValidator* clone() const;
    };
}

#endif //FRONTEND_SEDOLSCREENFIELDVALIDATOR_H
