#ifndef CLASSES_USER_HPP
#define CLASSES_USER_HPP

#include <memory>

namespace user
{

enum class ActionType { RUN = 0, JUMP, SWIM };

template <typename Actions> class User
{
public:
  User(const Actions& actions) : actions_(actions) {}
  ~User() = default;

  void PerformAction(const ActionType& type)
  {
    switch (type) {
    case ActionType::RUN:
      actions_.Run();
      break;
    case ActionType::JUMP:
      actions_.Jump();
      break;
    case ActionType::SWIM:
      actions_.Swim();
      break;
    }
  }

private:
  Actions actions_;
};

} // namespace user

#endif