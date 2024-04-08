#include <thread>
#include <exception>

#include "worker.hpp"

/**
 * Waiting for thread to end, but using RAII for it
 */

class ScopedThread
{
    std::thread t_;

public:
    explicit ScopedThread(std::thread t) : t_(std::move(t))
    {
        if (!t_.joinable())
        {
            throw std::logic_error("No thread");
        }
    }

    ~ScopedThread()
    {
        t_.join();
    }

    ScopedThread(const ScopedThread &) = delete;
    ScopedThread &operator=(const ScopedThread &) = delete;
};

void doSomething()
{
}

int main()
{
    int local_state = 42;
    ScopedThread t{std::thread(Worker(local_state))};
    doSomething();
    return 0;
}