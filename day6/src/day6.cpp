/*
 * day2.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

#include "COrbitMap.h"
using namespace std;

int main()
{
  COrbitMap orbitMap;
  std::ifstream ifile("input.txt");

  // Get input data into orbit map
  orbitMap.parseInputMap(ifile);

  // Create the tree based in the read data
  orbitMap.constructOrbitMap();

  // Get max depth
  unsigned orbitDepth = orbitMap.maxOrbitMapDepth();
  unsigned orbitSum = orbitMap.getSumOfOrbitConnections();
  // out part 1
  std::cout << "Part 1: " << orbitSum + 1 << std::endl;

}

