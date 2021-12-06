#ifndef INHERIT_WRAPPER_HPP
#define INHERIT_WRAPPER_HPP

namespace inherit {

class WrapperExampleClass {};

template<typename T>
class Wrapper {
  private:
  T object;
  public:
  Wrapper(T object) : object(object) {}

  friend void foo(Wrapper<T> const&) {}
};

} // namespace inherit

#endif // INHERIT_WRAPPER_HPP