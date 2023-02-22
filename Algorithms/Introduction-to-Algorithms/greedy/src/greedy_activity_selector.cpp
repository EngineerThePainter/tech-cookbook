#include "greedy_activity_selector.hpp"

namespace greedy
{

std::vector<Activity> recursiveActivitySelector(std::vector<Activity>& activities, const unsigned int& k, const unsigned int& n)
{
  unsigned int m = k + 1;
  while (m < n && activities[m].start_time_ < activities[k].end_time_) {
    ++m;
  }
  if (m < n) {
    std::vector<Activity> to_return{activities[m]};
    auto vec = recursiveActivitySelector(activities, m, n);
    to_return.insert(to_return.end(), vec.begin(), vec.end());
    return to_return;
  }
  return {};
}

std::vector<Activity> greedyActivitySelector(std::vector<Activity>& activities)
{
  unsigned int n = activities.size();
  std::vector<Activity> activities_selected{activities[0]};
  unsigned int k = 1;
  for (unsigned int m = 2; m < activities.size(); ++m) {
    if (activities[m].start_time_ >= activities[k].end_time_) {
      activities_selected.push_back(activities[m]);
      k = m;
    }
  }
  return activities_selected;
}
} // namespace greedy
