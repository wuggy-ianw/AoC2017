#include "gtest/gtest.h"
#include "day22.h"
#include "../utils/aocutils.h"


TEST(DAY22, TestExample)
{
  std::istringstream iss("..#\n"
                         "#..\n"
                         "...\n");
  std::vector<std::string> input = AOCUtils::parseByLines<std::string>(iss, [](const std::string& s)->std::string{return s;});

  // check the start position
  Day22::sparse_grid grid;
  auto start_point = Day22::populate_grid(grid, input);
  ASSERT_EQ(start_point.first, 1);
  ASSERT_EQ(start_point.second, 1);

  // check the initial grid
  ASSERT_EQ(grid.at(2,0), '#');
  ASSERT_EQ(grid.at(0,1), '#');
  ASSERT_EQ(grid.at(0,0), '.');
  ASSERT_EQ(grid.at(1,1), '.');
  ASSERT_EQ(grid.at(2,2), '.');
  ASSERT_EQ(grid.at(-50,-50), '.');
  ASSERT_EQ(grid.at(50,50), '.');

  ASSERT_EQ(grid.grid.size(), 2);

  // check the first few iterations...
  Day22::ant a(start_point.first, start_point.second, Day22::ant::Up);

  bool infected1 = Day22::step(grid, a, Day22::solve_part1_change_state);
  ASSERT_TRUE(infected1);
  ASSERT_EQ(grid.at(1,1), '#');
  ASSERT_EQ(grid.grid.size(), 3);

  bool infected2 = Day22::step(grid, a, Day22::solve_part1_change_state);
  ASSERT_FALSE(infected2);
  ASSERT_EQ(grid.at(0,1), '.');
  ASSERT_EQ(grid.grid.size(), 2);

  bool infected3 = Day22::step(grid, a, Day22::solve_part1_change_state);
  ASSERT_TRUE(infected3);

  bool infected4 = Day22::step(grid, a, Day22::solve_part1_change_state);
  ASSERT_TRUE(infected4);

  bool infected5 = Day22::step(grid, a, Day22::solve_part1_change_state);
  ASSERT_TRUE(infected5);

  bool infected6 = Day22::step(grid, a, Day22::solve_part1_change_state);
  ASSERT_TRUE(infected6);

  ASSERT_EQ(grid.at(0,0), '#');
  ASSERT_EQ(grid.at(-1,0), '#');
  ASSERT_EQ(grid.at(-1,1), '#');
  ASSERT_EQ(grid.at(0,1), '#');
  ASSERT_EQ(grid.at(1,1), '#');
  ASSERT_EQ(grid.at(2,0), '#');
  ASSERT_EQ(grid.grid.size(), 6);
}


TEST(DAY22, TestSolvePart1_1)
{
  std::istringstream iss("..#\n"
                         "#..\n"
                         "...\n");
  std::vector<std::string> input = AOCUtils::parseByLines<std::string>(iss, [](const std::string& s)->std::string{return s;});

  Day22::sparse_grid grid;
  auto start_point = Day22::populate_grid(grid, input);

  unsigned int infected = Day22::solve_part1(grid, start_point.first, start_point.second, 70);
  ASSERT_EQ(41, infected);
}

TEST(DAY22, TestSolvePart1_2)
{
  std::istringstream iss("..#\n"
                         "#..\n"
                         "...\n");
  std::vector<std::string> input = AOCUtils::parseByLines<std::string>(iss, [](const std::string& s)->std::string{return s;});

  Day22::sparse_grid grid;
  auto start_point = Day22::populate_grid(grid, input);

  unsigned int infected = Day22::solve_part1(grid, start_point.first, start_point.second, 10000);
  ASSERT_EQ(5587, infected);
}

TEST(DAY22, TestSolvePart2_1)
{
  std::istringstream iss("..#\n"
                         "#..\n"
                         "...\n");
  std::vector<std::string> input = AOCUtils::parseByLines<std::string>(iss, [](const std::string& s)->std::string{return s;});

  Day22::sparse_grid grid;
  auto start_point = Day22::populate_grid(grid, input);

  unsigned int infected = Day22::solve_part2(grid, start_point.first, start_point.second, 100);
  ASSERT_EQ(26, infected);
}

TEST(DAY22, TestSolvePart2_2)
{
  std::istringstream iss("..#\n"
                         "#..\n"
                         "...\n");
  std::vector<std::string> input = AOCUtils::parseByLines<std::string>(iss, [](const std::string& s)->std::string{return s;});

  Day22::sparse_grid grid;
  auto start_point = Day22::populate_grid(grid, input);

  unsigned int infected = Day22::solve_part2(grid, start_point.first, start_point.second, 10000000);
  ASSERT_EQ(2511944, infected);
}
