#include "utilities.h"


bool Utilities::directoryExists(char* directroyPath)
{
    DIR* dir = opendir(directroyPath);
    if (dir) {
        /* Directory exists. */
        closedir(dir);
        return true;
    }
    else if (ENOENT == errno) {
        return false;
    }
}

bool Utilities::directoryAccessible(char* directroyPath)
{
    DIR* dir = opendir(directroyPath);
    if (dir) {
        /* Directory exists. */
        closedir(dir);
        return true;
    }
    else if (ENOENT != errno) {
        return false;
    }
}

std::vector<std::string> Utilities::readDirectory(char* directroyPath)
{

    std::vector<std::string> fileList;
    if (!(directroyPath)) {
        return fileList;
    }

    std::string dir(directroyPath);
    if ( (!filesys::exists(dir)) || (!filesys::is_directory(dir)) ) {
        return fileList;
    }

    // Create a Recursive Directory Iterator object and points to the starting of directory
    filesys::recursive_directory_iterator iter(dir);

    // Create a Recursive Directory Iterator object pointing to end.
    filesys::recursive_directory_iterator end;

    while (iter != end) {
        if ((!filesys::is_directory(iter->path())) && (".txt" == iter->path().extension().string() )) {
            // it's not a directory and has .txt extension
            fileList.push_back(iter->path().string());
        }
        boost::system::error_code ec;
        // Increment the iterator to point to next entry in recursive iteration
        iter.increment(ec);
        if (ec) {
            std::cout << "Error While Accessing " << iter->path().string() << ": "<< ec.message();
        }
    }
}
