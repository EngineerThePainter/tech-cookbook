#include "animals/animal.hpp"

#include <iostream>

namespace animals
{
namespace
{
class AnimalImpl : public Animal
{
public:
  AnimalImpl(float weight) : weight_(weight) { std::cout << "AnimalImpl constructor" << std::endl; }
  AnimalImpl(AnimalImpl& AnimalImpl)
  {
    std::cout << "AnimalImpl copy constructor" << std::endl;
    this->weight_ = AnimalImpl.weight_;
  }
  AnimalImpl(AnimalImpl&& AnimalImpl)
  {
    std::cout << "AnimalImpl move constructor" << std::endl;
    this->weight_ = std::move(AnimalImpl.weight_);
  }
  void Run() const override { std::cout << "AnimalImpl runs" << std::endl; }

  void Eat(float calories) override
  {
    std::cout << "AnimalImpl eats: " << calories << " calories" << std::endl;
  }

  float Weight() override { return weight_; }

private:
  float weight_;
};
} // namespace

std::unique_ptr<Animal> GetAnimal(float weight) { return std::make_unique<AnimalImpl>(weight); }
std::shared_ptr<Animal> GetAnimalShared(float weight)
{
  return std::make_shared<AnimalImpl>(weight);
}

} // namespace animals