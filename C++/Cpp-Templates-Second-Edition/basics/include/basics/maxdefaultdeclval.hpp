#ifndef MAX_DEFAULT_DECLVAL_HPP
#define MAX_DEFAULT_DECLVAL_HPP

#include <utility>

namespace basics {

template<typename T1, typename T2, typename RT = std::decay_t<decltype(true ? std::declval<T1>() : std::declval<T2>())>>
RT maxDefaultDeclval(T1 a, T2 b) {
  return b < a ? a : b;
}

} // basics

#endif