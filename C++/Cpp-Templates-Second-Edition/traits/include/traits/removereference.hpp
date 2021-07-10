#ifndef REMOVE_REFERENCE_HPP
#define REMOVE_REFERNECE_HPP

namespace traits {

template<typename T>
struct RemoveReferenceT {
  using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&> {
  using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&&> {
  using Type = T;
};

template<typename T>
using RemoveReference = typename RemoveReference<T>::Type;

}

#endif // REMOVE_REFERENCE_HPP