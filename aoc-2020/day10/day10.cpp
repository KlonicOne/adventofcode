/**
 * @file day10.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day10.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
#include <regex>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define DEBUG_OUT false

/**
 * @brief constructor
 *
 */
day10::day10(/* args */) {}

/**
 * @brief Destroy the day10::day10
 *
 */
day10::~day10() {}

/**
 * @brief Solve part 1
 *
 */
void day10::solver_part1(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;

  // Sort jolts
  this->sort_adapter_jolt();

  // Loop through jolts
  for (int i = 1; i <= 3; ++i) {
    this->m_num_jolt_diffs.push_back(this->eval_num_jolt_diff(i));
    std::cout << "Diff: " << i << ", Result: "
              << this->m_num_jolt_diffs.at(this->m_num_jolt_diffs.size() - 1)
              << std::endl;
  }

  // Answer is num of 1diff jolts mul with 3jolt num
  answer = this->m_num_jolt_diffs.at(0) * this->m_num_jolt_diffs.at(2);

  // My bag in list so result - 1 should be good
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day10::solver_part2(void) {
  long long answer = 0;
  // Info out
  std::cout << "Part 2" << std::endl;

  // Check combinations for 1, 2 and 3
  answer = eval_number_combis();;

  // Result fits already
  std::cout << "Result: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Set the input vector to the call member
 *
 * @param in_vector
 */
void day10::setInput(std::vector<int> in_vector) {
  this->m_jolt_adapters = in_vector;

  // Add start and end
  this->m_jolt_adapters.push_back(0);
  this->m_jolt_adapters.push_back(
      *max_element(this->m_jolt_adapters.begin(), this->m_jolt_adapters.end()) +
      3);

  // Unsorted vec not changed
  this->m_jolt_adapters_raw = in_vector; // keep unsorted

  if (DEBUG_OUT) {
    for (auto &eit : this->m_jolt_adapters) {
      std::cout << eit << ", ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief sort the input vector to get all ascending
 *
 */
void day10::sort_adapter_jolt(void) {
  sort(this->m_jolt_adapters.begin(), this->m_jolt_adapters.end());

  if (DEBUG_OUT) {
    std::cout << "(0), ";
    for (auto &eit : this->m_jolt_adapters) {
      std::cout << eit << ", ";
    }
    std::cout << "("
              << this->m_jolt_adapters.at(this->m_jolt_adapters.size() - 1) + 3
              << ")" << std::endl;
  }
}

/**
 * @brief Calclate the number of diffs for given jolt
 *
 * @param jolt_diff Diff for which to check
 * @return int number of diffs for given jolts
 */
int day10::eval_num_jolt_diff(int jolt_diff) {
  int num_adapters = 0; // My adapter fits for all difs so here 1

  // Loop through elements, but start on higher for diff
  for (int i = 1; i < this->m_jolt_adapters.size(); ++i) {
    if (this->m_jolt_adapters[i] - this->m_jolt_adapters[i - 1] == jolt_diff) {
      // matching diff
      num_adapters++;
    }
  }

  return (num_adapters);
}

/**
 * @brief Evaluate the possible combinations
 *
 * @return int
 */
int day10::eval_number_combis(void) {
  int found_combinations = 0;

  unordered_map<uintmax_t, uintmax_t> map_combinations{{0, 1}};

  for (auto &it : this->m_jolt_adapters) {
    map_combinations[it] += map_combinations[it - 1] +
                            map_combinations[it - 2] + map_combinations[it - 3];
  }
  found_combinations = map_combinations[this->m_jolt_adapters.back()];

  return (found_combinations);
}
