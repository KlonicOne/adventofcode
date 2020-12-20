/**
 * @file day18.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY18_H_
#define _DAY18_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

// An expression tree node
typedef struct tree_el {
  std::string value;
  tree_el *left;
  tree_el *right;
} tree_el;

class day18 {
private:
  /* data */
  std::vector<std::vector<std::string>> m_format_input;

public:
  day18(/* args */);
  ~day18();

  // Part1
  void solver_part1(void);
  tree_el* calc_line(std::vector<std::string> in_line);
  bool is_operator(std::string s);
  void inorder(tree_el *t);
  tree_el* new_tree_element(std::string v);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
  std::string remove_spaces(const std::string s);
};

#endif
