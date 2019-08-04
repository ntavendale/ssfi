#include <iostream>
#include <thread>
#include "utilities.h"
#include "fileprocessor.h"
#include "wordmap.h"
#include "threadidlist.h"

void print_usage();
//file processing function. will be run in it's own thread
void process_file(std::string fileName, word_map* wordMap, thread_id_list* threadIdList);
//Comparison function. Used for sorting results as a list.
bool compare_function(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second);

int main(int argc, char *argv[])
{
    char* path;
    int maxThreads = 1;

    if (2 == argc) {
        path = argv[1];
    }
    else if (4 == argc) {
        path = argv[3];
        char* pEnd;
        errno = 0;
        maxThreads = strtol(argv[2], &pEnd, 10);
        if (ERANGE == errno) {
            std::cout << "Error: invalid argument \"" << argv[2] <<"\"for number of worker threads" << std::endl;
            return 1;
        }
    } else {
        //must have 3 or 1 command line arguments after exe name
        print_usage();
        return 0;
    }

    //check filepath and workerThreads
    if ( !Utilities::directoryExists(path) ) {
        std::cout << "Error: directory " << path << " does not exist" << std::endl;
        return 1;
    } else if (!Utilities::directoryAccessible(path)) {
        std::cout << "Error: directory " << path << " is not accessible" << std::endl;
        return 1;
    } else if (0L == maxThreads) {
        std::cout << "Error: invalid argument \"" << argv[2] << "\" for number of worker threads" << std::endl;
    }

    std::cout << "Directory " << path << " exits and is accessible." << std::endl;
    std::cout << "Using "<< maxThreads << " worker thread(s)." << std::endl;

    //Now lets pull a list of files from the directory and it's sub directories
    std::vector<std::string> textFiles = Utilities::readDirectory(path);
    std::cout << "Found " << textFiles.size() << " text file(s)." << std::endl;

    word_map* wordMap = new word_map();
    thread_id_list* threadList = new thread_id_list();


    std::vector<std::string>::iterator fileNameIterator;
    for(fileNameIterator = textFiles.begin(); fileNameIterator != textFiles.end(); fileNameIterator++) {
        if (threadList->size() < maxThreads) {
            std::thread* newThread = new std::thread(process_file, *fileNameIterator, wordMap, threadList);
            threadList->insert(newThread->get_id(), newThread, true);
            std::cout << "Created thread " << newThread->get_id() << std::endl;
        }
        std::cout << threadList->size() << " threads running" <<std::endl;
        while (threadList->size() >= maxThreads) {
             threadList->purge();
        }
    }

    //keep purging until remaining threads done.
    while (0 != threadList->size()) {
        threadList->purge();
    }
    std::cout << "All threads ended" << std::endl;

    std::list<std::pair<std::string, int>> results = wordMap->get_list();

    delete wordMap;
    delete threadList;

    results.sort(compare_function);

    std::list<std::pair<std::string, int>>::iterator it;

    int writeCount = 0;
    for ( it = results.begin(); it != results.end(); it++ )
    {
        writeCount++;
        std::cout << it->first  // string (key)
                  << '\t'
                  << it->second   // string's value
                  << std::endl ;
        if (10 == writeCount) {
            break; //only write out top 10.
        }
    }

    return 0;
}

void print_usage()
{
    std::cout << "ssfi by Nigel Tavendale" << std::endl;
    std::cout << "usage: ssfi -t N <directory>" << std::endl;
    std::cout << "          N = number of worker threads (default 1)" << std::endl;
}

void process_file(std::string fileName, word_map* wordMap, thread_id_list* threadIdList)
{
    std::thread::id myId = std::this_thread::get_id();
    threadIdList->insert(myId, NULL, true);
    try
    {
        file_processor fp(fileName, wordMap);
        fp.process();
    }
    catch (...)
    {

    }
    std::cout << "Signal End For Thread thread " << myId << std::endl;
    threadIdList->end(myId);
}

bool compare_function(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second)
{
    //use greater than so they are in desceding order on printout
    return (first.second > second.second);
}
