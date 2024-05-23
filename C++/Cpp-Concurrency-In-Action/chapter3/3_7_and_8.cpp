/**
 * This file contains hierarchical mutex that keeps the hierarchy of locked mutexes, so it should avoid deadlocks
 */

#include <iostream>
#include <mutex>
#include <limits>
#include <thread>

namespace hm
{
    class HierarchicalMutex
    {
    public:
        explicit HierarchicalMutex(unsigned long value) : hierarchy_value_(value),
                                                          previous_hierarchy_value_(0) {}

        void lock()
        {
            checkForHierarchyViolation();
            internal_mutex_.lock();
            updateHierarchyValue();
        }

        void unlock()
        {
            if (this_thread_hierarchy_value_ != hierarchy_value_)
            {
                throw std::logic_error("Hierarchy of mutexes is violated");
            }
            this_thread_hierarchy_value_ = previous_hierarchy_value_;
            internal_mutex_.unlock();
        }

        bool tryLock()
        {
            checkForHierarchyViolation();
            if (!internal_mutex_.try_lock())
            {
                return false;
            }
            updateHierarchyValue();
            return true;
        }

    private:
        void checkForHierarchyViolation()
        {
            if (this_thread_hierarchy_value_ <= hierarchy_value_)
            {
                throw std::logic_error("Hierarchy of mutexes is violated");
            }
        }

        void updateHierarchyValue()
        {
            previous_hierarchy_value_ = this_thread_hierarchy_value_;
            this_thread_hierarchy_value_ = hierarchy_value_;
        }

    private:
        std::mutex internal_mutex_;
        const unsigned long hierarchy_value_;
        unsigned long previous_hierarchy_value_;

        static thread_local unsigned long this_thread_hierarchy_value_;
    };
}
thread_local unsigned long hm::HierarchicalMutex::this_thread_hierarchy_value_(std::numeric_limits<unsigned long>::max());

hm::HierarchicalMutex high_level_mutex(10000);
hm::HierarchicalMutex low_level_mutex(5000);
hm::HierarchicalMutex other_mutex(6000);

int doLowLevelStuff()
{
    int val = 0;
    for (int i = 0; i < 100000; ++i)
    {
        ++val;
    }
    return val;
}

int lowLevelFunc()
{
    std::lock_guard<hm::HierarchicalMutex> lk(low_level_mutex);
    return doLowLevelStuff();
}

void doHighLevelStuff(int param)
{
    if (param > 50)
    {
        for (int i = 0; i < 10; ++i)
        {
            printf("Param %d\n", param);
        }
    }
}

void highLevelFunc()
{
    std::lock_guard<hm::HierarchicalMutex> lk(high_level_mutex);
    doHighLevelStuff(lowLevelFunc());
}

void threadA()
{
    highLevelFunc();
}

void doOtherStuff()
{
    int v;
    for (int i = 0; i < 100000; ++i)
    {
        if (i % 50 == 0)
        {
            v += i;
        }
    }
    printf("Other stuff %d\n", v);
}

void otherStuffFunc()
{
    highLevelFunc();
    doOtherStuff();
}

void threadB()
{
    /**
     * This thread violates the hierarchy of mutexes, by first locking the other_mutex
     * with a value of 6000 and then trying to lock a mutex with a higher value.
     */
    std::lock_guard<hm::HierarchicalMutex> lk(other_mutex);
    otherStuffFunc();
}

int main()
{
    std::thread a(threadA);
    // std::thread b(threadB);

    a.join();
    // b.join();
    return 0;
}