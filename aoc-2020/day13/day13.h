/**
 * @file day13.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY13_H_
#define _DAY13_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

class day13 {
private:
  /* data */
  int m_arrive_time;
  int m_best_bus_id_p1;
  int m_result_p1;
  long long m_result_p2;
  std::vector<int> m_bus_ids;
  std::vector<int> m_bus_subs_time;

public:
  day13(/* args */);
  ~day13();

  // Part1
  void solver_part1(void);
  void eval_best_bus_id_p1(void);
  int get_result_p1(void);

  // Part2
  void solver_part2(void);
  void eval_cond_p2(void);
  long long get_result_p2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
};

#endif // _DAY06_H_