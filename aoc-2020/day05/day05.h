/**
 * @file day05.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY05_H_
#define _DAY05_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

class day05 {
private:
  /* data */
  std::vector<int> format_seat_list;
  const int format_seat_list_size = 500;

public:
  day05(/* args */);
  ~day05();

  void solver_part1(void);
  void solver_part2(void);
  void format_input(std::vector<std::string> inTable);

  // part 1
  // part 2
};

#endif // _DAY05_H_