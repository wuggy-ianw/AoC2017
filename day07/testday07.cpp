//
// Created by wuggy on 13/12/2017.
//

#include "gtest/gtest.h"

#include "day07.h"
#include "../utils/aocutils.h"

TEST(DAY07, TestParse1)
{
  Day7::Program program = Day7::Program::parse("vvwrg (51)");
  Day7::Program expected = {"vvwrg", 51};
  ASSERT_EQ(program.name, expected.name);
  ASSERT_EQ(program.weight, expected.weight);
  ASSERT_EQ(program.child_names, expected.child_names);
}

TEST(DAY07, TestParse2)
{
  Day7::Program program = Day7::Program::parse("uglvj (99) -> ymfjt");
  Day7::Program expected = {"uglvj", 99, {"ymfjt"}};
  ASSERT_EQ(program.name, expected.name);
  ASSERT_EQ(program.weight, expected.weight);
  ASSERT_EQ(program.child_names, expected.child_names);
}

TEST(DAY07, TestParse3)
{
  Day7::Program program = Day7::Program::parse("zfotzg (45) -> ovomgd, mqhwlq");
  Day7::Program expected = {"zfotzg", 45, {"ovomgd", "mqhwlq"}};
  ASSERT_EQ(program.name, expected.name);
  ASSERT_EQ(program.weight, expected.weight);
  ASSERT_EQ(program.child_names, expected.child_names);
}

TEST(DAY07, TestParse4)
{
  Day7::Program program = Day7::Program::parse("yciccp (173) -> ijpsv, fjtafl, lxwntcm, saacvs");
  Day7::Program expected = {"yciccp", 173, {"ijpsv", "fjtafl", "lxwntcm", "saacvs"}};
  ASSERT_EQ(program.name, expected.name);
  ASSERT_EQ(program.weight, expected.weight);
  ASSERT_EQ(program.child_names, expected.child_names);
}


TEST(DAY07, SimpleTreeify)
{
  std::string s = "pbga (66)\n"
      "xhth (57)\n"
      "ebii (61)\n"
      "havc (66)\n"
      "ktlj (57)\n"
      "fwft (72) -> ktlj, cntj, xhth\n"
      "qoyq (66)\n"
      "padx (45) -> pbga, havc, qoyq\n"
      "tknk (41) -> ugml, padx, fwft\n"
      "jptl (61)\n"
      "ugml (68) -> gyxo, ebii, jptl\n"
      "gyxo (61)\n"
      "cntj (57)\n";

  std::istringstream iss(s);
  std::vector<Day7::Program> programs = AOCUtils::parseByLines<Day7::Program>(iss, Day7::Program::parse );

  Day7::Program& root = Day7::make_tree(programs);
  ASSERT_EQ(root.name, "tknk");

  // sort the children based on their name so we can do saner comparisons
  for (Day7::Program& p : programs)
  {
    std::sort(p.children.begin(), p.children.end(), [](const Day7::Program& a, const Day7::Program& b){return a.name < b.name;});
  }

  ASSERT_EQ(root.children[0].get().name, "fwft");
  ASSERT_EQ(root.children[1].get().name, "padx");
  ASSERT_EQ(root.children[2].get().name, "ugml");

  Day7::Program& fwft = root.children[0];
  ASSERT_EQ(fwft.children[0].get().name, "cntj");
  ASSERT_EQ(fwft.children[1].get().name, "ktlj");
  ASSERT_EQ(fwft.children[2].get().name, "xhth");

  Day7::Program& padx = root.children[1];
  ASSERT_EQ(padx.children[0].get().name, "havc");
  ASSERT_EQ(padx.children[1].get().name, "pbga");
  ASSERT_EQ(padx.children[2].get().name, "qoyq");

  Day7::Program& ugml = root.children[2];
  ASSERT_EQ(ugml.children[0].get().name, "ebii");
  ASSERT_EQ(ugml.children[1].get().name, "gyxo");
  ASSERT_EQ(ugml.children[2].get().name, "jptl");
}



