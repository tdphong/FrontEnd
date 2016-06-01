//
// Created by phtran on 14/05/2016.
//

#include <algorithm>

#include "screen.h"
#include "screenfieldfactory.h"
#include "integerscreenfield.h"
#include "xmlnode.h"
#include "xml.h"
#include "leadingzerosnumericscreenfieldformatter.h"
#include "mandatorynumericscreenfieldformatter.h"
#include "stringscreenfield.h"
#include "mandatorystringscreenfieldformatter.h"
#include "mandatorydatescreenfieldformatter.h"
#include "upperstringscreenfield.h"
#include "sedolscreenfield.h"
#include "realscreenfield.h"
#include "datescreenfield.h"
#include "sysexception.h"
#include "mandatoryscreenfieldvalidator.h"

static const std::string NODE_HINT("hint");
static const std::string NODE_TYPE("type");
static const std::string NODE_MANDATORY("mandatory");
static const std::string NODE_DEFAULT("default");
static const std::string NODE_READONLY("readonly");
static const std::string NODE_QENTERSUPPORT("q_enter_support");
static const std::string NODE_ALIAS("alias");
static const std::string NODE_XCOORDINATE("x_coordinate");
static const std::string NODE_YCOORDINATE("y_coordinate");
static const std::string NODE_LENGTH("length");
static const std::string NODE_DECIMALPLACES("decimal_places");
static const std::string NODE_FORMATTER("formatter");
static const std::string FORMATTER_LEADING_ZEROS("leading_zeros");
static const std::string XML_TRUE("true");
static const std::string XML_FALSE("false");

static std::string childValue(const XmlNode& r, const std::string& n)
{
    XmlNode::Children::const_iterator i(std::find_if(r.children().begin(), r.children().end(), NameMatches(n)));
    if (i == r.children().end()) {
        return std::string("");
    }
    return i->content();
}

static UI::ScreenField* newIntegerField(const bool m, const std::string& fmt)
{
    UI::ScreenField* f(new UI::IntegerScreenField);
    if (fmt == FORMATTER_LEADING_ZEROS) {
        f->formatter(UI::LeadingZerosNumericScreenFieldFormatter());
    } else if (m) {
        f->formatter(UI::MandatoryNumericScreenFieldFormatter());
    } else {
        f->formatter(UI::NumericScreenFieldFormatter());
    }
    return f;
}

static UI::ScreenField* newStringField(const bool m)
{
    UI::ScreenField* f(new UI::StringScreenField);
    if (m) {
        f->formatter(UI::MandatoryStringScreenFieldFormatter());
    }
    return f;
}

static UI::ScreenField* newUpperStringField(const bool m)
{
    UI::ScreenField* f(new UI::UpperStringScreenField);
    if ( m ) {
        f->formatter(UI::MandatoryStringScreenFieldFormatter());
    }
    return f;
}

static UI::ScreenField* newRealField(const bool m)
{
    UI::ScreenField* f(new UI::RealScreenField);
    if (m) {
        f->formatter(UI::MandatoryNumericScreenFieldFormatter());
    }
    return f;
}

static UI::ScreenField* newDateField(const bool m)
{
    UI::ScreenField* f(new UI::DateScreenField);
    if ( m ) {
        f->formatter(UI::MandatoryDateScreenFieldFormatter());
    }
    return f;
}

static UI::ScreenField* newSedolField(const bool m)
{
    UI::ScreenField* f(new UI::SedolScreenField);
    if (m) {
        f->formatter(UI::MandatoryStringScreenFieldFormatter());
    }
    return f;
}

