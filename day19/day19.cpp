#include <sstream>
#include <cassert>
#include "day19.h"


struct packet
{
  int x = 0;
  int y = 0;
  int dx = 0;
  int dy = 0;
};

bool can_move_to_position(const std::vector<std::string>& path, int x, int y)
{
  // we accept 'A'-'Z', '+', '|' and '-' characters...
  if (y<0 || y>=path.size()) return false;
  if (x<0 || x>=path[y].size()) return false;

  const char c = path[y][x];
  return c=='+' || c=='|' || c=='-' || (c>='A' && c<='Z');
}

std::pair<std::string, int> Day19::solve(const std::vector<std::string>& path)
{
  // find the origin on the first line of the path
  // direction is always down
  packet p;
  p.x = path[0].find('|');
  p.dy = 1;

  // follow this direction until we encounter:
  //   a '+' character, indicating a corner (we should search for the direction to take next)
  //   a 'A'-'Z' character, which should be added to our output
  std::ostringstream oss;
  int steps = 1;  // 1 for moving 'off-screen' to the first position

  bool can_move = true;
  while(can_move)
  {
    const char c = path[p.y][p.x];

    if (c>='A' && c<='Z') oss << c;
    else if (c=='+')
    {
      // scan for the direction to move to...
      // match the first, but check there's no ambiguity
      bool matched = false;
      std::pair<int,int> newdir;
      for (const auto& dir : {std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(1,0), std::make_pair(-1,0)})
      {
        // skip if this direction is where we just come from
        if (dir.first == -p.dx && dir.second == -p.dy) continue;

        // otherwise, if we can move in that direction, set the dx/dy
        if (can_move_to_position(path, p.x + dir.first, p.y + dir.second))
        {
          newdir = dir;

          assert(!matched);
          matched = true;
        }
      }

      if (matched)
      {
        p.dx = newdir.first;
        p.dy = newdir.second;
      }
    }

    // try and move...
    can_move = can_move_to_position(path, p.x + p.dx, p.y + p.dy);
    if (can_move)
    {
      p.x += p.dx; p.y += p.dy;
      steps++;
    }
  }

  return std::make_pair(oss.str(), steps);
}
