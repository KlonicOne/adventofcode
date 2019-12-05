/*
 * day3.cpp
 *
 */
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
#include <tuple>

#include "Path.h"

using namespace std;

int main()
{
  std::ifstream ifile("input.txt");
  std::vector<std::tuple<int, int>> wire1, wire2;
  std::vector<std::string> pathTable;

  Path path;

  // Get path each of it in an vector elelemt
  pathTable = path.separateWirePath(ifile);

  for (unsigned int i = 0; i < pathTable.size(); i++)
  {
    // Get path in xy coordinates based on string
    path.getPathOfString(pathTable.at(i));
  }

}

