/**
 * @file day23.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day23.h"
#include "show_container.h"

#include <algorithm>
#include <iostream>
#include <istream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

#define DEBUG_OUT true

/**
 * @brief constructor
 *
 */
day23::day23(/* args */) {}

/**
 * @brief Destroy the day23::day23
 *
 */
day23::~day23() {}

/**
 * @brief Solve part 1
 *
 */
void day23::solver_part1(void) {
  int answer = 0;

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day23::solver_part2(void) {
  int answer = 0;

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
void day23::format_input(std::vector<std::string> inTable) {
  std::vector<int> temp_buffer;

  // Loop through lines of file in input
  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // used temp to store line and each element
    std::string string_line = "";

    // Get single line as string_line
    string_line = (*i);

    for (const char c : string_line) {
      this->m_start_buffer.push_back(atoi((const char*) &c));
    }
  }

  if (DEBUG_OUT) {
    show_container(this->m_start_buffer);
  }
}

/**
 * @brief Plot player when debug on
 *
 */
void day23::print_out_ringbuffer(void) {}

/**
 * @brief Remove all spaces in string
 *
 * @param s string reference
 * @return std::string new string without spaces
 */
std::string day23::remove_spaces(const std::string s) {
  std::string ret_s = s;
  std::string::size_type pos = ret_s.find(' ');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find(' ');
  }
  return (ret_s);
}

/**
 * @brief Remove open or close brackets from the sring
 *
 * @param s String in which the backets are searched
 * @return std::string Removed brackets
 */
std::string day23::remove_brackets(const std::string s) {
  std::string ret_s = s;
  std::string::size_type pos = ret_s.find('(');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find('(');
  }
  pos = ret_s.find(')');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find(')');
  }
  return (ret_s);
}
