#include "coroutine.hpp"

#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace
{
auto switchToNewThread(std::jthread& out)
{
  struct awaitable {
    std::jthread* p_out;
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> h)
    {
      std::jthread& out = *p_out;
      if (out.joinable()) {
        throw std::runtime_error("Output jthread parameter not empty");
      }
      out = std::jthread([h] { h.resume(); });
      std::cout << "New Thread ID " << out.get_id() << "\n";
    }
    void await_resume() {}
  };
  return awaitable(&out);
}

struct task {
  struct promise_type {
    task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

task resumingOnNewthread(std::jthread& out)
{
  std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << "\n";
  co_await switchToNewThread(out);
  std::cout << "Couroutine resumed on thread: " << std::this_thread::get_id() << "\n";
}
} // namespace

void coroutine()
{
  std::cout << "Coroutines \n" << std::endl;
  std::cout << "co_await\n";
  std::jthread out;
  resumingOnNewthread(out);
}
