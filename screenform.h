//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENFORM_H
#define FRONTEND_SCREENFORM_H

#include <string>
#include <vector>

#include "errors.h"

#define SCREEN_FIELD_OPEN_CHAR '[';
#define SCREEN_FIELD_CLOSE_CHAR ']';
#define FORM_WIDTH  80
#define FORM_HEIGHT 25
#define FORM_FILE_INPUT_LINE_LEN 256

namespace UI
{
    class ScreenField;
    class ScreenForm
    {
        std::string filename_;
        std::vector<std::string> form_;

    public:
        typedef std::vector<std::string>::iterator iterator;
        typedef std::vector<std::string>::const_iterator const_iterator;
        ScreenForm& operator=( const ScreenForm& );
        errCode_t load( std::string );
        errCode_t load(const char buffer[][FORM_WIDTH], int nlines);
        void draw() const;
        iterator begin() { return form_.begin(); }
        iterator end() { return form_.end(); }
        const_iterator begin() const { return form_.begin(); }
        const_iterator end() const { return form_.end(); }
        size_t lines() const { return form_.size(); }
    };
}


#endif //FRONTEND_SCREENFORM_H
