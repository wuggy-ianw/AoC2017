#include <vector>
#include "day17.h"

unsigned int Day17::solve_part1(unsigned int stepsize)
{
  std::vector<unsigned int> buffer;
  buffer.push_back(0);

  // insert into the (circular) buffer each value in turn, stepping forward the stepsize
  unsigned int pos = 0;
  for (unsigned int i=1; i<2018;i++)
  {
    pos = (pos + stepsize) % buffer.size();
    pos++;  // insertion happen AFTER the pos, but we also want to set the pos to the index of the inserted item...
    buffer.insert(buffer.begin()+pos, i);
  }

  // get the pos of the item after the insertion point
  pos = (pos + 1) % buffer.size();
  return buffer[pos];
}


unsigned int Day17::solve_part2(unsigned int stepsize)
{
  // don't bother using the buffer, we're just looking for the most recent item
  // to be inserted after pos zero... just go through the logic of size and pos
  unsigned int bufsize = 1; // zero is at index 0

  // insert into the (circular) buffer each value in turn, stepping forward the stepsize
  unsigned int pos = 0;
  unsigned int second_item = 0;
  for (unsigned int i=1; i<50000000;i++)
  {
    pos = (pos + stepsize) % bufsize;
    pos++;  // insertion happen AFTER the pos, but we also want to set the pos to the index of the inserted item...
    if (pos==1) second_item = i;
    bufsize++;
  }

  // get the pos of the item after the insertion point
  return second_item;
}
