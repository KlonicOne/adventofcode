/**
 * @file load_data.h
 * @author klonicone
 * @brief
 * @version 0.1
 * @date 2020-11-30
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _LOAD_DATA_
#define _LOAD_DATA_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>


using namespace std;

class load_data {
private:
  /* data */
  void debugOutVector(vector<int> inVector);
  void debugOutTable(std::vector<std::string> inTable);

public:
  load_data(/* args */);
  virtual ~load_data();

  std::vector<std::string> getInputVectorString(std::ifstream &inputFile);
  std::vector<int> getInputVectorInt(std::vector<std::string>);
};

#endif // !_LOAD_DATA_
