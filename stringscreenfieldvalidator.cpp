//
// Created by phtran on 14/05/2016.
//

#include <sstream>
#include <algorithm>

#include "stringscreenfieldvalidator.h"
#include "sysexception.h"
#include "screenfield.h"

static void validatePrintable(const char c)
{
    if (!isprint(c)) {
        throw ValidationException();
    }
}

void UI::StringScreenFieldValidator::validate(const ScreenField& f) const
{
    std::for_each(f.get().begin(), f.get().end(), validatePrintable);
}

UI::StringScreenFieldValidator* UI::StringScreenFieldValidator::clone() const
{
    return new StringScreenFieldValidator(*this);
}