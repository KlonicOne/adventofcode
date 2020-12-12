/**
 * @file day12.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day12.h"
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

/**
 * @brief constructor
 *
 */
day12::day12(/* args */) {
  this->m_start_pos = {0, 0, 'E'};
  this->m_ship_route.push_back(this->m_start_pos);
  this->m_waypoint = {10, -1, 'E'};
  this->m_waypoint_route.push_back(this->m_start_pos);
}

/**
 * @brief Destroy the day12::day12
 *
 */
day12::~day12() {}

/**
 * @brief Solve part 1
 *
 */
void day12::solver_part1(void) {
  int answer = 0;

  // Create ship route
  this->create_ship_route(this->m_format_input);

  // calculate manhatten distance
  answer = this->calc_manhatten_distance(this->m_ship_route.back().x,
                                         this->m_ship_route.back().y);

  // My bag in list so result - 1 should be good
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day12::solver_part2(void) {
  int answer = 0;

  // Reuse route, so clear before start
  this->m_ship_route.clear();
  // Set start point again and waypoint
  this->m_ship_route.push_back(this->m_start_pos);
  this->m_waypoint_route.push_back(this->m_waypoint);

  // Create ship route
  this->create_ship_route_p2(this->m_format_input);

  // calculate manhatten distance
  answer = this->calc_manhatten_distance(this->m_ship_route.back().x,
                                         this->m_ship_route.back().y);
  // My bag in list so result - 1 should be good
  std::cout << "Result Part2: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Calculate manhatten distance
 *
 * @param x x value
 * @param y y value
 * @return int
 */
int day12::calc_manhatten_distance(int x, int y) {
  int man_dist = 0;

  // Absolute distance
  man_dist = abs(x) + abs(y);

  return (man_dist);
}

/**
 * @brief Generate formatted input
 *
 * @param input
 */
void day12::create_format_input(std::vector<std::string> input) {
  t_input_element temp_inel;

  for (auto iter : input) {
    temp_inel.cmd = iter[0];
    std::string str_value = iter.substr(1, (iter.size() - 1));
    temp_inel.value = stoi(str_value);

    // Create formated input
    this->m_format_input.push_back(temp_inel);

    if (DEBUG_OUT) {
      std::cout << "cmd: " << temp_inel.cmd << ", value: " << temp_inel.value
                << std::endl;
    }
  }
}

/**
 * @brief Crete the route, each step is on element in vector
 *
 * @param input
 */
void day12::create_ship_route(std::vector<t_input_element> input) {
  t_Position temp_pos = this->m_ship_route.at(0); // Init with start

  for (auto iter : input) {
    // Get next position
    temp_pos = this->m_ship_route.back(); // get last element in route

    // Check the next step based on command
    switch (iter.cmd) {
    case 'N':
      temp_pos.y -= iter.value;
      break;
    case 'E':
      temp_pos.x += iter.value;
      break;
    case 'S':
      temp_pos.y += iter.value;
      break;
    case 'W':
      temp_pos.x -= iter.value;
      break;

    // Now check the moves
    case 'F':
      switch (temp_pos.heading) {
      case 'N':
        temp_pos.y -= iter.value;
        break;
      case 'E':
        temp_pos.x += iter.value;
        break;
      case 'S':
        temp_pos.y += iter.value;
        break;
      case 'W':
        temp_pos.x -= iter.value;
        break;
      default:
        break;
      }
      break;

    case 'R':
      switch (temp_pos.heading) {
      case 'N':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'E';
          break;
        case 180:
          temp_pos.heading = 'S';
          break;
        case 270:
          temp_pos.heading = 'W';
          break;
        default:
          break;
        }
        break;
      case 'E':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'S';
          break;
        case 180:
          temp_pos.heading = 'W';
          break;
        case 270:
          temp_pos.heading = 'N';
          break;
        default:
          break;
        }
        break;
      case 'S':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'W';
          break;
        case 180:
          temp_pos.heading = 'N';
          break;
        case 270:
          temp_pos.heading = 'E';
          break;
        default:
          break;
        }
        break;
      case 'W':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'N';
          break;
        case 180:
          temp_pos.heading = 'E';
          break;
        case 270:
          temp_pos.heading = 'S';
          break;
        default:
          break;
        }
        break;
      default:
        break;
      }
      break;

    case 'L':
      switch (temp_pos.heading) {
      case 'N':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'W';
          break;
        case 180:
          temp_pos.heading = 'S';
          break;
        case 270:
          temp_pos.heading = 'E';
          break;
        default:
          break;
        }
        break;
      case 'E':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'N';
          break;
        case 180:
          temp_pos.heading = 'W';
          break;
        case 270:
          temp_pos.heading = 'S';
          break;
        default:
          break;
        }
        break;
      case 'S':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'E';
          break;
        case 180:
          temp_pos.heading = 'N';
          break;
        case 270:
          temp_pos.heading = 'W';
          break;
        default:
          break;
        }
        break;
      case 'W':
        switch (iter.value) {
        case 90:
          temp_pos.heading = 'S';
          break;
        case 180:
          temp_pos.heading = 'E';
          break;
        case 270:
          temp_pos.heading = 'N';
          break;
        default:
          break;
        }
        break;
      default:
        break;
      }
      break;

    default:
      break;
    }

    // Take over element in route
    this->m_ship_route.push_back(temp_pos);
  }
}

