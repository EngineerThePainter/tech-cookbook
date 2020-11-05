#ifndef MAX_HPP
#define MAX_HPP

namespace basics {

template<typename T>
T max(T a, T b) {
    return b < a ? a : b;
}

}

#endif