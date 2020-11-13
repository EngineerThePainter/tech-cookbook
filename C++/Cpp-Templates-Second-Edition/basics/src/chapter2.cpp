#include "chapter2.hpp"

#include <iostream>
#include <string>
#include <utility>

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

void partialUsage() {
    printTitle("Partial usage based on the operator<<");

    basics::Stack<std::string> partialStringStack;
    partialStringStack.push("Hello");
    partialStringStack.push("Template");

    printCallFunction("partialStringStack.top()", partialStringStack.top());
    std::cout << "Calling printOn on partialStringStack" << std::endl;
    partialStringStack.printOn(std::cout);
    emptyLine();

    basics::Stack<std::pair<int,int>> partialPairStack;
    partialPairStack.push({4,5});
    partialPairStack.push({6,7});

    printCallFunction("partialPairStack.top().first", partialPairStack.top().first);
    printCallFunction("partialPairStack.top().second", partialPairStack.top().second);
    // Will cause compilation error as operator<< is not defined for type std::pair.
    // Please note, that this will be only the issue if we USE this function for this type.
    // partialPairStack.printOn(std::cout);
}

}

void runChapter2() {
    printTitle("C++ Templates Chapter 2");
    useStack();
    partialUsage();
}

}