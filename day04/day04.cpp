//
// Created by wuggy on 06/12/2017.
//

#include <algorithm>
#include <sstream>
#include <unordered_set>

#include "day04.h"

bool Day4::is_valid_core(const std::string& passphrase, std::function<void(std::string&)> filter)
{
  std::istringstream is(passphrase);
  std::unordered_set<std::string> seen;
  for (std::string word; is >> word;)
  {
    filter(word);
    if (seen.find(word) == seen.end()) seen.insert(word);
    else return false;
  }

  return true;
}

bool Day4::is_valid_part1(const std::string& passphrase)
{
  return Day4::is_valid_core(passphrase, [](std::string&){});
}

bool Day4::is_valid_part2(const std::string& passphrase)
{
  return Day4::is_valid_core(passphrase, [](std::string& s)
    {
      std::sort(s.begin(), s.end());
    });
}




int Day4::solve_part1(const std::vector< std::string >& passphrases)
{
  return std::count_if(passphrases.begin(), passphrases.end(), is_valid_part1);
}

int Day4::solve_part2(const std::vector< std::string >& passphrases)
{
  return std::count_if(passphrases.begin(), passphrases.end(), is_valid_part2);
}
