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

  orbitMap.parseInputMap(ifile);


}

