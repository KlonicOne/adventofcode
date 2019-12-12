/*
 * day2.cpp
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "CDecodePW.h"
using namespace std;

int main(void)
{
  int start = 235741;
  int stop = 706948;
  int counter = 0;

  CDecodePW decoder;

  // Part 1
  for (int index = start; index <= stop; index++)
  {
    counter += decoder.checkCodePart1(index);
  }
  std::cout << "Part 1 : " << counter << std::endl;

  // Part 2
  counter = 0;
  for (int index = start; index <= stop; index++)
  {
    counter += decoder.checkCodePart2(index);
  }
  std::cout << "Part 2 : " << counter << std::endl;

  return(0);
}

