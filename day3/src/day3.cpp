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
  std::vector<std::tuple<int, int>> wire1, wire2, intersections;
  std::vector<std::string> pathTable;

  Path path;

  // Get path each of it in an vector elelemt
  pathTable = path.separateWirePath(ifile);

  // Get path in xy coordinates based on string
  wire1 = path.getPathOfString(pathTable.at(0));
  wire2 = path.getPathOfString(pathTable.at(1));

  intersections = path.getIntersections(wire1, wire2);

  // debug out intersections
  for (const auto &it : intersections)
  {
    std::cout << "X: " << std::get<0>(it) << "Y: " << std::get<1>(it) << std::endl;
  }
}

