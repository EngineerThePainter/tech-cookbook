#ifndef TYPEOVERLOAD_CONTAINER1_HPP
#define TYPEOVERLOAD_CONTAINER1_HPP

#include <iterator>
#include <type_traits>
#include "enableif.hpp"

#include "traits/iterator_traits.hpp"

namespace typeoverload {

template<typename T>
class Container {
public:
  template<typename Iterator, typename = EnableIf<traits::IsInputIterator<Iterator>>>
  Container(Iterator first, Iterator last){};

  /*To create another overload of the constructor for example for bidirectional operator, we would have unfortunately add dummy type to the template
  as default values are not considered during determination if the two templates are equivalent.*/

  template<typename U, typename = EnableIf<std::is_convertible_v<T,U>>>
  operator Container<U>() const {};
};

} // namespace typeoverload

#endif // TYPEOVERLOAD_CONTAINER1_HPP