#ifndef TYPELIST_TYPELISTPUSHFRONT_HPP
#define TYPELIST_TYPELISTPUSHFRONT_HPP

#include "typelist.hpp"

namespace typelist {

template<typename List, typename NewElement>
class PushFrontT;

template<typename... Elements, typename NewElement>
class PushFrontT<TypeList<Elements...>, NewElement> {
  public:
  using Type = TypeList<NewElement, Elements...>;
};

template<typename List, typename NewElement>
using PushFront = typename PushFrontT<List, NewElement>::Type;

} // namespace typelist

#endif // TYPELIST_TYPELISTPUSHFRONT_HPP