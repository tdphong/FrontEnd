//
// Created by phtran on 13/05/2016.
//

#ifndef FRONTEND_MESSAGEDIALOGUE_H
#define FRONTEND_MESSAGEDIALOGUE_H

#include "component.h"

namespace UI
{
    class MessageDialogue : public Component
    {
        std::string message_;

    public:
        MessageDialogue();
        MessageDialogue(const std::string&);
        const std::string& message() const;
        virtual const std::string& message(const std::string&);
        virtual void draw() = 0;
    };
}

#endif //FRONTEND_MESSAGEDIALOGUE_H
