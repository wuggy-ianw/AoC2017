//
// Created by wuggy on 15/12/2017.
//

#include <sstream>
#include <cassert>
#include "day09.h"



Day9::stream_memento::stream_memento(std::istream& s) : s(s), pos(s.tellg()), state(s.rdstate())
{
}

void Day9::stream_memento::revert()
{
  s.clear(state);
  s.seekg(pos);
}

std::istream& Day9::operator >>(std::istream& s, Day9::canceled_sequence& candidate)
{
  // canceled chars are prefixed with '!'
  std::istream::pos_type candidate_start = s.tellg();

  while (s)
  {
    char c = -1;
    stream_memento memento(s);
    s >> c;

    // if this isn't a cancelled character, put it back and finish
    if (!s || c != '!')
    {
      memento.revert();

      // we've matched a (possibly zero-length) sequence...
      candidate.start = candidate_start;
      candidate.end = s.tellg();
      break;
    }

    // this is a cancelled character, try and read the following character
    // continue trying to read cancelled chars until there aren't any
    s >> c;
  }

  return s;
}

template<typename T, char open_char, char close_char>
std::istream& Day9::operator >>(std::istream& s, T& candidate)
{

}

std::istream& Day9::operator >>(std::istream& s, Day9::garbage& candidate)
{
  // garbage starts with a '<' character
  // and ends with a '>' character
  std::istream::pos_type candidate_start = s.tellg();

  char c;
  s >> c;
  if (!s) return s; // couldn't read a character, it's all bad

  // if it's not a '<' character, then fail
  if (c != '<')
  {
    s.setstate(std::ios_base::failbit);
    return s;
  }

  // otherwise, keep reading until after we get a '>' character, ignoring cancelled characters
  canceled_sequence ignore_canceled;
  int count = 0;
  while (s && c!='>')
  {
    s >> ignore_canceled >> c;
    if (s && c!='>') count++;
  }

  // if we have a match preserve it
  // otherwise, we'll return s in a bad state
  if (c=='>')
  {
    candidate.start = candidate_start;
    candidate.end = s.tellg();
    candidate.count = count;
  }

  return s;
}


std::istream& Day9::operator >>(std::istream& s, Day9::group& candidate)
{
  // groups start with a '{' and are closed by a '}' character
  // groups have children which can be garbage or another group, separated by commas
  // groups can be nested
  std::istream::pos_type candidate_start = s.tellg();
  std::vector<group> child_groups;

  char c;
  s >> c;
  if (!s) return s; // couldn't read a character, it's all bad

  // if it's not a '{' character, then fail
  if (c != '{')
  {
    s.setstate(std::ios_base::failbit);
    return s;
  }

  // otherwise, we have child-garbages and child-groups or a close character
  int garbage_count = 0;
  while (s)
  {
    bool didmatch = false;

    // check for close
    {
      stream_memento memento(s);
      s >> c;
      if (s && c == '}')
      {
        // this is a successful close!
        candidate.start = candidate_start;
        candidate.end = s.tellg();
        candidate.child_groups = std::move(child_groups);
        candidate.garbage_count = garbage_count;
        break;
      }
      memento.revert(); // otherwise not a close
    }

    // skip a comma separator
    {
      stream_memento memento(s);
      s >> c;
      if (s && c == ',') /* do nothing */;
      else memento.revert();
    }

    // try and match a garbage child
    {
      stream_memento memento(s);
      garbage ignore_garbage;
      s >> ignore_garbage;
      if (!s) memento.revert();
      else
      {
        garbage_count += ignore_garbage.count;
        didmatch = true;
      }
    }

    // try and match a group
    {
      stream_memento memento(s);
      group child;
      s >> child;
      if (s)
      {
        child_groups.push_back(std::move(child));
        didmatch = true;
      } else memento.revert();
    }

    // if nothing matched at all, then things are bad
    if (!didmatch)
    {
      s.setstate(std::ios_base::failbit);
    }
  }

  return s;
}


namespace
{

  int score_group(const Day9::group& group, int level = 1)
  {
    // the score for this group is the level, plus the score for all our children
    int score = level;
    for (const Day9::group& child : group.child_groups)
    {
      score += score_group(child, level+1);
    }
    return score;
  }

  int count_garbage(const Day9::group& group)
  {
    // the garbage count is this groups count plus all it's children's
    int count = group.garbage_count;
    for (const Day9::group& child : group.child_groups)
    {
      count += count_garbage(child);
    }
    return count;
  }

} // anonymous namespace

int Day9::solve_part1(const std::string& input)
{
  std::istringstream iss(input);

  Day9::group group;
  iss >> std::noskipws >> group;
  assert(iss);

  return score_group(group);
}


int Day9::solve_part2(const std::string& input)
{
  std::istringstream iss(input);

  Day9::group group;
  iss >> std::noskipws >> group;
  assert(iss);

  return count_garbage(group);
}
