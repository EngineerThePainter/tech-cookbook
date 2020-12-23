#ifndef CREF_HPP
#define CREF_HPP

#include <functional>
#include <iostream>
#include <string>

namespace basics {

void printString(std::string const& s) {
  std::cout << s << std::endl;
}

template<typename T>
void printT(T arg) {
  /**
   * If we would try to cout arg here directly we could run into error when passing arg by std::cref,
   * as std::reference_wrapper does not have operator<< defined.
   */
  printString(arg); // might convert arg back to the std::string
}

} // basics

#endif