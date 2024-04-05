#include <thread>
#include <iostream>

#include "worker.hpp"

/*Waiting till the end of thread work*/

int main()
{
    int some_local_value = 42;
    int other_value = 0;
    Worker worker(some_local_value);
    std::thread my_thread(worker);
    try
    {
        for (int i = 0; i < 1000000; ++i)
        {
            ++other_value;
        }
    }
    catch (std::exception &e)
    {
        my_thread.join();
        throw;
    }
    my_thread.join();

    return 0;
}