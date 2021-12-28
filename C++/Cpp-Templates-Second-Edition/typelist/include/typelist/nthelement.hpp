#ifndef TYPELIST_NTHELEMENT_HPP
#define TYPELIST_NTHELEMENT_HPP

#include "typelist_pop_front.hpp"
#include "typelist_front.hpp"

namespace typelist {

// recursive
template<typename List, unsigned N>
class NthElementT: public NthElementT<PopFront<List>, N-1>
{};

// basic
template<typename List>
class NthElementT<List, 0> : public FrontT<List>
{};

template<typename List, unsigned N>
using NthElement = typename NthElementT<List, N>::Type;

} // namespace typelist

#endif // TYPELIST_NTHELEMENT_HPP