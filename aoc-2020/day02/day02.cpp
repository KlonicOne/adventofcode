/**
 * @file day02.cpp
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

#include "day02.h"

using namespace std;

#define LIMIT_YEAR (2020)

day02::day02(/* args */) { number_valid_policies = 0; }

day02::~day02() {}

/**
 * @brief Solve part 1
 *
 * @param inTable
 */
void day02::solver_part1(std::vector<std::string> inTable) {
  bool result_found = false;
  int result = 0;

  std::cout << "Policy check part 1" << std::endl;

  // Format code
  this->format_code(inTable);

  // Check all valid policies
  this->count_valid_policies();
}

/**
 * @brief Solve part 1
 *
 * @param inTable
 */
void day02::solver_part2(std::vector<std::string> inTable) {
  bool result_found = false;
  int result = 0;

  std::cout << "Policy check part 2" << std::endl;

  // Check all valid policies
  this->count_valid_policies_p2();
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day02::format_code(std::vector<std::string> inTable) {
  std::string string_line = "";
  std::string element = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    std::vector<std::string> string_vec_element;
    std::string::size_type start{0};
    std::string::size_type pos;
    std::string delimiter = " -";

    // Get single line as string_line
    string_line = (*i);

    // Split string_line
    do {
      pos = string_line.find_first_of(delimiter, start);
      element = string_line.substr(start, pos - start);
      string_vec_element.push_back(element);
      start = pos + 1;
    } while (pos != std::string::npos);

    // add to code list
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
bool day02::check_single_policy(t_code_element password_element) {
  bool is_password_valid = false;
  int counted_characters_in_string = 0;
  int min_occurrences = get<0>(password_element);
  int max_occurrences = get<1>(password_element);
  std::string eval_character = get<2>(password_element);
  std::string eval_string = get<3>(password_element);

  // Split string to characters and loop through string
  for (int i = 0; i < eval_string.length(); i++) {
    if ((char)eval_string.at(i) ==
        (char)eval_character.at(0)) { // Check if equal
      counted_characters_in_string++;
    }
  }

  // Now check if number fits to policy
  if (min_occurrences <= counted_characters_in_string &&
      counted_characters_in_string <= max_occurrences) {
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
bool day02::check_single_policy_p2(t_code_element password_element) {
  bool is_password_valid = false;
  int counted_characters_in_string = 0;
  int min_occurrences = get<0>(password_element);
  int max_occurrences = get<1>(password_element);
  std::string eval_character = get<2>(password_element);
  std::string eval_string = get<3>(password_element);

  // Split string to characters and loop through string
  if ((char)eval_string.at(min_occurrences - 1) == (char)eval_character.at(0) &&
          !((char)eval_string.at(max_occurrences - 1) ==
            (char)eval_character.at(0)) ||
      !((char)eval_string.at(min_occurrences - 1) ==
        (char)eval_character.at(0)) &&
          (char)eval_string.at(max_occurrences - 1) ==
              (char)eval_character.at(0)) {
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
int day02::count_valid_policies(void) {
  int valid_passwords = 0;
  bool policy_valid = false;

  // Loop thorugh tuple formatted code and call policy check
  for (const auto &itcoli : format_code_list) {
    policy_valid = this->check_single_policy(itcoli);

    // count events
    if (policy_valid) {
      valid_passwords++;
    }
  }

  std::cout << "Found valid policies: " << valid_passwords << std::endl;

  return (valid_passwords);
}

/**
 * @brief Iterates through the complete password list and counts up all valid
 * once and stor in private result variable and print result
 *
 * @return int number of valid passwords
 */
int day02::count_valid_policies_p2(void) {
  int valid_passwords = 0;
  bool policy_valid = false;

  // Loop thorugh tuple formatted code and call policy check
  for (const auto &itcoli : format_code_list) {
    policy_valid = this->check_single_policy_p2(itcoli);

    // count events
    if (policy_valid) {
      valid_passwords++;
    }
  }

  std::cout << "Found valid policies: " << valid_passwords << std::endl;

  return (valid_passwords);
}