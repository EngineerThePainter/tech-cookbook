#include "chapter3.hpp"

#include <iostream>
#include <string>

#include "basics/stacknontype.hpp"

#include "common_prints.hpp"

namespace chapter {

namespace {

void useStackNonType() {
    printTitle("Usage of Stack none type");

    basics::StackNonType<int, 20> int20Stack;
    basics::StackNonType<int, 40> int40Stack;
    basics::StackNonType<std::string, 40> stringStack;

    int20Stack.push(7);
    printCallFunction("int20Stack.top()", int20Stack.top());
    int20Stack.pop();

    stringStack.push("string value");
    printCallFunction("stringStack.top()", stringStack.top());
    stringStack.pop();

    emptyLine();
}

} // namespace

void runChapter3() {
    useStackNonType();
}

}