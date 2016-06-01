//
// Created by phtran on 13/05/2016.
//

#ifndef FRONTEND_ACKNOWLEDGEMESSAGEDIALOGUE_H
#define FRONTEND_ACKNOWLEDGEMESSAGEDIALOGUE_H

#include <string>

#include "messagedialogue.h"

namespace UI
{
    class AcknowledgeMessageDialogue : public MessageDialogue
    {
    public:
        AcknowledgeMessageDialogue(const std::string&);
        void drawMessage();
        void drawPressAnyKey();
        virtual void draw();
        virtual void notifyEvent(const BaseEvent&);
    };
}

#endif //FRONTEND_ACKNOWLEDGEMESSAGEDIALOGUE_H
