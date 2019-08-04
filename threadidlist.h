#ifndef THREADIDLIST_H
#define THREADIDLIST_H

#include <iostream>
#include <thread>
#include <map>
#include <list>
#include <mutex>

class thread_id_list
{
public:
    thread_id_list();
    void insert(std::thread::id threadId, std::thread* thread, bool running);
    void end(std::thread::id threadId);
    int purge();
    int size();
private:
    //we'll use a map and use the thread id as the key.
    //this way we get methods to test for key exists etc
    //that we don't get with vectors or lists
    std::map<std::thread::id, std::pair<std::thread*, bool>> _ids;
    std::mutex _mtx;
};

#endif // THREADIDLIST_H
