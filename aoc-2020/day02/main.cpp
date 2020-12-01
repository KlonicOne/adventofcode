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
#include "day02.h"

using namespace std;

/**
 * @brief main function calling process
 * 
 * @return int alway 0
 */
int main(int, char **) {
  std::ifstream ifile_one("input.txt");
  std::vector<std::string> inputTable;
  std::vector<int> inputVectorInt;

  // Class to prepare the data
  load_data Load_Data;
  // Class to solve day problem
  day02 Day02;

  // get data
  inputTable = Load_Data.getInputVectorString(ifile_one);
  inputVectorInt = Load_Data.getInputVectorInt(inputTable);

  // Go processing
  std::cout << "Start caclulation" << std::endl;

  // Solve problems
  Day02.solver_part1(inputVectorInt);
  Day02.solver_part2(inputVectorInt);

  return (0);
}
