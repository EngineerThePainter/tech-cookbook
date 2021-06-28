#ifndef STATIC_POLY_HPP
#define STATIC_POLY_HPP

#include "statichier.hpp"
#include <iostream>
#include <vector>

namespace poly {

template<typename Animal>
void my_sound(Animal const& animal) {
    animal.sound();
}

template<typename Animal>
void my_walk(Animal const& animal) {
    animal.walk();
}

template<typename Animal>
void sound_and_walk(std::vector<Animal> const& animals) {
    for (const auto& animal : animals) {
        animal.sound();
        animal.walk();
        std::cout << "*****\n";
    }
}

template<typename Animal1, typename Animal2>
int weight_difference(Animal1 const& animal1, Animal2 const& animal2) {
    auto diff = animal1.weight() - animal2.weight();
    return diff >= 0 ? diff : diff * -1;
}

} // namespace poly

#endif // STATIC_POLY_HPP