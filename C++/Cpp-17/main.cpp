#include <filesystem>
#include <iostream>

// From cpp reference
void demo_status(const std::filesystem::path &p, std::filesystem::file_status s)
{
  std::cout << p;
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
  const std::filesystem::path path_dir("./bin/test_dir/");
  std::cout << std::boolalpha;
  demo_status(path_dir, std::filesystem::status(path_dir));
}

int main()
{
  std::cout << "********** C++ 17 **********\n";
  std::cout << "Some from the C++ reference, some written by myself\n";
  FileSystemLibrary();
}