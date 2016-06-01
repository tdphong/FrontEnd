//
// Created by phtran on 15/05/2016.
//

#include "datescreenfield.h"
#include "datescreenfieldformatter.h"
#include "datescreenfieldvalidator.h"
#include "sysexception.h"
#include "wallclock.h"

static const std::string DEFAULT_ALIAS_TODAY( "@today" );
static const std::string FORMAT( "%Y%m%d" );

UI::DateScreenField::DateScreenField()
{
    formatter(DateScreenFieldFormatter());
    addValidators();
}

const std::string& UI::DateScreenField::defaultValue() const
{
    return ScreenField::defaultValue();
}

const std::string& UI::DateScreenField::defaultValue( const std::string &v )
{
    if ( v == DEFAULT_ALIAS_TODAY ) {
        const std::string
                s( WallClock( time( 0 ) ).asFormattedLocalDateTimeString( FORMAT ) );
        return ScreenField::defaultValue( s );
    }
    return ScreenField::defaultValue( v );
}

void UI::DateScreenField::loseFocus()
{
    try {
        if (!isBlank()) {
            std::ostringstream s;
            s << Date( atoi(get().c_str())).asInt();
            set( s.str() );
        }
    } catch ( const ApplicationException& ) {
    }
    ScreenField::loseFocus();
}

void UI::DateScreenField::addValidators()
{
    addValidator( DateScreenFieldValidator() );
}

