//
// Created by phtran on 08/05/2016.
//

#ifndef FRONTEND_BASEEVENTHANDLER_H
#define FRONTEND_BASEEVENTHANDLER_H

class BaseEventHandler
{
public:
    virtual ~BaseEventHandler() { }
    virtual void invoke() = 0;
    virtual BaseEventHandler* clone() const = 0;
};

#endif //FRONTEND_BASEEVENTHANDLER_H
