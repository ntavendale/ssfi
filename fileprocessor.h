#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "wordmap.h"

class FileProcessor
{
public:
    FileProcessor(std::string filePath, WordMap* wordMap);
    void ProcessFile();
private:
    WordMap* _wordMap;
    std::string _filePath;
};

#endif // FILEPROCESSOR_H
