//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_LEADINGZEROSNUMERICSCREENFIELDFORMATTER_H
#define FRONTEND_LEADINGZEROSNUMERICSCREENFIELDFORMATTER_H

#include "numericscreenfieldformatter.h"

namespace UI
{
    class LeadingZerosNumericScreenFieldFormatter : public NumericScreenFieldFormatter
    {
    public:
        virtual LeadingZerosNumericScreenFieldFormatter* clone() const;

    protected:
        virtual char fillCharacter() const;
    };
}

#endif //FRONTEND_LEADINGZEROSNUMERICSCREENFIELDFORMATTER_H
