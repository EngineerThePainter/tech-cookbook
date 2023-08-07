#include <iostream>

#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>

class Source
{
public:
  Poco::BasicEvent<int> event_;

  void callEvent(int n) { event_(this, n); }
};

class Target
{
public:
  void onEvent(const void* sender, int& arg) { std::cout << "onEvent: " << arg << std::endl; }
};

int main() {
  Source source;
  Target target;

  source.event_ += Poco::delegate(&target, &Target::onEvent);
  source.callEvent(42);
  source.event_ -= Poco::delegate(&target, &Target::onEvent);

  return 0;
}