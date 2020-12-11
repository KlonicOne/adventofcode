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

#define DEBUG_OUT false
#define NUM_SUPER_LOOP 100

/**
 * @brief constructor
 *
 */
day11::day11(/* args */) { this->m_occupied_seats = 0; }

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
  std::vector<std::vector<char>> next_seat_map;
  // Info out
  std::cout << "Part 1" << std::endl;

  if (DEBUG_OUT) {
    std::cout << "Start map" << std::endl;
    this->plot_seat_map(this->m_seat_map);
  }

  // Start with map read in
  next_seat_map = this->m_seat_map;

  // Now go through map and apply rules
  int loop_iterations = NUM_SUPER_LOOP;
  while (loop_iterations) {
    // Go over map and store in next map
    for (unsigned y = 0; y < this->m_seat_map.size(); y++) {
      for (unsigned x = 0; x < this->m_seat_map.at(0).size(); x++) {
        // Check which rule is applied
        if (this->m_seat_map[y].at(x) == 'L') {
          // is empty
          if (this->check_to_occupy(x, y)) {
            next_seat_map[y].at(x) = '#'; // Yes change ot occupied
          }
        } else if (this->m_seat_map[y].at(x) == '#') {
          if (this->check_to_free(x, y)) {
            next_seat_map[y].at(x) = 'L'; // Yes change to free
          }
        } else {
          // floor do nothing
        }
      }
    }

    if (DEBUG_OUT) {
      std::cout << "Round: " << NUM_SUPER_LOOP - loop_iterations << std::endl;
    }

    // Check end criterion
    if (compare_maps(next_seat_map, this->m_seat_map) &&
        loop_iterations < NUM_SUPER_LOOP) {
      loop_iterations = 0; // Stop looping
    } else {
      // Next loop
      loop_iterations--;
    }

    // The calculated map has to taken over for next loop
    this->m_seat_map = next_seat_map;

    // round loop_iteration
    if (DEBUG_OUT) {
      this->plot_seat_map(next_seat_map);
    }
  }

  answer = this->count_occupied_seats();

  // My bag in list so result - 1 should be good
  std::cout << "Result part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day11::solver_part2(void) {
  int answer = 0;
  std::vector<std::vector<char>> next_seat_map;
  // Info out
  std::cout << "Part 2" << std::endl;

  // Reset map to completely free
  this->set_all_seats_free();

  if (DEBUG_OUT) {
    std::cout << "Start map" << std::endl;
    this->plot_seat_map(this->m_seat_map);
  }

  // Start with map read in
  next_seat_map = this->m_seat_map;

  // Now go through map and apply rules
  int loop_iterations = NUM_SUPER_LOOP;
  while (loop_iterations) {
    // Go over map and store in next map
    for (unsigned y = 0; y < this->m_seat_map.size(); y++) {
      for (unsigned x = 0; x < this->m_seat_map.at(0).size(); x++) {
        // Check which rule is applied
        if (this->m_seat_map[y].at(x) == 'L') {
          // is empty
          if (this->check_line_to_occupy(x, y)) {
            next_seat_map[y].at(x) = '#'; // Yes change ot occupied
          }
        } else if (this->m_seat_map[y].at(x) == '#') {
          if (this->check_line_to_free(x, y)) {
            next_seat_map[y].at(x) = 'L'; // Yes change to free
          }
        } else {
          // floor do nothing
        }
      }
    }

    if (DEBUG_OUT) {
      std::cout << "Round: " << NUM_SUPER_LOOP - loop_iterations << std::endl;
    }

    // Check end criterion
    if (compare_maps(next_seat_map, this->m_seat_map) &&
        (loop_iterations < NUM_SUPER_LOOP)) {
      std::cout << "Loops used: " << NUM_SUPER_LOOP - loop_iterations
                << std::endl;
      loop_iterations = 0; // Stop looping
    } else {
      // Next loop
      loop_iterations--;

      // The calculated map has to taken over for next loop
      this->m_seat_map = next_seat_map;
    }

    // round loop_iteration
    if (DEBUG_OUT) {
      this->plot_seat_map(next_seat_map);
    }
  }

  // Check seats with previous seats
  answer = this->count_occupied_seats();

  std::cout << "Result part2: " << answer << std::endl;
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
          if (DEBUG_OUT) {
          }
        }
      }
    }
  }

  // Check if more than four then empty
  if (sum_occ_seats == 0) {
    to_occupy = true;
    //   if (DEBUG_OUT) {
    //     std::cout << "To occupy" << std::endl;
    //   }
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
    // if (DEBUG_OUT) {
    //   std::cout << "To free" << std::endl;
    // }
  }

  return (to_free);
}

/**
 * @brief Check each line direction for first occupied seat
 *
 * consider the first seat in each of those eight directions
 *
 * @param in_x current pos
 * @param in_y pos
 * @return true Seat can be occupied
 * @return false rule not met
 */
bool day11::check_line_to_occupy(int in_x, int in_y) {
  bool to_occupy = false;
  int sum_occ_seats = 0;
  std::vector<std::vector<char>> loc_map = this->get_seats_line(in_x, in_y);

  // Check rule for all except given seat
  for (unsigned y = 0; y < loc_map.size(); y++) {
    // Check if occupied seat can be seen
    auto it_free = std::find(loc_map.at(y).begin(), loc_map.at(y).end(), 'L');
    auto it_occ = std::find(loc_map.at(y).begin(), loc_map.at(y).end(), '#');

    // both iterator at the end we can occupy seat
    if (it_free == loc_map.at(y).end() && it_occ == loc_map.at(y).end()) {
      to_occupy = true;
    } else if (it_free < it_occ) {
      // In this direction first seat is free
      to_occupy = true;
    } else {
      // Oh no in this direction first seat is occupied, stop immediately
      to_occupy = false;
      break;
    }
  }

  return (to_occupy);
}

