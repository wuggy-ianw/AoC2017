//
// Created by wuggy on 03/12/2017.
//

#include "day03.h"

#include <cassert>
#include <algorithm>
#include <map>


const int Day3::SpiralIterator::directions[4][2] =
{
  {0, 1}, {-1, 0}, {0, -1}, {1, 0}
};

bool Day3::SpiralIterator::atcorner()
{
  // if this x,y pos is at the corner of this shell, return true
  // that happens when abs(x), abs(y) == shell, shell
  return std::abs(x) == shell && std::abs(y) == shell;
}

Day3::SpiralIterator &Day3::SpiralIterator::next()
{
  // a shell has 4 side, each twice the length of the shell number
  // expect shell zero, which has length 1
  const int edge_length = shell > 0 ? 2 * shell : 1;
  const int shell_length = shell > 0 ? 2 * 4 * shell : 1;

  // if we're at the last position in this shell, move onto the next shell
  if (pos == (shell_length - 1))
  {
    pos = 0;
    shell++;

    // the next shell is one x further out, and reset the direction
    x++;
    direction = 0;
  }
  else
  {
    // move onto the next pos
    pos++;
    x += directions[direction][0];
    y += directions[direction][1];

    // if we're at a corner, move onto the next direction
    if (atcorner()) direction++;
  }
  index++;

  return *this;
}

std::size_t Day3::solve_part1_directly(std::size_t num)
{
  assert(num>0);

  // determine what shell this value is in
  // shells are different sizes
  // the shells follow odd-square numbers: 1, 9, 25, etc
  // they are odd-numbers wide: 1, 3, 5, etc
  // the odd-square number is the LAST number in that shell (i.e. the shell 3-wide contains 9 but not 10)
  std::size_t shellwidth = 1;
  while(num > shellwidth*shellwidth) shellwidth+=2;

  // the 'shell' number starts at zero, and increases by one
  // so, the shell-number is the (shellwidth - 1)/2
  std::size_t shell = (shellwidth - 1)/2;

  // there are at least one move per shell
  // there is an additional move for each position away from the N/S/E/W line that the
  // number is around the shell...
  // we number backwards from the LAST number in the shell (so if we're in shell 5... 25 has position zero, 10 has position 15)
  std::size_t shellpos = (shellwidth*shellwidth) - num;

  // the number of moves is the shortest distance to the nsew points
  // those are at shell, shell + 2*shell, shell + 4*shell and shell + 6*shell
  // aka... shell + 2*n*shell for n=0..3
  std::size_t distance_to_nsew = shellwidth;  // shellwidth is bigger than the distance can be
  for (long n=0;n<4;n++)
  {
    long ordinalpos = shell + 2*n*shell;
    long distance_to_ordinal = std::abs(ordinalpos - (long)shellpos);
    distance_to_nsew = std::min(distance_to_nsew, std::size_t(distance_to_ordinal));
  }

  // the total number of moves is one-per-shell and one per distance from nsew
  return shell + distance_to_nsew;
}

int Day3::solve_part1(int num)
{
  SpiralIterator si;
  while(si.index < num)
  {
    si.next();
  }

  return std::abs(si.x) + std::abs(si.y);
}

int Day3::solve_part2(int num)
{
  SpiralIterator si;
  std::map<std::pair<int,int>, int> resultsMap = { {std::make_pair(si.x,si.y), si.index} };

  int result = si.index;
  while(result < num)
  {
    // move onto the next item, compute the result as the sum of the adjacent 8 items
    si.next();

    result = 0;
    for (int y = si.y - 1; y <= si.y + 1; y++)
    {
      for (int x = si.x - 1; x <= si.x + 1; x++)
      {
        auto r = resultsMap.find(std::make_pair(x,y));
        if (r!=resultsMap.end()) result += r->second;
      }
    }

    resultsMap[std::make_pair(si.x, si.y)] = result;
  }

  return result;
}
