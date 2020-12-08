/**
 * @file day08.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day08.h"

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

day08::day08(/* args */) {}

day08::~day08() {}

/**
 * @brief Solve part 1
 *
 */
void day08::solver_part1(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;

  while(computer.execute_acc_comp()) {} // Run while end of program

  answer = computer.get_acc_value();

  // My bag in list so result - 1 should be good
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day08::solver_part2(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 2" << std::endl;

  // My bag in list so result - 1 should be good
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief Forward to generate code
 *
 * @param inTable
 */
void day08::format_input(std::vector<std::string> inTable) {
  // Call computer code generator
  computer.generate_program(inTable);
}
