//
// Created by phtran on 13/05/2016.
//

#ifndef FRONTEND_ERRORMESSAGE_H
#define FRONTEND_ERRORMESSAGE_H

#include "acknowledgemessagedialogue.h"

namespace UI
{
    class ErrorMessage : public AcknowledgeMessageDialogue
    {
    public:
        ErrorMessage(const std::string&);
        virtual ErrorMessage* clone() const;
        virtual std::string name() const;
    };

    ErrorMessage* errorMessage(const std::string&);
}

#endif //FRONTEND_ERRORMESSAGE_H
