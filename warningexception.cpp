//
// Created by phtran on 14/05/2016.
//

#include "warningexception.h"

std::string UI::Screen::WarningException::addMessage(const std::string& s)
{
    messages_.push_back(s);
    return s;
}

const std::vector<std::string>& UI::Screen::WarningException::messages() const
{
    return messages_;
}
