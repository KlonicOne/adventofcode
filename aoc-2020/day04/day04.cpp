/**
 * @file day04.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day04.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief constructor
 *
 */
day04::day04(/* args */) {
  this->number_valid_policies_p1 = 0;
  this->number_valid_policies_p2 = 0;
  this->fromat_pp_list.resize(this->passport_length);
  this->format_list_size = 0;
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
void day04::format_input(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  int current_pp_index = 0;
  std::string string_line = "";
  std::string element = "";

  // Init first pp element
  fromat_pp_list[current_pp_index].byr.name = "";
  fromat_pp_list[current_pp_index].byr.value = "";
  fromat_pp_list[current_pp_index].byr.optional = false;

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // variables to loop through string
    std::vector<std::string> string_vec_element;
    std::string::size_type start{0};
    std::string::size_type pos;
    std::string delimiter = " :";

    // Get single line as string_line
    string_line = (*i);

    // If only newline in line, go over to next pp and init it
    if (string_line.length() == 0) {
      current_pp_index++;
      // Init next pp element
      fromat_pp_list[current_pp_index].byr.name = "";
      fromat_pp_list[current_pp_index].byr.value = "";
      fromat_pp_list[current_pp_index].byr.optional = false;

      std::cout << "Next pp element." << std::endl;
      continue;
    }

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

    // add to pport list with required format for current pp index
    // catch all available elements
    for (std::string vecel : string_vec_element) {
      std::cout << vecel << ", ";
    }
    std::cout << std::endl;

    // debug out
    // for (std::string vecel : string_vec_element) {
    //   std::cout << vecel << ", ";
    // }
    // std::cout << std::endl;
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