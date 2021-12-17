#ifndef TYPELIST_LARGESTTYPE_HPP
#define TYPELIST_LARGESTTYPE_HPP

#include "typelist.hpp"
#include "typelist_front.hpp"
#include "typelist_is_empty.hpp"
#include "typelist_pop_front.hpp"

#include <traits/ifthenelse.hpp>

namespace typelist {

template<typename List, bool Empty = IsEmpty<List>::value>
class LargestTypeT;

// recursive case
template<typename List>
class LargestTypeT<List, false>
{
  private:
  using First = Front<List>;
  using Rest = typename LargestTypeT<PopFront<List>>::Type;

  public:
  using Type = traits::IfThenElse<(sizeof(First) >= sizeof(Rest)), First, Rest>;
};

// basic case
template<typename List>
class LargestTypeT<List, true>
{
  public:
  using Type = char;
};

template<typename List>
using LargestType = typename LargestTypeT<List>::Type;

} // namespace typelist

#endif // TYPELIST_LARGESTTYPE_HPP