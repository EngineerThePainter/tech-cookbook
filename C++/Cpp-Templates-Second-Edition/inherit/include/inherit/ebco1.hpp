#ifndef INHERIT_EBCO1_HPP
#define INHERIT_EBCO1_HPP

namespace inherit {

class Empty {
  using Int = int; // type alias members don't make a class nonempty
};

class EmptyToo : public Empty {

};

class EmptyThree : public EmptyToo {

};

class NonEmpty : public Empty, public EmptyToo, public EmptyThree {

};

} // namespace inherit

#endif // INHERIT_EBCO1_HPP