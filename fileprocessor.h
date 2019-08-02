#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
#include <map>

class FileProcessor
{
public:
    FileProcessor(string filePath);
    void LoadMap();
    std::map<std::string, int> wordMap;
private:
    std::string _filePath;
};

#endif // FILEPROCESSOR_H
