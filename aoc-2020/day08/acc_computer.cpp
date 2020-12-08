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
  this->last_pos_replaced = 0;
  this->exit_code = 0;
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
bool acc_computer::execute_acc_comp_p1(void) {
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

  // Check for end condition
  continue_program = eval_stop_condition();

  return (continue_program);
}

/**
 * @brief Cyclic exection
 *
 * @return true continue
 * @return false stop execution
 */
bool acc_computer::execute_acc_comp_p2(void) {
  bool continue_program = true;
  int current_isr = this->program_code.at(this->pc).instruction;
  std::vector<int> current_args = this->program_code.at(this->pc).arguments;

  // List of all hit adresses
  this->hit_instructions.push_back(this->pc);

  // Replace next jump nop
  current_isr = this->replace_next_nopjump(this->pc, current_isr);

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

  // Check for end condition
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
    this->exit_code = 1;       // exit with endless loop
    this->last_pos_replaced++; // Replace on ext pos the isr
  } else if (this->pc >= this->program_code.size()) {
    condition = false;
    this->exit_code = 2;       // exit with last command in program
    this->last_pos_replaced++; // Replace on ext pos the isr
  }
  return (condition);
}

/**
 * @brief Reset running retgister for exection
 *
 */
void acc_computer::reset_program_exec(void) {
  // Reset all relevant register
  this->pc = 0;
  this->acc = 0;
  this->exit_code = 0;
  this->hit_instructions.clear();
}

/**
 * @brief Reset all register and internal data except program
 *
 */
void acc_computer::reset_computer(void) {
  // Reset all relevant register
  this->reset_program_exec();
  this->last_pos_replaced = 0;
}

/**
 * @brief Return exit reason
 *
 * @return int
 */
int acc_computer::get_exit_code(void) { return (this->exit_code); }

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
 * @brief Replace next occurence of jump or nop
 *
 * @param current_pc
 */
int acc_computer::replace_next_nopjump(int current_pc, int current_isr) {
  int replaced_isr = current_isr;
  // Check if current isr to be replaced
  if (current_pc == this->last_pos_replaced) {
    switch (current_isr) {
    case jmp_cmd: {
      replaced_isr = nop_cmd;
    } break;
    case nop_cmd: {
      replaced_isr = jmp_cmd;
    }
    default:
      break;
    }
  }
  return (replaced_isr);
}

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
