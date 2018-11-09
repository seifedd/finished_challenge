/*
Another example of using conditional
 c++11 std::condition_var

 */

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include "lock_guard.h"

bool is_ready(false);
std::mutex m;
std::condition_variable cv;

void
test()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"Hello::1\n";
    std::unique_lock<std::mutex> lk(m);
    //my_lock_guard::Lock_guard<std::mutex> lock(m);
    std::cout<<"Hello::2\n";
    is_ready = true;
    cv.notify_one();
}

int
main()
{
    std::thread th1(test);
    std::thread th2(test);
    std::thread th3(test);
    std::thread th4(test);
    std::unique_lock<std::mutex> lk(m);
    while (!is_ready)
    {
        cv.wait(lk);
        if (is_ready)
            std::cout << "Spurious wake up!\n";
    }

    th1.join();
    th2.join();
    th3.join();
    th4.join();

}
