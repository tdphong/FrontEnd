//
// Created by phtran on 16/05/2016.
//

#ifndef FRONTEND_WALLCLOCK_H
#define FRONTEND_WALLCLOCK_H

#include "basewallclock.h"

class WallClock : public BaseWallClock
{

public:

    /*** Constructor/Destructor ***/
    WallClock();
    WallClock( time_t );

protected:

    virtual time_t timeOnClock() const;

private:
    time_t t_;
};

#endif //FRONTEND_WALLCLOCK_H
