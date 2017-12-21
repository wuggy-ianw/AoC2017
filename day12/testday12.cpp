//
// Created by wuggy on 21/12/2017.
//

#include "gtest/gtest.h"
#include "day12.h"




TEST(DAY12, TestParse)
{
  std::string example = "0 <-> 2\n"
      "1 <-> 1\n"
      "2 <-> 0, 3, 4\n"
      "3 <-> 2, 4\n"
      "4 <-> 2, 3, 6\n"
      "5 <-> 6\n"
      "6 <-> 4, 5\n";
  std::istringstream iss(example);
  std::map<int, Day12::program> parsed = Day12::parse_input(iss);

  std::map<int, Day12::program> expected =
      {
        std::make_pair(0, Day12::program{0, {2}}),
        std::make_pair(1, Day12::program{1, {1}}),
        std::make_pair(2, Day12::program{2, {0, 3, 4}}),
        std::make_pair(3, Day12::program{3, {2, 4}}),
        std::make_pair(4, Day12::program{4, {2, 3, 6}}),
        std::make_pair(5, Day12::program{5, {6}}),
        std::make_pair(6, Day12::program{6, {4, 5}})
      };

  ASSERT_EQ(expected, parsed);
}

TEST(DAY12, TestSolvePart1)
{
  std::string example = "0 <-> 2\n"
      "1 <-> 1\n"
      "2 <-> 0, 3, 4\n"
      "3 <-> 2, 4\n"
      "4 <-> 2, 3, 6\n"
      "5 <-> 6\n"
      "6 <-> 4, 5\n";
  std::istringstream iss(example);
  std::map<int, Day12::program> programs = Day12::parse_input(iss);

  int actual = Day12::solve_part1(programs);
  ASSERT_EQ(6, actual);
}

TEST(DAY12, TestSolvePart2)
{
  std::string example = "0 <-> 2\n"
      "1 <-> 1\n"
      "2 <-> 0, 3, 4\n"
      "3 <-> 2, 4\n"
      "4 <-> 2, 3, 6\n"
      "5 <-> 6\n"
      "6 <-> 4, 5\n";
  std::istringstream iss(example);
  std::map<int, Day12::program> programs = Day12::parse_input(iss);

  int actual = Day12::solve_part2(programs);
  ASSERT_EQ(2, actual);
}

