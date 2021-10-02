#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>
#include <boost/optional/optional.hpp>

void runTutorial1() {
    constexpr int timeout = 5;
    std::cout << "*** Tutorial 1: Using a timer synchronously ***" << std::endl;
    boost::asio::io_context io;
    std::cout << "Deadline timer instance with "<< timeout << " seconds" << std::endl;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(timeout));
    std::cout << "Trigger timer wait()" << std::endl;
    t.wait();
    std::cout << "Hello Asio" << std::endl;
    std::cout << std::endl;
}

int main() {
  boost::optional<int> i;
  std::cout << "Example of the libraries" << std::endl;
  if (i) {
    std::cout << "Optional set" << std::endl;
  } else {
    std::cout << "Optional not set" << std::endl;
  }

  runTutorial1();
  

  boost::chrono::nanoseconds start;
  boost::chrono::nanoseconds end;
  boost::chrono::milliseconds d = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start);

  // d now holds the number of milliseconds from start to end.

  std::cout << d.count() << "ms\n";
}