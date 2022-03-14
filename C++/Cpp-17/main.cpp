#include <any>
#include <filesystem>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <variant>

// From cpp reference
void demo_status(const std::filesystem::path &p, std::filesystem::file_status s)
{
  std::cout << p.string();
  // alternative: switch(s.type()) { case std::filesystem::file_type::regular: ...}
  if (std::filesystem::is_regular_file(s))
    std::cout << " is a regular file\n";
  if (std::filesystem::is_directory(s))
    std::cout << " is a directory\n";
  if (std::filesystem::is_block_file(s))
    std::cout << " is a block device\n";
  if (std::filesystem::is_character_file(s))
    std::cout << " is a character device\n";
  if (std::filesystem::is_fifo(s))
    std::cout << " is a named IPC pipe\n";
  if (std::filesystem::is_socket(s))
    std::cout << " is a named IPC socket\n";
  if (std::filesystem::is_symlink(s))
    std::cout << " is a symlink\n";
  if (!std::filesystem::exists(s))
    std::cout << " does not exist\n";
}

void FileSystemLibrary()
{
  std::cout << "*** File System\n";
  const std::filesystem::path path_dir("./bin/test_dir/");
  const std::filesystem::path path_file("./bin/test_dir/hello.txt");
  demo_status(path_dir, std::filesystem::status(path_dir));
  demo_status(path_dir, std::filesystem::status(path_file));
  std::cout << std::endl;
}

void Optional()
{
  std::cout << "*** Optional\n";
  std::optional<int> x;
  std::cout << std::boolalpha;
  std::cout << "X has value? " << x.has_value() << std::endl;
  x = 42;
  std::cout << "X has value? " << x.has_value() << std::endl;
  std::cout << std::endl;
}

void StringView()
{
  std::cout << "*** String View\n";
  constexpr std::string_view codes[]{"W", "w", "*W*", "*w*"};
  for (int y{}, p{}; y != 6; ++y, p = ((p + 1) % 4))
  {
    for (int x{}; x != 16; ++x)
      std::cout << codes[p];
    std::cout << '\n';
  }
  std::cout << std::endl;
}

int add(int x, int y) { return x + y; }

void Apply()
{
  std::cout << "*** Apply\n";
  std::tuple<int, int> int_tuple{1, 2};
  std::cout << std::get<0>(int_tuple) << " ";
  std::cout << std::get<1>(int_tuple) << " ";
  std::cout << std::apply(add, int_tuple);
  std::cout << std::endl;
}

void Searchers()
{
  std::cout << "*** Searchers\n";
  std::string in = "Lorem impsum dolor sit amet";
  std::string searching_elem = "dolor";
  auto it = std::search(in.begin(), in.end(), std::default_searcher(searching_elem.begin(), searching_elem.end()));
  if (it != in.end())
  {
    std::cout << "Found at offset " << it - in.begin() << std::endl;
  }
  std::cout << std::endl;
}

void Invoke()
{
  std::cout << "*** Invoke\n";
  auto lambda = [](int x)
  { std::cout << "Lambda has: " << x << std::endl; };
  std::invoke(lambda, 42);
  std::invoke(lambda, 56);
  std::cout << std::endl;
}

void Any()
{
  std::cout << "*** Any\n";
  std::any x;
  std::cout << std::boolalpha;
  std::cout << "X has value? " << x.has_value() << std::endl;
  x = 42;
  std::cout << x.type().name() << ": " << std::any_cast<int>(x) << std::endl;
  x = 42.4242;
  std::cout << x.type().name() << ": " << std::any_cast<double>(x) << std::endl;
  std::cout << std::endl;
}

template <typename... Args>
void printer(Args &&...args)
{
  (std::cout << ... << args) << '\n';
}

void FoldExpression()
{
  std::cout << "*** Fold expressions\n";
  printer(1, 2, 3, "Text");
  std::cout << std::endl;
}

template <typename T>
auto get_value(T t)
{
  if constexpr (std::is_pointer_v<T>)
    return *t; // deduces return type to int for T = int*
  else
    return t; // deduces return type to int for T = int
}

void ConstexprIf()
{
  std::cout << "*** Constexpr if\n";
  std::unique_ptr<int> x = std::make_unique<int>(42);
  std::cout << get_value(x.get()) << std::endl;
  std::cout << std::endl;
}

void Variant()
{
  std::cout << "*** Variant\n";
  std::variant<int, double> var;
  var = 42;
  std::cout << "Variant value " << std::get<int>(var) << std::endl;
  var = 42.4242;
  try
  {
    std::cout << "Variant int value when it's double " << std::get<int>(var) << std::endl;
  }
  catch (const std::bad_variant_access &ex)
  {
    std::cout << ex.what() << '\n';
  }

  std::cout << "Variant double value " << std::get<double>(var) << std::endl;

  std::cout << std::endl;
}

int main()
{
  std::cout << "********** C++ 17 **********\n";
  std::cout << "Some from the C++ reference, some written by myself\n";
  FileSystemLibrary();
  Optional();
  StringView();
  Apply();
  Searchers();
  Invoke();
  Any();
  FoldExpression();
  ConstexprIf();
  Variant();
}