/*question3
 c++11 std::condition_var
 */

// condition_variable example
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdlib.h>
#include <random>
using namespace std;



mutex mtx;
condition_variable cv;
bool ready = false;
int g=0;

void increment_variable_g (int id) {
  while(g<1000000000){
        unique_lock<std::mutex> lck(mtx);

  while (!ready) {
         cout<<"thread" <<id<<": starting, waiting.\n";
         cv.wait(lck);

  }

  cout<<"thread" <<id<<": signal received, doing the work.\n";

  g++;
  cout << "thread" <<id<<": done with work, signal next thread "<<endl;

  cv.notify_one();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
}

int main ()
{


  thread th1 = thread(increment_variable_g,1);
  thread th2 = thread(increment_variable_g,2);
  thread th3 = thread(increment_variable_g,3);


  cout << "main: starting all threads \n";
/*for (int i=0; i<3; i++)
    threads[i] = std::thread(print_id,i);
  */

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  //unique_lock<std::mutex> lck(mtx);
  cout << "main: starting thread \n";
  ready = true;
  cv.notify_one();

  //for (auto& th : threads)
  th3.join();
  th2.join();
  th1.join();

  return 0;
}


