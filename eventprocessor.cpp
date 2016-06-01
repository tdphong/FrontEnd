//
// Created by phtran on 08/05/2016.
//

#include <algorithm>

#include "eventprocessor.h"
#include "baseeventhandler.h"
#include "event.h"

class UI::EventProcessor::PushBackClone
{
    EventHandlerList& eventHandlers_;

public:
    PushBackClone(EventHandlerList& ev) : eventHandlers_(ev)
    { }
    void operator()(const EventHandlerPtr& h) const
    {
        if (h.get() == 0) {
            return;
        }
        eventHandlers_.push_back(EventHandlerPtr(h->clone()));
    }
};

static void invoke(std::shared_ptr<BaseEventHandler>& h)
{
    if (!h.get()) {
        return;
    }
    h->invoke();
}

UI::EventProcessor::EventHandlerTable::iterator
UI::EventProcessor::findHandlers(const ::BaseEvent& e)
{
    return eventHandlers_.find(e.name());
}

void UI::EventProcessor::addHandler(const ::BaseEvent& e, const ::BaseEventHandler& h)
{
    EventHandlerTable::iterator i(findHandlers(e));
    if (i != eventHandlers_.end()) {
        i->second.push_back(EventHandlerPtr(h.clone()));
        return;
    }
    EventHandlerList l;
    l.push_back(EventHandlerPtr(h.clone()));
    eventHandlers_[e.name()] = l;
}

void
UI::EventProcessor::addUppercaseEventHandler(const PrintableKeyEvent& e, const ::BaseEventHandler& h)
{
    addHandler(PrintableKeyEvent(static_cast<char>(::toupper(e.keyStroke()))), h);
}

void
UI::EventProcessor::addLowercaseEventHandler(const PrintableKeyEvent& e, const ::BaseEventHandler& h)
{
    addHandler(PrintableKeyEvent(static_cast<char>(::tolower(e.keyStroke()))), h);
}

void UI::EventProcessor::addEventHandler(const ::BaseEvent& e, const ::BaseEventHandler& h, const bool s)
{
    const PrintableKeyEvent* pke = dynamic_cast<const PrintableKeyEvent*>(&e);
    if (!pke) {
        addHandler(e, h);
        return;
    }
    if (isalpha(pke->keyStroke()) && !s) {
        addUppercaseEventHandler(*pke, h);
        addLowercaseEventHandler(*pke, h);
        return;
    }
    addHandler(e, h);
}

bool
UI::EventProcessor::empty() const
{
    return eventHandlers_.empty();
}

void UI::EventProcessor::clear()
{
    eventHandlers_.clear();
}

void
UI::EventProcessor::clear(const ::BaseEvent& e)
{
    EventHandlerTable::iterator i(findHandlers(e));
    if (i != eventHandlers_.end()) {
        eventHandlers_.erase(i);
    }
}

#include <iostream>
void
UI::EventProcessor::processEvent(const ::BaseEvent& e)
{
    EventHandlerTable::iterator i(findHandlers(e));
    if (i == eventHandlers_.end()) {
        return;
    }
    EventHandlerList ev;
    std::for_each(i->second.begin(), i->second.end(), PushBackClone(ev));
    std::for_each(ev.begin(), ev.end(), invoke);
}