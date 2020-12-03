/**
 * @file day03.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY03_H_
#define _DAY03_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<long long, long long, long long> map_element_t;

#define YDIM 512  // Map y
#define XDIM 1024  // Map z
#define ZDIM 2  // Value in zdim, 0 free, 1 tree

class day03 {
 private:
  /* data */
  // max positiond in dimensions
  long long m_ydim;
  long long m_xdim;
  long long m_zdim;

  map_element_t current_pos;               // position of mower
  std::vector<map_element_t> m_path;       // path trhough map with value
  long long m_tree_map[XDIM][YDIM][ZDIM];  // Map with tree info on z dim
  int m_map_multiplier;  // how often is the map repeated to right
  int slope_right;       // input from puzzle
  int slope_down;        // intput from puzzle

  long long found_trees;  // result with found trees on path

 public:
  day03(/* args */);
  ~day03();

  void solver_part1(void);
  void solver_part2(void);

  // part 1
  void create_map(std::vector<std::string> inTable);
  void calc_path(void);
  void calc_trees_on_path(void);
};

#endif  // _DAY03_H_