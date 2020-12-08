/**
 * @file acc_computer.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-12-08
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef _ACC_COMPUTER_H_
#define _ACC_COMPUTER_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

using namespace std;

enum isr_list {
  acc_cmd,
  jmp_cmd,
  nop_cmd,
};

typedef struct instruction_t {
  int instruction;
  std::vector<int> arguments;
} instruction_t;

class acc_computer {
public:
  acc_computer();
  virtual ~acc_computer();

  void generate_program(std::vector<std::string> inTable);
  bool execute_acc_comp(void); // Cyclic operation function
  int get_int_code(std::string s_code);
  bool eval_stop_condition(void);
  int get_acc_value(void);

  // Helper
  std::string trim_lead_whspace(const std::string &s);

private:
  // Registers for computer
  int acc; // contains accumulator
  int pc; // contains instruction pointer

  std::vector<instruction_t> program_code; // Code of the current program
  std::vector<int> hit_instructions;

  int acc_op(int pc, int value);
  int jmp_op(int pc, int value);
  int nop_op(int pc);
};

#endif
