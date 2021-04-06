#ifndef FUNC_OVERLOAD1_HPP
#define FUNC_OVERLOAD1_HPP

namespace details
{

template<typename T>
int fun(T) {
  return 1;
}

template<typename T>
int fun(T*) {
  return 2;
}

} // namespace details

#endif // FUNC_OVERLOAD1_HPP