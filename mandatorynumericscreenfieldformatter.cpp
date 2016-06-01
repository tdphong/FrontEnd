//
// Created by phtran on 14/05/2016.
//

#include "mandatorynumericscreenfieldformatter.h"
#include "terminal.h"

void UI::MandatoryNumericScreenFieldFormatter::draw(const ScreenField& f) const
{
    drawContent(f);
}

void UI::MandatoryNumericScreenFieldFormatter::drawForEdit(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    UI::terminal().startUnderline();
    drawForEdit(f);
}

UI::MandatoryNumericScreenFieldFormatter*
UI::MandatoryNumericScreenFieldFormatter::clone() const
{
    return new MandatoryNumericScreenFieldFormatter(*this);
}