/**
 * @brief Check each line direction for number of occupied seats to free
 *
 * it now takes five or more visible occupied seats for an occupied seat to
 * become empty
 *
 * @param in_x
 * @param in_y
 * @return true
 * @return false
 */
bool day11::check_line_to_free(int in_x, int in_y) {
  bool to_free = false;
  int sum_occ_seats = 0;
  std::vector<std::vector<char>> loc_map = this->get_seats_line(in_x, in_y);

  // Check rule for all except given seat
  for (unsigned y = 0; y < loc_map.size(); y++) {
    // Check if occupied seat can be seen
    auto it_occ = std::find(loc_map.at(y).begin(), loc_map.at(y).end(), '#');
    auto it_free = std::find(loc_map.at(y).begin(), loc_map.at(y).end(), 'L');

    // First seen is occupied
    if (it_occ < it_free) {
      sum_occ_seats++; // sum up seats
    }
  }

  // Check if more than four then empty
  if (sum_occ_seats >= 5) {
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

  // if (DEBUG_OUT) {
  //   plot_seat_map(temp_map);
  // }
  return (temp_map);
}

/**
 * @brief Return a vector with 8 vectors for each direction one, they will have
 * different size
 *
 * @param in_x start pos
 * @param in_y start pos
 * @return std::vector<std::vector<char>> Vector with 8 vectors in each line one
 */
std::vector<std::vector<char>> day11::get_seats_line(int in_x, int in_y) {
  std::vector<std::vector<char>> line_vectors; // vectors in each line
  std::vector<char> single_line;               // single line vector
  int stop_y = this->m_seat_map.size();        // stop in y
  int stop_x = this->m_seat_map.at(0).size();  // stop in x
  int delta_x{0}, delta_y{0};                  // delta for line search
  int cur_x{in_x}, cur_y{in_y};                // current position

  // Loop through all 8 directions and store the vector up to first occupied
  // seat
  for (int dir = 0; dir < 8; ++dir) { // y loop
    // Prepare for next line
    single_line.clear();
    cur_x = in_x; // back to start
    cur_y = in_y;

    // First set the delta for each direction
    switch (dir) {
    case (0): {
      // up
      delta_x = 0;
      delta_y = 1;
    } break;
    case (1): {
      // up left
      delta_x = -1;
      delta_y = 1;
    } break;
    case (2): {
      // left
      delta_x = -1;
      delta_y = 0;
    } break;
    case (3): {
      // down left
      delta_x = -1;
      delta_y = -1;
    } break;
    case (4): {
      // down
      delta_x = 0;
      delta_y = -1;
    } break;
    case (5): {
      // down right
      delta_x = 1;
      delta_y = -1;
    } break;
    case (6): {
      // right
      delta_x = 1;
      delta_y = 0;
    } break;
    case (7): {
      // up right
      delta_x = 1;
      delta_y = 1;
    } break;
    default: {
      // do nothing
    }
    }

    // next pos on start because start pos is element itself
    cur_x = cur_x + delta_x;
    cur_y = cur_y + delta_y;

    // Create a single line until end of seat map
    while (((cur_y >= 0) && (cur_x >= 0)) &&
           ((cur_y < stop_y) && (cur_x < stop_x))) {
      // Push back to line
      single_line.push_back(this->m_seat_map[cur_y][cur_x]);

      // next pos
      cur_x = cur_x + delta_x;
      cur_y = cur_y + delta_y;
    }
    // Take over the line
    line_vectors.push_back(single_line);
  }

  return (line_vectors);
}

/**
 * @brief Count the number of seats in the map occipied
 *
 * @return int occupied seats
 */
int day11::count_occupied_seats(void) {
  int tmp_seats = 0;

  for (unsigned y = 0; y < this->m_seat_map.size(); ++y) {
    for (unsigned x = 0; x < this->m_seat_map.at(0).size(); ++x) {
      if (this->m_seat_map[y].at(x) == '#') {
        tmp_seats++;
      }
    }
  }

  return (tmp_seats);
}

/**
 * @brief Set all seats occupied
 *
 */
void day11::set_all_seats_occupied(void) {
  for (unsigned y = 0; y < this->m_seat_map.size(); y++) {
    for (unsigned x = 0; x < this->m_seat_map.at(0).size(); x++) {
      if (this->m_seat_map[y].at(x) != '.') {
        this->m_seat_map[y].at(x) = '#';
      }
    }
  }
}

/**
 * @brief Set all seats empty
 *
 */
void day11::set_all_seats_free(void) {
  for (unsigned y = 0; y < this->m_seat_map.size(); y++) {
    for (unsigned x = 0; x < this->m_seat_map.at(0).size(); x++) {
      if (this->m_seat_map[y].at(x) != '.') {
        this->m_seat_map[y].at(x) = 'L';
      }
    }
  }
}

bool day11::compare_maps(std::vector<std::vector<char>> A,
                         std::vector<std::vector<char>> B) {
  bool are_same = false;

  for (unsigned y = 0; y < this->m_seat_map.size(); y++) {
    are_same = std::equal(A.begin(), A.end(), B.begin());
    if (are_same == false) {
      // Maps can not be same
      break;
    }
  }

  return (are_same);
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