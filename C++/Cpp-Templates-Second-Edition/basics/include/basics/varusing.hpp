#ifndef VARUSING_HPP
#define VARUSING_HPP

#include <iostream>
#include <string>
#include <unordered_set>

namespace basics {

class Customer {
    public:
    Customer(const std::string& name)
    : name(name)
    {}
    std::string getName() const {return name;}
    private:
    std::string name;
};

struct CustomerEq {
    bool operator() (Customer const& c1, Customer const& c2) const {
        std::cout << "Customer Eq" << std::endl;
        return c1.getName() == c2.getName();
    }
};

struct CustomerHash {
    std::size_t operator() (Customer const& c) const {
        std::cout << "Customer Hash" << std::endl;
        return std::hash<std::string>()(c.getName());
    }
};

// Class that combines operator() for variadic base classes
template<typename... Bases>
struct Overloader : Bases...
{
    using Bases::operator()...; //Works since C++17
};

} // basics

#endif // VARUSING_HPP