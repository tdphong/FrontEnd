//
// Created by phtran on 16/05/2016.
//

#include "basewallclock.h"
#include "sysexception.h"

const std::string BaseWallClock::standard( "%e-%b-%y %H:%M:%S" );

bool BaseWallClock::operator<( const BaseWallClock &rhs ) const
{

    return timeOnClock() < rhs.timeOnClock();

}

bool BaseWallClock::operator<=( const BaseWallClock &rhs ) const
{

    return ( *this < rhs ) || ( timeOnClock() == rhs.timeOnClock() );

}

time_t BaseWallClock::operator-( const BaseWallClock &rhs ) const
{

    return timeOnClock() - rhs.timeOnClock();

}

time_t BaseWallClock::time() const
{

    return timeOnClock();

}

std::string BaseWallClock::asFormattedLocalDateTimeString( const std::string &formatSpecifier ) const
{
    time_t toc( timeOnClock() );
    struct tm *time = localtime( &toc );
    return createString( time, formatSpecifier );
}

std::string BaseWallClock::createString( struct tm         *t,
                                         const std::string &f ) const
{
    char buf[100];
    strftime( buf, 100, f.c_str(), t );
    return std::string(buf);
}