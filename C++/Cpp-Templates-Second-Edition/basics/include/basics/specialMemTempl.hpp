#ifndef SPECIAL_MEM_TEMPL_HPP
#define SPECIAL_MEM_TEMPL_HPP

#include <iostream>
#include <string>
#include <utility>

namespace basics {

class Person {
    public:
    explicit Person(std::string const& name): name(name) {
        std::cout << "Copying string ctor for " << name << std::endl; 
    }

    explicit Person(std::string const&& name): name(std::move(name)) {
        std::cout << "Moving string ctor for " << name << std::endl; 
    }

    Person(Person const& p): name(p.name) {
        std::cout << "Copy ctor Person " << name << std::endl; 
    }

    Person(Person const&& p): name(std::move(p.name)) {
        std::cout << "Move ctor Person " << name << std::endl; 
    }
    private:
    std::string name;
};

class Person2 {
    public:
    template<typename STR>
    explicit Person2(STR&& name): name(std::forward<STR>(name)) {
        std::cout << "TMPL string ctor for " << name << std::endl;
    }

    Person2(Person2 const& p): name(p.name) {
        std::cout << "Copy ctor Person " << name << std::endl; 
    }

    Person2(Person2 const&& p): name(std::move(p.name)) {
        std::cout << "Move ctor Person " << name << std::endl; 
    }
    private:
    std::string name;
};

} // basics

#endif