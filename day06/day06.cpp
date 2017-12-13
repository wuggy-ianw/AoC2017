//
// Created by wuggy on 07/12/2017.
//

#include "day06.h"

#include <map>
#include <algorithm>


std::pair<std::size_t, std::size_t> Day6::solve(std::vector<std::size_t> banks)
{
  std::map<std::vector<std::size_t>, std::size_t> seen;
  std::size_t cycles = 0;
  std::size_t foundcycles = 0;
  while(true)
  {
    // if we're in a state we're already in, we're done!
    auto finditer = seen.find(banks);
    if (finditer != seen.end())
    {
      foundcycles=finditer->second;
      break;
    }

    // otherwise, insert it and do a cycle
    seen[banks] = cycles;
    cycles++;

    auto iter = std::max_element(banks.begin(), banks.end());

    std::size_t chunks = *iter;
    *iter = 0;

    while(chunks)
    {
      iter++;
      if (iter==banks.end()) iter=banks.begin();
      (*iter)++;
      chunks--;
    }
  }

  return std::make_pair(cycles, cycles - foundcycles);
}
