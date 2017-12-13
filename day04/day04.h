//
// Created by wuggy on 06/12/2017.
//

#ifndef AOC2017_DAY04_H
#define AOC2017_DAY04_H


#include <cstddef>
#include <vector>
#include <string>
#include <functional>

namespace Day4
{
  bool is_valid_core(const std::string& passphrase, std::function<void(std::string&)> filter);

  bool is_valid_part1(const std::string& passphrase);
  bool is_valid_part2(const std::string& passphrase);

  int solve_part1(const std::vector< std::string >& passphrases);
  int solve_part2(const std::vector< std::string >& passphrases);
}

#endif //AOC2017_DAY04_H
