#include <chrono>
#include <iostream>
#include <thread>

#include <Tracy.hpp>

extern const char* const outside_printer = "Outside printer";
extern const char* const inside_printer = "Inside printer";

void printer()
{
  ZoneScoped;
  TracyMessageL("Printer");
  FrameMarkNamed(outside_printer);

  for (int i = 1; i <= 3; ++i) {
    FrameMarkNamed(inside_printer);
    std::this_thread::sleep_for(std::chrono::seconds(i));
    std::cout << "Printer Companion \n";
  }
}

int main(int argc, const char* argv[])
{
  for (int i = 0; i < 10; ++i) {
    ZoneScoped;
    std::cout << "Hello Tracy" << std::endl;
    printer();
  }
  return 0;
}