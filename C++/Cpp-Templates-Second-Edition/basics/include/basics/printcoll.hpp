#ifndef PRINTCOLL_HPP
#define PRINTCOLL_HPP

#include <iostream>

namespace basics {

template<typename T>
void printcoll (T const& coll) {
    typename T::const_iterator pos; // to iterate over coll
    typename T::const_iterator end(coll.end());
    for (pos = coll.begin(); pos != end; ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
}

/**
 * This is a value initialization - we are ensuring that 'variable' constructor is called, 
 * or it's zero initialized. 
 */ 
template<typename T>
void valueInitialization() {
    T variable{};
}

template<typename T>
T valueInitialization(T x = T{}) {
    return x;   
}

} // basics

#endif