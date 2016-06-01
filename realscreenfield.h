//
// Created by phtran on 15/05/2016.
//

#ifndef FRONTEND_REALSCREENFIELD_H
#define FRONTEND_REALSCREENFIELD_H

#include "screenfield.h"

namespace UI
{
    class RealScreenField : public ScreenField
    {
        virtual RealScreenField* clone() const { return  0; }

    public:
        RealScreenField();
        virtual double setDouble(const double);
        virtual void loseFocus();
        virtual std::string name() const;

    protected:
        virtual void addValidators();
    };
}

#endif //FRONTEND_REALSCREENFIELD_H
