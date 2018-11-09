/*
Question4:
//
 An example using my own implementation of lock_guard to protect safe_increment()
Reference: check my lock_guard implementation on lock_guard.h

*/

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <iostream>
#include <map>


#include "lock_guard.h"

using namespace std;
using namespace my_lock_guard;

//global variable g_i to be incremented
int g_i = 0;
std::mutex g_i_mutex;  // protects g_i
/*
Function increment common to all thread
*/
void safe_increment()
{   //lock mutex
    my_lock_guard::Lock_guard<std::mutex> lock(g_i_mutex);
    g_i++;

    std::cout << "Thread"<<std::this_thread::get_id() << ": " << g_i << '\n';

    // g_i_mutex is automatically released when lock
    // goes out of scope
}

int main()
{
    std::cout << "main: " << g_i << '\n';

    std::thread t1(safe_increment);
    std::thread t2(safe_increment);
    std::thread t3(safe_increment);
    t1.join();
    t2.join();
    t3.join();
    std::cout << "main: " << "g_i=" << g_i<<'\n';
}
