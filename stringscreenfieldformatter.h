//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_STRINGSCREENFIELDFORMATTER_H
#define FRONTEND_STRINGSCREENFIELDFORMATTER_H

#include "screenfieldformatter.h"

namespace UI
{
    class StringScreenFieldFormatter : public ScreenFieldFormatter
    {
    public:
        virtual void draw(const ScreenField&) const;
        virtual void drawForEdit(const ScreenField&) const;
        virtual StringScreenFieldFormatter* clone() const;

    protected:
        virtual void drawContent(const ScreenField&) const;
        virtual void drawContentForEdit(const ScreenField&) const;
    };
}

#endif //FRONTEND_STRINGSCREENFIELDFORMATTER_H
