//
// Created by phtran on 17/05/2016.
//

#include "logicaldatexmlentity.h"

static const std::string ENTITY_REFERENCE_STUB( "logical_date_" );

LogicalDateXmlEntity::LogicalDateXmlEntity( const unsigned int s )
        : streamCode_( s )
{

}

std::string LogicalDateXmlEntity::name() const
{
    //@TODO: Need to fix
    return std::string("ABCDE");

}

std::string LogicalDateXmlEntity::value() const
{
    //@TODO: Need to fix
    std::string("XYZ");
}

BaseXmlEntity* LogicalDateXmlEntity::clone() const
{

    return new LogicalDateXmlEntity( *this );

}

std::list<LogicalDateXmlEntity> allLogicalDateXmlEntities()
{
    //@TODO: Need to fix
    std::list<LogicalDateXmlEntity> l;
    return l;
}