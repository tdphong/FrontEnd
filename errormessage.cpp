//
// Created by phtran on 13/05/2016.
//

#include "errormessage.h"

static const std::string MESSAGE_PREFIX("Error:  ");
static const std::string COMPONENT_NAME("ErrorMessage");

UI::ErrorMessage* UI::errorMessage(const std::string& m)
{
    return new UI::ErrorMessage(m);
}

UI::ErrorMessage::ErrorMessage(const std::string& m)
    : AcknowledgeMessageDialogue(MESSAGE_PREFIX + m)
{ }

UI::ErrorMessage* UI::ErrorMessage::clone() const
{
    return new ErrorMessage(*this);
}
std::string UI::ErrorMessage::name() const
{
    return COMPONENT_NAME;
}
