#include <list>
#include <thread>
#include <mutex>
#include <iostream>
#include <algorithm>

class ListWrapper
{
public:
    void addToList(const int value)
    {
        std::lock_guard lock(mutex_);
        std::cout << "Add " << value << std::endl;
        list_.push_back(value);
    }
    bool listContains(const int value)
    {
        std::lock_guard lock(mutex_);
        auto found = std::find(list_.begin(), list_.end(), value);
        return found != list_.end();
    }

private:
    std::list<int> list_;
    std::mutex mutex_;
};

int main()
{
    ListWrapper wrapper;
    auto t1 = [&wrapper]()
    {
        for (int i = 0; i < 10000; ++i)
        {
            wrapper.addToList(i);
        }
    };

    auto t2 = [&wrapper]()
    {
        for (int i = 10000; i < 20000; ++i)
        {
            wrapper.addToList(i);
        }
    };
    std::thread adder1(t1);
    std::thread adder2(t2);
    adder1.join();
    adder2.join();
    for (int i = 0; i < 20000; ++i)
    {
        if (!wrapper.listContains(i))
        {
            std::cout << "NO " << i << " in list!!!" << std::endl;
            break;
        }
    }
    return 0;
}
