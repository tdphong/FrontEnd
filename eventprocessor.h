//
// Created by phtran on 08/05/2016.
//

#ifndef FRONTEND_EVENTPROCESSOR_H
#define FRONTEND_EVENTPROCESSOR_H

#include <map>
#include <list>
#include <string>
#include <memory>


class BaseEvent;
class BaseEventHandler;

namespace UI
{
    class PrintableKeyEvent;

    class EventProcessor
    {
        typedef std::shared_ptr<BaseEventHandler> EventHandlerPtr;
        typedef std::list<EventHandlerPtr> EventHandlerList;
        typedef std::map<std::string, EventHandlerList> EventHandlerTable;

        EventHandlerTable eventHandlers_;
        EventHandlerTable::iterator findHandlers(const ::BaseEvent&);

        void addUppercaseEventHandler(const PrintableKeyEvent&, const ::BaseEventHandler&);
        void addLowercaseEventHandler(const PrintableKeyEvent&, const ::BaseEventHandler&);
        void addHandler(const ::BaseEvent&, const ::BaseEventHandler&);

        class PushBackClone;

    public:
        void addEventHandler(const ::BaseEvent&, const ::BaseEventHandler&, const bool);
        virtual void processEvent(const ::BaseEvent&);
        bool empty() const;
        void clear();
        void clear(const ::BaseEvent&);
    };
}
#endif //FRONTEND_EVENTPROCESSOR_H
