#ifndef TYPELIST_TRANSFORM_HPP
#define TYPELIST_TRANSFORM_HPP

#include "typelist_is_empty.hpp"
#include "typelist_push_front.hpp"
#include "typelist_pop_front.hpp"
#include "typelist_front.hpp"

namespace typelist {

template<typename List, template<typename T> class MetaFun, bool Empty = IsEmpty<List>::value>
class TransformT;

// recursive case:
template<typename List, template<typename T> class MetaFun>
class TransformT<List, MetaFun, false> : public PushFrontT<typename TransformT<PopFront<List>, MetaFun>::Type, typename MetaFun<Front<List>>::Type> {};

// basis case:
template<typename List, template<typename T> class MetaFun>
class TransformT<List, MetaFun, true> {
public:
using Type = List;
};

template<typename List, template<typename T> class MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;

} // namespace typelist

#endif // TYPELIST_TRANSFORM_HPP