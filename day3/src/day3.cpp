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
  std::vector<int> manhattenDist;
  std::vector<std::string> pathTable;

  Path path;

  // Get path each of it in an vector elelemt
  pathTable = path.separateWirePath(ifile);

  // Get path in xy coordinates based on string
  wire1 = path.getPathOfString(pathTable.at(0));
  wire2 = path.getPathOfString(pathTable.at(1));

  // Calculate intersections
  intersections = path.getIntersections(wire1, wire2);

  // Manhatten distance sorted
  manhattenDist = path.getManhattenDistance(intersections);

  // Result part 1
  std::cout << "Manhatten Distance1: " << manhattenDist.at(1) << std::endl;
}

