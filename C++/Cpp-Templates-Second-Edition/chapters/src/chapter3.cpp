#include "chapters/chapter3.hpp"

#include <iostream>
#include <string>

#include <basics/stacknontype.hpp>
#include <basics/stackTemplateParameterAuto.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

extern char const sExternal[] = "hello"; // external linkeage
char const sInternal[] = "hello"; //internal linkeage

void useStackNonType() {
    common::printTitle("Usage of Stack none type");

    basics::StackNonType<int, 20> int20Stack;
    basics::StackNonType<int, 40> int40Stack;
    basics::StackNonType<std::string, 40> stringStack;

    int20Stack.push(7);
    common::printCallFunction("int20Stack.top()", int20Stack.top());
    int20Stack.pop();

    stringStack.push("string value");
    common::printCallFunction("stringStack.top()", stringStack.top());
    stringStack.pop();

    basics::printPassedX<52>(5);
    // Floating point value is not allowed as parameter, same for class objects
    // basics::printPassedX<5.62>(5);

    basics::printPassedX<sExternal>("world");
    basics::printPassedX<sInternal>("world"); // since C++11
    static char const sNoLinkeage[] = "hello";
    basics::printPassedX<sNoLinkeage>("world"); // since C++17

    common::emptyLine();
}

void useTemplateParameterTypeAuto() {
    common::printTitle("Template parameter type auto");
    basics::StackTemplateParameterAuto<int, 20u> int20Stack;
    basics::StackTemplateParameterAuto<std::string, 40> stringStack;

    int20Stack.push(42);
    common::printCallFunction("int20Stack.top()", int20Stack.top());
    auto size1 = int20Stack.size();

    stringStack.push("hello");
    common::printCallFunction("stringStack.top()", stringStack.top());
    auto size2 = stringStack.size();

    if (!std::is_same_v<decltype(size1), decltype(size2)>) {
        std::cout << "Size types are different types" << std::endl;
    }

    common::emptyLine();
}


} // namespace

void runChapter3() {
    useStackNonType();
    useTemplateParameterTypeAuto();
}

}