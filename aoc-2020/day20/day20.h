/**
 * @file day20.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY20_H_
#define _DAY20_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <numeric>
#include <vector>

using namespace std;

typedef struct t_tile {
  std::string tile_id;
  std::vector<std::vector<char>> image;
} t_tile;

class day20 {
private:
  /* data */
  std::vector<t_tile> m_cam_input;

public:
  day20(/* args */);
  ~day20();

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
  std::string remove_spaces(const std::string s);
};

#endif
