#ifndef BRIDGE_FUNCTORBRIDGE_HPP
#define BRIDGE_FUNCTORBRIDGE_HPP

namespace bridge {

template<typename R, typename... Args>
class FunctorBridge {
public:
  virtual ~FunctorBridge() {}
  virtual FunctorBridge* clone() const = 0;
  virtual R invoke(Args.. args) const = 0;
};

} // namespace poly

#endif // BRIDGE_FUNCTORBRIDGE_HPP