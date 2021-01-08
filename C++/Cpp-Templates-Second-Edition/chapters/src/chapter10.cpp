#include "chapters/chapter10.hpp"

#include <iostream>
#include <string>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

const std::string notes = R"notes(
    For the precision we should use term "class template" when referring to the class that is a template.
    "Template class" might be used as synonym to "class template", but also when referring classes generated from templates,
    so it can rise confusion.

    Same for "function template", "member template" etc.

    Template instatiantiation is the proces of creating a definition for a regular class, function etc. from template by substituting 
    concrete arguments for the template parameters.

    Template parameters - the names listed after keyword 'template' in the template declaration or definition.

    Template arguments - the items that are substituted for template parameters.
)notes";

} // namespace

void runChapter10() {
    common::printTitle("C++ Templates Chapter 10");
    common::printMessage("Notes about template terminology.");
    common::printMessage(notes);
    common::emptyLine();
}

}