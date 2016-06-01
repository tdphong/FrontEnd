//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_MANDATORYNUMERICSCREENFIELDFORMATTER_H
#define FRONTEND_MANDATORYNUMERICSCREENFIELDFORMATTER_H

#include "numericscreenfieldformatter.h"

namespace UI
{
    class MandatoryNumericScreenFieldFormatter : public NumericScreenFieldFormatter
    {
    public:
        virtual void draw(const ScreenField&) const;
        virtual void drawForEdit(const ScreenField&) const;
        virtual MandatoryNumericScreenFieldFormatter* clone() const;
    };
}

#endif //FRONTEND_MANDATORYNUMERICSCREENFIELDFORMATTER_H
