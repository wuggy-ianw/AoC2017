//
// Created by wuggy on 21/12/2017.
//

#include <cassert>
#include <set>
#include "day12.h"
#include "../utils/aocutils.h"

std::map<int, Day12::program> Day12::parse_input(std::istream& stream)
{
  std::vector<program> programitems = AOCUtils::parseByLines<program>(stream, [](const std::string& s) -> program
    {
      program p;
      std::istringstream iss(s);
      std::string remainder;
      iss >> p.id >> AOCUtils::literal("<->");
      assert(bool(iss));

      p.sibling_ids = AOCUtils::parseCommaSeparatedItems<int>(iss, [](const std::string& s) -> int { return std::stoi(s); });

      return p;
    });

  std::map<int, program> programmap;
  for (program& p : programitems)
  {
    programmap[p.id] = std::move(p);
  }
  return programmap;
}



namespace
{
  void walk(std::set<int>& visited, int visit, const std::map<int, Day12::program>& programs)
  {
    // skip already visited id's
    if (visited.find(visit) != visited.end()) return;

    // otherwise, mark it visited and visit it's siblings
    const Day12::program& p = programs.at(visit);
    visited.insert(p.id);

    for (int sib : p.sibling_ids)
    {
      walk(visited, sib, programs);
    }
  }
}

int Day12::solve_part1(const std::map<int, Day12::program>& programs)
{
  // count all the programs that are connected to program zero
  std::set<int> visited;
  walk(visited, 0, programs);

  return visited.size();
}

int Day12::solve_part2(const std::map<int, Day12::program>& programs)
{
  // until all the program ids are visited... try visiting the group in each one
  std::set<int> visited;
  int group_count = 0;
  for (const auto& pr : programs)
  {
    int pid = pr.second.id;
    if (visited.find(pid) == visited.end())
    {
      group_count++;
      walk(visited, pid, programs);
    }
  }

  return group_count;
}
