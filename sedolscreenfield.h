//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SEDOLSCREENFIELD_H
#define FRONTEND_SEDOLSCREENFIELD_H

#include "upperstringscreenfield.h"

namespace UI
{
    class SedolScreenField : public UpperStringScreenField
    {
    public:
        SedolScreenField();
        virtual char receiveKey(const char);

    protected:
        virtual void addValidators();
    };
}

#endif //FRONTEND_SEDOLSCREENFIELD_H
