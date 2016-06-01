//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_WARNINGEXCEPTION_H
#define FRONTEND_WARNINGEXCEPTION_H

#include "screen.h"

class UI::Screen::WarningException
{
    std::vector<std::string> messages_;

public:
    std::string addMessage(const std::string&);
    const std::vector<std::string>& messages() const;
};


#endif //FRONTEND_WARNINGEXCEPTION_H
