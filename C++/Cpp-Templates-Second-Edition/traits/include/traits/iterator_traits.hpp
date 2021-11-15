#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>
#include <type_traits>

namespace traits {

template<typename Iterator>
constexpr bool IsRandomAccessIterator
 = std::is_convertible<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>;

template<typename Iterator>
constexpr bool IsBidirectionalIterator = 
  std::is_convertible<typename std::iterator_traits<Iterator>::iterator_category, std::bidirectional_iterator_tag>;

}; // namespace traits

#endif // ITERATOR_TRAITS_HPP