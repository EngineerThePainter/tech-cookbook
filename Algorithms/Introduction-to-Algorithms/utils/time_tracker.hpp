#ifndef UTILS_TIME_TRACKER_HPP
#define UTILS_TIME_TRACKER_HPP

#include <chrono>
#include <functional>
#include <utility>

namespace utils
{

template <typename T, typename... Args> std::chrono::milliseconds runWithTimeMeasure(T& funToCall, Args&&... arguments)
{
  std::chrono::time_point start = std::chrono::high_resolution_clock::now();
  funToCall(std::forward<Args>(arguments)...);
  std::chrono::time_point end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

} // namespace utils

#endif // UTILS_TIME_TRACKER_HPP