#include <iostream>
static UI::ScreenField* newField(UI::Screen& s, const std::string& t, const bool m, const std::string& fmt)
{
    if (t.empty()) {
        throw InternalException();
    }
    UI::ScreenField *f(0);
    switch (t[0]) {
        case 'i': f = newIntegerField( m, fmt ); break;
        case 'r': f = newRealField( m ); break;
        case 'd': f = newDateField( m ); break;
        case 'a': f = newStringField( m ); break;
            //@TODO: Uncommentout when code completes
        //case 'b': f = newBooleanField( m ); break;

    }
    if ( t == std::string( "country_name" ) ) {
        //@TODO: Need to change it to newCountryNameField
        f = newStringField( m );
    }
    if ( t == std::string( "holiday_year" ) ) {
        //@TODO: Need to change it to newHolidayYearField
        f = newStringField( m );
    }

    if (!f) {
        throw InternalException();
    }
    if (m) {
        f->addValidator(UI::MandatoryScreenFieldValidator());
    }
    return f;
}

UI::ScreenField* UI::ScreenFieldFactory::generate(const XmlNode& r, Screen& s) const
{
    const std::string t(childValue(r, NODE_TYPE));
    const std::string m( childValue(r, NODE_MANDATORY));
    ScreenField* f(newField(s, t, m == XML_TRUE, childValue(r, NODE_FORMATTER)));
    f->readonly(childValue(r, NODE_READONLY) == XML_TRUE );
    f->xCoordinate(static_cast<unsigned int>(atoi(childValue(r, NODE_XCOORDINATE).c_str())));
    f->yCoordinate(static_cast<unsigned int>(atoi(childValue( r, NODE_YCOORDINATE).c_str())));
    f->length(static_cast<unsigned int>(atoi(childValue(r, NODE_LENGTH).c_str())));
    f->hint(childValue(r, NODE_HINT));
    f->decimalPlaces(static_cast<unsigned int>(atoi(childValue(r, NODE_DECIMALPLACES).c_str())));
    f->defaultValue(childValue(r, NODE_DEFAULT));
    return f;
}

void UI::ScreenFieldFactory::addType( XmlNode& n, const std::string& v) const
{
    n.addChild(XmlNode(NODE_TYPE, v));
}

void UI::ScreenFieldFactory::addMandatory(XmlNode& n, const bool v) const
{
    n.addChild(XmlNode(NODE_MANDATORY, v ? XML_TRUE : XML_FALSE));
}

void UI::ScreenFieldFactory::addDefault(XmlNode& n, const std::string& v) const
{
    n.addChild(XmlNode(NODE_DEFAULT, v));
}

void UI::ScreenFieldFactory::addReadonly(XmlNode& n, const bool v) const
{
    n.addChild(XmlNode(NODE_READONLY, v ? XML_TRUE : XML_FALSE));
}

void UI::ScreenFieldFactory::addQEnterSupport(XmlNode& n, const bool v) const
{
    n.addChild(XmlNode(NODE_QENTERSUPPORT, v ? XML_TRUE : XML_FALSE));
}

void UI::ScreenFieldFactory::addAlias(XmlNode&, const std::string&, const std::string&)
{
    //@TODO: Will be implemented

}

void UI::ScreenFieldFactory::addXCoordinate(XmlNode& n, const unsigned int v) const
{
    std::ostringstream s;
    s << v;
    n.addChild(XmlNode(NODE_XCOORDINATE, s.str()));
}

void UI::ScreenFieldFactory::addYCoordinate(XmlNode& n, const unsigned int v) const
{
    std::ostringstream s;
    s << v;
    n.addChild(XmlNode(NODE_YCOORDINATE, s.str()));
}

void UI::ScreenFieldFactory::addLength(XmlNode& n, const unsigned int v) const
{
    std::ostringstream s;
    s << v;
    n.addChild(XmlNode(NODE_LENGTH, s.str()));
}

void UI::ScreenFieldFactory::addDecimalPlaces(XmlNode& n, const unsigned int v) const
{
    std::ostringstream s;
    s << v;
    n.addChild(XmlNode(NODE_DECIMALPLACES, s.str()));
}

void UI::ScreenFieldFactory::addHint(XmlNode& n, const std::string& v) const
{
    n.addChild(XmlNode(NODE_HINT, v));
}

void UI::ScreenFieldFactory::addLeadingZerosFormatter(XmlNode& n) const
{
    n.addChild(XmlNode(NODE_FORMATTER, FORMATTER_LEADING_ZEROS));
}