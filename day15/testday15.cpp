//
// Created by wuggy on 23/12/2017.
//

#include "gtest/gtest.h"
#include "day15.h"

TEST(DAY15, TestGeneratorA)
{
  Day15::generator gen_a(65, 16807);
  uint32_t actual0 = gen_a.next();
  ASSERT_EQ(1092455, actual0);

  uint32_t actual1 = gen_a.next();
  ASSERT_EQ(1181022009, actual1);

  uint32_t actual2 = gen_a.next();
  ASSERT_EQ(245556042, actual2);

  uint32_t actual3 = gen_a.next();
  ASSERT_EQ(1744312007, actual3);

  uint32_t actual4 = gen_a.next();
  ASSERT_EQ(1352636452, actual4);
}

TEST(DAY15, TestGeneratorB)
{
  Day15::generator gen_b(8921, 48271);
  uint32_t actual0 = gen_b.next();
  ASSERT_EQ(430625591, actual0);

  uint32_t actual1 = gen_b.next();
  ASSERT_EQ(1233683848, actual1);

  uint32_t actual2 = gen_b.next();
  ASSERT_EQ(1431495498, actual2);

  uint32_t actual3 = gen_b.next();
  ASSERT_EQ(137874439, actual3);

  uint32_t actual4 = gen_b.next();
  ASSERT_EQ(285222916, actual4);
}

TEST(DAY15, TestSolvePart1)
{
  int actual = Day15::solve_part1(65, 8921);
  ASSERT_EQ(588, actual);
}

TEST(DAY15, TestSolvePart2)
{
  int actual = Day15::solve_part2(65, 8921);
  ASSERT_EQ(309, actual);
}
