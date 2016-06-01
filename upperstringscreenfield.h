//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_UPPERSTRINGSCREENFIELD_H
#define FRONTEND_UPPERSTRINGSCREENFIELD_H

#include "stringscreenfield.h"

namespace UI
{
    class UpperStringScreenField : public StringScreenField
    {
    public:
        virtual char receiveKey(const char c)
        {
            return StringScreenField::receiveKey( ::toupper( c ) );
        }
    };
}

#endif //FRONTEND_UPPERSTRINGSCREENFIELD_H
