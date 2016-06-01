//
// Created by phtran on 15/05/2016.
//

#include "mandatorydatescreenfieldformatter.h"
#include "screenfield.h"
#include "terminal.h"

void UI::MandatoryDateScreenFieldFormatter::drawForEdit(const ScreenField& f) const
{
    UI::terminal().endEnhanced();
    if (!f.readonly()) {
        drawFrame(f);
    }
    UI::terminal().startUnderline();
    drawContentForEdit( f );
}

UI::MandatoryDateScreenFieldFormatter* UI::MandatoryDateScreenFieldFormatter::clone() const
{
    return new MandatoryDateScreenFieldFormatter(*this);
}