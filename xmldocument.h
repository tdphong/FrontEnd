//
// Created by phtran on 09/05/2016.
//

#ifndef FRONTEND_XMLDOCUMENT_H
#define FRONTEND_XMLDOCUMENT_H

#include "xmlnode.h"

class XmlDocument
{
public:
    XmlDocument(const std::string&);
    XmlDocument(const XmlDocument&);
    virtual  ~XmlDocument();
    void operator=(const xmlDocPtr&);
    void operator=(const XmlDocument&);
    xmlDocPtr& docPtr();
    const xmlDocPtr& docPtr() const;
    XmlNode& root();
    const XmlNode& root() const;
    void expandEntities();

private:
    xmlDocPtr doc_;
    XmlNode root_;
};

#endif //FRONTEND_XMLDOCUMENT_H
