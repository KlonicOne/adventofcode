/**
 * @file day01.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY02_H_
#define _DAY02_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

typedef std::tuple<int, int, std::string, std::string> t_code_element;

class day02 {
private:
  /* data */
  std::vector<t_code_element> format_code_list;
  int number_valid_policies;

public:
  day02(/* args */);
  ~day02();

  void solver_part1(std::vector<std::string> inTable);
  void solver_part2(std::vector<std::string> inTable);

  // part 1
  void format_code(std::vector<std::string> inTable);
  bool check_single_policy(t_code_element password_element);
  bool check_single_policy_p2(t_code_element password_element);
  int count_valid_policies(void);
  int count_valid_policies_p2(void);
};

#endif // _DAY02_H_