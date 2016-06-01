//
// Created by phtran on 14/05/2016.
//

#include "leadingzerosnumericscreenfieldformatter.h"

static const char FILL_CHARACTER('0');

UI::LeadingZerosNumericScreenFieldFormatter*
UI::LeadingZerosNumericScreenFieldFormatter::clone() const
{
    return new LeadingZerosNumericScreenFieldFormatter(*this);
}

char UI::LeadingZerosNumericScreenFieldFormatter::fillCharacter() const
{
    return FILL_CHARACTER;
}



