#include <sstream>
#include <cassert>
#include <unordered_map>

#include "day24.h"
#include "../utils/aocutils.h"

Day24::part Day24::parse_part(const std::string& s)
{
  std::istringstream iss(s);
  int a=0, b=0;
  iss >> a >> AOCUtils::literal("/") >> b;
  assert(iss);

  return {a,b};
}


Day24::state walk_bridge_tree_for_maximum_weight(const std::vector<Day24::part>& parts,
                                                 const std::unordered_multimap<int, int>& port_index,
                                                 const Day24::state& base_state,
                                                 const std::function<bool(const Day24::state&, const Day24::state&)> compare) // if a > b
{
  // given the base state, enumerate all the possible states from this one, recursively
  // keep the one with the largest weight and return it

  // clone the base-state... this is the best so-far especially if we have no-child candidates
  Day24::state best = base_state;

  // for every bridge part that matches the port at the end of our bridge
  auto matching_parts = port_index.equal_range(base_state.end_port);
  for (auto iter = matching_parts.first; iter != matching_parts.second; iter++)
  {
    // if this part is already used in the base state, skip it...
    int part_index = iter->second;
    if (base_state.used[part_index]) continue;

    // make a new state for this candidate from the base-state
    Day24::state candidate = base_state;

    // extend it by the selected bridge part
    const Day24::part& part = parts[part_index];
    assert(part.first == candidate.end_port || part.second == candidate.end_port);  // one end of this part should match our end-port

    candidate.strength += part.first + part.second;
    candidate.end_port = (part.first == candidate.end_port) ? part.second : part.first;
    candidate.used[part_index] = true;
    candidate.length++;

    // walk the subtree of this candidate, get the 'best' weighted child
    Day24::state best_candidate = walk_bridge_tree_for_maximum_weight(parts, port_index, candidate, compare);

    // if the best_candidate is better than the best we know so far, use that
    if (compare(best_candidate, best)) best = best_candidate;
  }

  return best;
}

int solve(const std::vector<Day24::part>& parts, const std::function<bool(const Day24::state&, const Day24::state&)> compare)
{
  // from the list of parts, make a more faster accessible index by port number
  // this is a map from port number (at either end of a part) to it's index in the part list
  std::unordered_multimap<int, int> port_index;
  for (int i=0; i<parts.size(); i++)
  {
    port_index.emplace(parts[i].first, i);
    if (parts[i].first != parts[i].second)  // if this bridge part has the same port at each end, just add it once for that port
    {
      port_index.emplace(parts[i].second, i);
    }
  }

  // from an initial state, starting with weight zero, at port zero... walk the tree
  Day24::state best = walk_bridge_tree_for_maximum_weight(parts, port_index, Day24::state(), compare);

  return best.strength;
}

int Day24::solve_part1(const std::vector<Day24::part>& parts)
{
  return solve(parts,
               [](const state& a, const state& b) -> bool
               {
                 // select the strongest bridge
                 return a.strength > b.strength;
               });
}

int Day24::solve_part2(const std::vector<Day24::part>& parts)
{
  return solve(parts,
               [](const state& a, const state& b) -> bool
               {
                 // select the longest bridge, with strongest as a tie-breaker
                 if (a.length > b.length) return true;
                 if (a.length == b.length) return (a.strength > b.strength);
                 return false;
               });
}
