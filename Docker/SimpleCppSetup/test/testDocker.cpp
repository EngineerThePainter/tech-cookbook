#include <gtest/gtest.h>

namespace docker {
namespace test {

TEST(DockerTest, SimpleTest) {
  ASSERT_TRUE(true);
}

}
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}