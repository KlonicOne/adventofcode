/**
 * @file day21.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY21_H_
#define _DAY21_H_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

class day21 {
private:
  /* data */
  map<int, std::vector<std::string>> m_meal_allergens;
  map<int, std::vector<std::string>> m_meal_ingredients;

  map<std::string, std::vector<int>> m_allergen_meals;
  map<std::string, std::vector<int>> m_ingredient_meals;

public:
  day21(/* args */);
  ~day21();

  // Part1
  void solver_part1(void);
  void create_allergen_meals_map(void);
  void create_ingredient_meals_map(void);

  // Part2
  void solver_part2(void);

  // Common
  void format_input(std::vector<std::string> inTable);
  std::string remove_spaces(const std::string s);
  std::string remove_brackets(const std::string s);
};

#endif
