//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_STRINGSCREENFIELD_H
#define FRONTEND_STRINGSCREENFIELD_H

#include "screenfield.h"
#include "stringscreenfieldformatter.h"
#include "string"
#include "stringscreenfieldvalidator.h"

namespace UI
{
    class StringScreenField : public ScreenField
    {
    public:
        StringScreenField()
        {
            formatter(StringScreenFieldFormatter());
            addValidators();
        }
        virtual std::string name() const
        {
            return std::string("StringScreenField");
        }

    protected:
        virtual void addValidators()
        {
            addValidator( StringScreenFieldValidator() );
        }
    };
}

#endif //FRONTEND_STRINGSCREENFIELD_H
