//
// Created by phtran on 14/05/2016.
//

#include "mandatorystringscreenfieldformatter.h"
#include "terminal.h"

void UI::MandatoryStringScreenFieldFormatter::drawForEdit(const ScreenField& f) const
{
    drawFrame(f);
    UI::terminal().startUnderline();
    drawContentForEdit(f);
}

UI::MandatoryStringScreenFieldFormatter*
UI::MandatoryStringScreenFieldFormatter::clone() const
{
    return new MandatoryStringScreenFieldFormatter(*this);
}



