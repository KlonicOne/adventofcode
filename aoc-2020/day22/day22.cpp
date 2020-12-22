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
#include <iostream>
#include <istream>
#include <iterator>
#include <string>
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
  int answer = 0;

  // Play until we have winner
  this->play_game();

  // Get winner score
  answer = this->calc_score();

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
  std::vector<int> temp_deck;

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
        this->m_decks.push_back(temp_deck);
        temp_deck.clear();
      }
      // New player found
      card_num = 0;
      continue;
    }

    // We are in deck numbers, add to the current temp map and at the end add to
    // the member map
    temp_deck.push_back(stoi(string_line));
    card_num++;
  }

  // Now add last player, found in last for iteration
  if (temp_deck.size() != 0) {
    // Add previous to the member maps
    this->m_decks.push_back(temp_deck);
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
    for (auto iter_deck : this->m_decks) {
      std::cout << "Player: " << out_player << std::endl;
      // Check if cards are existing
      if (iter_deck.size() != 0) {
        for (auto iter_card : iter_deck) {
          std::cout << iter_card << ", ";
        }
        std::cout << std::endl;
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

/**
 * @brief Play the game round by round and stop only when game finished
 *
 */
void day22::play_game(void) {
  bool play_game = true;
  int winner_in_round = 0;
  int round_played = 0;
  std::vector<int> current_cards;

  while (play_game) {
    // Get cards and delete cards
    for (auto &iter_player : this->m_decks) {
      current_cards.push_back(iter_player.at(0));
      iter_player.erase(iter_player.begin());
    }

    // Check for higher
    if (current_cards.at(0) > current_cards.at(1)) {
      // Player 1 has higher
      winner_in_round = 0;
    } else {
      // Here player 2 wins
      winner_in_round = 1;
    }

    // Own card must be added first, it was winner card, so higher
    // First sort current cards descending, then add to deck of winner
    sort(current_cards.begin(), current_cards.end(), greater<>());
    // Add to deck
    for (auto iter_cards : current_cards) {
      this->m_decks[winner_in_round].push_back(iter_cards);
    }

    if (DEBUG_OUT) {
      std::cout << "Winner: " << winner_in_round << ", Cards: ";
      for (auto ca_it : current_cards) {
        std::cout << ca_it << ", ";
      }
      std::cout << std::endl;
    }

    // Prep current cards next round
    current_cards.clear();
    round_played++;

    // Check stop condition, if any has not cards stop here
    for (auto &iter_player : this->m_decks) {
      if (iter_player.size() == 0) {
        play_game = false;
      }
    }

    if (DEBUG_OUT) {
      std::cout << "Played round: " << round_played << std::endl;
      this->print_out_player();
    }
  }
}

/**
 * @brief Calculate the result of score for winner
 *
 * @return int Score of winner
 */
int day22::calc_score(void) {
  int temp_res = 0;
  int fac = 0;

  for (auto iter_deck : this->m_decks) {
    // Check if cards are existing
    fac = iter_deck.size();
    if (fac != 0) {
      for (auto iter_card : iter_deck) {
        temp_res += iter_card * fac;
        fac--;
      }
    }
  }
  return (temp_res);
}
