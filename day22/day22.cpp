#include <stdexcept>
#include <cassert>

#include "day22.h"

char Day22::sparse_grid::at(ordinate x, ordinate y) const
{
  auto iter = grid.find(std::make_pair(x,y));
  return iter==grid.end() ? '.' : iter->second;
}

void Day22::sparse_grid::set(ordinate x, ordinate y, char c)
{

  if (c=='.')
  {
    // if we're setting it to 'clear', remove it from the map
    grid.erase(std::make_pair(x,y));   // already missing will just return a soft-failure, which we ignore
  }
  else
  {
    // otherwise, update it
    grid[std::make_pair(x,y)] = c;
  }
}

void Day22::ant::move()
{
  switch(direction)
  {
    case Up:    { y--; break; }
    case Down:  { y++; break; }
    case Left:  { x--; break; }
    case Right: { x++; break; }
    default:    { assert(false); }  // unknown direction?!
  }

  // don't allow moving the the min/max... so we at least detect overflow!
  assert(x>ordinate_min);
  assert(x<ordinate_max);
  assert(y>ordinate_min);
  assert(y<ordinate_max);
}

void Day22::ant::switch_direction(char state)
{
  // if '#' infected, turn cw (right)
  // if '.' clear, turn ccw (left)

  // for part 2, also
  // if 'W' weakened, do not turn
  // if 'F' flagged, reverse direction


  if (state=='#' || state=='.')    // infected or cleared
  {
    bool is_infected = (state=='#');
    switch(direction)
    {
      case Up:    { direction = is_infected? Right : Left; break; }
      case Down:  { direction = is_infected? Left : Right; break; }
      case Left:  { direction = is_infected? Up : Down; break; }
      case Right: { direction = is_infected? Down : Up; break; }
      default:    { assert(false); }  // unknown direction?!
    }
  }
  else if (state=='W') /* do nothing */;
  else if (state=='F')
  {
    switch(direction)
    {
      case Up:    { direction = Down; break; }
      case Down:  { direction = Up; break; }
      case Left:  { direction = Right; break; }
      case Right: { direction = Left; break; }
      default:    { assert(false); }  // unknown direction?!
    }
  }
  else assert(false);   // unknown state?
}

std::pair<Day22::ordinate, Day22::ordinate> Day22::populate_grid(sparse_grid& grid, const std::vector<std::string>& input)
{
  ordinate height = input.size();
  assert(height>0);           // should have rows
  assert((height & 1) == 1);  // should have an odd number of rows

  ordinate width = input[0].size();
  assert(width>0);
  assert((width & 1) == 1);   // should have an odd number of columns

  for(ordinate y=0;y<input.size();y++)
  {
    assert(input[y].size() == width);   // all rows should have the same number of columns

    for (ordinate x=0;x<input[y].size();x++)
    {
      if (input[y][x]=='.') /* ignore clear */;
      else if (input[y][x]=='#') grid.set(x, y, '#');
      else assert(false); // only expect . or # in input
    }
  }

  return { (width/2), (height/2) }; // since w and h are odd, just divide by two to get the 'middle'
}

bool Day22::step(sparse_grid &grid, ant &a, const std::function<char(char)>& change_state)
{
  // switch the ant's direction
  char state = grid.at(a.x, a.y);
  a.switch_direction(state);

  // invert the infection status of the ants location
  char updated_state = change_state(state);
  grid.set(a.x, a.y, updated_state);

  // move the ant
  a.move();

  return updated_state=='#';
}

unsigned int Day22::solve(const sparse_grid& initial_grid, int start_x, int start_y, int iterations, const std::function<char(char)>& change_state)
{
  sparse_grid grid = initial_grid;  // copy
  ant a(start_x, start_y, ant::Up);

  unsigned int infected_count = 0;
  for(int i=0;i<iterations;i++)
  {
    bool did_infect = step(grid, a, change_state);
    if (did_infect) infected_count++;
  }

  return infected_count;
}

char Day22::solve_part1_change_state(char c)
{
  // for part 1, toggle clear to infected state and back
  switch(c)
  {
    case '.': return '#';
    case '#': return '.';
    default:   assert(false);   // unknown value?
  }

  return '.'; // safe disabled assert path
}

char Day22::solve_part2_change_state(char c)
{
  // for part 2, clear -> weakened -> infected -> flagged -> clear
  switch(c)
  {
    case '.': return 'W';
    case 'W': return '#';
    case '#': return 'F';
    case 'F': return '.';
    default:   assert(false);   // unknown value?
  }

  return '.'; // safe disabled assert path
}


unsigned int Day22::solve_part1(const sparse_grid& initial_grid, int start_x, int start_y, int iterations)
{
  return solve(initial_grid, start_x, start_y, iterations, solve_part1_change_state);
}

unsigned int Day22::solve_part2(const sparse_grid& initial_grid, int start_x, int start_y, int iterations)
{
  return solve(initial_grid, start_x, start_y, iterations, solve_part2_change_state);
}
