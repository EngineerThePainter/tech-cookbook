#ifndef TYPELIST_TYPELISTISEMPTY_HPP
#define TYPELIST_TYPELISTISEMPTY_HPP

#include "typelist.hpp"

namespace typelist {

template<typename List>
class IsEmpty
{
  public:
  static constexpr bool value = false;
};

template<>
class IsEmpty<TypeList<>>{
  public:
  static constexpr bool value = true;
};

} // namespace typelist

#endif // TYPELIST_TYPELISTISEMPTY_HPP