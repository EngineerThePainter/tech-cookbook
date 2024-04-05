#include <thread>

#include "worker.hpp"

/**
 In this code we are passing some local value to a thread
 that is later on detached, which leads to undefined behaviour - due to detach the
 main thread ending will not terminate the my_thread.

 My thread will keep work on some piece of data that was already removed.
*/

int main()
{
    int some_local_value = 42;
    Worker worker(some_local_value);
    std::thread my_thread(worker);
    my_thread.detach();

    return 0;
}