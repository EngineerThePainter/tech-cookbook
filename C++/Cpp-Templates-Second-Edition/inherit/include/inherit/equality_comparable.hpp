#ifndef INHERIT_EQUALITYCOMPARABLE_HPP
#define INHERIT_EQUALITYCOMPARABLE_HPP

namespace inherit {

template<typename Derived>
class EqualityComparable {
public:
friend bool operator!= (Derived const& x1, Derived const& x2) {
  return !(x1 == x2);
}
};

class X : public EqualityComparable<X> {
private:
const int val;

public:

X(const int val) : val(val) {}

friend bool operator== (X const& x1, X const& x2) {
  return x1.val == x2.val;
}

};

} // namespace inherit

#endif // INHERIT_EQUALITYCOMPARABLE_HPP