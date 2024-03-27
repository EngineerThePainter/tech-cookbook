#include <iostream>
#include <thread>

/**
 In this code we are passing some local value to a thread
 that is later on detached, which leads to undefined behaviour - due to detach the
 main thread ending will not terminate the my_thread.

 My thread will keep work on some piece of data that was already removed.
*/

struct Worker
{
    int &i_;
    Worker(int &i) : i_(i)
    {
    }

    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            std::cout << i_ << std::endl;
        }
    }
};

int main()
{
    int some_local_value = 42;
    Worker worker(some_local_value);
    std::thread my_thread(worker);
    my_thread.detach();
    return 0;
}