//
// Created by phtran on 08/05/2016.
//

#include <assert.h>

#include "baseeventhandler.h"
#include "component.h"
#include "event.h"

static const unsigned int FIRST_ID_NUMBER(1);

class HideEventHandler : public BaseEventHandler
{
    bool& flag_;

public:
    HideEventHandler(bool& f) : flag_(f)
    { }
    virtual void invoke()
    {
        flag_ = true;
    }
    virtual HideEventHandler* clone() const
    {
        return new HideEventHandler(*this);
    }
};

class UnhideEventHandler : public BaseEventHandler
{
    bool& flag_;

public:
    UnhideEventHandler(bool& f) : flag_(f)
    { }
    virtual void invoke()
    {
        flag_ = false;
    }
    virtual UnhideEventHandler* clone() const
    {
        return new UnhideEventHandler(*this);
    }
};

static unsigned int nextComponentId()
{
    static unsigned int id(FIRST_ID_NUMBER);
    return id++;
}

UI::Component::Component()
    : id_(nextComponentId())
    , hidden_(false)
    , parent_(0)

{
    assignEventHandlers();
}

bool
UI::Component::operator<(const BaseComponent& rhs) const
{
    return id() < rhs.id();
}

bool
UI::Component::operator==(const BaseComponent& rhs) const
{
    return id() == rhs.id();
}

bool
UI::Component::operator!=(const BaseComponent& rhs) const
{
    return id() != rhs.id();
}

void
UI::Component::addEventHandler(const ::BaseEvent& e, const ::BaseEventHandler& h, const bool s)
{
    eventProcessor_.addEventHandler(e, h, s);
}

void
UI::Component::clearEventHandlers()
{
    eventProcessor_.clear();
}

void
UI::Component::clearEventHandler(const ::BaseEvent& e)
{
    eventProcessor_.clear(e);
}

#include <iostream>
void
UI::Component::notifyEvent(const ::BaseEvent& e)
{
    std::map<std::string, std::shared_ptr<BaseComponent> >::iterator
    i(delegates_.find(e.name()));

    if (i != delegates_.end()) {
        i->second->notifyEvent(e);
        return;
    }
    eventProcessor_.processEvent(e);
}

void
UI::Component::delegate(const ::BaseEvent& e, BaseComponent& c)
{
    delegates_[e.name()] = std::shared_ptr<BaseComponent>(c.clone());
}

void
UI::Component::hide()
{
    hidden_ = true;
    notifyEvent(HideEvent());
}

void
UI::Component::unhide()
{
    hidden_ = false;
    notifyEvent(UnhideEvent());
}

bool
UI::Component::hidden() const
{
    return hidden_;
}

unsigned int
UI::Component::id() const
{
    return id_;
}

UI::Container& UI::Component::parent()
{
    assert(parent_);
    return *parent_;
}

UI::Container& UI::Component::parent(UI::Container& c)
{
    parent_ = &c;
    return *parent_;
}

void
UI::Component::assignEventHandlers()
{
    addEventHandler(HideEvent(), HideEventHandler(hidden_));
    addEventHandler(UnhideEvent(), UnhideEventHandler(hidden_));
}