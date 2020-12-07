/**
 * @file day07.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day07.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief Construct a new bag node::bag node object
 *
 */
bag_node::bag_node() { this->bag_name = ""; }

/**
 * @brief Destroy the bag node::bag node object
 *
 */
bag_node::~bag_node() {}

/**
 * @brief constructor
 *
 */
day07::day07(/* args */) { this->root_bag = NULL; }

/**
 * @brief Destroy the day07::day07
 *
 */
day07::~day07() {}

/**
 * @brief Solve part 1
 *
 */
void day07::solver_part1(void) {
  int answer = 0;
  // Info out
  std::cout << "Part 1" << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day07::solver_part2(void) {
  // Info out
  std::cout << "Part 2" << std::endl;
}

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day07::format_input(std::vector<std::string> inTable) {
  // Separate to better debug and use the input
  std::string string_line = "";

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    std::vector<std::string> string_vec_element;
    std::string element = "";
    std::string::size_type start{0};
    std::string::size_type len{0};
    std::string::size_type pos;
    std::string delimiter = ","; // No splitting this time

    // Get single line as string_line
    string_line = (*i);

    // Replace plural on bags
    string_line = replace_all_strings(string_line, "bags", "bag");
    // Replace containt with , to have only one delimiter
    string_line = replace_all_strings(string_line, " contain", ",");
    // Replace point at the end of line
    string_line = replace_all_strings(string_line, ".", "");

    // debug
    std::cout << string_line << std::endl;

    // Should not get non string in lines
    if (string_line.length() == 0) {
      std::cout << "Empty line found in intput!!!" << std::endl;
    }

    // Split string_line and store in vector of strings
    do {
      // get pos from start to first delimiter
      pos = string_line.find_first_of(delimiter, start);
      // get substring until delimiter
      element = string_line.substr(start, pos - start);
      // Delete leading space
      element = trim_lead_whspace(element);
      // add element to end of vector
      string_vec_element.push_back(element);
      // next position to start searching for delimiter
      start = pos + 1;

      // debug out
      std::cout << "Element: " << element << std::endl;
    } while (pos != std::string::npos);

    // Now create graph
    for (int i = 1; i < string_vec_element.size(); ++i) {
      std::string root_bag_name = "";
      std::string new_bag_name = "";
      std::string allowed_bags_s = "";
      int allowed_bags = 0;

      // Split number and node name: 1 bright white bag
      root_bag_name = string_vec_element[0];
      int not_end_node = string_vec_element[i].compare("no other bag");

      // Check if childs are existing, if not nothing need to be done
      if (not_end_node) {
        new_bag_name = string_vec_element[i].substr(
            string_vec_element[i].find_first_of(" ", 0),
            string_vec_element[i].size());
        allowed_bags_s = string_vec_element[i].substr(
            0, string_vec_element[i].find_first_of(" ", 0));
        allowed_bags = stoi(allowed_bags_s);

        // Call function to create graph
        this->insert_bag_node(root_bag_name, new_bag_name, allowed_bags);
        // debug out
        // std::cout << "func(" << root_bag_name << ", " << new_bag_name << ", "
        //           << allowed_bags << ");" << std::endl;
      }
    }
  }
}

/**
 * @brief insert bag in graph
 *
 * @param root_bag_name
 * @param new_bag_name
 */
void day07::insert_bag_node(std::string root_bag_name, std::string new_bag_name,
                            int allowed_new_bags) {
  bag_node *found_bag_root =
      this->search_bag_node(root_bag_name); // Get reference on root from tree
  bag_node *found_bag_childs =
      this->search_bag_node(new_bag_name); // Get reference on child from tree

  // Both elements are existing, so must be new connection only
  if ((found_bag_root != NULL) && (found_bag_childs != NULL)) {
    found_bag_root->child_bag_nodes.push_back(
        found_bag_childs); // Child on root
    found_bag_root->amount_each_child.push_back(
        allowed_new_bags); // Allowed childs
    found_bag_childs->parent_bag_nodes.push_back(
        found_bag_root); // Root on child
  }
  // Root not in tree but child
  else if ((found_bag_root == NULL) && (found_bag_childs != NULL)) {
    bag_node *new_bag_root = new bag_node(); // New root element

    // Add element for search in vector of bags
    this->bag_graph.push_back(new_bag_root);

    // Root creation with new element
    this->bag_graph.push_back(new_bag_root);
    // Assign name
    new_bag_root->bag_name = root_bag_name;
    // Set number of allowed childs
    new_bag_root->amount_each_child.push_back(allowed_new_bags);
    // Connect child
    new_bag_root->child_bag_nodes.push_back(found_bag_childs);
    // Root on found child
    found_bag_childs->parent_bag_nodes.push_back(new_bag_root);

    // This is root bag, found on file
    if (!root_bag_name.compare("vibrant purple bag")) {
      this->root_bag = new_bag_root; // Get reference on new COM root element
    }
  }
  // Root in tree but new child
  else if ((found_bag_root != NULL) && (found_bag_childs == NULL)) {
    bag_node *new_bag_child = new bag_node(); // New child element

    // Add element for search in vector of bags
    this->bag_graph.push_back(new_bag_child);

    // Assign name
    new_bag_child->bag_name = new_bag_name;
    new_bag_child->parent_bag_nodes.push_back(
        found_bag_root); // Parent connection
    found_bag_root->child_bag_nodes.push_back(
        new_bag_child); // Root on found child
    found_bag_root->amount_each_child.push_back(
        allowed_new_bags); // Allowed bags
  }
  // Nothing there all new
  else {
    bag_node *new_bag_root = new bag_node();  // New root element
    bag_node *new_bag_child = new bag_node(); // New child element

    // Add element for search in vector of bags
    this->bag_graph.push_back(new_bag_root);
    this->bag_graph.push_back(new_bag_child);

    // Root
    new_bag_root->bag_name = root_bag_name; // Assign name
    new_bag_root->amount_each_child.push_back(
        allowed_new_bags); // Allowed child bags
    new_bag_root->child_bag_nodes.push_back(new_bag_child); // Child connection

    // Child
    new_bag_child->bag_name = new_bag_name; // Assign name
    new_bag_child->parent_bag_nodes.push_back(
        new_bag_root); // Root on found child

    // Special treatment of COM  we store as root reference
    if (!root_bag_name.compare("vibrant purple bag")) {
      this->root_bag = new_bag_root; // Get reference on new COM root element
    }
  }
}

/**
 * @brief Search for a bag in graph
 *
 * @param search_bag_name
 * @return bag_node*
 */
bag_node *day07::search_bag_node(std::string search_bag_name) {
  bag_node *found_bag = NULL;
  for (std::vector<bag_node *>::iterator it = this->bag_graph.begin();
       it != this->bag_graph.end(); it++) {
    if (search_bag_name.compare((*it)->bag_name) == 0) {
      found_bag = *it;
    }
  }

  return (found_bag);
}

/**
 * @brief Replace all occurences of search in subject
 *
 * @param subject
 * @param search
 * @param replace
 * @return std::string string with replaced search
 */
std::string day07::replace_all_strings(std::string subject,
                                       const std::string &search,
                                       const std::string &replace) {
  std::string::size_type pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return subject;
}

/**
 * @brief Trim sapces on start of string
 *
 * @param s
 * @return std::string
 */
std::string day07::trim_lead_whspace(const std::string &s) {
  std::string::size_type start = s.find_first_not_of(" ");
  return (start == std::string::npos) ? "" : s.substr(start);
}
