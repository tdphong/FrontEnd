//
// Created by phtran on 16/05/2016.
//

#include <cstdlib>

#include "date.h"

static const int DATE_NOT_SET = 0;

std::string getTimeZone()
{
    const char *c(::getenv("TZ"));
    if ( ! c ) {
        return std::string("");
    }
    return std::string( c );
}

void setTimeZone( const std::string &tz )
{
    if ( tz.empty() ) {

        ::unsetenv( "TZ" );

    } else {

        ::setenv( "TZ", tz.c_str(), 1 );

    }
}


Date::Date() : cymd_(DATE_NOT_SET)
{ }

Date::Date(int t) : cymd_(t) { }

int Date::asInt() const
{
    return cymd_;
}



