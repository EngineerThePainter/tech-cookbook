#include <iostream>

#include "class_having_all_traits.hpp"
#include "no_moveable.hpp"
#include "no_moveable_accepting.hpp"

int main()
{
    ClassHavingAllTraits class_having_all_traits;
    std::cout << "*** NO MOVE SEMANTICS" << std::endl;
    NoMoveable no_moveable;
    // Fails with error message
    // doNotAcceptTypeWithMoveSemanticsStaticAsserts(class_having_all_traits);
    doNotAcceptTypeWithMoveSemanticsStaticAsserts(no_moveable);

    // This one also will fail as there will be no matching function
    // doNotAcceptTypeWithMoveSemanticsSfinae(class_having_all_traits);
    doNotAcceptTypeWithMoveSemanticsSfinae(no_moveable);
    return 0;
}