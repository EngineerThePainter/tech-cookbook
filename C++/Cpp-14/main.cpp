#include <iostream>

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

int main()
{
  std::cout << "********** C++ 14 **********\n";
  VariableTemplate();
  GenericLambda();
  LambdaWithDefaultParam();
  RelaxedConstexprFunction();
  BinaryLiteral();
  DigitSeparator();
  ReturnTypeDeduction();
  AggregateInitializationWithDefaultNonStaticInitializers();
}