/**
 * @file day12.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY09_H_
#define _DAY09_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

typedef struct t_Position {
  int x;        // East(+) and West(-)
  int y;        // North(-) and South(+)
  char heading; // Char for heading, N,E,S,W
} t_Position;

typedef struct t_input_element {
  char cmd;
  int value;
} t_input_element;

class day12 {
private:
  /* data */

public:
  day12(/* args */);
  ~day12();

  std::vector<t_input_element> m_format_input;
  std::vector<t_Position> m_ship_route;

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);

  // Common
  void create_ship_route(std::vector<std::string> input);
  void create_format_input(std::vector<std::string> input);
};

#endif // _DAY06_H_