//
// Created by phtran on 14/05/2016.
//

#include "sedolscreenfieldvalidator.h"
#include "screenfield.h"

void UI::SedolScreenFieldValidator::validate(const ScreenField& f) const
{
    if (f.isBlank()) {
        return;
    }
    StringScreenFieldValidator::validate(f);
}

UI::SedolScreenFieldValidator* UI::SedolScreenFieldValidator::clone() const
{
    return new SedolScreenFieldValidator(*this);
}