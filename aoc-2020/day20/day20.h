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
  int num_side_match;
  std::vector<std::string> adjacent_tile_ids;
  std::vector<std::vector<char>> image;
} t_tile;

class day20 {
private:
  /* data */
  std::vector<t_tile> m_cam_input;
  std::vector<t_tile> m_corner_tiles;

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
  void rot_image_90cw(std::vector<std::vector<char>> &image);
  void flip_image_v(std::vector<std::vector<char>> &image);
  void flip_image_h(std::vector<std::vector<char>> &image);
  void plot_mat(std::vector<std::vector<char>> &image);
  bool compare_lines(std::vector<char> a, std::vector<char> b);
  std::vector<char>
  get_line_from_image(int line_num,
                      const std::vector<std::vector<char>> &image);
  std::vector<char>
  get_column_from_image(int column_num,
                        const std::vector<std::vector<char>> &image);
  int eval_matching_sides(const t_tile &A, const t_tile &B);
};

#endif
