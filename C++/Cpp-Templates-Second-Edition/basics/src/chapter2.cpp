#include "chapter2.hpp"

#include <deque>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include "basics/stack1.hpp"
#include "basics/stack2.hpp"
#include "basics/stack3.hpp"
#include "basics/stackpartspec.hpp"
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

    basics::Stack<int> partialIntStack;
    partialIntStack.push(42);
    partialIntStack.push(404);

    printCallFunction("partialIntStack.top()", partialIntStack.top());
    std::cout << "Calling printOn on partialIntStack" << std::endl;
    partialIntStack.printOn(std::cout);
    emptyLine();
    std::cout << "Calling operator<< on partialIntStack: " << partialIntStack << std::endl;
    emptyLine();

    basics::Stack<std::string> partialStringStack;
    partialStringStack.push("Hello");
    partialStringStack.push("Template");

    printCallFunction("partialStringStack.top()", partialStringStack.top());
    std::cout << "Calling printOn on partialStringStack" << std::endl;
    partialStringStack.printOn(std::cout);
    emptyLine();
    std::cout << "Calling operator<< on partialStringStack: " << partialStringStack << std::endl;
    emptyLine();

    basics::Stack<std::pair<int,int>> partialPairStack;
    partialPairStack.push({4,5});
    partialPairStack.push({6,7});

    printCallFunction("partialPairStack.top().first", partialPairStack.top().first);
    printCallFunction("partialPairStack.top().second", partialPairStack.top().second);
    // Will cause compilation error as operator<< is not defined for type std::pair.
    // Please note, that this will be only the issue if we USE this function for this type.
    // partialPairStack.printOn(std::cout);

    /**
     * Build will not pass as well for this call, as type std::pair<> does not have implemented operator<<, 
     * despite the fact that the operator<< is defined for this class template
    */
    // std::cout << "Calling operator<< on partialPairStack: " << partialPairStack << std::endl;
    emptyLine();

    printTitle("Partial specialization of class template");
    basics::Stack<int*> partialPointerStack;
    int* a = new int(42);
    int* b = new int(404);

    partialPointerStack.push(a);
    partialPointerStack.push(b);
    printCallFunction("partialPointerStack.top()", *partialPointerStack.top());
    /**
     * Impossible as there is no operator<< for this specialization
    */
    // std::cout << "Calling operator<< on partialPointerStack: " << partialPointerStack << std::endl;
    delete a;
    delete b;
    emptyLine();
}

void defaultClassTemplateArguments() {
    printTitle("Default Class Template Arguments");
    basics::StackDefaultArg<int> intStack;
    intStack.push(5);
    intStack.push(6);
    printMessage("Declaration of this template with not default argument");
    basics::StackDefaultArg<double, std::deque<double>> dblStack;
    dblStack.push(42.5);

    printCallFunction("intStack.top()", intStack.top());
    printCallFunction("dblStack.top()", dblStack.top());
    emptyLine();
}

void constness() {
    printTitle("Checking constness");
    using NormalIntStack = basics::Stack<int>;
    using ConstIntStack = std::add_const_t<NormalIntStack>;
    std::cout << std::boolalpha;
    std::cout << "Const for NormalIntStack: " << std::is_const<NormalIntStack>::value << std::endl;
    std::cout << "Const for ConstIntStack: " << std::is_const<ConstIntStack>::value << std::endl;
    emptyLine();
}

}

void runChapter2() {
    printTitle("C++ Templates Chapter 2");
    useStack();
    partialUsage();
    defaultClassTemplateArguments();
    constness();
}

}