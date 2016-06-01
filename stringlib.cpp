//
// Created by phtran on 14/05/2016.
//

#include "stringlib.h"

std::string forceLength(std::string s, unsigned l)
{
    int pad( l - s.size() );
    if ( pad < 0 ) {
        s.erase( l );
    } else if ( pad > 0 ) {
        s.append( pad, ' ' );
    }
    return s;
}

std::string strip(const std::string& input)
{
    const std::string lookup(" \t\n\r\f");
    std::string str(input);
    std::size_t pos = str.find_first_not_of(lookup);
    if (pos == std::string::npos) {
        str.clear();
        /* Variable has leading spaces */
    } else if (pos != 0) {
        str.erase(0, pos);
    }

    pos = str.find_last_not_of(lookup);
    if ( pos == std::string::npos ) {
        str.clear();
    } else {
        str.erase(pos + 1);
    }
    return str;
}

void strip(std::string& str)
{
    const std::string input(str);
    str = strip(input);
}