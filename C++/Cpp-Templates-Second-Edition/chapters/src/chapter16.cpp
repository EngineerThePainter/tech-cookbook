#include "chapters/chapter16.hpp"

#include <iostream>

#include <common/common_prints.hpp>
#include <details/quickExchange.hpp>

namespace chapters
{

    namespace
    {

        struct S
        {
            int x;
        } s1, s2;

        void distinguish()
        {
            common::printTitle("Same functionality, different memory behavior");

            common::emptyLine();
        }
    }

} // namespace

void runChapter16()
{
    common::printTitle("C++ Templates Chapter 16");
    common::emptyLine();
}
}