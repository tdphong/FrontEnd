//
// Created by phtran on 14/05/2016.
//

#include <fstream>

#include "screenfield.h"
#include "loadscreenfields.h"
#include "sysexception.h"
#include "stringtokeniser.h"
#include "xmlnode.h"
#include "screenfieldfactory.h"
using FieldPtr = std::shared_ptr<UI::ScreenField>;

#include <iostream>
static const std::string FIELD_DEFINITION_NODE_NAME("screen_field_definition");

void loadScreenFields(UI::Screen& s, std::vector<FieldPtr> &fv, const std::string& n)
{
    std::ifstream f(n.c_str());
    if (!f) {
        throw FileOpenException();
    }
    std::string b;
    getline(f, b);
    const int c(atoi(b.c_str()));
    for (int i = 0; i < c; ++i) {
        getline(f, b);
        if (!f) {
            break;
        }
        StringTokeniser tok(b, ":", true);
        tok.stripAll();
        if (tok.has_more_tokens()) {
            b = tok.next_token();
        }
        XmlNode fd(FIELD_DEFINITION_NODE_NAME);
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addMandatory(fd, tok.next_token() == "M");
        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addHint(fd, tok.next_token());
        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addReadonly(fd, tok.next_token() == "R");
        }
        if (tok.has_more_tokens()) {
            StringTokeniser aliasTokens(tok.next_token(), ",");
            if ( aliasTokens.size() > 1 ) {
            }

        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addQEnterSupport(fd, tok.next_token() == "Q");
        }
        if (tok.has_more_tokens()) {
            const std::string formatter(tok.next_token());
            if (formatter == "LZ") {
                UI::ScreenFieldFactory().addLeadingZerosFormatter(fd);
            }
        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addDefault(fd, tok.next_token());
        }
        tok = StringTokeniser( b );
        tok.stripAll();
        bool isReal( false );
        if (tok.has_more_tokens()) {
            const std::string t(tok.next_token());
            UI::ScreenFieldFactory().addType(fd, t);
            isReal = t == "r";
        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addXCoordinate(fd, static_cast<unsigned int>(atoi(tok.next_token().c_str())));
        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addYCoordinate(fd, static_cast<unsigned int>(atoi(tok.next_token().c_str())));
        }
        if (tok.has_more_tokens()) {
            UI::ScreenFieldFactory().addLength(fd, static_cast<unsigned int>(atoi(tok.next_token().c_str())));
        }
        if (isReal && (tok.has_more_tokens())) {
            UI::ScreenFieldFactory().addDecimalPlaces(fd, static_cast<unsigned int>(atoi(tok.next_token().c_str())));
        } else {
            UI::ScreenFieldFactory().addDecimalPlaces(fd, 0);
        }
        fv.push_back( FieldPtr(UI::ScreenFieldFactory().generate(fd, s)));
    }

}



