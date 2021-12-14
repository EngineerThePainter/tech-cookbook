#ifndef BRIDGE_SPECIFICFUNCTORBRIDGE_HPP
#define BRIDGE_SPECIFICFUNCTORBRIDGE_HPP

#include "functorbridge.hpp"
#include "try_equals.hpp"

namespace bridge {

template<typename Functor, typename R, typename... Args>
class SpecificFunctorBridge : public FunctorBridge<R, Args...> {
  Functor functor;
public:
  template<typename FunctorFwd>
  SpecificFunctorBridge(FunctorFwd&& functor): functor(std::forward<FunctorFwd>(functor)) {}
  
  virtual SpecificFunctorBridge* clone() const override {
    return new SpecificFunctorBridge(functor);
  }

  virtual R invoke(Args... args) const override {
    return functor(std::forward<Args>(args)...);
  }

  virtual bool equals(FunctorBridge<R, Args...> const* fb) const override {
    if (auto specFb = dynamic_cast<SpecificFunctorBridge const*>(fb)) {
      return TryEquals<Functor>::equals(functor, specFb->functor);
    }

    return false;
  }
};

} // namespace poly

#endif // BRIDGE_SPECIFICFUNCTORBRIDGE_HPP