//
// Created by phtran on 10/05/2016.
//

#ifndef FRONTEND_XMLENTITYREFERENCETABLE_H
#define FRONTEND_XMLENTITYREFERENCETABLE_H

#include <memory>
#include <list>

#include "countedpointer.h"

class BaseXmlEntity;

std::list<std::shared_ptr<BaseXmlEntity> > xmlEntityReferenceTable();

#endif //FRONTEND_XMLENTITYREFERENCETABLE_H
