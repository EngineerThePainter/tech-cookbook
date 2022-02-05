#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include <utility>
#include <vector>

template <typename T>
constexpr T pi = T(3.14159);

void VariableTemplate()
{
  std::cout << "Variable template 5.5 * pi<double>: " << 5.5 << " * " << pi<double> << " = " << 5.5 * pi<double> << std::endl;
  std::cout << "Variable template 5.5 * pi<int>: " << 5.5 << " * " << pi<int> << " = " << 5.5 * pi<int> << std::endl;
}

void GenericLambda()
{
  auto fun = [](const auto &x)
  { std::cout << "From generic lambda: " << x << std::endl; };
  fun(42);
}

void LambdaWithDefaultParam()
{
  auto func1 = [](int i = 6)
  { return i + 4; };
  std::cout << "func1: " << func1() << '\n';
  std::cout << "func1 with 3: " << func1(3) << '\n';
}

/** C++ 14 allows for local variables and loops in constexpr functions. */
constexpr unsigned int factorial(unsigned int n)
{
  unsigned int result = 1;
  for (unsigned int i = 1; i <= n; ++i)
  {
    result *= i;
  }
  return result;
}

void RelaxedConstexprFunction()
{
  std::cout << "Factorial by loop: " << factorial(5) << std::endl;
}

void BinaryLiteral()
{
  std::cout << "Binary: " << 0b101010 << std::endl;
}

void DigitSeparator()
{
  std::cout << "Digit separator: " << 100'000'000 << std::endl;
}

auto DeduceMe()
{
  return 42;
}

void ReturnTypeDeduction()
{
  std::cout << "Deduce: " << DeduceMe() << std::endl;
}

struct Point
{
  double x = 1.0;
  double y = 5.0;
};

void AggregateInitializationWithDefaultNonStaticInitializers()
{
  Point p{3.0, 2.0};
  std::cout << "Aggregate: " << p.x << " : " << p.y << std::endl;
}

struct PointUnique
{
  PointUnique(const double x, const double y) : x(x), y(y) {}

  const double x;
  const double y;
};

void MakeUnique()
{
  std::unique_ptr<PointUnique> p = std::make_unique<PointUnique>(2.0, 3.0);
  std::cout << "Make unique: " << p->x << " : " << p->y << std::endl;
}

class SharedMutex
{
  mutable std::shared_timed_mutex mut;

public:
  SharedMutex &operator=(const SharedMutex &other)
  {
    // requires exclusive ownership to write to *this
    std::unique_lock<std::shared_timed_mutex> lhs(mut, std::defer_lock);
    // requires shared ownership to read from other
    std::shared_lock<std::shared_timed_mutex> rhs(other.mut, std::defer_lock);
    std::lock(lhs, rhs);
    x = other.x;
    y = other.y;
    return *this;
  }

  int x = 5;
  int y = 7;
};

void SharedMutexSuperSimpleExample()
{
  SharedMutex sm;
  SharedMutex sm2;
  sm2.x = 10;
  sm2.y = 10;

  sm = sm2;

  std::cout << "Shared mutex " << sm.x << " : " << sm.y << std::endl;
}

template <typename T, T... ints>
void print_integer_sequence(const std::integer_sequence<T, ints...> &int_seq)
{
  std::cout << "The sequence of size " << int_seq.size() << "\n";
}

void IntegerSequence()
{
  std::integer_sequence<unsigned, 1, 2, 3, 4, 5, 6> sequence{};
  print_integer_sequence(sequence);
}

void Exchange()
{
  std::vector<int> vec{5, 6, 7, 8};
  for (const auto &v : vec)
  {
    std::cout << v << ", ";
  }
  std::cout << std::endl;
  std::exchange(vec, {1, 2, 3, 4});
  for (const auto &v : vec)
  {
    std::cout << v << ", ";
  }
  std::cout << std::endl;
}

void Quoted()
{
  std::stringstream ss;
  std::string in = "String with spaces and having \"quotes\" too";
  std::string out;

  auto show = [&](const auto &what)
  {
    &what == &in ? std::cout << "read in " << in << "\n"
                             << "stored as " << ss.str() << "\n"
                 : std::cout << "written out " << out << "\n\n";
  };

  ss << std::quoted(in);
  show(in);
  ss >> std::quoted(out);
  show(out);

  ss.str("");
  in = "String with spaces, and embedded $quotes$ too";
  const char delim{'$'};
  const char escape{'%'};

  ss << std::quoted(in, delim, escape);
  show(in);
  ss >> std::quoted(out, delim, escape);
  show(out);
}

int main()
{
  std::cout << "********** C++ 14 **********\n";
  std::cout << "Some from the C++ reference, some written by myself\n";
  VariableTemplate();
  GenericLambda();
  LambdaWithDefaultParam();
  RelaxedConstexprFunction();
  BinaryLiteral();
  DigitSeparator();
  ReturnTypeDeduction();
  AggregateInitializationWithDefaultNonStaticInitializers();
  MakeUnique();
  SharedMutexSuperSimpleExample();
  IntegerSequence();
  Exchange();
  Quoted();
}