//
// Created by phtran on 16/05/2016.
//

#include "wallclock.h"

WallClock::WallClock() : t_( 0 )
{ }

WallClock::WallClock(time_t t) : t_( t )
{ }

time_t WallClock::timeOnClock() const
{
    return t_;
}
