#ifndef TEMPLATIZED_AGGREGATE_HPP
#define TEMPLATIZED_AGGREGATE_HPP

#include <string>

namespace basics {

template<typename T>
struct ValueWithComment {
    T value;
    std::string comment;
};

ValueWithComment(char const*, char const*) -> ValueWithComment<std::string>;

} // namespace basics

#endif // TEMPLATIZED_AGGREGATE_HPP