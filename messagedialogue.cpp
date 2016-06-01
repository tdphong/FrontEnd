//
// Created by phtran on 13/05/2016.
//

#include "messagedialogue.h"
#include "event.h"
#include "draweventhandler.h"

UI::MessageDialogue::MessageDialogue()
{
    addEventHandler(DrawAllEvent(), DrawEventHandler<MessageDialogue>(*this));
}
UI::MessageDialogue::MessageDialogue(const std::string& m)
        : message_(m)
{
    addEventHandler(DrawAllEvent(), DrawEventHandler<MessageDialogue>(*this));
}
const std::string& UI::MessageDialogue::message(const std::string& m)
{
    return message_ = m;
}
const std::string& UI::MessageDialogue::message() const
{
    return message_;
}