//
// Created by phtran on 15/05/2016.
//

#include <sstream>
#include <iomanip>
#include <cstdlib>

#include "realscreenfield.h"
#include "numericscreenfieldformatter.h"
#include "realscreenfieldvalidator.h"

static const std::string NAME("RealScreenField");

UI::RealScreenField::RealScreenField()
{
    formatter(NumericScreenFieldFormatter());
    addValidators();
}

void UI::RealScreenField::loseFocus()
{
    setDouble(atof(get().c_str()));
    draw();
    ScreenField::loseFocus();
}

double UI::RealScreenField::setDouble(const double v)
{
    std::ostringstream s;
    s << std::fixed << std::setprecision(decimalPlaces()) << v;
    set(s.str());
    return v;
}

std::string UI::RealScreenField::name() const
{
    return NAME;
}

void UI::RealScreenField::addValidators()
{
    addValidator(RealScreenFieldValidator());
}