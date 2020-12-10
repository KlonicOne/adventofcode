/**
 * @file day10.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY09_H_
#define _DAY09_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

class day10 {
private:
  /* data */
  std::vector<int> m_jolt_adapters;
  std::vector<int> m_jolt_adapters_raw;
  std::vector<int> m_num_jolt_diffs;


public:
  day10(/* args */);
  ~day10();

  // Part1
  void solver_part1(void);
  void sort_adapter_jolt(void);
  int eval_num_jolt_diff(int jolt_diff);
  

  // Part2
  void solver_part2(void);


  // Common
  void setInput(std::vector<int> in_vector);

};

#endif // _DAY06_H_