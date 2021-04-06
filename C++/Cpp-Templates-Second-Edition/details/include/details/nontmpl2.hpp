#ifndef NON_TMPL2_HPP
#define NON_TMPL2_HPP

#include <string>

namespace details
{

template<typename T>
std::string f2(T&) {
  return "Template";
}

std::string f2(const int&) {
  return "Function";
}

} // namespace details

#endif // NON_TMPL2_HPP