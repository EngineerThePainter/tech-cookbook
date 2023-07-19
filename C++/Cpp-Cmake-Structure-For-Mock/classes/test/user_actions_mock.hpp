#include <gmock/gmock.h>

namespace user
{
namespace test
{

class UserActionsMock
{
public:
  UserActionsMock() {}
  UserActionsMock(const UserActionsMock& other) {}
  MOCK_METHOD(void, Run, ());
  MOCK_METHOD(void, Jump, ());
  MOCK_METHOD(void, Swim, ());
};

} // namespace test
} // namespace user