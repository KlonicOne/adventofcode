/**
 * @file acc_computer.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-12-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

#include "acc_computer.h"

using namespace std;

/**
 * @brief Construct a new acc computer::acc computer object
 * 
 */
acc_computer::acc_computer() {
  this->acc = 0;
  this->pc = 0;
}

/**
 * @brief Destroy the acc computer::acc computer object
 * 
 */
acc_computer::~acc_computer() {}

/**
 * @brief Create program code
 * 
 * @param inTable 
 */
void acc_computer::generate_program(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  std::string string_line = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    std::vector<std::string> string_vec_element;
    std::string element = "";
    std::string::size_type start{0};
    std::string::size_type len{0};
    std::string::size_type pos;
    std::string delimiter = " "; // No splitting this time
    instruction_t temp_instruction;

    // Get single line as string_line
    string_line = (*i);

    // debug
    // std::cout << string_line << std::endl;

    // Should not get non string in lines
    if (string_line.length() == 0) {
      std::cout << "Empty line found in intput!!!" << std::endl;
    }

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // Delete leading space
      element = trim_lead_whspace(element);
      // add element to end of vector
      string_vec_element.push_back(element);
      // next position to start searching for delimiter
      start = pos + 1;

      // debug out
      //   std::cout << "Element: " << element << std::endl;
    } while (pos != std::string::npos);

    // Now program
    temp_instruction.instruction =
        this->get_int_code(string_vec_element[0]); // ISR on front

    // Split arguments, only integers
    for (int j = 1; j < string_vec_element.size(); ++j) {
      temp_instruction.arguments.push_back(stoi(string_vec_element[j]));
    }

    // Push back program line in program
    this->program_code.push_back(temp_instruction);
  }
}

/**
 * @brief Translate to own id for instruction
 *
 * @param s_code
 * @return int
 */
int acc_computer::get_int_code(std::string s_code) {
  int int_code;
  if (!s_code.compare("acc")) {
    int_code = acc_cmd;
  } else if (!s_code.compare("jmp")) {
    int_code = jmp_cmd;
  } else if (!s_code.compare("nop")) {
    int_code = nop_cmd;
  }
  return (int_code);
}

/**
 * @brief Cyclic exection
 * 
 * @return true continue
 * @return false stop execution
 */
bool acc_computer::execute_acc_comp(void) {
  bool continue_program = true;
  int current_isr = this->program_code.at(this->pc).instruction;
  std::vector<int> current_args = this->program_code.at(this->pc).arguments;

  // List of all hit adresses
  this->hit_instructions.push_back(this->pc);

  switch (current_isr) {
  case acc_cmd: {
    // Call func and set next pc
    this->pc = this->acc_op(this->pc, current_args.at(0));
  } break;

  case jmp_cmd: {
    // Call func and set next pc
    this->pc = this->jmp_op(this->pc, current_args.at(0));
  } break;

  case nop_cmd: {
    // Call func and set next pc
    this->pc = this->nop_op(this->pc);
  } break;

  default: {
    std::cout << "Illegal operation!!!" << std::endl;
  }
  }

  continue_program = eval_stop_condition();

  return (continue_program);
}

/**
 * @brief Check if condition to contiue is met
 * 
 * @return true 
 * @return false 
 */
bool acc_computer::eval_stop_condition(void) {
  bool condition = true;
  // Check if current pc already met
  std::vector<int>::iterator it = std::find(
      this->hit_instructions.begin(), this->hit_instructions.end(), this->pc);
  // Check if element hit
  if (it != this->hit_instructions.end()) {
    condition = false;
  }
  return (condition);
}

/**
 * @brief Acc operation
 * 
 * @return int 
 */
int acc_computer::get_acc_value(void) { return (this->acc); }

int acc_computer::acc_op(int pc, int value) {
  this->acc += value;
  return (pc + 1);
}

/**
 * @brief jump operation
 * 
 * @param pc 
 * @param value 
 * @return int 
 */
int acc_computer::jmp_op(int pc, int value) { return (pc + value); }

/**
 * @brief nop operation
 * 
 * @param pc 
 * @return int 
 */
int acc_computer::nop_op(int pc) { return (pc + 1); }

/**
 * @brief Trim sapces on start of string
 *
 * @param s
 * @return std::string
 */
std::string acc_computer::trim_lead_whspace(const std::string &s) {
  std::string::size_type start = s.find_first_not_of(" ");
  return (start == std::string::npos) ? "" : s.substr(start);
}
