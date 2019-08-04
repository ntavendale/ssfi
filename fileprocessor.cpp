#include "fileprocessor.h"

file_processor::file_processor(std::string filePath, word_map* wordMap)
{
    _filePath = filePath;
    _wordMap = wordMap;
}

 void file_processor::process()
 {
     std::map<std::string, int> localWordMap;
     std::ifstream fileStream;
     fileStream.open (_filePath);
     std::string word;
     char x ;
     word.clear();

     while (!fileStream.eof()) {
         x = fileStream.get();

         //instructions specifically stated
         //Words are delimited by any character other than A-Z, a-z, or 0-9.
         //
         //So "hello?world" will be split into "hello" & "world" and listed separately in map
         while ((( 'A' <=  x) && ( x <= 'Z' )) || (( 'a' <=  x) && ( x <= 'z' )) || (( 'a' <=  x) && ( x <= 'z' )) ) {
             word = word + x;
             x = fileStream.get();
         }

         if ("" == word) {
             continue;
         }

         boost::algorithm::to_lower(word);
         if (0 == localWordMap.count(word) ) {
             localWordMap.insert(std::pair<std::string, int>(word, 1));
         }
         else {
             localWordMap[word] += 1;
         }
         word.clear();

     }
     fileStream.close();

     _wordMap->insert(localWordMap);


 }
