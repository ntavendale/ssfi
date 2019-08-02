#include "fileprocessor.h"

FileProcessor::FileProcessor(string filePath)
{
    _filePath = filePath;
}

 void FileProcessor::LoadMap()
 {
     std::ifstream fileStream;
     Stream.open (_filePath);
 }
