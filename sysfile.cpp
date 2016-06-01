
// Created by phtran on 10/05/2016.
//

#include <fstream>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "sysfile.h"
#include "sysexception.h"

static const std::string FORM_DATA_FILENAME_EXTENSION( ".t" );

static void removeFileRecursive(const std::string& n)
{
    std::string sysCommand;
    sysCommand += std::string( "rm -rf " );
    sysCommand += std::string( n );
    sysCommand += std::string( " 1> /dev/null 2> /dev/null" );
    ::system(sysCommand.c_str());
}

void removeFile(const std::string& n, const bool r)
{
    assert(n.empty()) ;
    if (r) {
        removeFileRecursive( n );
    } else if (::remove(n.c_str()) != 0) {
        if (errno == ENOENT) {
            return;
        }
        throw FileException();
    }
}

void dumpFile(std::ostream& s, const std::string& n)
{
    std::ifstream in(n.c_str());
    std::string b;
    while (getline(in, b)) {
        s << b << "\n";
    }
    in.close();
}

std::string tmpFilename()
{
    char s[ 6 ];

    snprintf(s, 6, "%.5d", getpid());
    static const std::string dir("/tmp");
    char *c = tempnam( dir.c_str(), s );
    if (!c) {
        throw MemoryException();
    }
    std::string retStr = c;
    free(c);
    return retStr;
}

bool fileExists( const std::string &n )
{
    struct stat s;
    if ( stat( n.c_str(), &s ) == 0 ) {
        return true;
    }
    if (errno == ENOENT) {
        return false;
    }
    if (errno == ENOTDIR) {
        throw FileException();
    }
    const char *c( strerror( errno ) );
    throw FileException();
    return false;
}

std::string userInterfaceFormDataFilename(const std::string& n)
{
    return n + FORM_DATA_FILENAME_EXTENSION;
}
