/**
 * @file day20.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day20.h"
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

#define DEBUG_OUT false

/**
 * @brief constructor
 *
 */
day20::day20(/* args */) {}

/**
 * @brief Destroy the day20::day20
 *
 */
day20::~day20() {}

/**
 * @brief Solve part 1
 *
 */
void day20::solver_part1(void) {
  int answer = 0;

  // Test rot90 cw
  this->plot_mat(this->m_cam_input.at(0).image);

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day20::solver_part2(void) {
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
void day20::format_input(std::vector<std::string> inTable) {
  bool start_new_image = true;
  t_tile temp_tile;

  // Loop through lines of file in input
  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // used temp to store line and each element
    std::string string_line = "";
    std::string element = "";
    std::vector<char> c_vec;
    // To split the string
    std::string::size_type pos;

    // Get single line as string_line
    string_line = (*i);

    // Check if the next image comes
    if (string_line.length() == 0) {
      // pushback last element to format input
      this->m_cam_input.push_back(temp_tile);

      // clear elements
      temp_tile.image.clear();
      temp_tile.tile_id = "";

      // Next line is first line with tile ID
      start_new_image = true;
      continue;
    }

    if (start_new_image) {
      // Check for tile and extract id
      element = string_line.substr(5, 4);
      temp_tile.tile_id = element;
      start_new_image = false;
    } else {
      // split elemente by element into image of tile
      for (auto c : string_line) {
        c_vec.push_back(c);
      }
      temp_tile.image.push_back(c_vec);
    }

    if (DEBUG_OUT) {
      show_container(c_vec);
    }
  }
}

/**
 * @brief Remove all spaces in string
 *
 * @param s string reference
 * @return std::string new string without spaces
 */
std::string day20::remove_spaces(const std::string s) {
  std::string ret_s = s;
  std::string::size_type pos = ret_s.find(' ');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find(' ');
  }
  return (ret_s);
}

/**
 * @brief Rotate the image clockwise by 90°
 *
 * @param image
 */
void day20::rot_image_90cw(std::vector<std::vector<char>> &image) {
  int n = image.size();

  for (int i = 0; i < (n / 2); i++) {
    for (int j = i; j < (n - i - 1); j++) {
      int temp_val = image[i][j];
      image[i][j] = image[n - 1 - j][i];
      image[n - 1 - j][i] = image[n - 1 - i][n - 1 - j];
      image[n - 1 - i][n - 1 - j] = image[j][n - 1 - i];
      image[j][n - 1 - i] = temp_val;
    }
  }
}

/**
 * @brief Flip image vertical
 *
 * @param image
 */
void day20::flip_image_v(std::vector<std::vector<char>> &image) {
  int n = image.size(); // lines and rows

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (n / 2); j++) {
      int temp_val = image[i][j];
      image[i][j] = image[i][n - j - 1];
      image[i][n - j - 1] = temp_val;
    }
  }
}

/**
 * @brief Flip image horizontal
 *
 * @param image
 */
void day20::flip_image_h(std::vector<std::vector<char>> &image) {
  int n = image.size(); // lines and rows

  for (int i = 0; i < (n / 2); i++) {
    for (int j = 0; j < n; j++) {
      int temp_val = image[i][j];
      image[i][j] = image[n - i - 1][j];
      image[n - i - 1][j] = temp_val;
    }
  }
}

/**
 * @brief Plot given matrix
 *
 * @param image
 */
void day20::plot_mat(std::vector<std::vector<char>> &image) {
  for (int i = 0; i < image.size(); i++) {
    for (int j = 0; j < image.at(i).size(); j++) {
      std::cout << image[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/**
 * @brief Compare two given lines
 *
 * @param a
 * @param b
 * @return true both are same
 * @return false unequal
 */
bool day20::compare_lines(std::vector<char> a, std::vector<char> b) {
  bool lines_equal = false;

  // Are equal?
  lines_equal = std::equal(a.begin(), a.end(), b.begin());

  return (lines_equal);
}
