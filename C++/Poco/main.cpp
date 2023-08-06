#include <iostream>
#include <utility>

#include <Poco/ActiveMethod.h>
#include <Poco/ActiveResult.h>
#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>

class Source {
    public:
    Poco::BasicEvent<int> event_;

    void callEvent(int n) {
        event_(this, n);
    }
};

class Target {
    public:
    void onEvent(const void* sender, int& arg) {
        std::cout << "onEvent: " << arg << std::endl;
    }
};

class ActiveAdder {
    public:
     ActiveAdder(): add(this, &ActiveAdder::addImpl) { }

     Poco::ActiveMethod<int, std::pair<int, int>, ActiveAdder> add;

     private:
     int addImpl(const std::pair<int, int>& args) {
         return args.first + args.second;
     } 
};

int main() {
    Source source;
    Target target;

    source.event_ += Poco::delegate(&target, &Target::onEvent);
    source.callEvent(42);
    source.event_ -= Poco::delegate(&target, &Target::onEvent);

    ActiveAdder adder;
    Poco::ActiveResult<int> result = adder.add(std::make_pair(3, 4));
    result.wait();
    std::cout << "Active result: " << result.data() << std::endl;
    return 0;
}