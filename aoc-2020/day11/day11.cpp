/**
 * @file day11.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day11.h"
#include "show_container.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

#define DEBUG_OUT true

#define FLOOR "."
#define OCCU "#"
#define FREE "L"

/**
 * @brief constructor
 *
 */
day11::day11(/* args */) {}

/**
 * @brief Destroy the day11::day11
 *
 */
day11::~day11() {}

/**
 * @brief Solve part 1
 *
 */
void day11::solver_part1(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;

  if (DEBUG_OUT) {
    this->plot_seat_map(this->m_seat_map);
  }

  answer = 0;

  // My bag in list so result - 1 should be good
  std::cout << "Result: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day11::solver_part2(void) {
  long long answer = 0;
  // Info out
  std::cout << "Part 2" << std::endl;

  answer = 0;

  // Result fits already
  std::cout << "Result: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Create map on input table
 *
 * @param input_table
 */
void day11::create_seat_map(std::vector<std::string> input_table) {
  std::string string_line = "";
  std::vector<char> temp_map_line;

  for (std::vector<std::string>::const_iterator i = input_table.begin();
       i != input_table.end(); ++i) {

    string_line = (*i);

    for (char &asteroidElement : string_line) {
      temp_map_line.push_back(asteroidElement);
    }

    // Add created line to the asteroid map
    this->m_seat_map.push_back(temp_map_line);
    temp_map_line.clear(); // clear content for new line
  }
}

/**
 * @brief Check if the given position can be occupied
 *
 * If a seat is empty (L) and there are no occupied seats adjacent to it, the
 * seat becomes occupied
 *
 * @param x pos
 * @param y pos
 * @return true Rule fulfilled to occupy pos
 * @return false Rule failed
 */
bool day11::check_to_occupy(int in_x, int in_y) {
  bool to_occupy = false;
  int sum_occ_seats = 0;
  std::vector<std::vector<char>> loc_map = this->get_seats_around(in_x, in_y);

  // Check rule for all except given seat
  for (unsigned y = 0; y < loc_map.size(); y++) {
    for (unsigned x = 0; x < loc_map.at(0).size(); x++) {
      // exclude center, own seat
      if (1 != x || 1 != y) {
        if (loc_map[y].at(x) == '#') {
          sum_occ_seats++;
          to_occupy = false;
        }
      }
    }
  }

  return (to_occupy);
}

/**
 * @brief Check if the seat has to be freed
 *
 * If a seat is occupied (#) and four or more seats adjacent to it are also
 * occupied, the seat becomes empty.
 *
 * @param x pos
 * @param y pos
 * @return true Seat will bee free
 * @return false No need to free
 */
bool day11::check_to_free(int in_x, int in_y) {
  bool to_free = false;
  int sum_occ_seats = 0;
  std::vector<std::vector<char>> loc_map = this->get_seats_around(in_x, in_y);

  // Check rule for all except given seat
  for (unsigned y = 0; y < loc_map.size(); y++) {
    for (unsigned x = 0; x < loc_map.at(0).size(); x++) {
      // exclude center, own seat
      if (1 != x || 1 != y) {
        if (loc_map[y].at(x) == '#') {
          sum_occ_seats++;
        }
      }
    }
  }

  // Check if more than four then empty
  if (sum_occ_seats >= 4) {
    to_free = true;
  }

  return (to_free);
}

/**
 * @brief Function returns all seats as small 3x3 map around given pos
 *
 * When boarder of map is reached the seats outside are set to floor
 *
 * @param x pos
 * @param y pos
 * @return std::vector<std::string> small 3x3 map around pos
 */
std::vector<std::vector<char>> day11::get_seats_around(int in_x, int in_y) {
  std::vector<std::vector<char>> temp_map{
      {'.', '.', '.'}, {'.', '.', '.'}, {'.', '.', '.'}}; // all floor
  int map_size_x = this->m_seat_map[0].size();
  int map_size_y = this->m_seat_map.size();
  int offset_x{0}, offset_y{0};

  // Calc offset on seat map to local map
  offset_x = in_x - 1;
  offset_y = in_y - 1;

  for (int y = 0; y < 3; ++y) {   // y loop
    for (int x = 0; x < 3; ++x) { // x loop
      // check limits for x and y
      if ((((y + offset_y) < 0) || ((x + offset_x) < 0)) // check too small
          || (((y + offset_y) >= map_size_y) ||
              ((x + offset_x) >= map_size_x))) { // too high {
        continue;
      } else {
        // We can create the local map
        temp_map[y][x] = this->m_seat_map[y + offset_y][x + offset_x];
      }
    }
  }

  if (DEBUG_OUT) {
    plot_seat_map(temp_map);
  }
  return (temp_map);
}

/**
 * @brief Plot the seat meap
 *
 */
void day11::plot_seat_map(std::vector<std::vector<char>> map_to_plot) {
  for (unsigned y = 0; y < map_to_plot.size(); y++) {
    for (unsigned x = 0; x < map_to_plot.at(0).size(); x++) {
      std::cout << map_to_plot[y].at(x);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}