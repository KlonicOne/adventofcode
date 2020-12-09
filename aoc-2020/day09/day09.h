/**
 * @file day09.h
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

class day09 {
private:
  /* data */
  std::vector<int> vec_input;

public:
  day09(/* args */);
  ~day09();

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
};

#endif // _DAY06_H_