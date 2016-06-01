//
// Created by phtran on 09/05/2016.
//

#ifndef FRONTEND_XMLNODE_H
#define FRONTEND_XMLNODE_H

#include <libxml/parser.h>

#include <map>
#include <vector>
#include <string>

class XmlNode
{
public:
    typedef std::vector<XmlNode> Children;
    typedef std::map<std::string, std::string> Properties;
    XmlNode(xmlNodePtr);
    XmlNode(std::string);
    XmlNode(std::string, std::string);
    operator xmlNodePtr() {return node_;}
    operator const xmlNodePtr() const {return node_;}
    std::string name() const;
    std::string content() const;
    void content(const std::string&);
    std::string property(std::string) const;
    void property(std::string, std::string);
    void property(std::string, long);
    void property(std::string, int);
    XmlNode& addChild(const XmlNode&);
    XmlNode parent() const;
    Children& children();
    const Children& children() const;

private:
    void refreshChildren();
    xmlNodePtr node_;
    Children children_;
};

#endif //FRONTEND_XMLNODE_H
