#ifndef TRAITS_IF_THEN_ELSE_HPP
#define TRAITS_IF_THEN_ELSE_HPP

namespace traits {

/*  Primary template: yield the second argument
    by default and rely on a partial specialization
    to yield the third argument if COND is false. */
template<bool COND, typename TrueType, typename FalseType>
struct IfThenElseT {
  using Type = TrueType;
};

// Partial specialization: false yields third argument
template<typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType> {
  using Type = FalseType;
};

template<bool COND, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<COND, TrueType, FalseType>::Type;

} // namespace traits

#endif // TRAITS_IF_THEN_ELSE_HPP