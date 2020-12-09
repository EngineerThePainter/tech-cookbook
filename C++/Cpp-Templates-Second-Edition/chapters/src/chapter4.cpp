#include "chapters/chapter4.hpp"

#include <iostream>
#include <string>

#include <basics/folding.hpp>
#include <basics/variadic_creation.hpp>
#include <basics/varprint1.hpp>
#include <basics/varprint2.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {
 void runVariadicPrint1() {
     common::printTitle("Print Variadic Template for three arguments");
     basics::print<double, std::string, int, std::string, int>(34.4, "Hello", 42, "Templates", 15);
     common::printMessage("Variadic Template for only one argument - the function parameter pack is empty");
     basics::print<std::string>("Only one parameter");
     common::emptyLine();
 }
 void runVariadicPrint2() {
     common::printTitle("Print2 Variadic Template for three arguments");
     basics::print2<double, std::string, int>(34.4, "Hello", 42);
     common::printMessage("Variadic Template for only one argument - the function parameter pack is empty");
     basics::print2<std::string>("Only one parameter");
     common::emptyLine();
 }

 void traverseOverTree() {
    common::printTitle("Folding");
    common::printMessage("Traverse over tree");
    basics::Node* root = new basics::Node(0);
    root->left = new basics::Node(1);
    root->left->right = new basics::Node(2);

    std::cout << "Root node value: " << root->value << std::endl;
    basics::Node* node = basics::traverse(root, &basics::Node::left, &basics::Node::right);
    std::cout << "Node value: " << node->value << std::endl;
    delete root->left->right;
    delete root->left;
    delete root;
    common::emptyLine();
    common::printMessage("Folding print");
    basics::printFolding<std::string, int, double>("Hello", 42, 12.6);
    common::emptyLine();
 }

 void variadic_creation() {
    common::printTitle("Using variadic template to create a basics::Person instance using generic construction");
    const std::string s = "Guy";
    basics::Person p = basics::createT<basics::Person>(s, 30, 74.5);
    std::cout << "Person: contains: ";
    basics::printFolding(p.name, p.age, p.weight);
    common::emptyLine();
 }
}

void runChapter4() {
    common::printTitle("C++ Templates Chapter 4");
    common::emptyLine();
    runVariadicPrint1();
    runVariadicPrint2();
    traverseOverTree();
    variadic_creation();
}

} // namespace chapters