#ifndef CONSTRAINTS_CONCEPTS_HPP
#define CONSTRAINTS_CONCEPTS_HPP

#include <concepts>

template <typename T>
concept Hashable = requires(T a)
{
  {
    std::hash<T>{}(a)
    } -> std::convertible_to<std::size_t>;
};

class A
{
public:
  A() = default;
  virtual ~A() = default;
};

class B : public A
{
public:
  B() = default;
  ~B() = default;
};

class C
{
public:
  C() = default;
  ~C() = default;
};

template <typename T>
concept DerivedFromA = std::derived_from<T, A>;

template <DerivedFromA T> void derivedFun(T arg) {}

template <Hashable T> void hashableFun(T arg) {}

void constraintsConcepts();

#endif