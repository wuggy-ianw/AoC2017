//
// Created by wuggy on 13/12/2017.
//

#ifndef AOC2017_DAY07_H
#define AOC2017_DAY07_H

#include <string>
#include <vector>
#include <functional>

namespace Day7
{
  struct Program
  {
    // populated by parsing
    std::string name;
    int weight;
    std::vector<std::string> child_names;

    // populate by tree-making
    std::vector<std::reference_wrapper<Program>> children;
    Program* parent = nullptr;

    // populated by search for unbalanced children
    int weight_including_children;

    static Program parse(const std::string& s);

    explicit Program() = default;
    Program(const std::string& name, int weight, const std::vector<std::string>& child_names = std::vector<std::string>())
      : name(name), weight(weight), child_names(child_names)
    {}
  };

  Program& make_tree(std::vector<Program>& programs);

  int solve_part2(Program& root);
}

#endif //AOC2017_DAY07_H
