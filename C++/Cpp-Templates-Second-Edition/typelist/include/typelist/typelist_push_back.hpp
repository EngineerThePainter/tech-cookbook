#ifndef TYPELIST_TYPELISTPUSHBACK_HPP
#define TYPELIST_TYPELISTPUSHBACK_HPP

#include "typelist.hpp"
#include "typelist_is_empty.hpp"
#include "typelist_front.hpp"
#include "typelist_pop_front.hpp"
#include "typelist_push_front.hpp"

namespace typelist {

template<typename List, typename NewElement, bool = IsEmpty<List>::value>
class PushBackRecT;

// recursive case
template<typename List, typename NewElement>
class PushBackRecT<List, NewElement, false> {

  using Head = Front<List>;
  using Tail = PopFront<List>;
  using NewTail = typename PushBackRecT<Tail, NewElement>::Type;

  public:
  using Type = PushFront<NewTail, Head>;
};

// basis case
template<typename List, typename NewElement>
class PushBackRecT<List, NewElement, true> {
  public:
  using Type = PushFront<List, NewElement>;
};

// generic push-back operation
template<typename List, typename NewElement>
class PushBackT : public PushBackRecT<List, NewElement> {};

template<typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;

} // namespace typelist

#endif // TYPELIST_TYPELISTPUSHBACK_HPP