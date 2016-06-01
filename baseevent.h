//
// Created by phtran on 13/05/2016.
//

#ifndef FRONTEND_BASEEVENT_H
#define FRONTEND_BASEEVENT_H

#include <string>

class BaseEvent
{
public:
    virtual ~BaseEvent() { }
    virtual bool operator< (const BaseEvent&) const = 0;
    virtual bool operator== (const BaseEvent&) const = 0;
    virtual std::string name() const = 0;
    virtual BaseEvent* clone() const = 0;
};

#endif //FRONTEND_BASEEVENT_H
