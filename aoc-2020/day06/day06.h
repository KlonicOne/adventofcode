/**
 * @file day06.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY06_H_
#define _DAY06_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

// Single seat element
typedef struct person_t {
  std::string yes_question_str;
  std::vector<std::string> yes_questions;
} person_t;

typedef struct group_t {
  std::string yes_question_str;
  std::vector<person_t> pers_in_group;
  std::vector<int> vec_all_questions = std::vector<int>(26); // fix size
  int num_yes_questions;
} group_t;

class day06 {
private:
  /* data */
  std::vector<group_t> all_groups;

public:
  day06(/* args */);
  ~day06();

  void solver_part1(void);
  void solver_part2(void);
  void format_input(std::vector<std::string> inTable);

  // part 1
  void eval_groups_p1(void);
  int calc_sum_yes_questions_p1(void);
  void print_group_results_p1(void);

  // part 2
  int eval_groups_p2(void);

  // common
  void print_format_input_list(void);
};

#endif // _DAY06_H_