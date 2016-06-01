//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENFIELDFORMATTER_H
#define FRONTEND_SCREENFIELDFORMATTER_H

#include "basescreenfieldformatter.h"

namespace UI
{
    class ScreenFieldFormatter : public BaseScreenFieldFormatter
    {
    protected:
        virtual void drawFrame(const ScreenField&) const;
        virtual void clearFrame(const ScreenField&) const;
    };
}

#endif //FRONTEND_SCREENFIELDFORMATTER_H
