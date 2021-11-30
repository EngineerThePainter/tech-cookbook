#ifndef INHERIT_VIRTUAL_HPP
#define INHERIT_VIRTUAL_HPP

#include <iostream>

namespace inherit {

class NotVirtual {
};

class Virtual {
public:
virtual void foo() {

}
};

template<typename... Mixins>
class Base: public Mixins... {
public:
void foo() {
  std::cout << "Base::foo()\n";
}
};

template<typename... Mixins>
class Derived : public Base<Mixins...> {
public:
void foo() {
  std::cout << "Derived::foo()\n";
}
};

} // namespace inherit

#endif // INHERIT_VIRTUAL_HPP