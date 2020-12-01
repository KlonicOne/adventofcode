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
 * @return int alway 0
 */
int main(int, char **) {
  std::ifstream ifile_one("input1.txt");
  std::vector<std::string> inputTable;
  std::vector<int> inputVectorInt;
  bool result_found = false;
  int result = 0;
  int sum = 0;

  // Class to prepare the data
  load_data Load_Data;

  // get data
  inputTable = Load_Data.getInputVectorString(ifile_one);
  inputVectorInt = Load_Data.getInputVectorInt(inputTable);

  // Go processing
  std::cout << "Start caclulation" << std::endl;

  for (std::vector<int>::const_iterator i = inputVectorInt.begin();
       i != inputVectorInt.end(); ++i) {
    for (std::vector<int>::const_iterator j = inputVectorInt.begin();
         j != inputVectorInt.end(); ++j) {
      for (std::vector<int>::const_iterator k = inputVectorInt.begin();
           k != inputVectorInt.end(); ++k) {
        sum = (*i) + (*j) + (*k);
        // check if sum is 2020
        if (sum == LIMIT_YEAR) {
          std::cout << "Summanden: " << (*i) << " + " << (*j) << " + " << (*k)
                    << std::endl;
          std::cout << "Sum: " << sum << std::endl;
          result = (*i) * (*j) * (*k);
          std::cout << "Result: " << result << std::endl;
          result_found = true;
        }
        if (result_found) {
          break;
        }
      }
      if (result_found) {
        break;
      }
    }
    if (result_found) {
      break;
    }
  }

  return (0);
}
