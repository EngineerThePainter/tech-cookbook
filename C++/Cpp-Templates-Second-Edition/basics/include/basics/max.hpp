#ifndef MAX_HPP
#define MAX_HPP

namespace chapter {
namespace basics {

template<typename T>
T max(T a, T b) {
    return b < a ? a : b;
}

} // basics
} // chapter

#endif