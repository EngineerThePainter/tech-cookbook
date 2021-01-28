#ifndef ADL_HPP
#define ADL_HPP

#include <iostream>

namespace details {

namespace X {
    template<typename T> void f(T);
}

namespace N {
    using namespace X;
    enum E {e1};
    void f(E) {
        std::cout << "N::f(N::E) called" << std::endl;
    }
}

} // details

void f(int) {
    std::cout << "::f(int) called" << std::endl;
}

#endif