//
// Created by wuggy on 07/12/2017.
//

#include "gtest/gtest.h"

#include "day06.h"

TEST(DAY06, Parts1And2Case1)
{
  std::vector<std::size_t> banks = {0, 2, 7, 0};
  std::pair<std::size_t, std::size_t> actual = Day6::solve(banks);
  ASSERT_EQ(actual.first, 5);
  ASSERT_EQ(actual.second, 4);
}

