//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_BASESCREENFIELDFORMATTER_H
#define FRONTEND_BASESCREENFIELDFORMATTER_H

namespace UI
{
    class ScreenField;

    class BaseScreenFieldFormatter
    {
    public:
        virtual ~BaseScreenFieldFormatter() { }
        virtual void draw(const ScreenField&) const = 0;
        virtual void drawForEdit(const ScreenField&) const = 0;
        virtual BaseScreenFieldFormatter* clone() const = 0;

    protected:
        virtual void drawFrame(const ScreenField&) const = 0;
    };
}

#endif //FRONTEND_BASESCREENFIELDFORMATTER_H
