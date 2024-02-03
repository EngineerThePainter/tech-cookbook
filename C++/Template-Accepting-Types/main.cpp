#include <iostream>

#include "class_having_all_traits.hpp"
#include "no_moveable.hpp"
#include "no_moveable_accepting.hpp"
#include "no_pass_by_reference_accepting.hpp"

int main()
{
    ClassHavingAllTraits class_having_all_traits;
    std::cout << "*** NO MOVE SEMANTICS" << std::endl;
    NoMoveable no_moveable;
    // Fails with error message
    // doNotAcceptTypeWithMoveSemanticsStaticAsserts(class_having_all_traits);
    // doNotAcceptTypeWithMoveSemanticsStaticAsserts(42);
    doNotAcceptTypeWithMoveSemanticsStaticAsserts(no_moveable);

    // This one also will fail as there will be no matching function
    // doNotAcceptTypeWithMoveSemanticsSfinae(class_having_all_traits);
    // doNotAcceptTypeWithMoveSemanticsSfinae(42);
    doNotAcceptTypeWithMoveSemanticsSfinae(no_moveable);

    std::cout << "*** NO ACCEPT AS REFERENCE" << std::endl;
    // Keep in mind that the function is made as T t, not T &t, so
    // the deduced type for T is always value - here only explicit type declaration will fail
    noPassByReferenceAcceptingStaticAssert<ClassHavingAllTraits>(class_having_all_traits);
    noPassByReferenceAcceptingSfinae<ClassHavingAllTraits>(class_having_all_traits);

    ClassHavingAllTraits &class_having_all_traits_ref = class_having_all_traits;
    // Error message will be shown due to fail of static assert
    // noPassByReferenceAcceptingStaticAssert<ClassHavingAllTraits &>(class_having_all_traits_ref);
    // This one will fail due to no matching function from SFINAE
    // noPassByReferenceAcceptingSfinae<ClassHavingAllTraits &>(class_having_all_traits_ref);
    return 0;
}