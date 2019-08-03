#ifndef WORDMAP_H
#define WORDMAP_H

#include <map>
#include <thread>
#include <mutex>

//thread safe access map of words and counts since instructions
//said to get top ten words over all the files, not top ten per file.
class WordMap
{
public:
    WordMap();
    void AddWord(std::string word, int count);
    void AddMap(std::map<std::string, int> inputMap);
    std::map<std::string, int> GetMap();
private:
    std::map<std::string, int> _wordMap;
    std::mutex _mtx;
};

#endif // WORDMAP_H
