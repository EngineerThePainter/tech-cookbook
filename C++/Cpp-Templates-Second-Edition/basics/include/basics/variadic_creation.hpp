#ifndef VARIADIC_CREATION_HPP
#define VARIADIC_CREATION_HPP

#include <string>
#include <utility>

namespace basics {

struct Person {
    std::string name;
    int age;
    double weight;

    Person(const std::string& name, const int age, const double weight)
    : name(name),
    age(age),
    weight(weight)
    {
    }
};

template<typename T, typename... Args>
T createT(Args&&... args) {
    return T(std::forward<Args>(args) ...);
}

} // namespace basic

#endif // VARIADIC_CREATION_HPP