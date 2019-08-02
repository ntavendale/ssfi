#ifndef UTILITIES_H
#define UTILITIES_H


#include <sys/types.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <errno.h>

namespace filesys = boost::filesystem;

class Utilities {
public:
    static bool directoryExists(char* directroyPath);
    static bool directoryAccessible(char* directroyPath);
    static std::vector<std::string> readDirectory(char* directroyPath);
private:

};

#endif // UTILITIES_H
