#ifndef TYPELIST_TYPELISTPOPFRONT_HPP
#define TYPELIST_TYPELISTPOPFRONT_HPP

#include "typelist.hpp"

namespace typelist {

template<typename List>
class PopFrontT;

template<typename Head, typename... Tail>
class PopFrontT<TypeList<Head, Tail...> > {
  public:
  using Type = TypeList<Tail...>;
};

template<typename List>
using PopFront = typename PopFrontT<List>::Type;

} // namespace typelist

#endif // TYPELIST_TYPELISTPOPFRONT_HPP