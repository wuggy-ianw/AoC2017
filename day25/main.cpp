#include "day25.h"
#include <iostream>

int main(void)
{
  // rather than parse the states, lets just code them in
  int num_steps = 12964419;
  Day25::state_table states{
      {'A', { { true,   1, 'B' }, {false,  1, 'F'} } },
      {'B', { { false, -1, 'B' }, {true,  -1, 'C'} } },
      {'C', { { true,  -1, 'D' }, {false,  1, 'C'} } },
      {'D', { { true,  -1, 'E' }, {true,   1, 'A'} } },
      {'E', { { true,  -1, 'F' }, {false, -1, 'D'} } },
      {'F', { { true,   1, 'A' }, {false, -1, 'E'} } }
  };

  std::cout << Day25::solve_part1(states, num_steps) << std::endl;
  return 0;
}
