#ifndef TUPLES_TUPLE0_HPP
#define TUPLES_TUPLE0_HPP

namespace tuples {

template<typename... Types>
class Tuple;

// recursive case
template<typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
  private:
  Head head;
  Tuple<Tail...> tail;

  public:
  Tuple() {}
  Tuple(Head const& head, Tuple<Tail...> const& tail) : head(head), tail(tail) {}
  Tuple(Head const& head, Tail const&... tail) : head(head), tail(tail...) {};

  
  Head& getHead() { return head; }
  Head const& getHead() const { return head; }
  Tuple<Tail...>& getTail() { return tail; }
  Tuple<Tail...> const& getTail() const { return tail; }
};

template<>
class Tuple<> {};

} // namespace tuples

#endif // TUPLES_TUPLE0_HPP