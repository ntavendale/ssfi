#include <iostream>
#include "utilities.h"
#include "fileprocessor.h"
#include "wordmap.h"

void print_usage();

int main(int argc, char *argv[])
{
    char* path;
    int workerThreads = 1;

    if (2 == argc) {
        path = argv[1];
    }
    else if (4 == argc) {
        path = argv[3];
        char* pEnd;
        errno = 0;
        workerThreads = strtol(argv[2], &pEnd, 10);
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
    } else if (0L == workerThreads) {
        std::cout << "Error: invalid argument \"" << argv[2] << "\" for number of worker threads" << std::endl;
    }

    std::cout << "Directory " << path << " exits and is accessible." << std::endl;
    std::cout << "Using "<< workerThreads << " worker thread(s)." << std::endl;

    //Now lets pull a list of files from the directory and it's sub directories
    std::vector<std::string> textFiles = Utilities::readDirectory(path);
    std::cout << "Found " << textFiles.size() << " text file(s)." << std::endl;

    WordMap* wordMap = new WordMap();

    FileProcessor fp("/home/ntavendale/testDoc/testdoc.txt", wordMap);
    fp.ProcessFile();


    std::map<std::string, int> results = wordMap->GetMap();
    delete wordMap;

    std::map<std::string, int>::iterator it;

    for ( it = results.begin(); it != results.end(); it++ )
    {
        std::cout << it->first  // string (key)
                  << ':'
                  << it->second   // string's value
                  << std::endl ;
    }

    return 0;
}

void print_usage()
{
    std::cout << "ssfi by Nigel Tavendale" << std::endl;
    std::cout << "usage: ssfi -t N <directory>" << std::endl;
    std::cout << "          N = number of worker threads (default 1)" << std::endl;
}
