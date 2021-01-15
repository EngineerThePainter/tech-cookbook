#ifndef FOREACH_INVOKE_HPP
#define FOREACH_INVOKE_HPP

#include <functional>
#include <utility>

namespace basics {

template <typename Iter, typename Callable, typename... Args>
void foreachInvoke(Iter current, Iter end, Callable op, Args const&... args) {
    while (current != end) {
        std::invoke(op, args..., *current);
        ++current;
    }
}

} // basics

#endif