#include <thread>

#include "worker.hpp"

/**
 * Waiting for thread to end, but using RAII for it
 */

class ThreadGuard
{
    std::thread &t_;

public:
    explicit ThreadGuard(std::thread &t) : t_(t)
    {
    }

    ~ThreadGuard()
    {
        if (t_.joinable())
        {
            t_.join();
        }
    }

    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard(const ThreadGuard &&) = delete;
};

int main()
{
    int local_state = 42;
    Worker worker(local_state);
    std::thread my_thread(worker);
    ThreadGuard guard(my_thread);
    int other_value = 0;
    for (int i = 0; i < 1000000; ++i)
    {
        ++other_value;
    }
    return 0;
}