//
// Created by phtran on 10/05/2016.
//

#ifndef FRONTEND_SYSFILE_H
#define FRONTEND_SYSFILE_H

#include <string>

void removeFile(const std::string&, const bool = false);
void dumpFile(std::ostream& s, const std::string& n);
std::string tmpFilename();
bool fileExists(const std::string&);
std::string userInterfaceFormDataFilename(const std::string&);


#endif //FRONTEND_SYSFILE_H
