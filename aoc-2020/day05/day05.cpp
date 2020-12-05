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
  // Eval values for each seat
  this->eval_seat_parameter();
  // Calc seat ID
  this->calc_seat_ids();
  // Check largest seat ID
  std::cout << "Max seat Id: " << this->max_seat_id() << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day05::solver_part2(void) {
  // Info out
  std::cout << "Policy check part 2" << std::endl;

  // Sort vector
  this->sort_seat_vector();

  // Check for diff 2 and get my seat
  std::cout << "My seat: " << this->get_my_seat() << std::endl;
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

/**
 * @brief Evaluate all seat parameter
 *
 */
void day05::eval_seat_parameter(void) {

  std::string B = "B", Br = "1";
  std::string F = "F", Fr = "0";
  std::string R = "R", Rr = "1";
  std::string L = "L", Lr = "0";
  size_t pos;

  for (seat_element_t &seatel : format_seat_list) {
    // prepare row
    while ((pos = seatel.row_string.find(B)) != std::string::npos) {
      seatel.row_string.replace(pos, 1, Br);
    }
    while ((pos = seatel.row_string.find(F)) != std::string::npos) {
      seatel.row_string.replace(pos, 1, Fr);
    }

    // prepare col
    while ((pos = seatel.col_string.find(L)) != std::string::npos) {
      seatel.col_string.replace(pos, 1, Lr);
    }
    while ((pos = seatel.col_string.find(R)) != std::string::npos) {
      seatel.col_string.replace(pos, 1, Rr);
    }

    // Now store value in row
    seatel.row = stoi(seatel.row_string, nullptr, 2);
    seatel.col = stoi(seatel.col_string, nullptr, 2);
    // debug out
    // std::cout << seatel.row_string << std::endl;
    // std::cout << seatel.row << std::endl;
    // std::cout << seatel.col_string << std::endl;
    // std::cout << seatel.col << std::endl;
  }
}

/**
 * @brief Calculate based on parameter the seat ids in own vector
 *
 */
void day05::calc_seat_ids(void) {
  for (seat_element_t &seatel : format_seat_list) {
    int seat_id = seatel.row * 8 + seatel.col;
    seat_ids.push_back(seat_id);
    // debug
    std::cout << seat_id << std::endl;
  }
}

/**
 * @brief Check for largest Id found in vector
 *
 * @return int Max id in vec
 */
int day05::max_seat_id(void) {
  int max_seat_id = 0;

  // Get maximum value in seat ids
  max_seat_id = *max_element(seat_ids.begin(), seat_ids.end());

  return (max_seat_id);
}

/**
 * @brief sort vector for part 2 to get positive diff
 * 
 */
void day05::sort_seat_vector(void) {
  std::sort(this->seat_ids.begin(), this->seat_ids.end());
}

/**
 * @brief Check for the difference and calc seat
 * 
 * @return int My seat :-)
 */
int day05::get_my_seat(void) {
  int found_seat = 0;
  // check for diff is 2, take last value and return it
  for (int i = 1; i < this->seat_ids.size(); i++) {
    int diff = this->seat_ids[i] - this->seat_ids[i - 1];
    if (diff == 2) {
      // seat found
      found_seat = this->seat_ids[i] - 1;
    }
  }
  return (found_seat);
}
