/**
 * @file day11.h
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

class day11 {
private:
  /* data */
  std::vector<std::vector<char>> m_seat_map;
  int m_occupied_seats;

public:
  day11(/* args */);
  ~day11();

  // Part1
  void solver_part1(void);

  // Part2
  void solver_part2(void);

  // Common
  void create_seat_map(std::vector<std::string> input_table);
  void plot_seat_map(std::vector<std::vector<char>> map_to_plot);
  bool check_to_occupy(int in_x, int in_y);
  bool check_to_free(int in_x, int in_y);
  std::vector<std::vector<char>> get_seats_around(int in_x, int in_y);
  void set_all_seats_occupied(void);
  void set_all_seats_free(void);
  int count_occupied_seats(void);
};

#endif // _DAY06_H_