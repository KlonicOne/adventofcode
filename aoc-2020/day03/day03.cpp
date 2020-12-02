/**
 * @file day03.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day03.h"

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
day03::day03(/* args */) {
  number_valid_policies_p1 = 0;
  number_valid_policies_p2 = 0;
}

/**
 * @brief Destroy the day03::day03
 *
 */
day03::~day03() {}

/**
 * @brief Solve part 1
 *
 */
void day03::solver_part1(void) {
  // Info out
  std::cout << "Policy check part 1" << std::endl;

  // Check all valid policies
  this->count_valid_policies_p1();
}

/**
 * @brief Solve part 2
 *
 */
void day03::solver_part2(void) {
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
void day03::format_code(std::vector<std::string> inTable) {
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

    // add to code list with required format
    this->format_code_list.push_back(t_code_element(
        stoi(string_vec_element.at(0)), stoi(string_vec_element.at(1)),
        string_vec_element.at(2), string_vec_element.at(3)));

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
bool day03::check_single_policy_p1(t_code_element password_element) {
  bool is_password_valid = false;
  int num_matching_chars = 0;
  int min_occurrences = get<0>(password_element);
  int max_occurrences = get<1>(password_element);
  std::string eval_character = get<2>(password_element);
  std::string eval_string = get<3>(password_element);

  // Split string to characters and loop through string
  for (int i = 0; i < eval_string.length(); i++) {
    if ((char)eval_string.at(i) ==
        (char)eval_character.at(0)) {  // Check if equal
      num_matching_chars++;
    }
  }

  // Now check if number fits to policy
  if (min_occurrences <= num_matching_chars &&
      num_matching_chars <= max_occurrences) {
    is_password_valid = true;
  }

  return (is_password_valid);
}

/**
 * @brief Check policy for part 2
 *
 * @param password_element contains password and policy
 * @return true policy valid
 * @return false invalidse
 */
bool day03::check_single_policy_p2(t_code_element password_element) {
  bool is_password_valid = false;
  int pos_one = get<0>(password_element);
  int pos_two = get<1>(password_element);
  std::string eval_character = get<2>(password_element);
  std::string eval_string = get<3>(password_element);

  // Check if only one pos contains char
  if ((char)eval_string.at(pos_one - 1) == (char)eval_character.at(0) &&
          !((char)eval_string.at(pos_two - 1) == (char)eval_character.at(0)) ||
      !((char)eval_string.at(pos_one - 1) == (char)eval_character.at(0)) &&
          (char)eval_string.at(pos_two - 1) == (char)eval_character.at(0)) {
    is_password_valid = true;
  }

  return (is_password_valid);
}

/**
 * @brief Iterates through the complete password list and counts up all valid
 * once and stor in private result variable and print result
 *
 * @return int number of valid passwords
 */
int day03::count_valid_policies_p1(void) {
  bool policy_valid = false;

  // Loop thorugh tuple formatted code and call policy check
  for (const auto &itcoli : format_code_list) {
    policy_valid = this->check_single_policy_p1(itcoli);

    // count events
    if (policy_valid) {
      number_valid_policies_p1++;
    }
  }

  std::cout << "Found valid policies: " << number_valid_policies_p1
            << std::endl;

  return (number_valid_policies_p1);
}

/**
 * @brief Iterates through the complete password list and counts up all valid
 * once and stor in private result variable and print result
 *
 * @return int number of valid passwords
 */
int day03::count_valid_policies_p2(void) {
  bool policy_valid = false;

  // Loop thorugh tuple formatted code and call policy check
  for (const auto &itcoli : format_code_list) {
    policy_valid = this->check_single_policy_p2(itcoli);

    // count events
    if (policy_valid) {
      number_valid_policies_p2++;
    }
  }

  std::cout << "Found valid policies: " << number_valid_policies_p2
            << std::endl;

  return (number_valid_policies_p2);
}
