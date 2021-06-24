#ifndef STATIC_HIER_HPP
#define STATIC_HIER_HPP

#include <iostream>

namespace poly {

class Cat {
    public:
    void sound() const {std::cout << "Meow, meow\n";}
    void walk() const {std::cout << "Cat walk graciously\n";}
    int weight() const {return 5;}
};

class Dog {
    public:
    void sound() const {std::cout << "Bark! Bark!\n";}
    void walk() const {std::cout << "Dog runs towards pool\n";}
    int weight() const {return 10;}
};

} // namespace poly

#endif // STATIC_HIER_HPP