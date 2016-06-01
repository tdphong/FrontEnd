//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_BASESCREENVALIDATOR_H
#define FRONTEND_BASESCREENVALIDATOR_H

namespace UI
{
    class Screen;
    class BaseScreenValidator
    {
    public:
        virtual void validate( const Screen& ) const = 0;
        virtual BaseScreenValidator* clone() const = 0;
    };
}

#endif //FRONTEND_BASESCREENVALIDATOR_H
