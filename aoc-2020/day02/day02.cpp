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

day02::day02(/* args */) {
    number_valid_policies = 0;
}

day02::~day02() {}

/**
 * @brief Solve part 1
 * 
 * @param inTable 
 */
void day02::solver_part1(std::vector<std::string> inTable) {
  bool result_found = false;
  int result = 0;
  std::string element = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    element = (*i);

    std::cout << "Line: " << element << std::endl;
  }
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day02::format_code(std::vector<std::string> inTable) {}

/**
 * @brief Check if given password fits to policy
 *
 * @param password_element contains password and policy
 * @return true policy valid
 * @return false invalid
 */
bool day02::check_single_policy(
    std::tuple<int, int, char, std::string> password_element) {
      bool is_password_valid = false;

      return(false);
    }

/**
 * @brief Iterates through the complete password list and counts up all valid
 * once and stor in private result variable and print result
 *
 * @return int number of valid passwords
 */
int day02::count_valid_policies(void) {
  int valid_passwords = 0;

  return (valid_passwords);
}

/**
 * @brief Solve part 1
 * 
 * @param inTable 
 */
void day02::solver_part2(std::vector<std::string> inTable) {}
