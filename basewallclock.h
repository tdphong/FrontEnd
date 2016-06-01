//
// Created by phtran on 16/05/2016.
//

#ifndef FRONTEND_BASEWALLCLOCK_H
#define FRONTEND_BASEWALLCLOCK_H

#include <string>
#include <sys/types.h>
#include <time.h>

#include "date.h"

class BaseWallClock
{

public:

    virtual ~BaseWallClock() { };

    bool operator<( const BaseWallClock& ) const;

    bool operator<=( const BaseWallClock& ) const;

    time_t operator-( const BaseWallClock& ) const;

    time_t time() const;

    Date localDate( const std::string& ) const;

    unsigned int localTime( const std::string& ) const;

    std::string asLocalDateTimeString() const;

    std::string asDateTimeString( const std::string& ) const;

    std::string asUTCDateTimeString() const;

    std::string asLocalTimeString() const;

    static const std::string standard;

    std::string asFormattedLocalDateTimeString( const std::string& ) const;

    bool empty() const { return timeOnClock() == 0; }

protected:

    virtual time_t timeOnClock() const = 0;

    std::string createString( struct tm*, const std::string& ) const;

};

#endif //FRONTEND_BASEWALLCLOCK_H
