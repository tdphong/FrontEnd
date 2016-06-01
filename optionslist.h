//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_OPTIONSLIST_H
#define FRONTEND_OPTIONSLIST_H

#include <list>

#include "component.h"

namespace UI
{
    class OptionsList : public Component
    {
        std::list<std::string> options_;
        std::string message_;
        void resetEventHandlers();

    public:
        OptionsList();
        OptionsList(const std::string&);
        void draw() const;
        void addOption(const std::string&, const BaseEvent&, const BaseEventHandler&);
        void addOption(const std::string&);
        void clear();
        virtual OptionsList* clone() const;
        virtual std::string name() const;
    };
}

#endif //FRONTEND_OPTIONSLIST_H
