//
// Created by phtran on 14/05/2016.
//


#include "sedolscreenfield.h"
#include "numericscreenfieldformatter.h"
#include "sedolscreenfieldvalidator.h"

UI::SedolScreenField::SedolScreenField()
{
    formatter(NumericScreenFieldFormatter());
    addValidators();
}

char UI::SedolScreenField::receiveKey(const char c)
{
    if ( hidden() ) {
        return c;
    }
    return UpperStringScreenField::receiveKey( c );
}

void UI::SedolScreenField::addValidators()
{
    addValidator(SedolScreenFieldValidator());
}