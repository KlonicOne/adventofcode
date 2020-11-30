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

using namespace std;

/**
 * @brief main function calling process
 *
 * @return int
 */
int main(int, char **) {
  std::ifstream ifile_one("input1.txt");
  std::ifstream ifile_two("input2.txt");

  std::vector<std::string> inputTable;
  std::vector<int> inputVector;

  load_data Load_Data;

  inputTable = Load_Data.getInputTable(ifile_one);
  inputVector = Load_Data.getInputVector(ifile_two);

  return (0);
}
