/**
 * @file day09.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day09.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief constructor
 *
 */
day09::day09(/* args */) {}

/**
 * @brief Destroy the day09::day09
 *
 */
day09::~day09() {}

/**
 * @brief Solve part 1
 *
 */
void day09::solver_part1(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;

  // My bag in list so result - 1 should be good
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day09::solver_part2(void) {
  int answer;
  // Info out
  std::cout << "Part 2" << std::endl;

  // Result fits already
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day09::format_input(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  std::string string_line = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {

    // Get single line as string_line
    string_line = (*i);

    // debug
    // std::cout << string_line << std::endl;

    // Should not get non string in lines
    if (string_line.length() == 0) {
      std::cout << "Empty line found in intput!!!" << std::endl;
    }
  }
}