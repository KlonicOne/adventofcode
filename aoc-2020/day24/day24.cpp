/**
 * @file day24.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day24.h"
#include "show_container.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <time.h>
#include <vector>

using namespace std;

#define DEBUG_OUT true

/**
 * @brief constructor
 *
 */
day24::day24(/* args */) { this->m_sum_out_of_range = 0; }

/**
 * @brief Destroy the day24::day24
 *
 */
day24::~day24() {}

/**
 * @brief Solve part 1
 *
 */
void day24::solver_part1(void) {
  int answer = 0;

  this->eval_values_out_of_range();
  this->calc_sum_out_of_range();
  answer = this->get_sum_out_of_range();

  if (DEBUG_OUT) {
    for (auto iter : this->m_rules) {
      std::cout << iter.name << ": ";
      for (auto iter_ranges : iter.ranges) {
        std::cout << iter_ranges.min_val << "-" << iter_ranges.max_val
                  << " or ";
      }
      std::cout << std::endl;
    }
    std::cout << "My ticket: ";
    for (auto iter : this->m_my_ticket.ticket_vals) {
      std::cout << iter << ", ";
    }
    std::cout << std::endl;
    std::cout << "Nearby tickets: " << std::endl;
    for (auto iter : this->m_nearby_tickets) {
      std::cout << "(" << iter.ticket_valid << "):";
      for (auto iter_tick : iter.ticket_vals) {
        std::cout << iter_tick << ", ";
      }
      std::cout << std::endl;
    }
    std::cout << "Values out of range: " << std::endl;
    for (auto iter : this->m_values_out_of_range) {
      std::cout << iter << ", ";
    }
    std::cout << std::endl;
  }

  // Out result
  std::cout << "Result Part1: " << std::dec << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day24::solver_part2(void) {
  long answer = 0;

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
void day24::format_input(std::vector<std::string> inTable) {
  t_input_section current_section = RULES;
  int line_num = 0;
  std::string string_line = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i, ++line_num) {
    std::size_t found;
    std::size_t found_enclosing;
    t_rule temp_rule;
    t_range temp_range;
    t_ticket temp_ticket;

    // variables to loop through string
    std::string::size_type start{0};
    std::string::size_type pos;
    std::string delimiter = ",";

    // Get single line as string_line
    string_line = (*i);

    // Skip empty line
    if (string_line == "") {
      // We completed section so go over to next
      switch (current_section) {
      case RULES: {
        current_section = MY_TICKET;
      } break;

      case MY_TICKET: {
        current_section = NEARBY_TICKET;
      } break;

      default:
        break;
      }
      // Skip the empty line
      continue;
    }

    // Which section of input
    switch (current_section) {
    case RULES: {
      // We are reading rules, start with name up to : and then ranges are
      // coming
      found = string_line.find(":");
      // Extract the rule name
      std::string rule_name = string_line.substr(0, 0 + found);
      temp_rule.name = rule_name;
      // Rule has always two ranges
      found_enclosing = string_line.find("or ");
      std::string rule1 =
          string_line.substr(found + 2, found_enclosing - found - 3);
      std::string rule2 = string_line.substr(
          found_enclosing + 3, std::string::npos - found_enclosing);
      // Extract the numbers of the rules and set the to temp rule
      found = rule1.find("-");
      temp_range.min_val = stoi(rule1.substr(0, found));
      temp_range.max_val =
          stoi(rule1.substr(found + 1, std::string::npos - found + 1));
      temp_rule.ranges.push_back(temp_range);
      found = rule2.find("-");
      temp_range.min_val = stoi(rule2.substr(0, found));
      temp_range.max_val =
          stoi(rule2.substr(found + 1, std::string::npos - found + 1));
      temp_rule.ranges.push_back(temp_range);
      // Add temp rule to input data of class
      this->m_rules.push_back(temp_rule);
    } break;

    case MY_TICKET: {
      if (string_line == "your ticket:") {
        continue;
      }
      // extract my ticket to vector of ints
      // Split string_line and store in vector of strings
      do {
        // get pos from start to first delimiter
        pos = string_line.find_first_of(delimiter, start);
        // get substring until delimiter
        std::string element = string_line.substr(start, pos - start);
        // add element to end of vector
        temp_ticket.ticket_vals.push_back(stoi(element));
        // next position to start searching for delimiter
        start = pos + 1;
      } while (pos != std::string::npos);
      // Take over the ticket
      this->m_my_ticket = temp_ticket;
      this->m_my_ticket.ticket_valid = true;
    } break;

    case NEARBY_TICKET: {
      if (string_line == "nearby tickets:") {
        continue;
      }
      // extract nearby ticket to vector of ints
      // Split string_line and store in vector of strings
      do {
        // get pos from start to first delimiter
        pos = string_line.find_first_of(delimiter, start);
        // get substring until delimiter
        std::string element = string_line.substr(start, pos - start);
        // add element to end of vector
        temp_ticket.ticket_vals.push_back(stoi(element));
        // next position to start searching for delimiter
        start = pos + 1;
      } while (pos != std::string::npos);
      // Take over the ticket
      temp_ticket.ticket_valid = true;
      this->m_nearby_tickets.push_back(temp_ticket);
    } break;

    default:
      break;
    }
  }
}

/**
 * @brief Evaluate all values out of range and store in member
 *
 */
void day24::eval_values_out_of_range(void) {
  bool value_valid = false;
  for (auto &iter : this->m_nearby_tickets) {
    for (auto iter_tick : iter.ticket_vals) {
      if (!this->check_value_for_rules(iter_tick)) {
        this->m_values_out_of_range.push_back(iter_tick);
        iter.ticket_valid = false;
      }
    }
  }
}

/**
 * @brief Function checks the given value is within all rules
 *
 * @param val Value to check against all rules
 * @return true Value correct
 * @return false Value out of any rule
 */
bool day24::check_value_for_rules(int val) {
  bool correct = false;
  for (auto iter : this->m_rules) {
    for (auto iter_ranges : iter.ranges) {
      if (val >= iter_ranges.min_val && val <= iter_ranges.max_val) {
        correct = true;
        break; // inner for
      }
    }
    if (correct) {
      break; // outer for
    }
  }
  return (correct);
}

/**
 * @brief Calculate the sum of all values in vector for out of range
 *
 */
void day24::calc_sum_out_of_range(void) {
  int temp_sum = 0;
  for (auto iter : this->m_values_out_of_range) {
    temp_sum += iter;
  }
  this->m_sum_out_of_range = temp_sum;
}

/**
 * @brief Provide result
 *
 * @return int Sum of all out of range values
 */
int day24::get_sum_out_of_range(void) { return (this->m_sum_out_of_range); }
