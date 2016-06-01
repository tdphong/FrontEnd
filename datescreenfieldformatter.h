//
// Created by phtran on 15/05/2016.
//


#ifndef FRONTEND_DATESCREENFIELDFORMATTER_H
#define FRONTEND_DATESCREENFIELDFORMATTER_H

#include "screenfieldformatter.h"

namespace UI
{
    class DateScreenFieldFormatter : public ScreenFieldFormatter
    {
    public:
        virtual void draw(const ScreenField&) const;
        virtual void drawForEdit(const ScreenField&) const;
        virtual DateScreenFieldFormatter* clone() const;

    protected:
        void drawContent(const ScreenField&) const;
        void drawContentForEdit(const ScreenField&) const;
    };
}

#endif //FRONTEND_DATESCREENFIELDFORMATTER_H
