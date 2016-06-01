//
// Created by phtran on 10/05/2016.
//

#ifndef FRONTEND_BASEXMLENTITY_H
#define FRONTEND_BASEXMLENTITY_H

#include <string>

class BaseXmlEntity
{
public:
    virtual ~BaseXmlEntity() { };
    virtual std::string name() const = 0;
    virtual std::string value() const = 0;
    virtual BaseXmlEntity* clone() const = 0;
};

#endif //FRONTEND_BASEXMLENTITY_H
