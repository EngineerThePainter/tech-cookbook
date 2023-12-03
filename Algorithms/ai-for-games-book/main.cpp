#include "algorithm_runner.hpp"
#include "kinematic/seek.hpp"

int main(int argc, char** argv)
{
  aifg::Seek seek;
  aifg::AlgorithmRunner<aifg::Seek> runner(seek);
  runner.run();
  return 0;
}