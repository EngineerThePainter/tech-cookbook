#include "chapters/chapter28.hpp"

#include <algorithm>
#include <iostream>

#include <common/common_prints.hpp>
#include <debugging/tracer.hpp>

namespace chapters
{
namespace
{

} // namespace

void runChapter28()
{
  common::printTitle("C++ Templates Chapter 28 - Templates debugging");

  debugging::SortTracer input[] = {7,3,5,6,4,2,0,1,9,8};

  for (int i = 0; i<10; i++) {
    std::cerr << input[i].val() << " ";
  }
  std::cerr << "\n";

  long created_at_start = debugging::SortTracer::creations();
  long max_live_at_start = debugging::SortTracer::max_live();
  long assigned_at_start = debugging::SortTracer::assignments();
  long compared_at_start = debugging::SortTracer::comparisons();

  std::cerr << "--- Start std::sort() ------\n";
  std::sort<>(&input[0], &input[9]+1);
  std::cerr << "--- End std::sort() --------\n";

  for (int i = 0; i<10; i++) {
    std::cerr << input[i].val() << " ";
  }
  std::cerr << "\n\n";

  std::cerr << "std::sort() of 10 SortTracer's" << "was performed by: \n"
  << debugging::SortTracer::creations() - created_at_start << " temporary tracers\n"
  << "up to "
  << debugging::SortTracer::max_live()
  << " tracers at the same time ("
  << max_live_at_start << " before)\n"
  << debugging::SortTracer::assignments() - assigned_at_start
  << " assignements\n"
  << debugging::SortTracer::comparisons() - compared_at_start << " comparisons\n\n";

  common::emptyLine();
}
}