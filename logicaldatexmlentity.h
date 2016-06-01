//
// Created by phtran on 10/05/2016.
//

#ifndef FRONTEND_LOGICALDATEXMLENTITY_H
#define FRONTEND_LOGICALDATEXMLENTITY_H

#include <list>

#include "basexmlentity.h"

class LogicalDateXmlEntity : public BaseXmlEntity
{
    unsigned int streamCode_;

public:
    LogicalDateXmlEntity( const unsigned int );
    virtual std::string name() const;
    virtual std::string value() const;
    virtual BaseXmlEntity* clone() const;
};

std::list<LogicalDateXmlEntity> allLogicalDateXmlEntities();

#endif //FRONTEND_LOGICALDATEXMLENTITY_H
