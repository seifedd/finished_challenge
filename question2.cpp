/*question2
Implement c++11 threading example

      2-3 threads running
*/

#include <iostream>
#include <thread>

using namespace std;


// A callable object used to create th2
class thread_obj {
public:
    void operator()(int x)
    {


        for(int i=0;i<x;i++){
            cout <<"thread 1 ...running\n";

        }
    }
};

//A callable function used to create th1
void f(int Z)
{


         for(int i=0;i<Z;i++){
             cout <<"thread 2 ...running\n";

         }

}


int main()
{
    cout << "main.. "<<endl;

    // Using function pointer as callable
    thread th1(f, 3);

    // Using function object as callable
    thread th2(thread_obj(), 3);

    // Using a Lambda Expression
    auto lamda = [](int x) {
        for (int i = 0; i < x; i++)
            cout <<"thread 3...running\n";

    };

    // lamda expression as callable
    thread th3(lamda, 3);

    // Wait for the threads to finish
    // Wait for thread t1 to finish
    th1.join();

    // Wait for thread t2 to finish
    th2.join();

    // Wait for thread t3 to finish
    th3.join();

    return 0;
}
