//
// Created by phtran on 16/05/2016.
//

#ifndef FRONTEND_DATE_H
#define FRONTEND_DATE_H

#include <string>
#include <sstream>
#include <time.h>

std::string getTimeZone();
void setTimeZone(const std::string& tz);

class Date
{
public:
    Date();
    Date(int);
    int asInt() const;

private:
    int cymd_;
};


#endif //FRONTEND_DATE_H
