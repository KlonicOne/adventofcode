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
  this->eval_num_loop();

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
  this->eval_num_opt();

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

void day15::eval_num_opt(void) {
  int stop_cond = this->m_stop_cond - this->m_num_list.size();
  int i = 0;
  int last_key = 0, next_key = 0;
  int last_value = 0, next_value = 0;
  map<int, int> num_map;

  // Fill map with given start list
  for (auto iter : this->m_num_list) {
    num_map.insert(pair<int, int>(iter, i));
    i++;
  }

  // Reuse of i for the current position in the num list
  i = this->m_num_list.size();
  // Preload initial key and value
  last_key = m_num_list.back();
  last_value = m_num_list.size() - 1;
  // And delete the element in the map, else it is found immediatly
  num_map.erase(last_key);
  // Search through list storing last element to search
  while (stop_cond != 0) {
    if (num_map.count(last_key)) {
      // key in list
      next_key = last_value - num_map[last_key];
      next_value = i;
      // And write last in map
      num_map[last_key] = last_value;
    } else {
      next_key = 0;
      next_value = i;
      // key not in list
      num_map.insert(make_pair(last_key, last_value));
    }
    // Take over next as last
    last_key = next_key;
    last_value = next_value;

    // next loop
    i++;
    stop_cond--;
  }

  // Store restul in last key
  this->m_result = last_key;

  if (DEBUG_OUT) {
    show_assocontainer(num_map);
  }
}

/**
 * @brief Evaluate the result for part 1 and store in member var. Searching for
 * the result of the 2020th number in the vector
 *
 */
void day15::eval_num_loop(void) {
  // Stop is position 2020 from beginning of vector
  int stop_cond = this->m_stop_cond - this->m_num_list.size();
  // copy as modified
  auto running_list = this->m_num_list;

  // Loop max times through the vector
  while (stop_cond != 0) {
    bool match_recent = false; // Was last found?

    // Find dist to most recent
    for (int i = running_list.size() - 2; i >= 0; --i) {
      if (running_list[i] == running_list.back()) {
        match_recent = true;
        // Now get the distance
        running_list.push_back(
            std::distance(running_list.begin() + i, running_list.end() - 1));
        break;
      }
    }

    // If we found no match, then we say 0
    if (!match_recent) {
      running_list.push_back(0);
    }

    // Check where we are
    if (stop_cond % 1000000 == 0) {
      std::cout << stop_cond << std::endl;
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
