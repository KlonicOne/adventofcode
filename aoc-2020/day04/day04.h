/**
 * @file day04.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY04_H_
#define _DAY04_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

typedef struct passport_type {
} passport_type;

class day04 {
 private:
  /* data */
  std::vector<passport_type> fromat_pp_list;
  int number_valid_policies_p1;
  int number_valid_policies_p2;

 public:
  day04(/* args */);
  ~day04();

  void solver_part1(void);
  void solver_part2(void);

  // part 1
  void format_code(std::vector<std::string> inTable);
  bool check_single_policy_p1(passport_type passport_type);
  bool check_single_policy_p2(passport_type passport_type);
  int count_valid_policies_p1(void);
  int count_valid_policies_p2(void);
};

#endif  // _DAY04_H_