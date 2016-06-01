//
// Created by phtran on 14/05/2016.
//

#include <fstream>

#include "screenform.h"
#include "stringlib.h"
#include "terminal.h"

static unsigned int XCOORD(1);
static unsigned int YCOORD(2);

UI::ScreenForm& UI::ScreenForm::operator= (const ScreenForm& rhs)
{
    filename_ = rhs.filename_;
    form_.clear();
    form_ = rhs.form_;
    return *this;
}

errCode_t UI::ScreenForm::load(std::string n)
{
    errCode_t exitStatus(  );
    filename_ = n;
    std::ifstream file(n.c_str());
    if (!file) {
        return ERROR_FILE_OPEN;
    }
    form_.clear();
    std::string line;
    while ( form_.size() < FORM_HEIGHT ) {
        getline( file, line );
        if ( ! file ) {
            break;
        }
        form_.push_back( line );
    }
    return NO_ERROR;
}

int UI::ScreenForm::load(const char buffer[][FORM_WIDTH], int nlines)
{
    std::string line;
    for ( int i = 0; i < nlines; ++i ) {
        line = strip( std::string(buffer[i], FORM_WIDTH));
        //@TODO: Need to revisit logic
        //form_.push_back(std::string(buffer[i], FORM_WIDTH));
        form_.push_back(line);
    }
    return NO_ERROR;
}

void UI::ScreenForm::draw() const
{
    if ( form_.size() == 0 ) {
        return;
    }
    UI::terminal().endEnhanced();
    for (const_iterator i(begin()); i != end(); ++i ) {
        UI::terminal().gotoxy(XCOORD, YCOORD + (i - begin()));
        UI::terminal().write( *i );
    }
}