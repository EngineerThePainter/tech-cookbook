#ifndef TYPELIST_TYPELISTPUSHBACK_HPP
#define TYPELIST_TYPELISTPUSHBACK_HPP

#include "typelist.hpp"

namespace typelist {

template<typename List, typename NewElement>
class PushBackT;

template<typename... Elements, typename NewElement>
class PushBackT<TypeList<Elements...>, NewElement> {
  public:
  using Type = TypeList<Elements..., NewElement>;
};

template<typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;

} // namespace typelist

#endif // TYPELIST_TYPELISTPUSHBACK_HPP