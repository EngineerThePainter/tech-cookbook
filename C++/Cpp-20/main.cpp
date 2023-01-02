#include "consteval_and_constinit.hpp"
#include "designated_initializer.hpp"
#include "init_statement_initializer_ranged_for.hpp"
#include "likely_unlikely.hpp"
#include "three_way_comparison.hpp"

int main(int argc, const char* argv[])
{
  showThreeWayComparison();
  showDesignatedInitializers();
  showInitStatementAndInitializerForRangedFor();
  likely_unlikely();
  constevalAndConstinit();
  return 0;
}
