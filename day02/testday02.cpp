//
// Created by wuggy on 01/12/2017.
//

#include "gtest/gtest.h"

#include "day02.h"
#include "../utils/aocutils.h"

TEST(DAY02, Part1Case1)
{
  std::istringstream ss("5 1 9 5\n7 5 3\n2 4 6 8\n");
  std::vector< std::vector<std::size_t> > sheet = AOCUtils::parseByLines<std::vector<std::size_t> >(ss, AOCUtils::parseItem<std::size_t>);

  auto actual = Day2::solve_part1(sheet);
  ASSERT_EQ(actual, 18);
}

TEST(DAY02, Part2Case1)
{
  std::istringstream ss("5 9 2 8\n9 4 7 3\n3 8 6 5\n");
  std::vector< std::vector<std::size_t> > sheet = AOCUtils::parseByLines<std::vector<std::size_t> >(ss, AOCUtils::parseItem<std::size_t>);

  auto actual = Day2::solve_part2(sheet);
  ASSERT_EQ(actual, 9);
}

