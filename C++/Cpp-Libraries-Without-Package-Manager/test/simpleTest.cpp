#include <gtest/gtest.h>

namespace test {
  TEST(SimpleTest, TrueAssertion) {
    ASSERT_TRUE(true);
  }

  TEST(SimpleTest, FalseAssertion) {
    ASSERT_FALSE(false);
  }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}