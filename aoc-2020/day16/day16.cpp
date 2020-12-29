/**
 * @file day16.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day16.h"
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
day16::day16(/* args */) {}

/**
 * @brief Destroy the day16::day16
 *
 */
day16::~day16() {}

/**
 * @brief Solve part 1
 *
 */
void day16::solver_part1(void) {
  unsigned long long answer = 0;

  // Out result
  std::cout << "Result Part1: " << std::dec << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day16::solver_part2(void) {
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
void day16::format_input(std::vector<std::string> inTable) {
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
      found_enclosing = string_line.find("or");
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
      this->m_nearby_tickets.push_back(temp_ticket);
    } break;

    default:
      break;
    }
  }

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
      for (auto iter_tick : iter.ticket_vals) {
        std::cout << iter_tick << ", ";
      }
      std::cout << std::endl;
    }
  }
}
