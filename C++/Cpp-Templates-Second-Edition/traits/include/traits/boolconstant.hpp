#ifndef BOOL_CONSTANT_HPP
#define BOOL_CONSTANT_HPP

namespace traits {

template<bool val>
struct BoolConstant
{
  using Type = BoolConstant<val>;
  static constexpr bool value = val;
};

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

}

#endif // BOOL_CONSTANT_HPP