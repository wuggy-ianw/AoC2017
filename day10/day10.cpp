//
// Created by wuggy on 17/12/2017.
//

#include "day10.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <sstream>
#include <iomanip>

void Day10::knot(std::size_t length, std::vector<int>& string, std::size_t& pos, std::size_t& skip)
{
  // reverse the string from pos to pos+length
  std::size_t sz = string.size();

  std::size_t left = pos;
  std::size_t right = pos+length-1;
  while(left<right)
  {
    std::swap(string[left%sz], string[right%sz]);
    left++;
    right--;
  }

  // update pos and skip
  pos = (pos + length + skip)%sz;
  skip++;
}

void Day10::knot(const std::vector<std::size_t>& lengths, std::vector<int>& string, std::size_t& pos, std::size_t& skip)
{
  for (std::size_t l : lengths) knot(l, string, pos, skip);
}

Day10::hash_value Day10::hash(const std::string& txt)
{
  // make a string containing 0-255
  std::vector<int> string(256);
  std::iota(string.begin(), string.end(), 0);

  // convert the string to lengths 0-255 as per ASCII value of each character
  std::vector<std::size_t> lengths;
  for (char c : txt) lengths.push_back( uint8_t(c) );

  // append the extra lengths
  std::array<int, 5> extras = {17, 31, 73, 47, 23};
  lengths.insert(lengths.end(), extras.begin(), extras.end());

  // do 64-rounds of knotting
  std::size_t pos = 0;
  std::size_t skip = 0;
  for (int i=0;i<64;i++) knot(lengths, string, pos, skip);

  // densify the hash
  hash_value value = {0};
  auto stringiter = string.begin();
  for (int h=7; h>=0; h--)
  {
    for (int i = 0; i < 16; i++, stringiter++) value.high ^= uint64_t(*stringiter) << (8*h);
  }
  for (int h=7; h>=0; h--)
  {
    for (int i = 0; i < 16; i++, stringiter++) value.low ^= uint64_t(*stringiter) << (8*h);
  }

  return value;
}

std::string Day10::hash_string(const std::string& txt)
{
  // get the hash and convert it to a stringified hash in hex
  hash_value value = hash(txt);
  std::ostringstream oss;
  oss << std::hex << std::setfill('0') << std::setw(16) << value.high ;
  oss << std::hex << std::setfill('0') << std::setw(16) << value.low;
  return oss.str();
}


int Day10::solve_part1(const std::vector<std::size_t>& lengths)
{
  std::vector<int> string(256);
  std::iota(string.begin(), string.end(), 0);

  std::size_t pos = 0;
  std::size_t skip = 0;
  knot(lengths, string, pos, skip);
  return string[0] * string[1];
}
std::string Day10::solve_part2(const std::string& txt)
{
  return hash_string(txt);
}
