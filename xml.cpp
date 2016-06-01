//
// Created by phtran on 10/05/2016.
//

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxslt/xslt.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#include <cstring>

#include "xml.h"
#include "sysexception.h"
#include "sysfile.h"

static const char* XML_AMPERSAND("&amp;");

std::string xmlNodeProperty(const xmlNodePtr& n, const std::string& p)
{
    const char* v((char*)xmlGetProp(n, (xmlChar*)p.c_str()));
    return v ? std::string(v) : std::string();
}

unsigned processXpathQuery(std::vector<XmlNode>& m,
                           const XmlDocument& d,
                           const std::string& q)
{
    xmlXPathContextPtr context(xmlXPathNewContext(d.docPtr()));
    if (!context) {
        throw ValidationException();
    }
    xmlXPathObjectPtr xPathObj(xmlXPathEvalExpression((xmlChar*)q.c_str(), context));
    if (!xPathObj) {
        xmlXPathFreeContext(context);
        throw ValidationException();
    }
    xmlNodeSetPtr n(xPathObj->nodesetval);
    if (!n) {
        xmlXPathFreeObject(xPathObj);
        xmlXPathFreeContext(context);
        return 0;
    }
    for ( unsigned i(0); i < n->nodeNr; ++i) {
        m.push_back(XmlNode(n->nodeTab[i]));
    }
    int numberOfNodes = n->nodeNr;

    xmlXPathFreeObject(xPathObj);
    xmlXPathFreeContext(context);
}

void loadXml(XmlDocument& d, const std::string& n)
{
    xmlDocPtr  p(xmlParseFile((char*)n.c_str()));
    if (!p) {
        throw FileInputException();
    }
    d = p;
    xmlFreeDoc(p);
}

std::string saveXml(const std::string& n, const XmlDocument& d)
{
    FILE* f(fopen(n.c_str(), "w"));
    if (!f) {
        throw FileException();
    }
    xmlDocDump(f, d.docPtr());
    fclose(f);
    return n;
}

void dumpXml(std::ostream& s, const XmlDocument& d)
{
    const std::string n(tmpFilename());
    saveXml(n, d);
    dumpFile(s, n);
    removeFile(n);
}

void applyXslt(const XmlDocument& in, const std::string& xslt, const std::string& out)
{
    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    xsltStylesheetPtr s(xsltParseStylesheetFile((const xmlChar*)xslt.c_str()));
    xmlDocPtr res(xsltApplyStylesheet(s, in.docPtr(), 0));
    FILE* f(fopen(out.c_str(), "w"));
    if (!f) {
        throw FileException();
    }
    xsltSaveResultToFile(f, res, s);
    fclose(f);
    xmlFreeDoc(res);
    xsltFreeStylesheet(s);
    xsltCleanupGlobals();
    xmlCleanupParser();
}

void cleanXml(std::string& s)
{
    std::string::size_type i(s.find(std::string("&")));
    while (i != std::string::npos) {
        s.erase(i, 1);
        s.insert(i, XML_AMPERSAND);
        i = s.find(std::string("&"), i+1);
    }
}

std::string cleanXml(const std::string& s)
{
    std::string t(s);
    cleanXml(t);
    return t;
}