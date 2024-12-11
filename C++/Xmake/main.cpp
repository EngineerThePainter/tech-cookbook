#include <iostream>
#include <new>

struct Base {
  virtual int transmogrify();
};

struct Derived : Base {
  int transmogrify() override {
    new (this) Base;
    return 2;
  }
};

int Base::transmogrify() {
  new (this) Derived;
  return 1;
}

static_assert(sizeof(Derived) == sizeof(Base));

int main() {
  std::cout << "Hello\n";
  Base base;
  int n = base.transmogrify();
  // int m = base.transmogrify(); // undefined behavior
  int m = std::launder(&base)->transmogrify(); // OK
  assert(m + n == 3);
  return 0;
}