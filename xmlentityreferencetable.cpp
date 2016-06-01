//
// Created by phtran on 10/05/2016.
//

#include "xmlentityreferencetable.h"
#include "logicaldatexmlentity.h"

std::list<std::shared_ptr<BaseXmlEntity> > xmlEntityReferenceTable()
{
    std::list<std::shared_ptr<BaseXmlEntity> > t;
    std::list<LogicalDateXmlEntity> l( allLogicalDateXmlEntities() );
    for ( std::list<LogicalDateXmlEntity>::const_iterator i( l.begin() );
          i != l.end(); ++i ) {
        t.push_back(std::shared_ptr<BaseXmlEntity>(i->clone()));
    }
    return t;
}