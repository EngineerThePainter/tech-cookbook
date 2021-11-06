#ifndef PLUS1_HPP
#define PLUS1_HPP

namespace traits {
  template<typename T1, typename T2>
  struct PlusResultT {
    using Type = decltype(T1() + T2());
  };

  template<typename T1, typename T2>
  using PlusResult1 = typename PlusResultT<T1, T2>::Type;
}

#endif //  PLUS1_HPP