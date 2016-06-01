//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_INTEGERSCREENFIELD_H
#define FRONTEND_INTEGERSCREENFIELD_H

#include "screenfield.h"
#include "numericscreenfieldformatter.h"
#include "integerscreenfieldvalidator.h"

namespace UI
{
    class IntegerScreenField : public ScreenField
    {
        virtual IntegerScreenField* clone() const { return 0; }

    public:
        IntegerScreenField()
        {
            formatter(NumericScreenFieldFormatter());
            addValidators();
        }
        virtual std::string name() const
        {
            return std::string("IntegerScreenField");
        }

    protected:
        virtual void addValidators()
        {
            addValidator(IntegerScreenFieldValidator());
        }
    };
}

#endif //FRONTEND_INTEGERSCREENFIELD_H
