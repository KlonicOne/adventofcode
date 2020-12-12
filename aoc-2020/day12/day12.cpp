/**
 * @file day12.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day12.h"
#include "show_container.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

#define DEBUG_OUT true

/**
 * @brief constructor
 *
 */
day12::day12(/* args */) {}

/**
 * @brief Destroy the day12::day12
 *
 */
day12::~day12() {}

/**
 * @brief Solve part 1
 *
 */
void day12::solver_part1(void) {
  int answer = 0;

  // My bag in list so result - 1 should be good
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day12::solver_part2(void) {
  int answer = 0;

  // My bag in list so result - 1 should be good
  std::cout << "Result Part2: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

void day12::create_format_input(std::vector<std::string> input) {
  t_input_element temp_inel;

  for (auto iter : input) {
    temp_inel.cmd = iter[0];
    std::string str_value = iter.substr(1, (iter.size() - 1));
    temp_inel.value = stoi(str_value);

    // Create formated input
    this->m_format_input.push_back(temp_inel);

    if(DEBUG_OUT) {
      std::cout << "cmd: " << temp_inel.cmd << ", value: " << temp_inel.value << std::endl;
    }
  }
}

void day12::create_ship_route(std::vector<std::string> input) {
  t_Position temp_pos;
}