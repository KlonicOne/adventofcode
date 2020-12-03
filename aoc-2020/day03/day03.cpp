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
  this->current_pos = {0, 0, 0};
  this->found_trees = 0;
  this->m_map_multiplier = MULTI_MAP;
  this->m_xdim = XDIM;
  this->m_ydim = YDIM;
  m_treemap.resize(XDIM, vec_1d_t(YDIM));
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
  int result_1 = 0;

  // Info out
  std::cout << "Part 1 how many trees" << std::endl;

  // Calculate the path and count trees
  this->calc_path(3, 1);
  result_1 = this->calc_trees_on_path();
  std::cout << "Found trees: " << this->found_trees << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day03::solver_part2(void) {
  int result_1 = 0;
  int result_2 = 0;
  int result_3 = 0;
  int result_4 = 0;
  int result_5 = 0;
  unsigned long long int final_result = 0;

  // Info out
  std::cout << "Part 2 how many trees" << std::endl;

  // Calculate the path and count trees
  this->calc_path(1, 1);
  result_1 = this->calc_trees_on_path();
  std::cout << "Found trees: " << result_1 << std::endl;

  // Calculate the path and count trees
  this->calc_path(3, 1);
  result_2 = this->calc_trees_on_path();
  std::cout << "Found trees: " << result_2 << std::endl;

  // Calculate the path and count trees
  this->calc_path(5, 1);
  result_3 = this->calc_trees_on_path();
  std::cout << "Found trees: " << result_3 << std::endl;

  // Calculate the path and count trees
  this->calc_path(7, 1);
  result_4 = this->calc_trees_on_path();
  std::cout << "Found trees: " << result_4 << std::endl;

  // Calculate the path and count trees
  this->calc_path(1, 2);
  result_5 = this->calc_trees_on_path();
  std::cout << "Found trees: " << result_5 << std::endl;

  // Final result !!! Must be multiplied not in one step
  final_result = result_5 * result_4;
  final_result = final_result * result_3;
  final_result = final_result * result_2;
  final_result = final_result * result_1;

  std::cout << "Final result: " << final_result << std::endl;
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

  // for (std::vector<std::string>::const_iterator i = inTable.begin();
  //      i != inTable.end(); ++i)
  for (int k = 0; k < inTable.size(); ++k) {
    // variables to loop through string
    std::vector<int> int_line;

    // Get single line as vector of ints
    string_line = inTable.at(k);
    // convert line to vector of ints
    for (char const element : string_line) {
      if (element == tree_sym) {
        int_line.push_back(1);
      } else {
        int_line.push_back(0);
      }
    }

    // copy vector to map
    for (int j = 0; j < m_map_multiplier; ++j) {
      int offset_i = j * int_line.size();
      for (int i = 0; i < int_line.size(); ++i) {
        m_treemap[i + offset_i][k] = int_line[i];
      }
    }
    this->m_xdim = m_map_multiplier * int_line.size();
  }

  this->m_ydim = inTable.size();

  // debug out
  // this->plotTreeMap();
}

/**
 * @brief To print out the used map
 *
 */
void day03::plotTreeMap(void) {
  for (unsigned y = 0; y < this->m_ydim; y++) {
    for (unsigned x = 0; x < this->m_xdim; x++) {
      std::cout << this->m_treemap[x].at(y);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/**
 * @brief Calculate the path and store in member
 *
 */
void day03::calc_path(int slope_x, int slope_y) {
  // Calculate with slope next position and check for boundary
  bool loop_path = true;
  this->current_pos.x = 0;
  this->current_pos.y = 0;

  // clear path vector
  this->m_path.clear();

  while (loop_path) {
    // add position with value in path
    this->current_pos.value = m_treemap[current_pos.x].at(current_pos.y);
    this->m_path.push_back(current_pos);
    // next pos calculation
    this->current_pos.x += slope_x;
    this->current_pos.y += slope_y;
    // Check limits exceeded then stop
    if (this->current_pos.x > this->m_xdim ||
        this->current_pos.y > this->m_ydim) {
      loop_path = false;
      std::cout << "slope: " << slope_x << ", " << slope_y << " stop x "
                << (this->current_pos.x > this->m_xdim) << " stop y "
                << (this->current_pos.y > this->m_ydim) << std::endl;
    }
  }
}

/**
 * @brief Calculate the number of hit trees in path and print out
 *
 */
int day03::calc_trees_on_path(void) {
  this->found_trees = 0;
  // Iterate through path and check for hit trees
  for (int i = 0; i < this->m_path.size(); ++i) {
    this->found_trees += this->m_path.at(i).value;
  }
  return (this->found_trees);
}
