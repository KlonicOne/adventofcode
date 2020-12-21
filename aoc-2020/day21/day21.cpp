/**
 * @file day21.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day21.h"
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
day21::day21(/* args */) {}

/**
 * @brief Destroy the day21::day21
 *
 */
day21::~day21() {}

/**
 * @brief Solve part 1
 *
 */
void day21::solver_part1(void) {
  long long answer = 0;

  // Create list with allergen and ingredients as key an vector with meals
  // containing it
  this->create_allergen_meals_map();
  this->create_ingredient_meals_map();

  // Check for intersections in ingredients on meals which have same allerged
  for (auto iter : this->m_allergen_meals) {
    std::vector<std::string> temp_ingredients;
    // Check if more than one meal in list
    if (iter.second.size() > 1) {
      // We have at least two meals with same allergen
      std::vector<std::string> v1 = this->m_meal_ingredients[iter.second.at(0)];
      std::vector<std::string> v2 = this->m_meal_ingredients[iter.second.at(1)];
      // Sort before intersection is checked
      std::sort(v1.begin(), v1.end());
      std::sort(v2.begin(), v2.end());
      // temp_ingredients contains the intersections
      std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                            back_inserter(temp_ingredients));
      // If more then two meals are in the list of the allergen, then we check
      // further with the intersection result
      if (iter.second.size() > 1) {
        for (int i = 2; i < iter.second.size(); ++i) {
          v1 = temp_ingredients;
          v2 = this->m_meal_ingredients[iter.second.at(i)];
          std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                                back_inserter(temp_ingredients));
        }
      }
    } else {
      // allergen is only in one meal list all ingredients
      for (int i = 0; i < this->m_meal_ingredients[iter.second.at(0)].size();
           ++i) {
        temp_ingredients.push_back(m_meal_ingredients[iter.second.at(0)].at(i));
      }
    }

    // Push to ingredients with allergen
    this->m_ingredients_with_allergen.insert(m_ingredients_with_allergen.end(),
                                             temp_ingredients.begin(),
                                             temp_ingredients.end());
  }

  // Sort and eliminate double values
  std::sort(this->m_ingredients_with_allergen.begin(),
            this->m_ingredients_with_allergen.end());
  this->m_ingredients_with_allergen.erase(
      std::unique(this->m_ingredients_with_allergen.begin(),
                  this->m_ingredients_with_allergen.end()),
      this->m_ingredients_with_allergen.end());

  // Sort vector with all allergene listed
  std::sort(this->m_all_ingredients.begin(), this->m_all_ingredients.end());
  // Get all elements which are not in the ingred with allergen list
  std::set_symmetric_difference(
      this->m_ingredients_with_allergen.begin(),
      this->m_ingredients_with_allergen.end(), this->m_all_ingredients.begin(),
      this->m_all_ingredients.end(),
      std::back_inserter(this->m_ingredients_without_allergen));

  // We need to know in how many meals the ingredients without allergen are


  if (DEBUG_OUT) {
    // show map contents
    for (auto iter : this->m_allergen_meals) {
      std::cout << "Allergen: " << iter.first << "; Meals: ";
      for (auto iter_val : iter.second) {
        std::cout << iter_val << ", ";
      }
      std::cout << std::endl;
    }
    for (auto iter : this->m_ingredient_meals) {
      std::cout << "Ingredient: " << iter.first << "; Meals: ";
      for (auto iter_val : iter.second) {
        std::cout << iter_val << ", ";
      }
      std::cout << std::endl;
    }
    show_container(this->m_all_ingredients);
    show_container(this->m_ingredients_with_allergen);
    show_container(this->m_ingredients_without_allergen);
  }

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day21::solver_part2(void) {
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
void day21::format_input(std::vector<std::string> inTable) {
  int meal_num = 0;
  // Loop through lines of file in input
  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // used temp to store line and each element
    std::string string_line = "";
    std::string element = "";
    std::vector<std::string> current_ingredients;
    std::vector<std::string> current_allergen;
    // To split the string
    std::string::size_type start{0};
    std::string::size_type len{0};
    std::string::size_type pos;
    std::string delimiter = " ,";

    // Get single line as string_line
    string_line = (*i);

    // Split string_line ingredients and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // Remove spaces
      element = this->remove_spaces(element);
      // Check to not add empty elements

      if (element.size() != 0) {
        // add element to end of vector
        current_ingredients.push_back(element);
      }
      // next position to start searching for delimiter
      start = pos + 1;

      // if ( then the allergen are starting
      if (string_line.substr(start, 1) == "(") {
        break; // Stop the do loop
      }
    } while (pos != std::string::npos);

    // Split string_line allergen and store in vector of strings
    // start value still continues from previous do while
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // Remove spaces and brackets
      element = this->remove_spaces(element);
      element = this->remove_brackets(element);

      // Check to not add empty elements
      if (element.size() != 0 && element.compare("contains")) {
        // add element to end of vector
        current_allergen.push_back(element);
      }
      // next position to start searching for delimiter
      start = pos + 1;
    } while (pos != std::string::npos);

    // Now for meal we have ingredients and allergen extracted, put in map
    this->m_meal_ingredients.insert({meal_num, current_ingredients});
    this->m_meal_allergens.insert({meal_num, current_allergen});
    // next meal
    meal_num++;
  }

  if (DEBUG_OUT) {
    // show map contents
    for (auto iter : this->m_meal_ingredients) {
      std::cout << "Meal: " << iter.first << "; Ingreds: ";
      for (auto iter_val : iter.second) {
        std::cout << iter_val << ", ";
      }
      std::cout << std::endl;
    }
    for (auto iter : this->m_meal_allergens) {
      std::cout << "Meal: " << iter.first << "; Allerg: ";
      for (auto iter_val : iter.second) {
        std::cout << iter_val << ", ";
      }
      std::cout << std::endl;
    }
  }
}

/**
 * @brief Remove all spaces in string
 *
 * @param s string reference
 * @return std::string new string without spaces
 */
std::string day21::remove_spaces(const std::string s) {
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
std::string day21::remove_brackets(const std::string s) {
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
 * @brief Create the map which meals contain the allergen
 *
 */
void day21::create_allergen_meals_map(void) {
  // Go through all meals and add allergen to map with list of meal
  for (auto iter : this->m_meal_allergens) {
    for (auto iter_val : iter.second) {
      // Check if allergen already in map
      if (this->m_allergen_meals.count(iter_val)) {
        // Is in list so add meal to allergen
        this->m_allergen_meals[iter_val].push_back(iter.first);
      } else {
        // New element
        std::vector<int> temp_meals;
        temp_meals.push_back(iter.first); // Add meal to list
        this->m_allergen_meals.insert({iter_val, temp_meals});
      }
    }
  }
}

/**
 * @brief Create the map which meals contain the ingredients
 *
 */
void day21::create_ingredient_meals_map(void) {
  // Go through all meals and add ingredients to map with list of meal
  for (auto iter : this->m_meal_ingredients) {
    for (auto iter_val : iter.second) {
      // Check if ingredient already in map
      if (this->m_ingredient_meals.count(iter_val)) {
        // Is in list so add meal to allergen
        this->m_ingredient_meals[iter_val].push_back(iter.first);
      } else {
        // New element
        std::vector<int> temp_meals;
        temp_meals.push_back(iter.first); // Add meal to list
        this->m_ingredient_meals.insert({iter_val, temp_meals});
        this->m_all_ingredients.push_back(iter_val);
      }
    }
  }
}
