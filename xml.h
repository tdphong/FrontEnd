//
// Created by phtran on 09/05/2016.
//

#ifndef FRONTEND_XML_H
#define FRONTEND_XML_H

#include <libxml/tree.h>

#include "xmlnode.h"
#include "xmldocument.h"

struct NameMatches
{
    NameMatches(const std::string& n)
            : name(n)
    { }
    bool operator() (const XmlNode& n) const
    {
        return n.name() == name;
    }
    const std::string name;
};

class NameDoesNotMatch
{
    const std::string name;

public:
    NameDoesNotMatch( const std::string &n )
            : name( n )
    { }
    bool operator()( const XmlNode &n ) const
    {
        return n.name() != name;
    }
};

void cleanXml(std::string&);
std::string cleanXml(const std::string&);
std::string saveXml(const std::string&, const XmlDocument&);
void loadXml(XmlDocument&, const std::string&);
void dumpXml(std::ostream&, const XmlDocument&);
#endif //FRONTEND_XML_H
