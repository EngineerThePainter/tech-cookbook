#ifndef INHERIT_BASEMEMBERPAIR_HPP
#define INHERIT_BASEMEMBERPAIR_HPP

namespace inherit {

template<typename Base, typename Member>
class BaseMemberPair : private Base {
  private:
  Member mem;

  public:
  BaseMemberPair(Base const& b, Member const& m): Base(b), mem(m) {}

  Base const& base() const {
    return static_cast<Base const&>(*this);
  }

  Base& base() const {
    return static_cast<Base&>(*this);
  }

  Member const& member() const {
    return this->mem;
  }

  Member& member() const {
    return this->mem;
  }
};

} // namespace inherit

#endif // INHERIT_BASEMEMBERPAIR_HPP