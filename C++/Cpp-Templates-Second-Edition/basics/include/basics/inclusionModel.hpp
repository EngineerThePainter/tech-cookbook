#ifndef INCLUSION_MODEL_HPP
#define INCLUSION_MODEL_HPP

#include <iostream>
#include <typeinfo>

namespace basics {

/**
 * Since we are not in later C++ standard than 17 here, to provide a definition for 
 * template we need to use inclusion model, which means both declaration and definition of the 
 * template in header file. If the definition would go to the .cpp file the compilation would be 
 * successfull BUT the linker would not find the template definition and it would raise an error.
 */

// template declaration
template<typename T>
void printTypeof(T const&);

// template definition
template<typename T>
void printTypeof(T const& x) {
    std::cout << typeid(x).name() << std::endl;
}

} // basics

#endif