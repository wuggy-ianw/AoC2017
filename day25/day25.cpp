#include <deque>
#include <algorithm>
#include "day25.h"

int Day25::solve_part1(const state_table& states, int iterations)
{
  // initialise the tape, cursor, and in the initial state
  std::deque<bool> tape(1, false);
  std::size_t cursor = 0;
  char state='A';

  // do the requested number of iterations
  int checksum = 0;
  for(int i=0;i<iterations;i++)
  {
    const conditional_actions& ca = states.at(state);
    const action& a = tape[cursor]? ca.when_true : ca.when_false;

    // update the checksum if we're changing the number of set bits on the tape with this action
    if (tape[cursor]) checksum--;
    if (a.write_val) checksum++;

    // write the value, update the state
    tape[cursor] = a.write_val;
    state = a.next_state;

    // if we're at the beginning or end, extend the tape... don't bother checking if we're going to actually move to the new point
    if (cursor==0)
    {
      tape.push_front(false);
      cursor++; // inserting at the front moves our position along
    }
    if (cursor==tape.size()-1)
    {
      tape.push_back(false);
    }
    cursor += a.move;
  }

  return checksum;
}
