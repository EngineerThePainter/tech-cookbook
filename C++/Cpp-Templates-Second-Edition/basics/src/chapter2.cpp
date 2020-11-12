#include "chapter2.hpp"

#include <iostream>
#include <string>

#include "basics/stack1.hpp"
#include "common_prints.hpp"

namespace chapter {

namespace {
void useStack() {
    printTitle("Use of class template");
    basics::Stack<int> intStack;
    basics::Stack<std::string> stringStack;

    intStack.push(7);
    printCallFunction("intStack.top()", intStack.top());

    stringStack.push("hello");
    printCallFunction("stringStack.top()", stringStack.top());
    stringStack.pop();
    emptyLine();
}
}

void runChapter2() {
    printTitle("C++ Templates Chapter 2");
    useStack();
}

}