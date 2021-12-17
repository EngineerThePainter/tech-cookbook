#ifndef TYPELIST_TYPELISTFRONT_HPP
#define TYPELIST_TYPELISTFRONT_HPP

#include "typelist.hpp"

namespace typelist {

template<typename List>
class FrontT;

template<typename Head, typename... Tail>
class FrontT<TypeList<Head, Tail...> > {
  public:
  using Type = Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;

} // namespace typelist

#endif // TYPELIST_TYPELISTFRONT_HPP