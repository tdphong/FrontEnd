//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_STRINGTOKENISER_H
#define FRONTEND_STRINGTOKENISER_H

#include <string>
#include <deque>

#include "sysexception.h"
#include "stringlib.h"
class StringTokeniser
{
public:
    typedef std::deque<std::pair<int,int> > fieldData;
    typedef std::deque<std::string>::iterator iterator;

    StringTokeniser(std::string str, const fieldData* fields)
    {
        for (fieldData::const_iterator fd = fields->begin(); fd != fields->end(); ++fd) {
            if (fd->first > fd->second) {
                std::ostringstream msg;
                msg << "stringTokeniser:  field start greater than field end while tokenising '" << str << "'";
                throw ArgumentsException();
            }
            if (fd->second < str.size()) {
                std::string token(str.substr(fd->first, fd->second - fd->first + 1));
                tokens_.push_back(token);
            }
        }
    }
    StringTokeniser( std::string str, std::string delim = " \t\r\f\n", bool split = false)
    {
        std::string::size_type pos;
        while ((pos = str.find_first_of(delim)) != std::string::npos) {
            if (split && pos == 0) {
                tokens_.push_back(std::string());
            } else if (pos > 0) {
                tokens_.push_back(str.substr(0, pos));
            }
            ++pos;
            if (!split && !str.empty()) {
                for (; delim.find(str[pos]) != std::string::npos; ++pos) { }
            }
            str = str.substr(pos);
        }
        if (split || !str.empty()) {
            tokens_.push_back(str);
        }
    }

    StringTokeniser(const StringTokeniser& rhs)
    {
        *this = rhs;
    }

    virtual ~StringTokeniser()
    { }

    iterator begin()
    {
        return tokens_.begin();
    }

    iterator end()
    {
        return tokens_.end();
    }

    StringTokeniser& operator= (const StringTokeniser &rhs)
    {
        if ( &rhs != this ) {
            tokens_ = rhs.tokens_;
        }
        return *this;
    }

    const std::string& operator[] (int index)
    {
        return tokens_[index];
    }

    size_t size() const
    {
        return tokens_.size();
    }

    bool empty() const
    {
        return size() == 0;
    }

    size_t token_count()
    {
        return size();
    }

    bool has_more_tokens()
    {
        return (tokens_.size() > 0);
    }

    std::string next_token()
    {
        std::string tok = tokens_.front();
        tokens_.pop_front();
        return tok;
    }

    void stripAll()
    {
        for (iterator token = begin(); token != end(); ++token) {
            strip((*token));
        }
    }

private:
    std::deque<std::string> tokens_;
};


#endif //FRONTEND_STRINGTOKENISER_H
