#ifndef GREEDY_ACTIVITY_SELECTOR_HPP
#define GREEDY_ACTIVITY_SELECTOR_HPP

#include <vector>

namespace greedy
{
struct Activity {
  unsigned int start_time_;
  unsigned int end_time_;
};

std::vector<Activity> recursiveActivitySelector(std::vector<Activity>& activities, const unsigned int& k, const unsigned int& n);
std::vector<Activity> greedyActivitySelector(std::vector<Activity>& activities);

}

#endif