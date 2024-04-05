#include <iostream>

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
