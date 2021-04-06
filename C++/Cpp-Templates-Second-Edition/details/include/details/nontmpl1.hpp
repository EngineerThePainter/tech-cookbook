#ifndef NON_TMPL1_HPP
#define NON_TMPL1_HPP

#include <string>

namespace details
{

template<typename T>
std::string f(T) {
  return "Template";
}

std::string f(int&) {
  return "Function";
}

} // namespace details

#endif // NON_TMPL1_HPP