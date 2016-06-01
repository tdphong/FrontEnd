//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENFIELDFACTORY_H
#define FRONTEND_SCREENFIELDFACTORY_H

#include <string>

class XmlNode;

namespace UI
{
    class ScreenField;
    class Screen;

    class ScreenFieldFactory
    {
    public:
        ScreenField* generate(const XmlNode&, Screen&) const;
        void addType(XmlNode&, const std::string&) const;
        void addHint(XmlNode&, const std::string&) const;
        void addDefault(XmlNode&, const std::string&) const;
        void addMandatory(XmlNode&, const bool) const;
        void addReadonly(XmlNode&, const bool) const;
        void addQEnterSupport(XmlNode&, const bool) const;
        void addAlias(XmlNode&, const std::string&, const std::string&);
        void addXCoordinate(XmlNode&, const unsigned int) const;
        void addYCoordinate(XmlNode&, const unsigned int) const;
        void addLength(XmlNode&, const unsigned int) const;
        void addDecimalPlaces(XmlNode&, const unsigned int) const;
        void addLeadingZerosFormatter(XmlNode&) const;
    };

}

#endif //FRONTEND_SCREENFIELDFACTORY_H
