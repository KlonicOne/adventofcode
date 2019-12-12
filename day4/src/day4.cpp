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

void part1()
{
  int start = 235741;
  int stop = 706948;
  int counter = 0;

  CDecodePW decoder;

  for (int index = start; index <= stop; index++)
  {
    counter += decoder.checkNumber(index);
  }
  cout << "Part 1 : " << counter << endl;
}

void part2()
{
  int start = 235741;
  int stop = 706948;
  int counter = 0;

  CDecodePW decoder;

  for (int index = start; index <= stop; index++)
  {
    counter += decoder.checkNumberPart2(index);
  }
  cout << "Part 2 : " << counter << endl;
}

int main()
{
  int returnObject = 0;

  part1();
  part2();

  return returnObject = 0;
}

