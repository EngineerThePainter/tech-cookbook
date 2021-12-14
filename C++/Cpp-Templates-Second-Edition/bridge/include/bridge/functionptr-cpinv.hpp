#ifndef BRIDGE_FUNCTIONPTRCPINV_HPP
#define BRIDGE_FUNCTIONPTRCPINV_HPP

#include "functionptr.hpp"

namespace bridge {

  template<typename R, typename... Args>
  FunctionPtr<R(Args...)>::FunctionPtr(FunctionPtr const& other) : bridge(nullptr) {
    if (other.bridge) {
      bridge = other.bridge->clone();
    }
  }

  template<typename R, typename... Args>
  R FunctionPtr<R(Args...)>::operator()(Args... args) const {
    return bridge->invoke(std::forward<Args...>(args)...);
  }
} // namespace poly

#endif // BRIDGE_FUNCTIONPTRCPINV_HPP