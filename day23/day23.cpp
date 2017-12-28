#include <iostream>
#include "day23.h"

long Day23::solve_part1()
{
  // just cheat and do a 1-1 translation to C++
  // so lazy...

  long a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0;
  long mc = 0;

    b = 67;         // set b 67
    c = b;          // set c b
    if (a) goto l1; //jnz a 2
    goto l2;        //jnz 1 5
l1: b *= 100; mc++; //mul b 100
    b -= -100000;   //sub b -100000
    c = b;          //set c b
    c -= -17000;    //sub c -17000
l2: f = 1;          //set f 1
    d = 2;          //set d 2
l5: e = 2;          //set e 2
l4: g = d;          //set g d
    g *= e; mc++;   //mul g e
    g -= b;         //sub g b
    if (g) goto l3; //jnz g 2
    f = 0;          //set f 0
l3: e -= -1;        //sub e -1
    g = e;          //set g e
    g -=b;          //sub g b
    if (g) goto l4; //jnz g -8
    d -= -1;        //sub d -1
    g = d;          //set g d
    g -= b;         //sub g b
    if (g) goto l5; //jnz g -13
    if (f) goto l6; //jnz f 2
    h -= -1;        //sub h -1
l6: g = b;          //set g b
    g -= c;         //sub g c
    if (g) goto l7; //jnz g 2
    goto end;       //jnz 1 3
l7: b -= -17;       //sub b -17
    goto l2;        //jnz 1 -23
end:

  return mc;
}

long Day23::solve_part2()
{
  // well, lets optimise this thing
  long a = 1, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
  long mc = 0;

  b = 67;         // set b 67
  c = b;          // set c b

  if (a)
  {
    b *= 100; mc++;
    b += 100000;
    c = b;
    c += 17000;
  }

  while(true)
  {
    f = 1;
    for (d=2; d!=b; d++)
    {
// so this bit is just b%d (mostly) for large b's
//      for(e=2; e!=b; e++)
//      {
//        mc++;
//        if (b == d*e) f=0;
//      };

// and knowing this, it's clear this program is doing something like counting the primes between b and c
      mc += b-2;
      if ((b%d)==0) f=0;
    };
    if (!f) h++;
    if (b==c) break;
    b += 17;
  }

  return h;
}
