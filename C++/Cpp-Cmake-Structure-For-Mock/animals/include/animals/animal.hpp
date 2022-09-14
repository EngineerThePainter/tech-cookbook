#ifndef ANIMALS_ANIMAL_HPP
#define ANIMALS_ANIMAL_HPP

#include <memory>

namespace animals
{
class Animal
{
public:
  virtual void Run() const = 0;
  virtual void Eat(float calories) = 0;
  virtual float Weight() = 0;
};

std::unique_ptr<Animal> GetAnimal(float weight);
std::shared_ptr<Animal> GetAnimalShared(float weight);
} // namespace animals

#endif