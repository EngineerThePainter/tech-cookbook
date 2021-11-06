#ifndef ACCUM_TRAITS4_HPP
#define ACCUM_TRAITS4_HPP

namespace traits {

template<typename T>
struct AccumulationTraits4;

template<>
struct AccumulationTraits4<char> {
  using AccT = int;
  static constexpr AccT const zero() {
    return 0;
  }
};

template<>
struct AccumulationTraits4<short> {
  using AccT = int;
  static constexpr AccT const zero() {
    return 0;
  }
};

template<>
struct AccumulationTraits4<int> {
  using AccT = long;
  static constexpr AccT const zero() {
    return 0;
  }
};

template<>
struct AccumulationTraits4<unsigned int> {
  using AccT = unsigned long;
  static constexpr AccT const zero() {
    return 0;
  }
};

template<>
struct AccumulationTraits4<float> {
  using AccT = double;
  static constexpr AccT zero = 0;
};

} // namespace traits

#endif // ACCUM_TRAITS4_HPP