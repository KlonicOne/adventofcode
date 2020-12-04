/**
 * @file day04.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

#include "day04.h"

using namespace std;

/**
 * @brief constructor
 *
 */
day04::day04(/* args */) {
  number_valid_policies_p1 = 0;
  number_valid_policies_p2 = 0;
}

/**
 * @brief Destroy the day04::day04
 *
 */
day04::~day04() {}

/**
 * @brief Solve part 1
 *
 */
void day04::solver_part1(void) {
  // Info out
  std::cout << "Policy check part 1" << std::endl;

  // Check all valid policies
  this->count_valid_policies_p1();
}

/**
 * @brief Solve part 2
 *
 */
void day04::solver_part2(void) {
  // Info out
  std::cout << "Policy check part 2" << std::endl;

  // Check all valid policies
  this->count_valid_policies_p2();
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day04::format_code(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  std::string string_line = "";
  std::string element = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // variables to loop through string
    std::vector<std::string> string_vec_element;
    std::string::size_type start{0};
    std::string::size_type pos;
    std::string delimiter = " -";

    // Get single line as string_line
    string_line = (*i);

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // add element to end of vector
      string_vec_element.push_back(element);
      // next position to start searching for delimiter
      start = pos + 1;
    } while (pos != std::string::npos);

    // add to pport list with required format


    // debug out
    // std::cout << "Line: " << string_line << std::endl;
    // std::cout << "min: " << get<0>(*(this->format_code_list.end() - 1))
    //           << ", max: " << get<1>((*(this->format_code_list.end() - 1)))
    //           << ", char: " << get<2>((*(this->format_code_list.end() - 1)))
    //           << ", string: " << get<3>((*(this->format_code_list.end() -
    //           1)))
    //           << std::endl;
  }
}

/**
 * @brief Check if given password fits to policy
 *
 * @param password_element contains password and policy
 * @return true policy valid
 * @return false invalid
 */
bool day04::check_single_policy_p1(passport_type pp_element) {
  bool is_password_valid = false;

  return (is_password_valid);
}

/**
 * @brief Check policy for part 2
 *
 * @param password_element contains password and policy
 * @return true policy valid
 * @return false invalidse
 */
bool day04::check_single_policy_p2(passport_type pp_element) {
  bool is_password_valid = false;

  return (is_password_valid);
}

/**
 * @brief Iterates through the complete password list and counts up all valid
 * once and stor in private result variable and print result
 *
 * @return int number of valid passwords
 */
int day04::count_valid_policies_p1(void) {
  bool policy_valid = false;

  // Loop thorugh tuple formatted code and call policy check
  for (const auto &itcoli : fromat_pp_list) {
    policy_valid = this->check_single_policy_p1(itcoli);

    // count events
    if (policy_valid) {
      this->number_valid_policies_p1++;
    }
  }

  std::cout << "Found valid policies: " << number_valid_policies_p1
            << std::endl;

  return (this->number_valid_policies_p1);
}

/**
 * @brief Iterates through the complete password list and counts up all valid
 * once and stor in private result variable and print result
 *
 * @return int number of valid passwords
 */
int day04::count_valid_policies_p2(void) {
  bool policy_valid = false;

  // Loop thorugh tuple formatted code and call policy check
  for (const auto &itcoli : fromat_pp_list) {
    policy_valid = this->check_single_policy_p2(itcoli);

    // count events
    if (policy_valid) {
      this->number_valid_policies_p2++;
    }
  }

  std::cout << "Found valid policies: " << number_valid_policies_p2
            << std::endl;

  return (this->number_valid_policies_p2);
}