/**
 * @file main.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-11-30
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

#include "load_data.h"
#include "day09.h"

using namespace std;

/**
 * @brief main function calling process
 * 
 * @return int alway 0
 */
int main(int, char **) {
  // !!! my input need 2 newline on end of file for correct group detection
  std::ifstream ifile_one("input.txt");
  std::vector<std::string> inputTable;

  // Class to prepare the data
  load_data Load_Data;
  // Class to solve day problem
  day09 Day07;

  // get data
  inputTable = Load_Data.getInputVectorString(ifile_one);

  // Go processing
  std::cout << "Start solving day09" << std::endl;

  // Fill formatted code
  Day07.format_input(inputTable);

  // Solve problems
  Day07.solver_part1();
  Day07.solver_part2();

  return (0);
}
