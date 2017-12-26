#include "gtest/gtest.h"
#include "day20.h"

#include "../utils/aocutils.h"

TEST(DAY20, TestSolvePart2)
{
  std::istringstream iss(
      "p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>\n"
      "p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>\n"
      "p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>\n"
      "p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>\n");

  std::vector<Day20::particle> particles = AOCUtils::parseByLines<Day20::particle>(iss, Day20::parse_particle);

  int actual = Day20::solve_part2(particles);
  ASSERT_EQ(1, actual);
}

TEST(DAY20, TestProjectTime)
{
  Day20::particle p;
  p.p = {-833,-499,-1391};
  p.v = {84,17,61};
  p.a = {-4,1,1};

  auto p1 = Day20::project_to_time(p, 1);
  EXPECT_EQ(p1, Day20::vec3(-753,-481,-1329));

  auto p2 = Day20::project_to_time(p, 2);
  EXPECT_EQ(p2, Day20::vec3(-677,-462,-1266));
}
