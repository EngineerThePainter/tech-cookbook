#include "chapters/chapter25.hpp"

#include <iostream>
#include <string>

#include <common/common_prints.hpp>

#include <tuples/tuple0.hpp>
#include <tuples/tupleget.hpp>

namespace chapters
{
namespace
{

void tuple0Usage() {
  common::printTitle("Tuple Get");
  tuples::Tuple<int, double, std::string> tuple(6, 7.66, "ora et labora");
  common::printCallFunction("tuples::get<0>(tuple)", tuples::get<0>(tuple));
  common::printCallFunction("tuples::get<1>(tuple)", tuples::get<1>(tuple));
  common::printCallFunction("tuples::get<2>(tuple)", tuples::get<2>(tuple));
}

} // namespace

void runChapter25()
{
  common::printTitle("C++ Templates Chapter 25 - Tuples");
  tuple0Usage();
  common::emptyLine();
}
}