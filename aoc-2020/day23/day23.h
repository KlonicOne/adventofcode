/**
 * @file day23.h
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

class day23 {
private:
  /* data */
  std::vector<int> m_start_buffer;
  std::vector<int> m_cup_buffer;      // all cups, removed 3 head and tail
  std::vector<int> m_temp_cup_buffer; // temp buffer for 3 cups
  /* control data */
  int m_current_pos;         // current cup
  int m_dest_pos;            // destination cup in buffer
  int m_dest_val;            // destination value
  int m_tail;                // current tail cup
  int m_initial_buffer_size; // contains the initial size of cup buffer
  int m_max_cup_value;
  const int m_temp_buffer_size = 3; // 3 cups

public:
  day23(/* args */);
  ~day23();

  // Part1
  void solver_part1(void);
  void init_cup_buffer(void);
  void pick_three_cups(void);
  void eval_destination_cup(void);
  void place_cups_after_dest(void);
  void eval_new_current(void);
  bool is_value_in_temp_buffer(int value);
  int get_pos_of_value_cup_buffer(int value);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
  std::string remove_spaces(const std::string s);
  std::string remove_brackets(const std::string s);
};

#endif
