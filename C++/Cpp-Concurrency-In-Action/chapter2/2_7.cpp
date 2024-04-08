#include <thread>
#include <exception>

#include "worker.hpp"

/**
 * Joining Thead - in the book it has suggested class implementation. But I'm using
 * The std::jthread from C++20
 */

void doSomething()
{
}

int main()
{
    int local_state = 42;
    std::jthread joining_thread{Worker(local_state)};

    doSomething();
    return 0;
}