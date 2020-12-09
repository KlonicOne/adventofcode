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

#include <algorithm>
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
day09::day09(/* args */) {
  this->size_preamble = 25;
  this->current_pos = 0;
  this->invalid_num = 0;
}

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
  bool loop_cond = true;
  long long answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;

  while (loop_cond) {
    // Next preamble check
    loop_cond = this->eval_valid_num();
    // next pos to check
    this->current_pos++;

    // Check if still elements in input
    if (this->current_pos >= this->vec_input.size()) {
      loop_cond = false;
    }
  }

  answer = this->get_invalid_num();

  // My bag in list so result - 1 should be good
  std::cout << "Result: " << answer << std::endl;
}

long long day09::get_invalid_num(void) { return (this->invalid_num); }

/**
 * @brief Check for valid number
 *
 * @return true found valid number
 * @return false not found
 */
bool day09::eval_valid_num(void) {
  bool result = false;
  long long temp_sum = 0;
  long long temp_value = 0;

  // check if current pos higher then preamble size
  if (this->current_pos >= this->size_preamble) {
    int start_tmp, stop_tmp;
    // eval last preamble
    temp_value = this->vec_input.at(this->current_pos);
    this->invalid_num = temp_value;
    start_tmp = this->current_pos - this->size_preamble;
    stop_tmp = this->current_pos;

    // Loop on preamble
    for (int i = start_tmp; i < stop_tmp; ++i) {
      for (int j = start_tmp; j < stop_tmp; ++j) {
        // not with itself
        if (i != j) {
          temp_sum = this->vec_input[i] + this->vec_input[j];
          if (temp_sum == temp_value) {
            result = true;         // found valid num
            this->invalid_num = 0; // no invalid num
            break;
          }
        }
      }
    }
  } else {
    result = true; // pos not above preamble
  }
  return (result);
}

/**
 * @brief Solve part 2
 *
 */
void day09::solver_part2(void) {
  long long answer = 0;
  // Info out
  std::cout << "Part 2" << std::endl;

  this->eval_minmax_buffer();

  answer = this->get_sum_minmax_buffer();

  // Result fits already
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief return result on min max sum in preamble
 *
 * @return long long sum of min max
 */
long long day09::get_sum_minmax_buffer(void) { return (this->minmax_sum); }

/**
 * @brief Calc sum with min max in current preamble
 *
 */
void day09::eval_minmax_buffer(void) {
  bool result_found = false;
  int search_range = 2;
  int search_pos = 0;
  long long temp_result = 0;

  this->minmax_buffer.clear();

  // Loop on preamble
  while (!result_found) {

    // Sum
    for (int i = search_pos; i < (search_pos + search_range); ++i) {
      temp_result += this->vec_input[i];
    }

    if (temp_result == this->invalid_num) {
      result_found = true;
      // Assign buffer for min max calculation
      this->minmax_buffer.assign(&this->vec_input[search_pos],
                                 &this->vec_input[search_pos] + search_range);
    } else if (temp_result > this->invalid_num) {
      // increase range
      search_pos++;
      search_range = 2;
      temp_result = 0;
    } else {
      // Increase search range
      search_range++;
      temp_result = 0;
    }
  }

  std::cout << this->minmax_buffer.size() << std::endl;

  // Sort vec and sum up
  sort(this->minmax_buffer.begin(), this->minmax_buffer.end());
  this->minmax_sum = this->minmax_buffer.at(0) +
                     this->minmax_buffer.at(this->minmax_buffer.size() - 1);
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
      continue;
    }

    // Push number to internal vec
    this->vec_input.push_back(stoll(string_line));
  }
}