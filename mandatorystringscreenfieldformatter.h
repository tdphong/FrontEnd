//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_MANDATORYSTRINGSCREENFIELDFORMATTER_H
#define FRONTEND_MANDATORYSTRINGSCREENFIELDFORMATTER_H

#include "stringscreenfieldformatter.h"

namespace UI
{
    class MandatoryStringScreenFieldFormatter : public StringScreenFieldFormatter
    {
    public:
        virtual void drawForEdit(const ScreenField&) const;
        virtual MandatoryStringScreenFieldFormatter* clone() const;
    };

};

#endif //FRONTEND_MANDATORYSTRINGSCREENFIELDFORMATTER_H
