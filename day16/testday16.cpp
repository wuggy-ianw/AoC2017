#include <fstream>
#include "gtest/gtest.h"
#include "day16.h"

TEST(DAY16, TestParse)
{
  std::istringstream iss("s1,x3/4,pe/b");
  std::vector<Day16::move> moves = Day16::parse_moves(iss);

  ASSERT_EQ(moves[0].type, Day16::move::Spin);
  ASSERT_EQ(moves[0].spin_size, 1);

  ASSERT_EQ(moves[1].type, Day16::move::Exchange);
  ASSERT_EQ(moves[1].swap_pos1, 3);
  ASSERT_EQ(moves[1].swap_pos2, 4);

  ASSERT_EQ(moves[2].type, Day16::move::Partner);
  ASSERT_EQ(moves[2].swap_program1, 'e');
  ASSERT_EQ(moves[2].swap_program2, 'b');
}


TEST(DAY16, TestSolvePart1)
{
  std::istringstream iss("s1,x3/4,pe/b");
  std::vector<Day16::move> moves = Day16::parse_moves(iss);

  std::string actual = Day16::solve_part1<5>(moves);
  ASSERT_EQ("baedc", actual);
}

TEST(DAY16, TestSolvePart2)
{
  std::istringstream iss("s1,x3/4,pe/b");
  std::vector<Day16::move> moves = Day16::parse_moves(iss);

  std::string actual = Day16::solve_part2_sensibly<5, 2>(moves);
  ASSERT_EQ("ceadb", actual);
}

TEST(DAY16, TestSolvePart2_harder)
{
  std::istringstream iss("s1,x3/4,pe/b");
  std::vector<Day16::move> moves = Day16::parse_moves(iss);

  std::string expected = Day16::solve<5, 1000>(moves);
  std::string actual = Day16::solve_part2_sensibly<5, 1000>(moves);
  ASSERT_EQ(expected, actual);
}

TEST(DAY16, TestSolvePart2_harder2)
{
  std::istringstream iss("s1,x3/4,pe/b");
  std::vector<Day16::move> moves = Day16::parse_moves(iss);

  std::string expected = Day16::solve<5, 10000>(moves);
  std::string actual = Day16::solve_part2_sensibly<5, 10000>(moves);
  ASSERT_EQ(expected, actual);
}


TEST(DAY16, TestSolvePart2_harder3)
{
  std::ifstream ifs("input.txt");
  std::vector<Day16::move> moves = Day16::parse_moves(ifs);

  std::string expected = Day16::solve<16, 1>(moves);
  std::string actual = Day16::solve_part2_sensibly<16, 1>(moves);
  ASSERT_EQ(expected, actual);
}


TEST(DAY16, TestSolvePart2_harder4)
{
  std::ifstream ifs("input.txt");
  std::vector<Day16::move> moves = Day16::parse_moves(ifs);

  std::string expected = Day16::solve<16, 2>(moves);
  std::string actual = Day16::solve_part2_sensibly<16, 2>(moves);
  ASSERT_EQ(expected, actual);
}

TEST(DAY16, TestSolvePart2_harder5)
{
  std::ifstream ifs("input.txt");
  std::vector<Day16::move> moves = Day16::parse_moves(ifs);

  std::string expected = Day16::solve<16, 1023>(moves);
  std::string actual = Day16::solve_part2_sensibly<16, 1023>(moves);
  ASSERT_EQ(expected, actual);
}
