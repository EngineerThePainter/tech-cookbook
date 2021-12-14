#ifndef BRIDGE_FUNCTIONPTRINIT_HPP
#define BRIDGE_FUNCTIONPTRINIT_HPP

#include "functionptr.hpp"
#include "specific_functor_bridge.hpp"

namespace bridge {

template<typename R, typename... Args>
template<typename F>
FunctionPtr<R(Args...)>::FunctionPtr(F&& f) : bridge(nullptr) {
  using Functor = std::decay_t<F>;
  using Bridge = SpecificFunctorBridge<Functor, R, Args...>;
  bridge = new Bridge(std::forward<F>(f));
}

} // namespace poly

#endif // BRIDGE_FUNCTIONPTRINIT_HPP