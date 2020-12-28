/**
 * @file day14.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY14_H_
#define _DAY14_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

typedef struct t_input_element {
  unsigned long set_mask;
  unsigned long reset_mask;
  map<int, int> mem_entry;
} t_input_element;

class day14 {
private:
  /* data */
  long m_sum_mem;
  std::vector<t_input_element> m_format_input;
  map<int, int> m_mem;

public:
  day14(/* args */);
  ~day14();

  // Part1
  void solver_part1(void);
  unsigned long get_set_mask(std::string str);
  unsigned long get_reset_mask(std::string str);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
};

#endif // _DAY06_H_