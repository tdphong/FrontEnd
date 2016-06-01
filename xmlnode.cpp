//
// Created by phtran on 09/05/2016.
//

#include <sstream>

#include <libxml/tree.h>
#include <libxml/parser.h>

#include "xml.h"
#include "xmlnode.h"

XmlNode::XmlNode(xmlNodePtr p)
    : node_(p)
{
    refreshChildren();
}

XmlNode::XmlNode(std::string n)
{
    ::cleanXml(n);
    node_ = xmlNewDocNode(0, 0, (xmlChar*)n.c_str(), 0);
}

XmlNode::XmlNode(std::string n, std::string c)
{
    ::cleanXml(n);
    node_ = xmlNewDocNode(0, 0, (xmlChar*)n.c_str(), 0);
    ::cleanXml(c);
    xmlNodeSetContent(node_, (xmlChar*)c.c_str());
}

std::string XmlNode::name() const
{
    if (!node_ || !node_->name) {
        return "";
    }
    return std::string((const char*)node_->name);
}

std::string XmlNode::content() const
{
    std::string c;
    if (node_) {
        if (node_->content) {
            c += std::string((const char*)node_->content);
        }
        for (xmlNodePtr i(node_->children); i; i= i->next) {
            if ((*i).content) {
                c += std::string((char*)(*i).content);
            }
        }
    }
    return c;
}

void XmlNode::content(const std::string& s)
{
    if (node_->children) {
        xmlNodeSetContent(node_->children, (xmlChar*)s.c_str());
    }
}

XmlNode XmlNode::parent() const
{
    XmlNode n(node_->parent);
    return n;
}

std::vector<XmlNode>& XmlNode::children()
{
    return children_;
}

const std::vector<XmlNode>& XmlNode::children() const
{
    return children_;
}

std::string XmlNode::property(std::string n) const
{
    std::string value;
    ::cleanXml( n );
    xmlChar *v(xmlGetProp(node_, (xmlChar*) n.c_str()));
    if (v) {
        value = std::string( reinterpret_cast<char *>(v) );
    }
    xmlFree(v);
    return value;
}

void XmlNode::property(std::string n, std::string v)
{
    ::cleanXml( n );
    ::cleanXml( v );
    xmlSetProp(node_, (xmlChar*) n.c_str(), (xmlChar*) v.c_str());
}

void XmlNode::property(std::string n, long v)
{
    std::ostringstream s;
    s << v;
    xmlSetProp(node_, (xmlChar*) n.c_str(), (xmlChar*) s.str().c_str());
}

void XmlNode::property(std::string n, int v)
{
    std::ostringstream s;
    s << v;
    xmlSetProp(node_, (xmlChar*) n.c_str(), (xmlChar*) s.str().c_str());
}

XmlNode& XmlNode::addChild(const XmlNode& c)
{
    xmlAddChild(node_, c);
    children_.push_back(c);
    return children_.back();
}

void XmlNode::refreshChildren()
{
    children_.clear();
    if (node_) {
        xmlNodePtr c(node_->children);
        while (c) {
            children_.push_back( XmlNode( c ) );
            c = c->next;
        }
    }
}