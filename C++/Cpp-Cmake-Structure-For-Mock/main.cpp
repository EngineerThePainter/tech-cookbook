#include <iostream>
#include <memory>

#include <classes/animal.hpp>

void fun(const animals::Animal& animal)
{
  const animals::Animal& a = animal;
  a.Run();
}

int main(int argc, const char** argv[])
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
  return 0;
}