#include <iostream>
#include <utility>

#include <Poco/ActiveMethod.h>

class ActiveAdder
{
public:
  ActiveAdder() : add(this, &ActiveAdder::addImpl) {}

  Poco::ActiveMethod<int, std::pair<int, int>, ActiveAdder> add;

private:
  int addImpl(const std::pair<int, int>& args) { return args.first + args.second; }
};

int main() {
    // Active method example
    ActiveAdder adder;
    Poco::ActiveResult<int> result = adder.add(std::make_pair(3, 4));
    result.wait();
    std::cout << "Active result: " << result.data() << std::endl;
    return 0;
}