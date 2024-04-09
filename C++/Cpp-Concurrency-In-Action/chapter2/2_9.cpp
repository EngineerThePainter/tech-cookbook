#include <numeric>
#include <thread>
#include <vector>
#include <iterator>
#include <iostream>

/**
 * Naive version of concurrent use of std::accumulate
 */

template <typename Iterator, typename T>
struct AccumulateBlock
{
    void operator()(Iterator first, Iterator last, T &result)
    {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T pararellAccumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    if (length == 0)
    {
        return init;
    }
    unsigned const long min_elements_per_thread = 25;
    unsigned const long max_number_of_threads = (length + min_elements_per_thread - 1) / min_elements_per_thread;
    unsigned const long hardware_threads = std::thread::hardware_concurrency();
    std::cout << "Number of hardware threads " << hardware_threads << std::endl;
    unsigned const long number_of_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_number_of_threads);
    std::cout << "Threads used " << number_of_threads << std::endl;
    unsigned const long block_size = length / number_of_threads;

    std::vector<T> results(number_of_threads);
    std::vector<std::thread> threads(number_of_threads - 1);
    Iterator block_start = first;
    for (unsigned long i = 0; i < (number_of_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(AccumulateBlock<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    AccumulateBlock<Iterator, T>()(block_start, last, results[number_of_threads - 1]);
    for (auto &entry : threads)
    {
        entry.join();
    }
    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
    constexpr int number_of_elements = 500;
    std::vector<int> vec(number_of_elements);
    for (int i = 0; i < vec.size(); ++i)
    {
        vec[i] = i;
    }
    std::cout << pararellAccumulate<std::vector<int>::iterator, int>(vec.begin(), vec.end(), 0) << std::endl;
    return 0;
}