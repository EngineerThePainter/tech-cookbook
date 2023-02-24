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

template <Hashable T> void hashableFun(T arg) {}

void constraintsConcepts();

#endif