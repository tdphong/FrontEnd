//
// Created by phtran on 08/05/2016.
//

#ifndef FRONTEND_BASECOMPONENT_H
#define FRONTEND_BASECOMPONENT_H

#include <string>

class BaseEventHandler;
class BaseEvent;

namespace UI
{
    class Container;

    class BaseComponent
    {
    public:
        virtual ~BaseComponent() { }
        virtual unsigned int id() const = 0;
        virtual void addEventHandler(const ::BaseEvent&,
                                     const ::BaseEventHandler&,
                                     const bool = false) = 0;
        virtual void notifyEvent(const ::BaseEvent&) = 0;
        virtual void delegate(const ::BaseEvent&, BaseComponent&) = 0;
        virtual bool operator<(const BaseComponent&) const = 0;
        virtual bool operator==(const BaseComponent&) const = 0;
        virtual BaseComponent* clone() const = 0;
        virtual Container& parent() = 0;
        virtual Container& parent(Container&) = 0;
        virtual std::string name() const = 0;
    };
}
#endif //FRONTEND_BASECOMPONENT_H
