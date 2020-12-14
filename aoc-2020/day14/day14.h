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

class day14 {
private:
  /* data */
  long m_sum_mem;

public:
  day14(/* args */);
  ~day14();

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
};

#endif // _DAY06_H_