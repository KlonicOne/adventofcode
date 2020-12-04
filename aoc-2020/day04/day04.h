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

typedef struct pp_entry_type {
  std::string name;
  std::string value;
  bool optional;
} pp_entry_type;

typedef struct passport_type {
  pp_entry_type byr;   // (Birth Year)
  pp_entry_type iyr;   // (Issue Year)
  pp_entry_type eeyr;  // (Expiration Year)
  pp_entry_type hgt;   // (Height)
  pp_entry_type hcl;   // (Hair Color)
  pp_entry_type ecl;   // (Eye Color)
  pp_entry_type pid;   // (Passport ID)
  pp_entry_type cid;   //  (Country ID)
} passport_type;

class day04 {
 private:
  /* data */
  std::vector<passport_type> fromat_pp_list;
  int number_valid_policies_p1;
  int number_valid_policies_p2;
  int format_list_size;
  const unsigned int passport_length = 1000;

 public:
  day04(/* args */);
  ~day04();

  void solver_part1(void);
  void solver_part2(void);

  // part 1
  void format_input(std::vector<std::string> inTable);
  bool check_single_policy_p1(passport_type passport_type);
  bool check_single_policy_p2(passport_type passport_type);
  int count_valid_policies_p1(void);
  int count_valid_policies_p2(void);
};

#endif  // _DAY04_H_