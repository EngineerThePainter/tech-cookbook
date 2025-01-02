#include <iostream>
#include <type_traits>

#include "algorithm_runner.hpp"
#include "kinematic/arrive.hpp"
#include "kinematic/seek.hpp"
#include "kinematic/seek_dynamic.hpp"
#include "kinematic/wander.hpp"

namespace
{
enum class Option { kExit = 0, kSeek = 1, kArrive, kWander, kSeekDynamic };

template <typename t> void runAlgorithm()
{
  t algorithm;
  aifg::AlgorithmRunner<t> runner(algorithm);
  runner.run();
}
} // namespace
// TODO:
// * add vector 2D for convienient operations and "normalize" operation
// * unified passed "time" as result of 1.0f/60.0f
// * better handling same parts
int main(int argc, char** argv)
{
  int selected_option = static_cast<std::underlying_type_t<Option>>(Option::kExit);
  bool end = false;
  while (!end) {
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. Seek" << std::endl;
    std::cout << "2. Arrive" << std::endl;
    std::cout << "3. Wander" << std::endl;
    std::cout << "4. Seek - dynamic version" << std::endl;
    std::cout << "Pass 0 to exit" << std::endl;
    std::cin >> selected_option;
    Option option = static_cast<Option>(selected_option);
    switch (option) {
    case Option::kExit:
      std::cout << "Exiting..." << std::endl;
      end = true;
      break;
    case Option::kSeek:
      std::cout << "Running seek..." << std::endl;
      runAlgorithm<aifg::Seek>();
      break;
    case Option::kArrive:
      std::cout << "Running arrive..." << std::endl;
      runAlgorithm<aifg::Arrive>();
      break;
    case Option::kWander:
      std::cout << "Running wander..." << std::endl;
      runAlgorithm<aifg::Wander>();
      break;
    case Option::kSeekDynamic:
      std::cout << "Running seek dynamic..." << std::endl;
      runAlgorithm<aifg::SeekDynamic>();
      break;
    }
  }
  return 0;
}