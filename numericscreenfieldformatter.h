//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_NUMERICSCREENFIELDFORMATTER_H
#define FRONTEND_NUMERICSCREENFIELDFORMATTER_H

#include "screenfieldformatter.h"

namespace UI
{
    class NumericScreenFieldFormatter : public ScreenFieldFormatter
    {
    public:
        virtual void draw(const ScreenField&) const;
        virtual void drawForEdit(const ScreenField&) const;
        virtual NumericScreenFieldFormatter* clone() const;

    protected:
        virtual char fillCharacter() const;
        void drawContent(const ScreenField&) const;
        void drawContentForEdit(const ScreenField&) const;
    };
}

#endif //FRONTEND_NUMERICSCREENFIELDFORMATTER_H
