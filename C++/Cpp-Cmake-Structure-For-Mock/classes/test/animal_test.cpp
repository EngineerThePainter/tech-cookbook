#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <classes/animal.hpp>

#include "animal_mock.hpp"

namespace animals
{
namespace test
{

namespace
{
class AnimalUser
{
public:
  AnimalUser(std::shared_ptr<animals::Animal> animal) : animal_(animal) {}
  void Use() { animal_->Run(); }

private:
  std::shared_ptr<animals::Animal> animal_;
};
} // namespace

TEST(AnimalTest, Test1)
{
  std::shared_ptr<AnimalMock> mock_animal = std::make_shared<AnimalMock>();
  AnimalUser user(mock_animal);
  EXPECT_CALL(*mock_animal, Run());
  user.Use();
}
} // namespace test
} // namespace animals