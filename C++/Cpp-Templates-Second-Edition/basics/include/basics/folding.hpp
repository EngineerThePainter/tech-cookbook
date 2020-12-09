#ifndef FOLDING_HPP
#define FOLDING_HPP

#include <iostream>
#include <utility>

namespace basics {

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int i=0)
    : value(i), left(nullptr), right(nullptr)
    {}
};

template<typename T, typename... TP>
Node* traverse(T np, TP... paths) {
    return (np ->* ... ->* paths); //np ->* paths1 ->* paths2...
}

// Util class for adding spaces in print folding
template<typename T>
class AddSpaceFolding {
    public:
    AddSpaceFolding(T const& r)
    : ref(r) {

    }

    friend std::ostream& operator<< (std::ostream& os, AddSpaceFolding<T> s) {
        return os << s.ref << " ";
    }

    private:
    T const& ref;
};

template<typename... Types>
void printFolding(Types const&... args) {
    (std::cout << ... << AddSpaceFolding(args)) << "\n";
}



} // basics

#endif // FOLDING_HPP