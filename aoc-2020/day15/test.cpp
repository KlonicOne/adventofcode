#include <vector>

#include "day15.h"
#include "gtest/gtest.h"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(day15_test, false_test) { ASSERT_EQ(5, 5); }
