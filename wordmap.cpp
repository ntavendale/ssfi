#include "wordmap.h"

word_map::word_map()
{

}

//Add a string and int
void word_map::insert(std::string word, int count)
{
    //no try-finally in C++ so use a clocal lock_guard to guarantee
    //unlock on exception
    std::lock_guard<std::mutex> lck(_mtx);
    if (0 == _wordMap.count(word) ) {
        _wordMap.insert(std::pair<std::string, int>(word, count));
    }
    else {
        _wordMap[word] += count;
    }

}

//On second though, just add content of an entire map
void word_map::insert(std::map<std::string, int> inputMap)
{
    std::lock_guard<std::mutex> lck(_mtx);

    std::map<std::string, int>::iterator it;

    for ( it = inputMap.begin(); it != inputMap.end(); it++ )
    {
        if (0 == _wordMap.count(it->first) ) {
            _wordMap.insert(std::pair<std::string, int>(it->first, it->second));
        }
        else {
            _wordMap[it->first] += it->second;
        }

    }
}

std::list<std::pair<std::string, int>> word_map::get_list()
{
    std::lock_guard<std::mutex> lck(_mtx);

    std::list<std::pair<std::string, int>> result;

    std::map<std::string, int>::iterator it;

    for ( it = _wordMap.begin(); it != _wordMap.end(); it++ )
    {
        result.push_back(std::pair<std::string, int>(it->first, it->second));
    }

    return result;
}
