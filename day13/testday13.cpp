//
// Created by wuggy on 22/12/2017.
//


#include "gtest/gtest.h"
#include "day13.h"

TEST(DAY13, TestParse)
{
  std::string example="0: 3\n"
      "1: 2\n"
      "4: 4\n"
      "6: 4\n";
  std::istringstream iss(example);
  std::vector<Day13::sentry> sentries = Day13::parse_sentries(iss);

  std::vector<Day13::sentry> expected = { Day13::sentry(0, 3),
                                          Day13::sentry(1, 2),
                                          Day13::sentry(4, 4),
                                          Day13::sentry(6, 4)};

  ASSERT_EQ(expected, sentries);
}

TEST(DAY13, TestSolvePart1)
{
  std::string example="0: 3\n"
      "1: 2\n"
      "4: 4\n"
      "6: 4\n";
  std::istringstream iss(example);
  std::vector<Day13::sentry> sentries = Day13::parse_sentries(iss);

  int actual = solve_part1(sentries);
  ASSERT_EQ(24, actual);
}

TEST(DAY13, TestSolvePart2)
{
  std::string example="0: 3\n"
      "1: 2\n"
      "4: 4\n"
      "6: 4\n";
  std::istringstream iss(example);
  std::vector<Day13::sentry> sentries = Day13::parse_sentries(iss);

  int actual = solve_part2(sentries);
  ASSERT_EQ(10, actual);
}

TEST(DAY13, TestSolvePart2Sensibly)
{
  std::string example="0: 3\n"
      "1: 2\n"
      "4: 4\n"
      "6: 4\n";
  std::istringstream iss(example);
  std::vector<Day13::sentry> sentries = Day13::parse_sentries(iss);

  int actual = solve_part2_sensibly(sentries);
  ASSERT_EQ(10, actual);
}
