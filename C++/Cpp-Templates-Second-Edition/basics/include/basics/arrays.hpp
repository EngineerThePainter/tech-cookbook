#ifndef ARRAYS_HPP
#define ARRAYS_HPP

#include <iostream>

namespace basics {

template<typename T>
struct MyClass; // primary template

// Partial specialization for templates for arrays of known bounds
template<typename T, std::size_t SZ>
struct MyClass<T[SZ]> 
{
    static void print() {std::cout << "print() for T[" << SZ << "]" << std::endl;}
};

// Partial specialization for templates for references to arrays of known bounds
template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]> 
{
    static void print() {std::cout << "print() for T(&)[" << SZ << "]" << std::endl;}
};

// Partial specialization for templates for arrays of unknown bounds
template<typename T>
struct MyClass<T[]> 
{
    static void print() {std::cout << "print() for T[]" << std::endl;}
};

// Partial specialization for templates for references to arrays of unknown bounds
template<typename T>
struct MyClass<T(&)[]> 
{
    static void print() {std::cout << "print() for T(&)[]" << std::endl;}
};

// Partial specialization for pointers
template<typename T>
struct MyClass<T*> 
{
    static void print() {std::cout << "print() for T*" << std::endl;}
};

} // basics

#endif // ARRAYS_HPP