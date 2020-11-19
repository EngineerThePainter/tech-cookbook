#ifndef TEMPLATIZED_AGGREGATE_HPP
#define TEMPLATIZED_AGGREGATE_HPP

#include <string>

namespace chapter {
namespace basics {

template<typename T>
struct ValueWithComment {
    T value;
    std::string comment;
};

ValueWithComment(char const*, char const*) -> ValueWithComment<std::string>;

} // namespace basics
} // namespace chapter

#endif // TEMPLATIZED_AGGREGATE_HPP