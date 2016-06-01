//
// Created by phtran on 15/05/2016.
//

#ifndef FRONTEND_DATESCREENFIELD_H
#define FRONTEND_DATESCREENFIELD_H

#include "screenfield.h"

namespace UI
{
    class DateScreenField : public ScreenField
    {
        virtual DateScreenField* clone() const { return 0; }

    public:
        DateScreenField();
        virtual void loseFocus();
        virtual std::string name() const
        {
            return std::string("DateScreenField");
        }
        virtual const std::string& defaultValue() const;
        virtual const std::string& defaultValue(const std::string&);

    protected:
        virtual void addValidators();
    };
}

#endif //FRONTEND_DATESCREENFIELD_H
