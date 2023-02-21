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
    bool await_ready()
    {
      std::cout << "Await Ready\n";
      return false;
    }
    void await_suspend(std::coroutine_handle<> h)
    {
      std::cout << "Await Suspend\n";
      std::jthread& out = *p_out;
      if (out.joinable()) {
        throw std::runtime_error("Output jthread parameter not empty");
      }
      out = std::jthread([h] { h.resume(); });
      std::cout << "New Thread ID " << out.get_id() << "\n";
    }
    void await_resume() { std::cout << "Await Resume\n"; }
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

template <typename T> struct Generator {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    T value_;
    std::exception_ptr exception_;

    Generator get_return_object() { return Generator(handle_type::from_promise(*this)); }

    std::suspend_always initial_suspend()
    {
      std::cout << "Initial suspend\n";
      return {};
    }

    std::suspend_always final_suspend() noexcept
    {
      std::cout << "Final suspend\n";
      return {};
    }

    void unhandled_exception() { exception_ = std::current_exception(); }

    template <std::convertible_to<T> From> std::suspend_always yield_value(From&& from)
    {
      std::cout << "Yield Value \n";
      value_ = std::forward<From>(from); // catching the result in promise
      return {};
    }

    void return_void() { std::cout << "Return void\n"; }
  };

  handle_type h_;
  Generator(handle_type h) : h_(h) {}
  ~Generator() { h_.destroy(); }

  explicit operator bool()
  {
    fill();
    return !h_.done();
  }

  T operator()()
  {
    fill();
    full_ = false;
    return std::move(h_.promise().value_);
  }

private:
  bool full_ = false;
  void fill()
  {
    if (!full_) {
      h_();
      if (h_.promise().exception_) {
        std::rethrow_exception(h_.promise().exception_);
      }
      full_ = true;
    }
  }
};

Generator<std::uint64_t> fibonacci_sequence(unsigned n)
{
  if (n == 0) {
    co_return;
  }

  if (n > 94) {
    throw std::runtime_error("Too big. It will overflow");
  }

  co_yield 0;

  if (n == 1) {
    co_return;
  }

  co_yield 1;

  if (n == 2) {
    co_return;
  }

  std::uint64_t a = 0;
  std::uint64_t b = 1;

  for (unsigned i = 2; i < n; ++i) {
    std::uint64_t s = a + b;
    co_yield s;
    a = b;
    b = s;
  }
}

void generate_sequence()
{
  try {
    auto gen = fibonacci_sequence(10);
    for (int j = 0; gen; j++) {
      std::cout << "fib(" << j << ")= " << gen() << "\n";
    }
  } catch (const std::exception& ex) {
    std::cerr << "Exception: " << ex.what() << "\n";
  } catch (...) {
    std::cerr << "Unkown exception\n";
  }
}

} // namespace

void coroutine()
{
  std::cout << "Coroutines \n" << std::endl;
  std::cout << "co_await\n";
  std::jthread out;
  resumingOnNewthread(out);
  out.join();
  std::cout << "\nCoroutine co_yield\n";
  generate_sequence();
}
