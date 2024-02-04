#include <iostream>

#include "class_with_specific_field.hpp"
#include "accept_with_specific_field.hpp"
#include "class_having_all_traits.hpp"
#include "no_moveable.hpp"
#include "no_moveable_accepting.hpp"
#include "no_pass_by_reference_accepting.hpp"
#include "no_assignable.hpp"
#include "no_assignable_accepting.hpp"

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

    std::cout << "*** NO ACCEPT IF ASSIGNABLE" << std::endl;
    NoAssignable no_assignable;

    doNotAcceptAssignableTypeStaticAssert(no_assignable);
    doNotAcceptAssignableTypeSfinae(no_assignable);

    // These will fail due to static assert
    // doNotAcceptAssignableTypeStaticAssert(class_having_all_traits);
    // doNotAcceptAssignableTypeSfinae(42);
    // doNotAcceptAssignableTypeSfinae(class_having_all_traits);

    std::cout << "*** ACCEPT WHEN HAVING SPECIFIC FIELD" << std::endl;
    ClassWithSpecificField class_with_specific_field;
    ClassWithNoSpecificField class_with_no_specific_field;
    acceptTypeWithSpecificFieldStaticAssert(class_with_specific_field);
    acceptTypeWithSpecificFieldSfinae(class_with_specific_field);

    // acceptTypeWithSpecificFieldSfinae(class_with_no_specific_field);
    // acceptTypeWithSpecificFieldStaticAssert(class_with_no_specific_field);
    return 0;
}