#ifndef FOREACH_HPP
#define FOREACH_HPP

namespace basics {

template <typename Iter, typename Callable>
void foreach(Iter current, Iter end, Callable op) {
    while (current != end) {
        op(*current);
        ++current;
    }
}

} // basics

#endif