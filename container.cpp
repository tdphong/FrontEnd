//
// Created by phtran on 08/05/2016.
//

#include <assert.h>
#include <algorithm>

#include "container.h"
#include "event.h"
#include "terminal.h"
#include "baseeventhandler.h"
#include "screen.h"
#include <iostream>

typedef std::pair<UI::Container::BaseEventPtr,
        UI::Container::BaseEventHandlerPtr> EventHandlerPair;
static const std::string COMPONENT_NAME("Container");

class IdMatches
{
    const unsigned int id_;

public:
    IdMatches(const unsigned int id) : id_(id)
    { }

    bool operator() (const UI::Container::value_type& c) const
    {
        return c->id() == id_;
    }
};

class RemoveComponent
{
    UI::Container& container_;

public:
    RemoveComponent(UI::Container& c) : container_(c)
    { }
    void operator() (const unsigned int id)
    {
        container_.removeComponent(id);
    }
};

class RemoveComponentEventHandler : public BaseEventHandler
{
    UI::Container& container_;

public:
    RemoveComponentEventHandler(UI::Container& c) : container_(c)
    { }
    void invoke()
    {
        std::list<unsigned int> children;
        for (UI::Container::iterator i(container_.begin());
                i != container_.end(); ++i) {
            children.push_back((*i)->id());
        }
        std::for_each(children.begin(), children.end(), RemoveComponent(container_));
    }
    RemoveComponentEventHandler* clone() const
    {
        return new RemoveComponentEventHandler(*this);
    }
};

class Matches
{
    unsigned int pattern_;

public:
    Matches(const UI::BaseComponent& p) : pattern_{p.id()}
    { }
    Matches(const unsigned int& p) : pattern_(p)
    { }
    bool operator() (const UI::Container::value_type& c) const
    {
        return pattern_ == c->id();
    }
};

class BroadcastEventHandler : public BaseEventHandler
{
    const std::shared_ptr<BaseEvent> event_;
    UI::Container& container_;

public:
    BroadcastEventHandler(UI::Container& c, const BaseEvent& e)
            : container_(c)
            , event_(std::shared_ptr<BaseEvent>(e.clone()))
    { }
    virtual void invoke()
    {
        for (UI::Container::iterator i(container_.begin());
                i != container_.end(); ++i) {
            (*i)->notifyEvent(*event_);
        }
    }
    virtual BroadcastEventHandler* clone() const
    {
        return new BroadcastEventHandler(*this);
    }
};

static EventHandlerPair
broadcastEventPair(const BaseEvent& e, UI::Container& c)
{
    typedef UI::Container::BaseEventPtr EP;
    typedef UI::Container::BaseEventHandlerPtr HP;
    return std::make_pair(EP(e.clone()), HP(BroadcastEventHandler(c, e).clone()));
}

class AddEventHandler
{
    UI::Container& container_;

public:
    AddEventHandler(UI::Container& c) : container_(c)
    { }
    void operator()(EventHandlerPair& eh)
    {
        container_.addEventHandler(*eh.first, *eh.second);
    }
};

UI::Container::Container()
{
    focus_ = end();
    std::list<std::pair<BaseEventPtr , BaseEventHandlerPtr > >
            l(broadcastEventHandlers());
    std::for_each(l.begin(), l.end(), AddEventHandler(*this));
    addEventHandler(UI::RemoveComponentEvent(), RemoveComponentEventHandler(*this));
}

std::string UI::Container::name() const
{
    return COMPONENT_NAME;
}

UI::Container::iterator
UI::Container::begin()
{
    return components_.begin();
}

UI::Container::iterator
UI::Container::end()
{
    return components_.end();
}

UI::Container::const_iterator
UI::Container::begin() const {
    return components_.begin();
}

UI::Container::const_iterator
UI::Container::end() const
{
    return components_.end();
}

unsigned int
UI::Container::addComponent(BaseComponent& c)
{
    c.parent(*this);
    //@TODO: Need to reconsider
    //components_.push_back(value_type(c.clone()));
    components_.push_back(std::shared_ptr<BaseComponent>(&c));
    focus(c);
    return c.id();
}

void
UI::Container::removeComponent(const unsigned int id)
{
    iterator i(find(id));
    if (i == end()) {
        return;
    }
    int newFocusId(0);
    if (focus() != end()) {
        newFocusId = (*focus())->id();
    }
    if (i == focus()) {
        if (i != begin()) {
            newFocusId = (*(focus() - 1))->id();
        }
    }
    (*i)->notifyEvent(RemoveComponentEvent());
    UI::terminal().dispose(*i);
    components_.erase(i);
    focus(find(newFocusId));
}

UI::Container::iterator
UI::Container::focus()
{
    return focus_;
}

void
UI::Container::focus(const BaseComponent& c)
{
    iterator i(std::find_if(begin(), end(), Matches(c)));
    assert(i != end());
    focus(i);
    (*focus())->notifyEvent(UI::GainFocusEvent());
}

void
UI::Container::focus(iterator i)
{
    focus_ = i;
}

size_t
UI::Container::size() const
{
    return components_.size();
}

void
UI::Container::clear()
{
    components_.clear();
    focus(end());
}

bool
UI::Container::empty() const
{
    return size() == 0;
}

void
UI::Container::notifyEvent(const ::BaseEvent& e)
{
    Component::notifyEvent(e);
    if (focus_ == end()) {
        return;
    }
    if (!isBroadcastEvent(e)) {
        (*focus_)->notifyEvent(e);
    }
}

void
UI::Container::draw(const unsigned int id) const
{
    const_iterator i(find(id));
    if (i == end()) {
        return;
    }
    (*i)->notifyEvent(DrawAllEvent());
}

UI::Container::const_iterator
UI::Container::find(const unsigned int id) const
{
    return std::find_if(begin(), end(), IdMatches(id));
}

UI::Container::iterator
UI::Container::find(const unsigned int id)
{
    return std::find_if(begin(), end(), Matches(id));
}

UI::Container*
UI::Container::clone() const
{
    return new UI::Container(*this);
}

bool
UI::Container::isBroadcastEvent(const BaseEvent &e) const
{
    return broadcastEventNames_.find(e.name()) != broadcastEventNames_.end();
}

std::list<EventHandlerPair>
UI::Container::broadcastEventHandlers()
{
    std::list<EventHandlerPair> l;
    l.push_back(broadcastEventPair(DrawAllEvent(), *this));
    l.push_back(broadcastEventPair(TerminalGeometryChangedEvent(), *this));
    l.push_back(broadcastEventPair(HideEvent(), *this));
    l.push_back(broadcastEventPair(UnhideEvent(), *this));
    l.push_back(broadcastEventPair(RemoveComponentEvent(), *this));
    l.push_back(broadcastEventPair(RequeryRequestEvent(), *this));

    for (std::list<EventHandlerPair>::iterator i(l.begin()); i != l.end(); ++i) {
        broadcastEventNames_.insert(i->first->name());
    }
    return l;
}