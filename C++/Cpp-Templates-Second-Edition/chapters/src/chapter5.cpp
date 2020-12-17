#include "chapters/chapter5.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <basics/arrays.hpp>
#include <basics/boolstring.hpp>
#include <basics/printcoll.hpp>
#include <basics/stack7decl.hpp>
#include <basics/stack8decl.hpp>
#include <basics/stack9.hpp>
#include <basics/variableTemplates.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void printingColls() {
    common::printTitle("Print container content");
    std::vector<std::string> container {"the good", "the bad", "the ugly"};
    basics::printcoll<std::vector<std::string>>(container);
    common::emptyLine();
}

template<typename T1, typename T2, typename T3>
void arraysFoo(int a1[7], int a2[], // pointers by language rules
               int (&a3)[42],       // reference to array of known bound
               int (&x0)[],         // reference to array of unknown bound
               T1 x1,               // passing by value decays
               T2& x2, T3&& x3)     // passing by reference
{
    basics::MyClass<decltype(a1)>::print();
    basics::MyClass<decltype(a2)>::print();
    basics::MyClass<decltype(a3)>::print();
    basics::MyClass<decltype(x0)>::print();
    basics::MyClass<decltype(x1)>::print();
    basics::MyClass<decltype(x2)>::print();
    basics::MyClass<decltype(x3)>::print();
}

void arraysUsage() {
    common::printTitle("Templates for raw arrays");
    int a[42];
    basics::MyClass<decltype(a)>::print();
    extern int x[];
    basics::MyClass<decltype(x)>::print();
    common::printMessage("Now let's call arraysFoo()");
    arraysFoo(a, a, a, x, x, x, x);
    common::emptyLine();
}

int x[] = {0, 8, 15};

void assignmentToDifferentType() {
    common::printTitle("Assignment To Different Type");
    basics::Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    basics::Stack<float> floatStack;
    /**
     * Can do it here, doing it line above would require to call copy constructor which is not defined
     */
    floatStack = intStack;
    common::printCallFunction("floatStack.top()", floatStack.top());
    floatStack.pop();
    common::printCallFunction("floatStack.top()", floatStack.top());
    floatStack.pop();
    common::printCallFunction("floatStack.top()", floatStack.top());
    common::emptyLine();
}

void memberFunctionTemplateSpecialization() {
    common::printTitle("Member function template specialization");
    std::cout << std::boolalpha;
    basics::BoolString s1("hello");
    common::printCallFunction("s1.get()", s1.get());
    common::printCallFunction("s1.get<bool>()", s1.get<bool>());

    basics::BoolString s2("on");
    common::printCallFunction("s2.get()", s2.get());
    common::printCallFunction("s2.get<bool>()", s2.get<bool>());
    common::emptyLine();
}

void variableTemplates() {
    common::printTitle("Variable templates");
    std::cout << "PI: " << basics::pi<float> << std::endl;
    std::cout << "PI: " << basics::pi<long double> << std::endl;
    common::emptyLine();
}

// Using Clang10 - it will not build despite the fact that it should since it's C++17
// void templateTemplateParameters() {
//     common::printTitle("Template template parameters");
//     basics::StackTemplateTemplateParameter<int, std::vector> stackTemplateTemplate;
//     stackTemplateTemplate.push(42);
//     stackTemplateTemplate.push(43);
//     stackTemplateTemplate.push(44);

//     common::printCallFunction("stackTemplateTemplate.top()", stackTemplateTemplate.top());
//     stackTemplateTemplate.pop();
//     common::printCallFunction("stackTemplateTemplate.top()", stackTemplateTemplate.top());
//     stackTemplateTemplate.pop();
//     common::printCallFunction("stackTemplateTemplate.top()", stackTemplateTemplate.top());
//     common::emptyLine();
// }

void finalStackVersion() {
    common::printTitle("Final Stack version");
    basics::Stack9<int> iStack;
    basics::Stack9<float> fStack;

    iStack.push(1);
    iStack.push(2);
    iStack.push(3);
    common::printCallFunction("iStack.top()", iStack.top());

    fStack.push(42.0);
    common::printCallFunction("fStack.top()", fStack.top());

    fStack = iStack;
    common::printCallFunction("fStack.top()", fStack.top());
    fStack.push(4.4);
    common::printCallFunction("fStack.top()", fStack.top());

    basics::Stack9<double, std::vector> vStack;
    vStack.push(42.0);
    vStack.push(40.4);
    vStack.push(12.5);
    common::printCallFunction("vStack.top()", vStack.top());

    vStack = fStack;
    std::cout << "vStack: ";
    while(!vStack.empty()) {
        std::cout << vStack.top();
        vStack.pop();
    }
    common::emptyLine();
}

} // namespace

void runChapter5() {
    common::printTitle("C++ Templates Chapter 5");
    printingColls();
    arraysUsage();
    assignmentToDifferentType();
    memberFunctionTemplateSpecialization();
    variableTemplates();
    // templateTemplateParameters();
    finalStackVersion();
    common::emptyLine();
}

}