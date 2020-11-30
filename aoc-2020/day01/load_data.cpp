/**
 * @file load_data.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-11-30
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

#include "load_data.h"

using namespace std;

/**
 * @brief constructor
 *
 */
load_data::load_data(/* args */) {}

/**
 * @brief Destroy the load data::load data object
 *
 */
load_data::~load_data() {}

/**
 * @brief Load data and return vector of string
 *
 * @param inputFile
 * @return std::vector<std::string>
 */
std::vector<std::string> load_data::getInputTable(std::ifstream &inputFile) {
  std::string Element;
  std::vector<std::string> retVector;

  while (getline(inputFile, Element)) {
    retVector.push_back(Element);
  }

  this->debugOutTable(retVector);

  return (retVector);
}

/**
 * @brief Load data and return vector of int
 *
 * @param input
 * @return std::vector<int>
 */
std::vector<int> load_data::getInputVector(istream &input) {
  string codeElement;
  std::vector<int> codeVector;

  while (getline(input, codeElement, ',')) {
    codeVector.push_back(stoi(codeElement));
  }

  this->debugOutVector(codeVector);

  return (codeVector);
}

/**
 * @brief Function to debug out the vector of int
 *
 * @param inVector
 */
void load_data::debugOutVector(vector<int> inVector) {
  for (std::vector<int>::const_iterator i = inVector.begin();
       i != inVector.end(); ++i) {
    std::cout << *i << ',' << ' ';
  }
  std::cout << std::endl;
}

/**
 * @brief Debug out the vector of strings
 *
 * @param inTable
 */
void load_data::debugOutTable(std::vector<std::string> inTable) {
    for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i) {
    std::cout << *i << std::endl;
  }
}
