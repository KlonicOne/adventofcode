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

#define LIMIT_YEAR (2020)

/**
 * @brief main function calling process
 *
 * @return int
 */
int main(int, char **) {
  std::ifstream ifile_one("input1.txt");
  std::vector<std::string> inputTable;
  int result;
  int sum;

  load_data Load_Data;

  // get data
  inputTable = Load_Data.getInputTable(ifile_one);

  for (std::vector<std::string>::const_iterator i = inputTable.begin();
       i != inputTable.end(); ++i) {
    for (std::vector<std::string>::const_iterator j = inputTable.begin();
         j != inputTable.end(); ++j) {
      for (std::vector<std::string>::const_iterator k = inputTable.begin();
           k != inputTable.end(); ++k) {
        sum = stoi(*i) + stoi(*j) + stoi(*k);
        // check if sum is 2020
        if (sum == LIMIT_YEAR) {
          std::cout << "Summanden: " << stoi(*i) << " + " << stoi(*j) << " + " << stoi(*k) << std::endl;
          std::cout << "Sum: " << sum << std::endl;
          result = stoi(*i) * stoi(*j) * stoi(*k);
          std::cout << "Result: " << result << std::endl;
        }
      }
    }
  }

  return (0);
}
