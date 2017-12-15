//
// Created by wuggy on 15/12/2017.
//

#ifndef AOC2017_DAY09_H
#define AOC2017_DAY09_H

#include <string>
#include <istream>
#include <memory>
#include <vector>

namespace Day9
{

  struct stream_memento
  {
    std::istream& s;
    std::istream::pos_type pos;
    std::istream::iostate state;

    explicit stream_memento(std::istream& s);
    void revert();
  };

  struct canceled_sequence
  {
    std::istream::pos_type start = -1; // position of first matching character
    std::istream::pos_type end = -1;   // position one past the end of the last matching character
  };
  std::istream& operator >>(std::istream& s, canceled_sequence& candidate);

  struct garbage
  {
    std::istream::pos_type start = -1; // position of first matching character
    std::istream::pos_type end = -1;   // position one past the end of the last matching character
    int count = 0;
  };
  std::istream& operator >>(std::istream& s, garbage& candidate);

  struct group
  {
    std::istream::pos_type start = -1; // position of first matching character
    std::istream::pos_type end = -1;   // position one past the end of the last matching character

    std::vector<group> child_groups;
    int garbage_count = 0;
  };
  std::istream& operator >>(std::istream& s, group& candidate);

  int solve_part1(const std::string& input);
  int solve_part2(const std::string& input);
} // namespace Day9

#endif //AOC2017_DAY09_H
