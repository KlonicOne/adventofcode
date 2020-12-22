/**
 * @file day22.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY21_H_
#define _DAY21_H_

#include <string>
#include <vector>

using namespace std;

class day22 {
private:
  /* data */
  std::vector<std::vector<int>> m_decks;

public:
  day22(/* args */);
  ~day22();

  // Part1
  void solver_part1(void);
  void play_game(void);
  int calc_score(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
  std::string remove_spaces(const std::string s);
  std::string remove_brackets(const std::string s);
  void print_out_player(void);
};

#endif
