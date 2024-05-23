#pragma once

#include <iostream>
#include <type_traits>

template <typename DerivedT, typename BaseT>
concept ShouldBeDerived = std::is_base_of_v<BaseT, DerivedT>;

template <typename Derived, typename Base>
    requires ShouldBeDerived<Derived, Base>
void doNotAcceptIfNotDervivedConcept(Derived T)
{
    std::cout << "doNotAcceptIfNotDervivedConcept was called" << std::endl;
}

template <typename DerivedT, typename BaseT>
void doNotAcceptIfNotDervivedStaticAssert(DerivedT T)
{
    static_assert(std::is_base_of<BaseT, DerivedT>::value, "Type is not derived");
    std::cout << "doNotAcceptIfNotDervivedStaticAssert was called" << std::endl;
}

template <typename DerivedT, typename BaseT>
typename std::enable_if<std::is_base_of<BaseT, DerivedT>::value>::type
doNotAcceptIfNotDerivedSfinae(DerivedT t)
{
    std::cout << "doNotAcceptIfNotDerivedSfinae was called" << std::endl;
}