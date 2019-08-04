#include "threadidlist.h"

thread_id_list::thread_id_list()
{

}

void thread_id_list::insert(std::thread::id threadId, std::thread* thread, bool running)
{
    std::lock_guard<std::mutex> lck(_mtx);
    if (0 == _ids.count(threadId)) {
        if (thread) {
            std::cout << "Inserting thread " << threadId << std::endl;
        }
        else {
            std::cout << "Inserting NULL thread " << threadId << std::endl;
        }
        _ids.insert( std::pair<std::thread::id, std::pair<std::thread*, bool>>(threadId, std::pair<std::thread*, bool>(thread, running)) );
    }
    else {
        if (!_ids[threadId].first) {
            _ids[threadId].first = thread;
        }
        _ids[threadId].second = (_ids[threadId].second & running); //if it's false, it stays false
        std::cout << "Updated thread " << threadId << std::endl;
    }
}

void thread_id_list::end(std::thread::id threadId)
{
    std::lock_guard<std::mutex> lck(_mtx);
    if (0 != _ids.count(threadId)) {
        _ids[threadId].second = false;
        std::cout << "_ids[" << threadId << "].second = " << _ids[threadId].second << std::endl;
    }

}

int thread_id_list::purge()
{
    std::lock_guard<std::mutex> lck(_mtx);
    std::map<std::thread::id, std::pair<std::thread*, bool>>::iterator it;

    std::list<std::thread::id> purgeList;

    int purged = 0;
    for ( it = _ids.begin(); it != _ids.end(); it++) {
        if (!it->second.second) {
            it->second.first->join();
            //it->second.first->teminate();
            delete it->second.first;
            purgeList.push_back(it->first);
            purged++;
        }
    }

    std::list<std::thread::id>::iterator purgeIterator;
    for (purgeIterator = purgeList.begin(); purgeIterator != purgeList.end(); purgeIterator++) {
        _ids.erase(*purgeIterator);
    }
    return purged;
}

int thread_id_list::size()
{
    std::lock_guard<std::mutex> lck(_mtx);
    return _ids.size();
}
