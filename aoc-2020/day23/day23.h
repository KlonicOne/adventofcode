/**
 * @file day23.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY21_H_
#define _DAY21_H_

#include <string>
#include <vector>

using namespace std;

class day23 {
private:
  /* data */
  std::vector<int> m_start_buffer;

public:
  day23(/* args */);
  ~day23();

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
  std::string remove_spaces(const std::string s);
  std::string remove_brackets(const std::string s);
  void print_out_ringbuffer(void);
};

#endif
