/**
 * @file day15.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY15_H_
#define _DAY15_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

class day15 {
private:
  /* data */
  long long m_result;
  int m_stop_cond;
  std::vector<long long> m_num_list;

public:
  day15(/* args */);
  ~day15();

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);
  
  // Common
  void format_input(std::vector<std::string> inTable);
  void eval_num(void);
  long long get_result(void);
  void set_stop_condition(int cond);
};

#endif
