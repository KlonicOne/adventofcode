/**
 * @file day24.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY24_H_
#define _DAY24_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

typedef enum t_input_section {
  RULES = 0,
  MY_TICKET,
  NEARBY_TICKET
} t_input_section;

/**
 * @brief defines a range of values
 *
 */
typedef struct t_range {
  int min_val;
  int max_val;
} t_range;

/**
 * @brief single ruly type
 *
 */
typedef struct t_rule {
  std::string name;
  std::vector<t_range> ranges;
} t_rule;

/**
 * @brief Type for a ticket
 *
 */
typedef struct t_ticket {
  std::vector<int> ticket_vals;
  bool ticket_valid;
} t_ticket;

/**
 * @brief Class to realize the tasks for the day
 *
 */
class day24 {
private:
  /* data */
  std::vector<t_rule> m_rules;
  t_ticket m_my_ticket;
  std::vector<t_ticket> m_nearby_tickets;
  std::vector<int> m_values_out_of_range;
  int m_sum_out_of_range;

public:
  day24(/* args */);
  ~day24();

  // Part1
  void solver_part1(void);
  void eval_values_out_of_range(void);
  bool check_value_for_rules(int val);
  void calc_sum_out_of_range(void);
  int get_sum_out_of_range(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
};

#endif
