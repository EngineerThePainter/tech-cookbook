#ifndef TYPELIST_TYPELISTREVERSE_HPP
#define TYPELIST_TYPELISTREVERSE_HPP

#include "typelist.hpp"
#include "typelist_is_empty.hpp"
#include "typelist_pop_front.hpp"
#include "typelist_push_back.hpp"
#include "typelist_front.hpp"

namespace typelist {

template<typename List, bool Empty = IsEmpty<List>::value>
class ReverseT;

template<typename List>
using Reverse = typename ReverseT<List>::Type;

// recursive case:
template<typename List>
class ReverseT<List, false> : public PushBackT<Reverse<PopFront<List>>, Front<List>> {};

// basis case:
template<typename List>
class ReverseT<List, true> {
  public:
  using Type = List;
};

} // namespace typelist

#endif // TYPELIST_TYPELISTREVERSE_HPP