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
#include "day12.h"

using namespace std;

/**
 * @brief main function calling process
 * 
 * @return int alway 0
 */
int main(int, char **) {
  // !!! my input need 2 newline on end of file for correct group detection
  std::ifstream ifile_one("input_test.txt");
  std::vector<std::string> inputTable;

  // Class to prepare the data
  load_data Load_Data;
  // Class to solve day problem
  day12 Day;

  // get data
  inputTable = Load_Data.getInputVectorString(ifile_one);

  // Go processing
  std::cout << "Start solving day12" << std::endl;

  // Solve problems
  Day.solver_part1();
  Day.solver_part2();

  return (0);
}
