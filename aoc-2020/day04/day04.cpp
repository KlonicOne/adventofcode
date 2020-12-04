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
  this->format_pp_list.resize(this->passport_length);
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
  this->init_element_pp_list(current_pp_index);

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
      this->init_element_pp_list(current_pp_index);

      // std::cout << "Next pp element " << current_pp_index << std::endl;
      continue;  // This line is not to be considered, eval next line
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
    for (int j = 0; j < string_vec_element.size(); j = j + 2) {
      std::string el_name = string_vec_element[j];
      std::string el_value = string_vec_element[j + 1];
      // Store value in table
      this->set_value_pp_list(current_pp_index, el_name, el_value);

      // debug
      // std::cout << current_pp_index << ", " << j << ", " << el_name << ", "
      //           << el_value << std::endl;
    }

    // debug out
    // for (std::string vecel : string_vec_element) {
    //   std::cout << vecel << ", ";
    // }
    // std::cout << std::endl;
  }
  this->format_list_size = current_pp_index;
}

/**
 * @brief Plot the list pp element
 *
 */
void day04::print_element_pp_list(void) {
  int current_index = 0;
  for (auto &pplistel : format_pp_list) {
    std::cout << "Passport: " << current_index+1 << std::endl;
    std::cout << pplistel.byr.name << ", " << pplistel.byr.value << ", "
              << pplistel.byr.optional << std::endl;
    std::cout << pplistel.iyr.name << ", " << pplistel.iyr.value << ", "
              << pplistel.iyr.optional << std::endl;
    std::cout << pplistel.eyr.name << ", " << pplistel.eyr.value << ", "
              << pplistel.eyr.optional << std::endl;
    std::cout << pplistel.hgt.name << ", " << pplistel.hgt.value << ", "
              << pplistel.hgt.optional << std::endl;
    std::cout << pplistel.hcl.name << ", " << pplistel.hcl.value << ", "
              << pplistel.hcl.optional << std::endl;
    std::cout << pplistel.ecl.name << ", " << pplistel.ecl.value << ", "
              << pplistel.ecl.optional << std::endl;
    std::cout << pplistel.pid.name << ", " << pplistel.pid.value << ", "
              << pplistel.pid.optional << std::endl;
    std::cout << pplistel.cid.name << ", " << pplistel.cid.value << ", "
              << pplistel.cid.optional << std::endl;

    // only elements to plot
    current_index++;
    if (current_index > this->format_list_size) break;
  }
  std::cout << std::endl;
}

/**
 * @brief Init given element to default
 *
 * @param element_pos
 */
void day04::init_element_pp_list(int element_pos) {
  this->format_pp_list[element_pos].byr.name = "byr";
  this->format_pp_list[element_pos].byr.value = "";
  this->format_pp_list[element_pos].byr.optional = false;
  this->format_pp_list[element_pos].iyr.name = "iyr";
  this->format_pp_list[element_pos].iyr.value = "";
  this->format_pp_list[element_pos].iyr.optional = false;
  this->format_pp_list[element_pos].eyr.name = "eyr";
  this->format_pp_list[element_pos].eyr.value = "";
  this->format_pp_list[element_pos].eyr.optional = false;
  this->format_pp_list[element_pos].hgt.name = "hgt";
  this->format_pp_list[element_pos].hgt.value = "";
  this->format_pp_list[element_pos].hgt.optional = false;
  this->format_pp_list[element_pos].hcl.name = "hcl";
  this->format_pp_list[element_pos].hcl.value = "";
  this->format_pp_list[element_pos].hcl.optional = false;
  this->format_pp_list[element_pos].ecl.name = "ecl";
  this->format_pp_list[element_pos].ecl.value = "";
  this->format_pp_list[element_pos].ecl.optional = false;
  this->format_pp_list[element_pos].pid.name = "pid";
  this->format_pp_list[element_pos].pid.value = "";
  this->format_pp_list[element_pos].pid.optional = false;
  this->format_pp_list[element_pos].cid.name = "cid";
  this->format_pp_list[element_pos].cid.value = "";
  this->format_pp_list[element_pos].cid.optional = true;
}

/**
 * @brief Check for given name and add value to list on given pos
 *
 * @param element_pos Which position
 * @param element_name Which name
 * @param element_value The value to be set
 */
void day04::set_value_pp_list(int element_pos, std::string element_name,
                              std::string element_value) {
  // std::cout << "el name: " << element_name;
  // std::cout << ", list name: " << this->format_pp_list[element_pos].byr.name;
  // std::cout << ", Comp: " <<
  // element_name.compare(this->format_pp_list[element_pos].byr.name) <<
  // std::endl;

  // Look up table
  if (element_name.compare(this->format_pp_list[element_pos].byr.name) == 0) {
    this->format_pp_list[element_pos].byr.value = element_value;
  } else if (element_name.compare(this->format_pp_list[element_pos].iyr.name) ==
             0) {
    this->format_pp_list[element_pos].iyr.value = element_value;
  } else if (element_name.compare(
                 this->format_pp_list[element_pos].eyr.name) == 0) {
    this->format_pp_list[element_pos].eyr.value = element_value;
  } else if (element_name.compare(this->format_pp_list[element_pos].hgt.name) ==
             0) {
    this->format_pp_list[element_pos].hgt.value = element_value;
  } else if (element_name.compare(this->format_pp_list[element_pos].hcl.name) ==
             0) {
    this->format_pp_list[element_pos].hcl.value = element_value;
  } else if (element_name.compare(this->format_pp_list[element_pos].ecl.name) ==
             0) {
    this->format_pp_list[element_pos].ecl.value = element_value;
  } else if (element_name.compare(this->format_pp_list[element_pos].pid.name) ==
             0) {
    this->format_pp_list[element_pos].pid.value = element_value;
  } else if (element_name.compare(this->format_pp_list[element_pos].cid.name) ==
             0) {
    this->format_pp_list[element_pos].cid.value = element_value;
  } else {
    std::cout << "No matching name" << std::endl;
    std::cout << element_pos << ", " << element_name << ", " << element_value
              << std::endl;
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
  for (const auto &itcoli : format_pp_list) {
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
  for (const auto &itcoli : format_pp_list) {
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