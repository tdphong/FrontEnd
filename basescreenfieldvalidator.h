//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_BASESCREENFIELDVALIDATOR_H
#define FRONTEND_BASESCREENFIELDVALIDATOR_H

namespace UI
{
    class ScreenField;
    class BaseScreenFieldValidator
    {
    public:
        virtual void validate(const ScreenField&) const = 0;
        virtual BaseScreenFieldValidator* clone() const = 0;
    };
};


#endif //FRONTEND_BASESCREENFIELDVALIDATOR_H
