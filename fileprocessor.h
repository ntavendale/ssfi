#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "wordmap.h"

class file_processor
{
public:
    file_processor(std::string filePath, word_map* wordMap);
    void process();
private:
    word_map* _wordMap;
    std::string _filePath;
};

#endif // FILEPROCESSOR_H
