#ifndef INVOKE_HPP
#define INVOKE_HPP

#include <functional>
#include <type_traits>
#include <utility>

namespace basics {

template <typename Callable, typename... Args>
decltype(auto) call(Callable&& op, Args&&... args) {

    /**
     * Will compile with C++17, since C++11 you need to use std::result_of<Callable(Args...)>::type
     */
    if constexpr(std::is_same_v<std::invoke_result_t<Callable, Args...>, void>) {
        std::invoke(std::forward<Callable>(op), std::forward<Args>(args)...);
        return;
    } else {
        decltype(auto) ret{std::invoke(std::forward<Callable>(op), std::forward<Args>(args)...)};
        return ret;
    }
}

} // basics

#endif