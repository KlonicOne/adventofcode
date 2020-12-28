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
day23::day23(/* args */) {
  this->m_current_pos = 0;
  this->m_dest_pos = 0;
  this->m_tail = 0;
  this->m_initial_buffer_size = 0;
  this->m_max_cup_value = 0;
  this->m_dest_val = 0;
}

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

  this->init_cup_buffer();

  // Play game
  for (int i = 0; i < 10; ++i) {
    std::cout << "Round: " << i << std::endl;

    if (DEBUG_OUT) {
      std::cout << "Current: " << this->m_current_pos << std::endl;
      std::cout << "Ring buffer: ";
      show_container(this->m_cup_buffer);
    }

    this->pick_three_cups();
    this->eval_destination_cup();
    this->place_cups_after_dest();
    this->eval_new_current();

    if (DEBUG_OUT) {
      std::cout << "Pick up: ";
      show_container(this->m_temp_cup_buffer);
      std::cout << "Destination: " << this->m_dest_val << std::endl;
      std::cout << endl;
    }
  }

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
      this->m_start_buffer.push_back(atoi((const char *)&c));
    }
  }

  if (DEBUG_OUT) {
    show_container(this->m_start_buffer);
  }
}

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

/**
 * @brief The crab picks up the three cups that are immediately clockwise of the
 * current cup. They are removed from the circle; cup spacing is adjusted as
 * necessary to maintain the circle.
 *
 */
void day23::init_cup_buffer(void) {
  this->m_cup_buffer = this->m_start_buffer;
  this->m_current_pos = 0;
  this->m_tail = this->m_cup_buffer.size() - 1;
  this->m_initial_buffer_size = this->m_cup_buffer.size();
  // Get max value in list for underflow destination value calc
  auto it = max_element(this->m_cup_buffer.begin(), this->m_cup_buffer.end());
  this->m_max_cup_value = *it;

  // if (DEBUG_OUT) {
  //   std::cout << "Ring buffer: ";
  //   show_container(this->m_cup_buffer);
  //   std::cout << "Current: " << this->m_current_pos << ", Tail: " <<
  //   this->m_tail
  //             << ", Size: " << this->m_initial_buffer_size
  //             << ", Max val: " << this->m_max_cup_value << std::endl;
  // }
}

/**
 * @brief The crab picks up the three cups that are immediately clockwise of the
 * current cup. They are removed from the circle; cup spacing is adjusted as
 * necessary to maintain the circle.
 *
 */
void day23::pick_three_cups(void) {
  // Clear what was in temp cup buffer
  this->m_temp_cup_buffer.clear();
  // Copy elements and remove from cup buffer
  for (int i = 0; i < this->m_temp_buffer_size; ++i) {
    // pos to copy and remove considering modulo as it is ring buffer
    int pos = (this->m_current_pos + 1) % this->m_initial_buffer_size;
    // copy to temp
    this->m_temp_cup_buffer.push_back(this->m_cup_buffer.at(pos));
    // delete element from cup buffer
    this->m_cup_buffer.erase(this->m_cup_buffer.begin() + pos);
  }
}

/**
 * @brief The crab selects a destination cup: the cup with a label equal to the
 * current cup's label minus one. If this would select one of the cups that was
 * just picked up, the crab will keep subtracting one until it finds a cup that
 * wasn't just picked up. If at any point in this process the value goes below
 * the lowest value on any cup's label, it wraps around to the highest value on
 * any cup's label instead.
 *
 */
void day23::eval_destination_cup(void) {
  bool value_in_temp_buffer = true;
  // Calc destination until found in cup buffer
  int dest_value = this->m_cup_buffer.at(this->m_current_pos);
  // Check if value is in the temp buffer, then continue to subtract
  while (value_in_temp_buffer) {
    dest_value--;
    // Check underflow
    if (dest_value == 0) {
      dest_value = this->m_max_cup_value;
    }
    value_in_temp_buffer = this->is_value_in_temp_buffer(dest_value);
  }
  // Here we know the destination value not in temp buffer so get position of it
  // in vector
  this->m_dest_val = dest_value;
  this->m_dest_pos = this->get_pos_of_value_cup_buffer(dest_value);
}

/**
 * @brief The crab places the cups it just picked up so that they are
 * immediately clockwise of the destination cup. They keep the same order as
 * when they were picked up.
 *
 */
void day23::place_cups_after_dest(void) {
  int pos_to_move;
  // First add three elements at end of cup buffer
  for (int i = 0; i < this->m_temp_buffer_size; ++i) {
    this->m_cup_buffer.push_back(0);
  }

  show_container(this->m_cup_buffer);

  // Then move the elements after the dest one pos
  for (int i = this->m_initial_buffer_size - 1;
       i > this->m_dest_pos + this->m_temp_buffer_size; --i) {
    this->m_cup_buffer.at(i) =
        this->m_cup_buffer.at(i - this->m_temp_buffer_size);
  }
  show_container(this->m_cup_buffer);

  // Write the temp cup buffer right after destination
  for (int i = 0; i < this->m_temp_buffer_size; ++i) {
    this->m_cup_buffer.at(this->m_dest_pos + i + 1) =
        this->m_temp_cup_buffer.at(i);
  }
  show_container(this->m_cup_buffer);
}

/**
 * @brief The crab selects a new current cup: the cup which is immediately
 * clockwise of the current cup.
 *
 */
void day23::eval_new_current(void) {
  this->m_current_pos++;
  this->m_current_pos = this->m_current_pos % this->m_initial_buffer_size;
  this->m_tail++;
  this->m_tail = this->m_tail % this->m_initial_buffer_size;
}

/**
 * @brief Check if given value is in buffer of the three cups take out of the
 * ring cup buffer
 *
 * @param value Value to check for
 * @return true Value is in temp buffer
 * @return false Not in temp buffer
 */
bool day23::is_value_in_temp_buffer(int value) {
  bool is_in = false;

  // Check if in buffer
  for (auto iter : this->m_temp_cup_buffer) {
    if (iter == value) {
      is_in = true;
      break;
    }
  }
  return (is_in);
}

/**
 * @brief Get the position in the vector for the value in arg
 *
 * @param value Value to check position for in cup buffer
 * @return int Position n cup buffer
 */
int day23::get_pos_of_value_cup_buffer(int value) {
  int index_value = 0;
  for (int i = 0; i < this->m_cup_buffer.size(); ++i) {
    if (this->m_cup_buffer.at(i) == value) {
      index_value = i;
      break;
    }
  }
  return (index_value);
}
