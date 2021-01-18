#ifndef DEFINITIONS1_HPP
#define DEFINITIONS1_HPP

namespace details {

// Namespace scope class template
template<typename T>
class Data {
  public:
  static constexpr bool copyable = true;
};

// Namespace scope function template
template<typename T>
void log(T) {

}

// Namespace scope vatiable template (>=C++14)
template<typename T>
T zero = 0;

// Namespace scope variable template (>=C++14)
template<typename T>
bool dataCopyable = Data<T>::copyable;

// Namespace scope alias template
using DataList = Data<T*>;

} // details

#endif