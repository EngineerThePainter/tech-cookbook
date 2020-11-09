#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

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

void print2(const boost::system::error_code& /*e*/) {
    std::cout << "Hello Asio" << std::endl;
}

void runTutorial2() {
    constexpr int timeout = 5;
    std::cout << "*** Tutorial 2: Using a timer asynchronously ***" << std::endl;
    boost::asio::io_context io;
    std::cout << "Deadline timer instance with "<< timeout << " seconds" << std::endl;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(timeout));
    std::cout << "Trigger timer async_wait()" << std::endl;
    t.async_wait(&print2);
    std::cout << "Async wait is ongoing. Calling io.run()." << std::endl;
    std::cout << "If not called callback for asynch_wait will not be invoked." << std::endl;
    io.run();
    std::cout << std::endl;
}

void print3(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* t, int* count) {
    if (*count < 5) {
        std::cout << "Count: " << *count << std::endl;
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print3, boost::asio::placeholders::error, t, count));
    }
}

void runTutorial3() {
    int count = 0;
    constexpr int timeout = 1;
    std::cout << "*** Tutorial 3: Binding arguments to a handler ***" << std::endl;
    boost::asio::io_context io;
    std::cout << "Deadline timer instance with "<< timeout << " seconds" << std::endl;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(timeout));
    std::cout << "Trigger timer async_wait()" << std::endl;
    t.async_wait(boost::bind(print3, boost::asio::placeholders::error, &t, &count));
    std::cout << "Async wait is ongoing. Calling io.run()." << std::endl;
    std::cout << "If not called callback for asynch_wait will not be invoked." << std::endl;
    io.run();
    std::cout << "Count called from main function: " << count << std::endl;
    std::cout << std::endl;
}

class Printer {
public:
    Printer(boost::asio::io_context& io): 
    timer(io, boost::posix_time::seconds(1)),
    count(0)
    {
        timer.async_wait(boost::bind(&Printer::print, this));
    }

    ~Printer() {
        std::cout << "Count called from Printer destructor: " << count << std::endl;
    }

    void print() {
        if (count < 5) {
            std::cout << "Count: " << count << std::endl;
            ++count;

            timer.expires_at(timer.expires_at() + boost::posix_time::seconds(1));
            timer.async_wait(boost::bind(&Printer::print, this));
        }
    }

private:
    boost::asio::deadline_timer timer;
    int count;
};

void runTutorial4() {
    std::cout << "*** Tutorial 4: Using a member function as a handler ***" << std::endl;
    boost::asio::io_context io;
    std::cout << "Creating Printer object" << std::endl;
    Printer printer(io);
    std::cout << "Calling io_context::run()" << std::endl;
    io.run();
    std::cout << std::endl;
}

class PrinterMultithread {

public:
    PrinterMultithread(boost::asio::io_context& io): 
    strand(io),
    timer1(io, boost::posix_time::seconds(1)),
    timer2(io, boost::posix_time::seconds(1)),
    count(0)
    {
        timer1.async_wait(boost::asio::bind_executor(strand, boost::bind(&PrinterMultithread::print1, this)));
        timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&PrinterMultithread::print2, this)));
    }

    ~PrinterMultithread() {
        std::cout << "Count called from Printer destructor: " << count << std::endl;
    }

    void print1() {
        if (count < 10) {
            std::cout << "Count Timer 1: " << count << std::endl;
            ++count;

            timer1.expires_at(timer1.expires_at() + boost::posix_time::seconds(1));
            timer1.async_wait(boost::asio::bind_executor(strand, boost::bind(&PrinterMultithread::print1, this)));
        }
    }

    void print2() {
        if (count < 10) {
            std::cout << "Count Timer 2: " << count << std::endl;
            ++count;

            timer2.expires_at(timer2.expires_at() + boost::posix_time::seconds(1));
            timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&PrinterMultithread::print2, this)));
        }
    }

private:
    boost::asio::io_context::strand strand;
    boost::asio::deadline_timer timer1;
    boost::asio::deadline_timer timer2;
    int count;
};

void runTutorial5() {
    std::cout << "*** Tutorial 5: Synchronising handlers in multithreaded programs ***" << std::endl;
    boost::asio::io_context io;
    std::cout << "Creating PrinterMultithread object" << std::endl;
    PrinterMultithread printer(io);
    std::cout << "Binding boost io_context to thread" << std::endl;
    std::thread t(boost::bind(&boost::asio::io_context::run, &io));
    std::cout << "Calling io_context::run()" << std::endl;
    io.run();
    std::cout << "Calling join() on thread" << std::endl;
    t.join();
    std::cout << std::endl;
}

int main() {

    runTutorial1();
    runTutorial2();
    runTutorial3();
    runTutorial4();
    runTutorial5();
    return 0;
}