#ifndef ENABLEIF_HPP
#define ENABLEIF_HPP

/**
 * @brief Since alias templates cannot be partially specialized we are using
 * a helper class template EnableIfT that makes the alias template EnableIf 
 * to get the result from the helper one. When the condition is true, then 
 * the template just evaluates to the second template argument T. If not, 
 * EnableIf does not produce a valid type, as the basic class template 
 * does not produce a Type. In normal situation it would be an error, but due to
 * SFINAE context (such as the return type of the function template) - is has the effect of 
 * causing template argument deduction to fail and removing the function template from the consideration.
 */
namespace typeoverload {

template<bool, typename T = void>
struct EnableIfT {
};

template<typename T>
struct EnableIfT<true, T> {
  using Type = T;
};

template<bool Cond, typename T = void>
using EnableIf = typename EnableIfT<Cond, T>::Type;

}; // namespace typeoverload

#endif // ENABLEIF_HPP