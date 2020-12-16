/**
 * @file day15.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day15.h"
#include "show_container.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define DEBUG_OUT false

/**
 * @brief constructor
 *
 */
day15::day15(/* args */) {
  this->m_result = 0;
  this->m_stop_cond = 0;
}

/**
 * @brief Destroy the day15::day15
 *
 */
day15::~day15() {}

/**
 * @brief Solve part 1
 *
 */
void day15::solver_part1(void) {
  long long answer = 0;

  // Stop cond
  this->set_stop_condition(2020);

  // Check for best bus
  this->eval_num();

  // Cacl result for best bus
  answer = this->get_result();

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day15::solver_part2(void) {
  long long answer = 0;

  // Stop cond
  this->set_stop_condition(30000000);

  // Check for best bus
  this->eval_num();

  // Cacl result for best bus
  answer = this->get_result();

  // Out result
  std::cout << "Result Part2: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day15::format_input(std::vector<std::string> inTable) {
  // Loop through lines of file in input
  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // used temp to store line and each element
    std::string string_line = "";
    std::string element = "";
    // To split the string
    std::string::size_type start{0};
    std::string::size_type len{0};
    std::string::size_type pos;
    std::string delimiter = ",";

    // Get single line as string_line
    string_line = (*i);

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);

      // add element to end of vector

      this->m_num_list.push_back(stoi(element));
      // next position to start searching for delimiter
      start = pos + 1;
    } while (pos != std::string::npos);

    if (DEBUG_OUT) {
      show_container(this->m_num_list);
    }
  }
}

/**
 * @brief Set the stop condition for the loop
 *
 * @param cond
 */
void day15::set_stop_condition(int cond) { this->m_stop_cond = cond; }

/**
 * @brief Getter for result p1
 *
 * @return result
 */
long long day15::get_result(void) { return (this->m_result); }

/**
 * @brief Evaluate the result for part 1 and store in member var. Searching for
 * the result of the 2020th number in the vector
 *
 */
void day15::eval_num(void) {
  // Stop is position 2020 from beginning of vector
  int stop_cond = this->m_stop_cond - this->m_num_list.size();
  // copy as modified
  auto running_list = this->m_num_list;

  // Loop max times through the vector
  while (stop_cond != 0) {
    bool match_recent = false; // Was last found?

    // Find dist to most recent with reverse iterator
    for (std::vector<long long>::reverse_iterator riter =
             (running_list.rbegin() + 1);
         riter < running_list.rend(); ++riter) {

      if (*riter == running_list.back()) {
        match_recent = true;
        // Now get the distance
        running_list.push_back(distance(running_list.rbegin(), riter));
        break;
      }
    }

    // If we found no match, then we say 0
    if (!match_recent) {
      running_list.push_back(0);
    }

    // Next loop until stop cond met
    --stop_cond;
  }

  // Store result
  this->m_result = running_list.back();

  if (DEBUG_OUT) {
    show_container(running_list);
  }
}
