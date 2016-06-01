//
// Created by phtran on 07/05/2016.
//

#ifndef FRONTEND_COMPONENT_H
#define FRONTEND_COMPONENT_H

#include <map>
#include <memory>

#include "basecomponent.h"
#include "eventprocessor.h"
#include "countedpointer.h"

namespace UI
{
    class Container;

    class Component : public BaseComponent
    {
        unsigned int id_;
        EventProcessor eventProcessor_;
        bool hidden_;
        Container* parent_;
        std::map<std::string, std::shared_ptr<BaseComponent> > delegates_;
    protected:
        void assignEventHandlers();
    public:
        Component();
        virtual unsigned int id() const;
        virtual bool operator<(const BaseComponent&)  const;
        virtual bool operator==(const BaseComponent&) const;
        virtual bool operator!=(const BaseComponent&) const;
        virtual void addEventHandler(const ::BaseEvent&,
                                     const ::BaseEventHandler&,
                                     const bool = false);
        void clearEventHandlers();
        void clearEventHandler(const ::BaseEvent&);
        virtual void notifyEvent(const ::BaseEvent&);
        virtual void delegate(const ::BaseEvent&, BaseComponent&);
        virtual void hide();
        virtual void unhide();
        bool hidden() const;
        virtual Container& parent();
        virtual Container& parent(Container&);
    };
}
#endif //FRONTEND_COMPONENT_H
