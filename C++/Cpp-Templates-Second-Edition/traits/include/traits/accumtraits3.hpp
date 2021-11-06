#ifndef ACCUM_TRAITS3_HPP
#define ACCUM_TRAITS3_HPP

namespace traits {

template<typename T>
struct AccumulationTraits3;

template<>
struct AccumulationTraits3<char> {
  using AccT = int;
  static AccT const zero = 0;
};

template<>
struct AccumulationTraits3<short> {
  using AccT = int;
  static AccT const zero = 0;
};

template<>
struct AccumulationTraits3<int> {
  using AccT = long;
  static AccT const zero = 0;
};

template<>
struct AccumulationTraits3<float> {
  using AccT = double;
  static constexpr AccT zero = 0;
};

} // namespace traits

#endif // ACCUM_TRAITS3_HPP