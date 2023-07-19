#include <gmock/gmock.h>

#include <classes/animal.hpp>

namespace animals
{
class AnimalMock : public Animal
{
public:
  ~AnimalMock() override {}
  MOCK_METHOD(void, Run, (), (const, override));
  MOCK_METHOD(void, Eat, (float), (override));
  MOCK_METHOD(float, Weight, (), (override));
};
} // namespace animals