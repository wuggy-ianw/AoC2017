//
// Created by wuggy on 13/12/2017.
//

#include "day07.h"
#include "../utils/aocutils.h"

#include <cassert>
#include <sstream>
#include <map>
#include <limits>

Day7::Program Day7::Program::parse(const std::string &s)
{
  Program p;

  std::istringstream ss(s);
  ss >> std::skipws >> p.name >> AOCUtils::literal("(") >> p.weight >> AOCUtils::literal(")");
  assert(bool(ss));

  // now try and parse the child_names...
  ss >> AOCUtils::literal("->");
  while (true)
  {
    // try and read a new childname
    std::string childname;
    ss >> childname;

    // if there isn't one, we're done
    if (!bool(ss)) break;

    // if we've got a comma at the end, truncate it and try again
    assert(childname.length() > 0);
    if (childname.back() == ',') childname.pop_back();
    p.child_names.push_back(childname);
  }

  return p;
}



Day7::Program& Day7::make_tree(std::vector<Day7::Program>& programs)
{
  // make a map from names to programs
  std::map<std::string, std::reference_wrapper<Program>> named_programs;
  for (Program& p : programs)
  {
    named_programs.emplace(p.name, std::ref(p));
  }

  // now iterate again, and resolve the parent and child references
  for (Program& p : programs)
  {
    for (std::string& child_name : p.child_names)
    {
      Program& child = named_programs.at(child_name);
      child.parent = &p;

      p.children.push_back(std::ref(child));
    }
  }

  // now iterate again and find the node with no parent
  // (iterate through them all to check there's only one root?)
  Program* root = nullptr;
  for (Program& p : programs)
  {
    if (p.parent == nullptr)
    {
      assert(root == nullptr);
      root = &p;
    }
  }

  assert(root != nullptr);
  return *root;
}


namespace
{
  int compute_total_weights(Day7::Program& node)
  {
    int sum = node.weight;
    for (Day7::Program& child : node.children)
    {
      sum += compute_total_weights(child);
    }

    node.weight_including_children = sum;
    return sum;
  }

  int find_correct_weight(Day7::Program& node)
  {
    // tally votes of the weights of our children
    std::map<int, int> votes;
    for (Day7::Program& child : node.children)
    {
      votes[child.weight_including_children]++;
    }

    // if all the votes landed in the same entry (or we have no children, and so no entries), then we're balanced...
    bool balanced = votes.size() <= 1;
    if (balanced)
    {
      return 0; // this isn't the correct weight... it's probably our parent that needs correcting!
    }

    // find the weight of the child which had only one vote
    int unique_weight = std::numeric_limits<int>::min();
    int correct_weight = std::numeric_limits<int>::min();
    for (auto entry : votes)
    {
      if (entry.second == 1)
      {
        // should only be one
        assert(unique_weight == std::numeric_limits<int>::min());
        unique_weight = entry.first;
      }
      else
      {
        // preserve the correct 'sibling' weight
        correct_weight = entry.first;
      }
    }
    // should be exactly one
    assert(unique_weight != std::numeric_limits<int>::min() );

    for (Day7::Program& child : node.children)
    {
      if (child.weight_including_children == unique_weight)
      {
        // this child has a unique weight... but it may be
        // because one of it's children are in error
        int found_correct_weight = find_correct_weight(child);
        if (found_correct_weight>0) return found_correct_weight;

        // this child's weight is bad...!
        int adjustment = unique_weight - correct_weight;
        return child.weight - adjustment;
      }
    }

    // should never reach here... this means we're not balanced
    // but none of our children have a mismatched weight?
    assert(false);
  }

}

int Day7::solve_part2(Day7::Program& root)
{
  compute_total_weights(root);
  return find_correct_weight(root);
}
