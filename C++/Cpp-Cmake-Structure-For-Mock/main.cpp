#include <iostream>
#include <memory>

#include <classes/animal.hpp>
#include <classes/user.hpp>
#include <classes/user_actions.hpp>

void fun(const animals::Animal& animal)
{
  const animals::Animal& a = animal;
  a.Run();
}

int main(int argc, const char** argv)
{
  std::unique_ptr<animals::Animal> animal = animals::GetAnimal(54.0f);
  animal->Run();
  animal->Eat(125.0f);
  fun(*animal);
  std::cout << "Shared approach" << std::endl;
  std::shared_ptr<animals::Animal> animal_shared = animals::GetAnimalShared(54.0f);
  animal_shared->Run();
  animal_shared->Eat(125.0f);
  fun(*animal_shared);

  std::cout << "Now with template mocking class\n";
  user::UserActions actions;

  user::User<user::UserActions> user(actions);
  user.PerformAction(user::ActionType::JUMP);
  user.PerformAction(user::ActionType::RUN);
  user.PerformAction(user::ActionType::SWIM);
  return 0;
}