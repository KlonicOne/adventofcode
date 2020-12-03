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

typedef struct path_element_t {
  int x;
  int y;
  int value;
} path_element_t;

typedef std::vector<int> vec_1d_t;
typedef std::vector<vec_1d_t> vec_2d_t;
typedef std::vector<vec_2d_t> vec_3d_t;

#define XDIM (1024)
#define YDIM (512)

const char tree_sym = '#';
const char free_sym = '.';

class day03 {
private:
  /* data */
  // max positiond in dimensions
  int m_map_multiplier;               // how often is the map repeated to right
  int m_xdim;                         // real used xdimension
  int m_ydim;                         // real used ydimension
  int slope_down;                     // intput from puzzle
  int slope_right;                    // input from puzzle
  path_element_t current_pos;         // position of mower
  std::vector<path_element_t> m_path; // path trhough map with value
  vec_2d_t m_treemap; // map with trees in x,y and value on pos(x,y)

  int found_trees; // result with found trees on path

public:
  day03(/* args */);
  ~day03();

  void solver_part1(void);
  void solver_part2(void);

  void plotTreeMap(void);

  // part 1
  void create_map(std::vector<std::string> inTable);
  void calc_path(void);
  void calc_trees_on_path(void);
};

#endif // _DAY03_H_