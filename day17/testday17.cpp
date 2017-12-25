#include "gtest/gtest.h"
#include "day17.h"

TEST(DAY17, TestSolvePart1)
{
  unsigned int actual = Day17::solve_part1(3);
  ASSERT_EQ(638, actual);
}
