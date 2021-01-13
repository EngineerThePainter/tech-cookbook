#ifndef TMPL_PARAM_REF_HPP
#define TMPL_PARAM_REF_HPP

#include <iostream>

namespace basics {

template<typename T>
void tmplParamIsReference(T) {
  std::cout << "T is reference: " << std::is_reference<T>() << std::endl;
}

} // basics

#endif