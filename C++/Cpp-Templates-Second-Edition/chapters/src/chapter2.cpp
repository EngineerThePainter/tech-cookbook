#include "chapters/chapter2.hpp"

#include <deque>
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <utility>

#include <basics/stack1.hpp>
#include <basics/stack2.hpp>
#include <basics/stack3.hpp>
#include <basics/stackpartspec.hpp>
#include <basics/templatized_aggregate.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {
void useStack() {
    common::printTitle("Use of class template");
    basics::Stack<int> intStack;
    basics::Stack<std::string> stringStack;

    intStack.push(7);
    common::printCallFunction("intStack.top()", intStack.top());

    stringStack.push("hello");
    common::printCallFunction("stringStack.top()", stringStack.top());
    stringStack.pop();
    common::emptyLine();
}

void partialUsage() {
    common::printTitle("Partial usage based on the operator<<");

    basics::Stack<int> partialIntStack;
    partialIntStack.push(42);
    partialIntStack.push(404);

    common::printCallFunction("partialIntStack.top()", partialIntStack.top());
    std::cout << "Calling printOn on partialIntStack" << std::endl;
    partialIntStack.printOn(std::cout);
    common::emptyLine();
    std::cout << "Calling operator<< on partialIntStack: " << partialIntStack << std::endl;
    common::emptyLine();

    basics::Stack<std::string> partialStringStack;
    partialStringStack.push("Hello");
    partialStringStack.push("Template");

    common::printCallFunction("partialStringStack.top()", partialStringStack.top());
    std::cout << "Calling printOn on partialStringStack" << std::endl;
    partialStringStack.printOn(std::cout);
    common::emptyLine();
    std::cout << "Calling operator<< on partialStringStack: " << partialStringStack << std::endl;
    common::emptyLine();

    basics::Stack<std::pair<int,int>> partialPairStack;
    partialPairStack.push({4,5});
    partialPairStack.push({6,7});

    common::printCallFunction("partialPairStack.top().first", partialPairStack.top().first);
    common::printCallFunction("partialPairStack.top().second", partialPairStack.top().second);
    // Will cause compilation error as operator<< is not defined for type std::pair.
    // Please note, that this will be only the issue if we USE this function for this type.
    // partialPairStack.printOn(std::cout);

    /**
     * Build will not pass as well for this call, as type std::pair<> does not have implemented operator<<, 
     * despite the fact that the operator<< is defined for this class template
    */
    // std::cout << "Calling operator<< on partialPairStack: " << partialPairStack << std::endl;
    common::emptyLine();

    common::printTitle("Partial specialization of class template");
    basics::Stack<int*> partialPointerStack;
    int* a = new int(42);
    int* b = new int(404);

    partialPointerStack.push(a);
    partialPointerStack.push(b);
    common::printCallFunction("partialPointerStack.top()", *partialPointerStack.top());
    /**
     * Impossible as there is no operator<< for this specialization
    */
    // std::cout << "Calling operator<< on partialPointerStack: " << partialPointerStack << std::endl;
    delete a;
    delete b;
    common::emptyLine();
}

void defaultClassTemplateArguments() {
    common::printTitle("Default Class Template Arguments");
    basics::StackDefaultArg<int> intStack;
    intStack.push(5);
    intStack.push(6);
    common::printMessage("Declaration of this template with not default argument");
    basics::StackDefaultArg<double, std::deque<double>> dblStack;
    dblStack.push(42.5);

    common::printCallFunction("intStack.top()", intStack.top());
    common::printCallFunction("dblStack.top()", dblStack.top());
    common::emptyLine();
}

void constness() {
    common::printTitle("Checking constness");
    using NormalIntStack = basics::Stack<int>;
    using ConstIntStack = std::add_const_t<NormalIntStack>;
    std::cout << std::boolalpha;
    std::cout << "Const for NormalIntStack: " << std::is_const<NormalIntStack>::value << std::endl;
    std::cout << "Const for ConstIntStack: " << std::is_const<ConstIntStack>::value << std::endl;
    common::emptyLine();
}

void classArgumentDeduction() {
    common::printTitle("Deduction of class template arguments");
    basics::Stack<int> intStack1;
    basics::Stack<int> intStack2 = intStack1;
    // since C++17
    basics::Stack intStack3 = intStack1;

    // Deduction of stack type based on the constructor
    // since C++17
    basics::Stack intStack4 = 42;
    common::printCallFunction("intStack4.top()", intStack4.top());
    common::emptyLine();
}

void templatizedAggregates() {
    common::printTitle("Templatized Aggregates");
    basics::ValueWithComment<int> vc = {42, "initial value"};
    std::cout << "Type of vc.value: " << typeid(vc.value).name() << std::endl;
    std::cout << "Type of vc.comment: " << typeid(vc.comment).name() << std::endl;

    //Works since C++17
    basics::ValueWithComment vc2 = {"hello", "initial value"};
    std::cout << "Type of vc2.value: " << typeid(vc2.value).name() << std::endl;
    std::cout << "Type of vc2.comment: " << typeid(vc2.comment).name() << std::endl;
    common::emptyLine();
}

} // namespace

void runChapter2() {
    common::printTitle("C++ Templates Chapter 2");
    useStack();
    partialUsage();
    defaultClassTemplateArguments();
    constness();
    classArgumentDeduction();
    templatizedAggregates();
}

}