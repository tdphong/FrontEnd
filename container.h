//
// Created by phtran on 07/05/2016.
//

#include <vector>
#include <list>
#include <set>

#include "component.h"
#include "countedpointer.h"

#ifndef FRONTEND_CONTAINER_H
#define FRONTEND_CONTAINER_H

namespace UI
{
    class Container : public Component
    {
    public:
        using value_type = std::shared_ptr<BaseComponent>;

        typedef std::vector<value_type> Components;
        typedef Components::iterator iterator;
        typedef Components::const_iterator const_iterator;

        Container();

        virtual std::string name() const;
        virtual void notifyEvent(const ::BaseEvent&);
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        unsigned int addComponent(BaseComponent&);
        void removeComponent(const unsigned int);
        iterator find(const unsigned int);
        const_iterator find(const unsigned int) const;
        iterator focus();
        void focus(iterator);
        void focus(const BaseComponent&);
        virtual Container* clone() const;
        size_t size() const;
        bool empty() const;
        void clear();
        void draw(const unsigned int) const;

        typedef std::shared_ptr<BaseEvent> BaseEventPtr;
        typedef std::shared_ptr<BaseEventHandler> BaseEventHandlerPtr;
    private:
        std::list<std::pair<BaseEventPtr, BaseEventHandlerPtr> > broadcastEventHandlers();
        bool isBroadcastEvent(const BaseEvent&) const;
        std::set<std::string> broadcastEventNames_;
        Components components_;
        iterator focus_;
    };

}
#endif //FRONTEND_CONTAINER_H
