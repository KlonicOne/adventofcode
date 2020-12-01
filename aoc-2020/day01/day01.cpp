/**
 * @file day01.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <cstring>
#include <iostream>
#include <vector>

#include "day01.h"

using namespace std;

#define LIMIT_YEAR (2020)

day01::day01(/* args */) {}

day01::~day01() {}

void day01::solver_part1(std::vector<int> inputVectorInt) {
  bool result_found = false;
  int result = 0;
  int sum = 0;

  for (std::vector<int>::const_iterator i = inputVectorInt.begin();
       i != inputVectorInt.end(); ++i) {
    for (std::vector<int>::const_iterator j = inputVectorInt.begin();
         j != inputVectorInt.end(); ++j) {
      sum = (*i) + (*j);
      // check if sum is 2020
      if (sum == LIMIT_YEAR) {
        std::cout << "Summanden: " << (*i) << " + " << (*j) << std::endl;
        std::cout << "Sum: " << sum << std::endl;
        result = (*i) * (*j);
        std::cout << "Result Part 1: " << result << std::endl;
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
}

void day01::solver_part2(std::vector<int> inputVectorInt) {
  bool result_found = false;
  int result = 0;
  int sum = 0;

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
          std::cout << "Result Part 2: " << result << std::endl;
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
}
