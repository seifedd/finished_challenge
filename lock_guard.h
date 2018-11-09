#ifndef LOCK_GUARD_H_INCLUDED
#define LOCK_GUARD_H_INCLUDED

#include <iostream>
#include <thread>
#include <mutex>

namespace my_lock_guard{

template<class T>
class Lock_guard{


public:
    explicit Lock_guard(std::mutex& lock): m_lock(lock) {
        //acquire the lock
       m_lock.lock();
    }
    ~Lock_guard() { m_lock.unlock(); }

private:
    std::mutex&  m_lock;


};

}
#endif // LOCK_GUARD_H_INCLUDED
