/**
 * @file day13.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day13.h"
#include "show_container.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

#define DEBUG_OUT false

/**
 * @brief constructor
 *
 */
day13::day13(/* args */) {
  this->m_arrive_time = 0;
  this->m_best_bus_id_p1 = 0;
  this->m_result_p2 = 0;
}

/**
 * @brief Destroy the day13::day13
 *
 */
day13::~day13() {}

/**
 * @brief Solve part 1
 *
 */
void day13::solver_part1(void) {
  int answer = 0;

  // Check for best bus
  this->eval_best_bus_id_p1();

  // Cacl result for best bus
  answer = this->get_result_p1();

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day13::solver_part2(void) {
  int answer = 0;

  // Check the conditions
  this->eval_cond_p2();

  // result
  answer = this->get_result_p2();

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
void day13::format_input(std::vector<std::string> inTable) {
  int line_num = 0;
  int bus_num = 0;
  std::string string_line = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i, ++line_num) {
    std::vector<std::string> string_vec_element;
    std::string element = "";
    std::string::size_type start{0};
    std::string::size_type len{0};
    std::string::size_type pos;
    std::string delimiter = ","; // No splitting this time

    // Get single line as string_line
    string_line = (*i);

    // First element is arrival time
    if (line_num == 0) {
      this->m_arrive_time = stoi(string_line);
      continue;
    }

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // add element to end of vector
      string_vec_element.push_back(element);

      // Take over if not x
      if (element.compare("x")) {
        // Not a x
        this->m_bus_ids.push_back(stoi(element));
        this->m_bus_subs_time.push_back(bus_num);
      }

      // next position to start searching for delimiter
      start = pos + 1;
      // Next bus number
      bus_num++;
    } while (pos != std::string::npos);

    if (DEBUG_OUT) {
      std::cout << "arrival: " << this->m_arrive_time << std::endl;
      show_container(this->m_bus_ids);
      show_container(this->m_bus_subs_time);
    }
  }
}

/**
 * @brief Evaluate which bus id fits best to the arrival time. Result is stored
 * in member
 *
 */
void day13::eval_best_bus_id_p1(void) {
  std::vector<int> temp_last_bus;
  std::vector<int> temp_next_diff_bus;

  // Get closes previous bus
  for (auto iter : this->m_bus_ids) {
    temp_last_bus.push_back(this->m_arrive_time % iter);
  }

  if (DEBUG_OUT) {
    show_container(temp_last_bus);
  }

  // Diff to next bus, smalles fits most
  for (int i = 0; i < this->m_bus_ids.size(); ++i) {
    // Just better to debug
    int temp_value = this->m_bus_ids[i] - temp_last_bus[i];
    temp_next_diff_bus.push_back(temp_value);
  }

  if (DEBUG_OUT) {
    show_container(temp_next_diff_bus);
  }

  // Now get iter for smalles element and set best ID to member
  std::vector<int>::iterator result =
      std::min_element(temp_next_diff_bus.begin(), temp_next_diff_bus.end());
  int pos_smallest = std::distance(temp_next_diff_bus.begin(), result);
  this->m_best_bus_id_p1 = this->m_bus_ids.at(pos_smallest);

  // multiplying the bus ID by the number of minutes
  this->m_result_p1 =
      temp_next_diff_bus.at(pos_smallest) * this->m_best_bus_id_p1;
}

/**
 * @brief Getter for result p1
 *
 * @return result
 */
int day13::get_result_p1(void) { return (this->m_result_p1); }

/**
 * @brief Evaluate the result for p2
 * Check for the modulo fits to the delay time to each bus
 *
 */
void day13::eval_cond_p2(void) {
  bool result_found = true;
  long long temp_limit = std::numeric_limits<long long>::max();

  for (long long i = 0; i <= temp_limit; ++i) {
    // set to result found, only if one not fitting the to false
    result_found = true;

    // now check the conditions for each bus
    for (int j = 0; j < this->m_bus_ids.size(); ++j) {
      long long temp_result = (i + this->m_bus_subs_time[j]) % this->m_bus_ids[j];

      if (DEBUG_OUT) {
        std::cout << "num: " << i << ", bus: " << this->m_bus_ids[j]
                  << ", res: " << temp_result << std::endl;
      }

      // Check if the condition for this bus is met
      if (temp_result != 0) {
        result_found = false;
        break; // Stop this for loop checking the rest
      }
    }

    // Check if last loop did match
    if (result_found) {
      // We had a match
      this->m_result_p2 = i;
      break; // Also stop this loop
    }
  }
}

/**
 * @brief Getter p2
 *
 * @return long long
 */
long long day13::get_result_p2(void) { return (this->m_result_p2); }
