/**
 * @file day25.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY25_H_
#define _DAY25_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

/**
 * @brief Class to realize the tasks for the day
 *
 */
class day25 {
private:
  /* data */
  std::vector<int> m_keys;
  std::vector<int> m_loop_nums;
  const int m_divisor = 20201227;
  const int m_start_val = 1;
  const int m_seed_val = 7;

public:
  day25(/* args */);
  ~day25();

  // Part1
  void solver_part1(void);
  int calc_loop_number(int key);
  long long calc_sec_key(int key, int loop);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
};

#endif
