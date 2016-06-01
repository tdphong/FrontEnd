//
// Created by phtran on 15/05/2016.
//

#ifndef FRONTEND_MANDATORYDATESCREENFIELDFORMATTER_H
#define FRONTEND_MANDATORYDATESCREENFIELDFORMATTER_H

#include "datescreenfieldformatter.h"

namespace UI
{
    class MandatoryDateScreenFieldFormatter : public DateScreenFieldFormatter
    {
    public:
        virtual void drawForEdit(const ScreenField&) const;
        virtual MandatoryDateScreenFieldFormatter* clone() const;
    };
}

#endif //FRONTEND_MANDATORYDATESCREENFIELDFORMATTER_H
