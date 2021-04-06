#ifndef TMPL_CONSTR_HPP
#define TMPL_CONSTR_HPP

#include <iostream>
#include <string>

namespace details
{

class C {
  public:
  C() = default;
  
  C (C const&) {
    std::cout << "Copy constructor" << std::endl;
  }

  C (C &&) {
    std::cout << "Move constructor" << std::endl;
  }

  template<typename T>
  C(T&&) {
    std::cout << "Template constructor" << std::endl;
  }
};

} // namespace details

#endif // TMPL_CONSTR_HPP