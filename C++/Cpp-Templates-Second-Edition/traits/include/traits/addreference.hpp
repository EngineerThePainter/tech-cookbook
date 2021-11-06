#ifndef ADD_REFERENCE_HPP
#define ADD_REFERENCE_HPP

namespace traits {

template<typename T>
struct AddLValueReferenceT {
  using Type = T&;
};

template<typename T>
using AddLValueReference = typename AddLvalueReferenceT<T>::Type;

template<typename T>
struct AddRValueReferenceT {
  using Type = T&&;
};

template<typename T>
using AddRValueReference = typename AddRvalueReferenceT<T>::Type;

template<>
struct AddLValueReferenceT<void> {
  using Type = void;
};

template<>
struct AddLValueReferenceT<void const> {
  using Type = void const;
};

template<>
struct AddLValueReferenceT<void volatile> {
  using Type = void volatile;
};

template<>
struct AddLValueReferenceT<void const volatile> {
  using Type = void const volatile;
};

template<>
struct AddRValueReferenceT<void> {
  using Type = void;
};

template<>
struct AddRValueReferenceT<void const> {
  using Type = void const;
};

template<>
struct AddRValueReferenceT<void volatile> {
  using Type = void volatile;
};

template<>
struct AddRValueReferenceT<void const volatile> {
  using Type = void const volatile;
};

} // namespace traits

#endif // ADD_REFERENCE_HPP