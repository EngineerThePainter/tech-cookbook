#include <iostream>
#include <type_traits>

#include "algorithm_runner.hpp"
#include "kinematic/seek.hpp"

namespace
{
enum class Option { kExit = 0, kSeek = 1 };
}

int main(int argc, char** argv)
{
  int selected_option = static_cast<std::underlying_type_t<Option>>(Option::kExit);
  bool end = false;
  while (!end) {
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. Seek" << std::endl;
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
      aifg::Seek seek;
      aifg::AlgorithmRunner<aifg::Seek> runner(seek);
      runner.run();
      break;
    }
  }
  return 0;
}