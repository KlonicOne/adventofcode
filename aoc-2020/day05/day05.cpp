/**
 * @file day05.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day05.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief constructor
 *
 */
day05::day05(/* args */) { this->used_seats_in_format_list = 0; }

/**
 * @brief Destroy the day05::day05
 *
 */
day05::~day05() {}

/**
 * @brief Solve part 1
 *
 */
void day05::solver_part1(void) {
  // Info out
  std::cout << "Policy check part 1" << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day05::solver_part2(void) {
  // Info out
  std::cout << "Policy check part 2" << std::endl;
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day05::format_input(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  int current_pp_index = 0;
  std::string string_line = "";
  std::string element = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // variables to loop through string
    std::vector<std::string> string_vec_element;
    std::string::size_type start{0};
    std::string::size_type pos;
    std::string delimiter = ""; // No splitting this time
    seat_element_t current_seat_element;

    // Get single line as string_line
    string_line = (*i);

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // add element to end of vector
      string_vec_element.push_back(element);
      // next position to start searching for delimiter
      start = pos + 1;
    } while (pos != std::string::npos);

    // debug out
    std::cout << string_vec_element[0] << std::endl;

    // Get last three character for column 0 1 2 3 4 5 6 7 8 9
    // Get first seven for row
    // Convert into seat number and  store all values
    current_seat_element.col_string = string_vec_element[0].substr(
        (string_vec_element[0].size() - 3), (string_vec_element[0].size() - 1));
    current_seat_element.row_string =
        string_vec_element[0].substr(0, (string_vec_element[0].size() - 3));
    format_seat_list.push_back(current_seat_element);
    // debug out
    std::cout << "col: " << current_seat_element.col_string << std::endl;
    std::cout << "rol: " << current_seat_element.row_string << std::endl;
  }
  this->used_seats_in_format_list = format_seat_list.size();
  // deboug out
  std::cout << "Seats: " << this->used_seats_in_format_list << std::endl;
}
