#ifndef TYPELIST_ADDCONST_HPP
#define TYPELIST_ADDCONST_HPP

namespace typelist {

template<typename T>
struct AddConstT {
  using Type = T const;
};

template<typename T>
using AddConst = typename AddConstT<T>::Type;

} // namespace typelist

#endif // TYPELIST_ADDCONST_HPP