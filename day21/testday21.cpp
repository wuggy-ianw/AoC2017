#include "gtest/gtest.h"
#include "day21.h"

TEST(DAY21, TestParse)
{
  std::istringstream iss("../.# => ##./#../...\n"
                         ".#./..#/### => #..#/..../..../#..#\n");

  auto actual = Day21::parse_rules(iss);
  ASSERT_EQ(actual.size(), 2);

  ASSERT_EQ(actual[0].source, Day21::pattern::from_human_readable(2, 0b0001));
  ASSERT_EQ(actual[0].target, Day21::pattern::from_human_readable(3, 0b110100000));

  ASSERT_EQ(actual[1].source, Day21::pattern::from_human_readable(3, 0b010001111));
  ASSERT_EQ(actual[1].target, Day21::pattern::from_human_readable(4, 0b1001000000001001));
}

TEST(DAY21, TestFlippedX)
{
  ASSERT_EQ(Day21::pattern::from_human_readable(2, 0b0001).flipped_x(), Day21::pattern::from_human_readable(2, 0b0010));
  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b110100000).flipped_x(), Day21::pattern::from_human_readable(3, 0b011001000));

  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b010001111).flipped_x(), Day21::pattern::from_human_readable(3, 0b010100111));
  ASSERT_EQ(Day21::pattern::from_human_readable(4, 0b1001000000001001).flipped_x(), Day21::pattern::from_human_readable(4, 0b1001000000001001));
}

TEST(DAY21, TestFlippedY)
{
  ASSERT_EQ(Day21::pattern::from_human_readable(2, 0b0001).flipped_y(), Day21::pattern::from_human_readable(2, 0b0100));
  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b110100000).flipped_y(), Day21::pattern::from_human_readable(3, 0b000100110));

  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b010001111).flipped_y(), Day21::pattern::from_human_readable(3, 0b111001010));
  ASSERT_EQ(Day21::pattern::from_human_readable(4, 0b1001000000001001).flipped_y(), Day21::pattern::from_human_readable(4, 0b1001000000001001));
}

TEST(DAY21, TestRotateCW)
{
  // 00 -> 00   110 -> 011
  // 01    10   100    001
  //            000    000
  ASSERT_EQ(Day21::pattern::from_human_readable(2, 0b0001).rotate_cw(), Day21::pattern::from_human_readable(2, 0b0010));
  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b110100000).rotate_cw(), Day21::pattern::from_human_readable(3, 0b011001000));

  // 010 -> 100    1001 -> 1001
  // 001    101    0000    0000
  // 111    110    0000    0000
  //               1001    1001
  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b010001111).rotate_cw(), Day21::pattern::from_human_readable(3, 0b100101110));
  ASSERT_EQ(Day21::pattern::from_human_readable(4, 0b1001000000001001).rotate_cw(), Day21::pattern::from_human_readable(4, 0b1001000000001001));
}

TEST(DAY21, TestRotateCCW)
{
  // 00 -> 01   110 -> 000
  // 01    00   100    100
  //            000    110
  ASSERT_EQ(Day21::pattern::from_human_readable(2, 0b0001).rotate_ccw(), Day21::pattern::from_human_readable(2, 0b0100));
  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b110100000).rotate_ccw(), Day21::pattern::from_human_readable(3, 0b000100110));

  // 010 -> 011    1001 -> 1001
  // 001    101    0000    0000
  // 111    001    0000    0000
  //               1001    1001
  ASSERT_EQ(Day21::pattern::from_human_readable(3, 0b010001111).rotate_ccw(), Day21::pattern::from_human_readable(3, 0b011101001));
  ASSERT_EQ(Day21::pattern::from_human_readable(4, 0b1001000000001001).rotate_ccw(), Day21::pattern::from_human_readable(4, 0b1001000000001001));
}

TEST(DAY21, TestSolverExample)
{
  std::istringstream iss("../.# => ##./#../...\n"
                         ".#./..#/### => #..#/..../..../#..#\n");

  auto rules = Day21::parse_rules(iss);
  ASSERT_EQ(rules.size(), 2);

  // generate a ruleset from the rules...
  auto ruleset = Day21::make_ruleset(rules);

  std::vector<char> grid{0, 1, 0,
                         0, 0, 1,
                         1, 1, 1};

  auto grid_1 = Day21::step(ruleset, grid, 3);
  ASSERT_EQ(grid_1.first, 4);
  ASSERT_EQ(grid_1.second, (std::vector<char>{1, 0, 0, 1,
                                              0, 0, 0, 0,
                                              0, 0, 0, 0,
                                              1, 0, 0, 1}));

  auto grid_2 = Day21::step(ruleset, grid_1.second, grid_1.first);
  ASSERT_EQ(grid_2.first, 6);
  ASSERT_EQ(grid_2.second, (std::vector<char>{1, 1, 0, 1, 1, 0,
                                              1, 0, 0, 1, 0, 0,
                                              0, 0, 0, 0, 0, 0,
                                              1, 1, 0, 1, 1, 0,
                                              1, 0, 0, 1, 0, 0,
                                              0, 0, 0, 0, 0, 0}));
}

TEST(DAY21, TestSolvePart1)
{
  std::istringstream iss("../.# => ##./#../...\n"
                         ".#./..#/### => #..#/..../..../#..#\n");

  auto rules = Day21::parse_rules(iss);
  ASSERT_EQ(rules.size(), 2);

  int numset = Day21::solve_part1(rules, 2);
  ASSERT_EQ(numset, 12);
}
