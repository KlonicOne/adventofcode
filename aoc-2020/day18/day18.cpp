/**
 * @file day18.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day18.h"
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
day18::day18(/* args */) {}

/**
 * @brief Destroy the day18::day18
 *
 */
day18::~day18() {}

/**
 * @brief Solve part 1
 *
 */
void day18::solver_part1(void) {
  int answer = 0;
  tree_el* ari_tree;

  for(int i = 0; i < this->m_format_input.size(); i++) {
    ari_tree = calc_line(this->m_format_input[i]);
    inorder(ari_tree);
  }

  // Out result
  std::cout << "Result Part1: " << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day18::solver_part2(void) {
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
void day18::format_input(std::vector<std::string> inTable) {
  // Loop through lines of file in input
  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    // used temp to store line and each element
    std::string string_line = "";
    std::string element = "";
    std::vector<std::string> string_vec;
    // To split the string
    std::string::size_type start{0};
    std::string::size_type len{0};
    std::string::size_type pos;
    std::string delimiter = "+*()";

    // Get single line as string_line
    string_line = (*i);

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);

      // Remove all spaces on current element
      element = remove_spaces(element);
      // add element to end of vector
      string_vec.push_back(element);
      if (pos != std::string::npos) {
        // And operation to the end
        string_vec.push_back(string_line.substr(pos, 1));
      }

      // next position to start searching for delimiter
      start = pos + 1;
    } while (pos != std::string::npos);

    if (DEBUG_OUT) {
      show_container(string_vec);
    }

    // Make overall vector of vectors
    this->m_format_input.push_back(string_vec);
  }
}

/**
 * @brief Remove all spaces in string
 *
 * @param s string reference
 * @return std::string new string without spaces
 */
std::string day18::remove_spaces(const std::string s) {
  std::string ret_s = s;
  std::string::size_type pos = ret_s.find(' ');
  while (pos != std::string::npos) {
    ret_s.erase(ret_s.begin() + pos);
    pos = ret_s.find(' ');
  }
  return (ret_s);
}

/**
 * @brief Function create an arithmetic tree and returns result
 *
 * @param in_line The input as vector of strings
 * @return tree_el* first element of arithmetic tree
 */
tree_el* day18::calc_line(std::vector<std::string> in_line) {
  std::stack<tree_el *> tree_stack;
  tree_el *t, *t1, *t2;

  // Traverse through every character of
  // input expression
  for (int i = 0; i < in_line.size(); i++) {
    // If operand, simply push into stack
    if (!is_operator(in_line[i])) {
      t = new_tree_element(in_line[i]);
      tree_stack.push(t);
    } else // operator
    {
      t = new_tree_element(in_line[i]);

      // Pop two top nodes
      t1 = tree_stack.top(); // Store top
      tree_stack.pop();      // Remove top
      t2 = tree_stack.top();
      tree_stack.pop();

      //  make them children
      t->right = t1;
      t->left = t2;

      // Add this subexpression to stack
      tree_stack.push(t);
    }
  }

  //  only element will be root of expression
  // tree
  t = tree_stack.top();
  tree_stack.pop();

  return (t);
}

/**
 * @brief Function to check if it is an operator
 *
 * @param s Input to check
 * @return true It is operator
 * @return false It is not operator
 */
bool day18::is_operator(std::string s) {
  bool check_result = false;
  const char *c = s.c_str();

  if (*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '^') {
    check_result = true;
  }

  return (check_result);
}

/**
 * @brief Utility function to do inorder traversal
 *
 * @param t Not to put in order of tee
 */
void day18::inorder(tree_el *t) {
  if (t) {
    inorder(t->left);
    std::cout << t->value;
    inorder(t->right);
  }
  std::cout << std::endl;
}

/**
 * @brief  A utility function to create a new node
 *
 * @param v char with op or val to be created
 * @return tree_el* new element
 */
tree_el *day18::new_tree_element(std::string v) {
  tree_el *temp = new tree_el;
  temp->left = NULL;
  temp->right = NULL;
  temp->value = v;
  return temp;
};
