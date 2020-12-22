/**
 * @file day22.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day22.h"
#include "show_container.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define DEBUG_OUT true

/**
 * @brief constructor
 *
 */
day22::day22(/* args */) {}

/**
 * @brief Destroy the day22::day22
 *
 */
day22::~day22() {}

/**
 * @brief Solve part 1
 *
 */
void day22::solver_part1(void) {
  long long answer = 0;

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day22::solver_part2(void) {
  int answer = 0;

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
void day22::format_input(std::vector<std::string> inTable) {
  int card_num = 0;
  map<int, int> temp_deck;

  // Loop through lines of file in input
  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // used temp to store line and each element
    std::string string_line = "";

    // Get single line as string_line
    string_line = (*i);

    // Check for newline, could be used to inc player
    if (string_line == "") {
      continue;
    }

    // Check if a player is found
    std::size_t found = string_line.find("Player");
    if (found != std::string::npos) {
      if (temp_deck.size() != 0) {
        // Add previous to the member maps
        this->m_deck.push_back(temp_deck);
        temp_deck.clear();
      }
      // New player found
      card_num = 0;
      continue;
    }

    // We are in deck numbers, add to the current temp map and at the end add to
    // the member map
    temp_deck.insert({card_num, stoi(string_line)});
    card_num++;
  }

  // Now add last player, found in last for iteration
  if (temp_deck.size() != 0) {
    // Add previous to the member maps
    this->m_deck.push_back(temp_deck);
    temp_deck.clear();
  }
  this->print_out_player();
}

/**
 * @brief Plot player when debug on
 * 
 */
void day22::print_out_player(void) {
  if (DEBUG_OUT) {
    // show read data
    int out_player = 1;
    for (auto iter_deck : this->m_deck) {
      std::cout << "Player: " << out_player << std::endl;
      for (auto iter_card : iter_deck) {
        std::cout << iter_card.first << ": " << iter_card.second << std::endl;
      }
      out_player++;
    }
  }
}

/**
 * @brief Remove all spaces in string
 *
 * @param s string reference
 * @return std::string new string without spaces
 */
std::string day22::remove_spaces(const std::string s) {
  std::string ret_s = s;
  std::string::size_type pos = ret_s.find(' ');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find(' ');
  }
  return (ret_s);
}

/**
 * @brief Remove open or close brackets from the sring
 *
 * @param s String in which the backets are searched
 * @return std::string Removed brackets
 */
std::string day22::remove_brackets(const std::string s) {
  std::string ret_s = s;
  std::string::size_type pos = ret_s.find('(');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find('(');
  }
  pos = ret_s.find(')');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find(')');
  }
  return (ret_s);
}
