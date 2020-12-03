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
  this->current_pos = std::make_tuple(0, 0, 0);
  this->found_trees = 0;
  this->m_map_multiplier = 8;
  this->m_ydim = XDIM;
  this->m_ydim = YDIM;
  this->m_zdim = ZDIM;
  this->slope_down = 1;
  this->slope_right = 3;
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

  // Calculate the path
  this->calc_path();

  // Count trees on path
  this->calc_trees_on_path();
}

/**
 * @brief Solve part 2
 *
 */
void day03::solver_part2(void) {
  // Info out
  std::cout << "Policy check part 2" << std::endl;
}

/**
 * @brief Create map from input
 *
 * @param inTable
 */
void day03::create_map(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  std::string string_line = "";
  std::string element = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // variables to loop through string
    std::vector<int> int_line;
    int int_element = 0;

    // Get single line as string_line
    string_line = (*i);
    // convert line to vector of ints
    for (auto &element : string_line) {
      int_element = stoi(&element);
      int_line.push_back(int_element);

      // debug out
      std::cout << int_line[int_line.size()-1] << std::endl;
    }

    // // Split string to characters and loop through string
    // for (int i = 0; i < eval_string.length(); i++) {
    //   if ((char)eval_string.at(i) ==
    //       (char)eval_character.at(0)) {  // Check if equal
    //     num_matching_chars++;
    //   }
    // }
  }
}

/**
 * @brief Calculate the path and store in member
 *
 */
void day03::calc_path(void) {
  // Calculate with slope next position

  // Store next position with value in path
}

/**
 * @brief Calculate the number of hit trees in path and print out
 *
 */
void day03::calc_trees_on_path(void) {
  // Iterate through path and check for hit trees

  // print out result
}