/**
 * @brief Create the route part 2 for ship and waypoint
 *
 * @param input
 */
void day12::create_ship_route_p2(std::vector<t_input_element> input) {
  t_Position temp_pos_ship = this->m_ship_route.at(0);    // Init with start
  t_Position temp_pos_way = this->m_waypoint_route.at(0); // Init with start

  for (auto iter : input) {
    // Get next position
    temp_pos_ship = this->m_ship_route.back(); // get last element in route
    temp_pos_way = this->m_waypoint_route.back();
    int temp_value = 0;

    if (DEBUG_OUT){
      std::cout << "ship: x: " << temp_pos_ship.x << ", y: " << temp_pos_ship.y << std::endl;
      std::cout << "way: x: " << temp_pos_way.x << ", y: " << temp_pos_way.y << std::endl;
    }

    // Check the next step based on command
    switch (iter.cmd) {
    case 'F':
      temp_pos_ship.x += iter.value * temp_pos_way.x;
      temp_pos_ship.y += iter.value * temp_pos_way.y;
      break;

    case 'N':
      temp_pos_way.y -= iter.value;
      break;
    case 'E':
      temp_pos_way.x += iter.value;
      break;
    case 'S':
      temp_pos_way.y += iter.value;
      break;
    case 'W':
      temp_pos_way.x -= iter.value;
      break;

    // Now the moves
    case 'R':
      switch (iter.value) {
      case 90: {
        temp_value = temp_pos_way.x;
        temp_pos_way.x = -1 * temp_pos_way.y;
        temp_pos_way.y = temp_value;
      } break;
      case 180: {
        temp_pos_way.x = -1 * temp_pos_way.x;
        temp_pos_way.y = -1 * temp_pos_way.y;
      } break;
      case 270: {
        int temp_value = temp_pos_way.x;
        temp_pos_way.x = temp_pos_way.y;
        temp_pos_way.y = -temp_value;
      } break;
      default:
        break;
      }
      break;

    case 'L':
      switch (iter.value) {
      case 90: {
        int temp_value = temp_pos_way.x;
        temp_pos_way.x = temp_pos_way.y;
        temp_pos_way.y = -temp_value;
      } break;
      case 180: {
        temp_pos_way.x = -1 * temp_pos_way.x;
        temp_pos_way.y = -1 * temp_pos_way.y;
      } break;
      case 270: {
        int temp_value = temp_pos_way.x;
        temp_pos_way.x = -1 * temp_pos_way.y;
        temp_pos_way.y = temp_value;
      } break;
      default:
        break;
      }
      break;
    default:
      break;
    }

    this->m_waypoint_route.push_back(temp_pos_way);
    this->m_ship_route.push_back(temp_pos_ship);
  }
}
