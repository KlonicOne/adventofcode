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

  // debug out the tree
  orbitMap.printOrbitMap();

  // Get max depth
  orbitMap.calcOrbitStat();
  int orbitSum = orbitMap.getSumOfOrbitConnections();

  // out part 1
  std::cout << "Part 1: " << orbitSum << std::endl;

  // Calc Santa path
  orbitMap.calcSantaPath();
  int SanPath = orbitMap.getSantaPathConnections();

  // out part 2
  std::cout << "Part 2: " << SanPath << std::endl;


}

