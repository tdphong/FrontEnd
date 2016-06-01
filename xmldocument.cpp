//
// Created by phtran on 10/05/2016.
//

#include <list>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include <memory>

#include "xmldocument.h"
#include "logicaldatexmlentity.h"
#include "xmlentityreferencetable.h"
#include "xml.h"
#include "sysfile.h"
#include "sysexception.h"

static const unsigned LIBXML2_COPY_RECURSIVE(1);

class Insert
{
    std::list<std::pair<std::string,std::string> > &substitutions_;

public:
    Insert( std::list<std::pair<std::string,std::string> > &sv )
            : substitutions_( sv )
    { }
    void operator()( const std::shared_ptr<BaseXmlEntity> &e )
    {
        /* Pointer safety. */
        if ( ! e.get() ) {
            return;
        }
        substitutions_.push_back( std::make_pair( e->name(), e->value() ) );
    }

};

class PerformSubstitution
{
    XmlDocument& doc_;

public:
    PerformSubstitution(XmlDocument& d)
            : doc_(d)
    { }
    void operator() (const std::pair<std::string, std::string>& s)
    {
        xmlEntityPtr e(xmlGetDocEntity(doc_.docPtr(), (const xmlChar*)s.first.c_str()));
        if (!e) {
            return;
        }
        xmlFree(e->orig);
        e->orig = (xmlChar*)strdup(s.second.c_str());
    }
};

static void
expandEntityReferences(XmlDocument& d, const std::list<std::pair<std::string, std::string> >& s)
{
    std::for_each(s.begin(), s.end(), PerformSubstitution(d));
    const std::string t( saveXml(tmpFilename(), d));

    try {
        xmlSubstituteEntitiesDefault(1);
        loadXml(d, t);
        removeFile(t);
        xmlSubstituteEntitiesDefault(0);
    } catch (const ApplicationException&) {
        xmlSubstituteEntitiesDefault(0);
        throw;
    }
}

XmlDocument::XmlDocument( const std::string &n )
        : doc_( xmlNewDoc( (const xmlChar*) XML_DEFAULT_VERSION ) )
        , root_( 0 )
{

    assert( ! n.empty() );

    root_ = xmlNewDocNode( doc_, 0, (const xmlChar*) n.c_str(), (const xmlChar*)"" );

    xmlDocSetRootElement( doc_, root_ );

}

XmlDocument::XmlDocument(const XmlDocument& orig)
    : doc_(xmlCopyDoc(orig.doc_, LIBXML2_COPY_RECURSIVE))
    , root_(0)
{
    xmlDocSetRootElement(doc_, root_);
}

XmlDocument::~XmlDocument()
{
    xmlFreeDoc(doc_);
}

void XmlDocument::operator=(const xmlDocPtr& rhs)
{
    xmlFreeDoc( docPtr() );
    doc_ = xmlCopyDoc( rhs, LIBXML2_COPY_RECURSIVE );
    root_ = xmlDocGetRootElement( doc_ );
}

void XmlDocument::operator=(const XmlDocument& rhs)
{
    xmlFreeNode( docPtr()->children );
    xmlFreeDoc( docPtr() );
    doc_ = xmlCopyDoc( rhs.docPtr(), LIBXML2_COPY_RECURSIVE );
    root_ = xmlDocGetRootElement( doc_ );
}

xmlDocPtr& XmlDocument::docPtr()
{
    return doc_;
}

const xmlDocPtr& XmlDocument::docPtr() const
{
    return doc_;
}

XmlNode& XmlDocument::root()
{
    return root_;
}

const XmlNode& XmlDocument::root() const
{
    return root_;
}

void XmlDocument::expandEntities()
{
    const std::list<std::shared_ptr<BaseXmlEntity> >
            ert(xmlEntityReferenceTable());
    std::list<std::pair<std::string,std::string> > substitutions;
    std::for_each( ert.begin(), ert.end(), Insert( substitutions ) );
    expandEntityReferences( *this, substitutions );
}