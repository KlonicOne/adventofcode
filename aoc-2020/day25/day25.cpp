/**
 * @file day25.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day25.h"
#include "show_container.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <time.h>
#include <vector>

using namespace std;

#define DEBUG_OUT true

/**
 * @brief constructor
 *
 */
day25::day25(/* args */) {}

/**
 * @brief Destroy the day25::day25
 *
 */
day25::~day25() {}

/**
 * @brief Solve part 1
 *
 */
void day25::solver_part1(void) {
  long long answer = 0;

  // Calc loop numbers
  for (auto iter : this->m_keys) {
    this->m_loop_nums.push_back(this->calc_loop_number(iter));
  }
  // The secret key you can use either device's loop size with the other
  // device's public key to calculate the encryption key
  answer = this->calc_sec_key(this->m_keys.at(0), this->m_loop_nums.at(1));

  if (DEBUG_OUT) {
    show_container(this->m_keys);
    show_container(this->m_loop_nums);
  }

  // Out result
  std::cout << "Result Part1: " << std::dec << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day25::solver_part2(void) {
  long answer = 0;

  // Out result
  std::cout << "Result Part2: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day25::format_input(std::vector<std::string> inTable) {
  std::string string_line = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {

    // Get single line as string_line
    string_line = (*i);

    // Read keys
    this->m_keys.push_back(stoi(string_line));
  }
}

/**
 * @brief Calculate the number of loops required with rule and key
 *
 * @param key key to check loop num
 * @param seed subject number
 * @return int Loop number
 */
int day25::calc_loop_number(int key) {
  int loop_num = 0;
  long long value = this->m_start_val; // start with the value 1

  while (value != key) {
    // Set the value to itself multiplied by the subject number
    value = value * this->m_seed_val;
    // Set the value to the remainder after dividing the value by 20201227
    value = value % this->m_divisor;
    // next loop
    loop_num++;
  }

  return (loop_num);
}

/**
 * @brief Calculate the secret encryption key with key and loop num
 *
 * @param key key from input
 * @param loop loop number calculated
 * @return int secret encryption key
 */
long long day25::calc_sec_key(int key, int loop) {
  long long sec_key = this->m_start_val;
  // Calculate the secret key
  for (int i = 0; i < loop; ++i) {
    sec_key = sec_key * key;
    sec_key = sec_key % this->m_divisor;
  }

  return (sec_key);
}
