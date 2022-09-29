#include <gtest/gtest.h>

#include <classes/user.hpp>

#include "user_actions_mock.hpp"

namespace user
{
namespace test
{
TEST(UserTest, Test1)
{
  testing::StrictMock<UserActionsMock> mock;

  User<UserActionsMock> user(mock);
  EXPECT_CALL(mock, Run());
  EXPECT_CALL(mock, Jump()).Times(2);
  EXPECT_CALL(mock, Swim());

  user.PerformAction(user::ActionType::RUN);
  user.PerformAction(user::ActionType::JUMP);
  user.PerformAction(user::ActionType::JUMP);
  user.PerformAction(user::ActionType::SWIM);
}
} // namespace test
} // namespace user