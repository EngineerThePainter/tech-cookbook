#ifndef BOOLSTRING_HPP
#define BOOLSTRING_HPP

#include <iostream>
#include <string>

namespace basics {

class BoolString {
    public:
    BoolString(std::string const& s)
    :value(std::move(s)){}

    template<typename T = std::string>
    T get() const {
        return value;
    }

    private:
    std::string value;
};

template<>
inline bool BoolString::get<bool>() const {
    return value == "true" || value == "1" || value == "on";
}

} // basics

#endif