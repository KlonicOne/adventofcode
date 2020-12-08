/**
 * @file day08.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY08_H_
#define _DAY08_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

#include "acc_computer.h"

using namespace std;

class day08 {
private:
  /* data */
  acc_computer computer; // We need on computer

public:
  day08(/* args */);
  ~day08();

  void format_input(std::vector<std::string> inTable);

  // Part1
  void solver_part1(void);
  
  // Part2
  void solver_part2(void);
  };

#endif // _DAY08_H_