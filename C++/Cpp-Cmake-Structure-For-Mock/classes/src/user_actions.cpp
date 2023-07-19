#include "classes/user_actions.hpp"

#include <iostream>

namespace user
{
void UserActions::Run() { std::cout << "I'm running\n"; }

void UserActions::Jump() { std::cout << "I'm jumping\n"; }

void UserActions::Swim() { std::cout << "I'm swimming\n"; }
} // namespace user