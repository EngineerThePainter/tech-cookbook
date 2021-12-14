#ifndef BRIDGE_FUNCTIONPTR_HPP
#define BRIDGE_FUNCTIONPTR_HPP

#include "functorbridge.hpp"

namespace bridge {

// Primary template
template<typename Signature>
class FunctionPtr;

// Partial specialization
template<typename R, typename... Args>
class FunctionPtr<R(Args...)>
{
  private:
  FunctorBridge<R, Args...>* bridge;

  public:
  FunctionPtr(): bridge(nullptr) {
  }

  FunctionPtr(FunctionPtr const& other);

  FunctionPtr(FunctionPtr& other) : FunctionPtr(static_cast<FunctionPtr const&>(other)) {
  }

  FunctionPtr(FunctionPtr&& other) : bridge(other.bridge) {
    other.bridge = nullptr;
  }

  template<typename F>
  FunctionPtr(F&& f);

  FunctionPtr& operator=(FunctionPtr const& other) {
    FunctionPtr tmp(other);
    swap(*this, tmp);
    return *this;
  }

  FunctionPtr& operator=(FunctionPtr&& other) {
    delete bridge;
    bridge = other.bridge;
    other.bridge = nullptr;
    return *this;
  }

  template<typename F> FunctionPtr& operator=(F&& f) {
    FunctionPtr tmp(std::forward<F>(f));
    swap(*this, tmp);
    return *this;
  }

  ~FunctionPtr() {
    delete bridge;
  }

  friend void swap(FunctionPtr& fp1, FunctionPtr& fp2) {
    std::swap(fp1.bridge, fp2.bridge);
  }

  explicit operator bool() const {
    return bridge == nullptr;
  }

  R operator()(Args... args) const;
};

} // namespace poly

#endif // BRIDGE_FUNCTIONPTR_HPP