/**
 * @file day07.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY06_H_
#define _DAY06_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

class bag_node {
public:
  bag_node();
  virtual ~bag_node();

  std::string bag_name;               // Name of node
  std::vector<int> amount_each_child; // Amount of bags each child
  // References
  std::vector<bag_node *> parent_bag_nodes; // parent vector
  std::vector<bag_node *> child_bag_nodes;  // child vector
};

class day07 {
private:
  /* data */
  std::vector<bag_node *> bag_graph; // Vector with all bags to search fast

public:
  day07(/* args */);
  ~day07();

  void solver_part1(void);
  void solver_part2(void);

  // Common
  bag_node *search_bag_node(std::string bag_name);
  void format_input(std::vector<std::string> inTable);
  void insert_bag_node(std::string root_bag_name, std::string new_bag_name,
                       int allowed_new_bags);
  std::string replace_all_strings(std::string subject,
                                  const std::string &search,
                                  const std::string &replace);
  std::string trim_lead_whspace(const std::string &s);
  void print_bag_graph(void);
};

#endif // _DAY06_H_