/**
 * @file day06.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day06.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief constructor
 *
 */
day06::day06(/* args */) {}

/**
 * @brief Destroy the day06::day06
 *
 */
day06::~day06() {}

/**
 * @brief Solve part 1
 *
 */
void day06::solver_part1(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;
  // Eval values for each group
  this->eval_groups();
  //this->print_group_results();
  // Calc sum of all yes questions
  answer = this->calc_sum_yes_questions();
  // Check largest seat ID
  std::cout << "Sum of all yes questions: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day06::solver_part2(void) {
  // Info out
  std::cout << "Part 2" << std::endl;
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day06::format_input(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  group_t current_group;   // New group
  person_t current_person; // New person

  std::string string_line = "";
  std::string element = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // variables to loop through string
    std::string::size_type start{0};
    std::string::size_type len{0};

    // Get single line as string_line
    string_line = (*i);

    // debug
    // std::cout << (*i) << std::endl;

    // If only newline in line, go over to next group in group
    if (string_line.length() == 0) {
      // push group to all groups
      this->all_groups.push_back(current_group);
      // Delete current groupt content
      current_group.pers_in_group.clear();
      // std::cout << "Next groups " << group_index << std::endl;
      continue; // This line is not to be considered, eval next line
    }

    // Split string_line and store in vector of strings
    start = 0; // start at pos 0
    len = 1;   // single character length
    do {
      element = string_line.substr(start, len);
      // add element to end of vector
      current_person.yes_questions.push_back(element);
      // Prepare next loop
      start++; // Next char in string
      // debug
      // std::cout << "Current char " << element << std::endl;
    } while (start != string_line.size());

    // Pushback result for current person in current group
    current_group.pers_in_group.push_back(current_person);
    // and delete content fo person for next person
    current_person.yes_questions.clear();
  }

  // debug
  std::cout << "Number of groups: " << this->all_groups.size() << std::endl;
}

/**
 * @brief evaluate all groups and person and store the yes questions each group
 *
 */
void day06::eval_groups(void) {
  // Loop through groups
  for (int i = 0; i < this->all_groups.size(); ++i) {
    // Loop through persons
    for (int j = 0; j < this->all_groups[i].pers_in_group.size(); ++j) {
      const int a_offset = 97;
      // Loop through person yes questions
      for (int k = 0;
           k < this->all_groups[i].pers_in_group[j].yes_questions.size(); ++k) {
        // Extract next question with yes
        std::string question =
            this->all_groups[i].pers_in_group[j].yes_questions[k];
        // calc index for vector
        int index = int(question[0]) - a_offset;
        // count hit character as index
        this->all_groups[i].vec_all_questions[index]++;

        // std::cout << "Group: " << i << ", Person: " << j
        //           << ", Char index: " << index << ", char: " << question[0]
        //           << std::endl;
      }
    }
  }
}

/**
 * @brief Print out all group resutls of yes questions
 *
 */
void day06::print_group_results(void) {
  // Loop through groups
  for (int i = 0; i < this->all_groups.size(); ++i) {
    // Print results of group each hit question
    std::cout << "Group: " << i + 1 << std::endl;
    for (int k = 0; k < 26; k++) {
      cout << this->all_groups[i].vec_all_questions[k] << ", ";
    }
    std::cout << std::endl;
  }
}

int day06::calc_sum_yes_questions(void) {
  int result_sum = 0;
  // Loop through groups
  for (int i = 0; i < this->all_groups.size(); ++i) {
    int group_sum = 0;
    // Print results of group each hit question
    for (int k = 0; k < 26; k++) {
      int current_pos = this->all_groups[i].vec_all_questions[k];
      if (current_pos > 0) { // each question not zero
        group_sum++;
      }
    }
    result_sum += group_sum;
  }
  return (result_sum);
}
