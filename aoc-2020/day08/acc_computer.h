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
  bool execute_acc_comp_p1(void); // Cyclic operation function
  bool execute_acc_comp_p2(void); // Same for part 2
  int get_int_code(std::string s_code);
  bool eval_stop_condition(void);
  int get_acc_value(void);
  int get_exit_code(void);
  int replace_next_nopjump(int current_pc, int current_isr);
  void reset_program_exec(void);
  void reset_computer(void);

  // Helper
  std::string trim_lead_whspace(const std::string &s);

private:
  // Registers for computer
  int acc; // contains accumulator
  int pc;  // contains instruction pointer
  int exit_code; // Why stopped execution

  // Part 2 anchors
  int last_pos_replaced;

  std::vector<instruction_t> program_code; // Code of the current program
  std::vector<int> hit_instructions;

  int acc_op(int pc, int value);
  int jmp_op(int pc, int value);
  int nop_op(int pc);
};

#endif
