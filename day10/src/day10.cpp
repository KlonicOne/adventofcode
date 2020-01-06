// --------------------------
// file : day1.cpp
// --------------------------

#include "CMonitoringStation.h"

using namespace std;


int main()
{
  std::ifstream ifile("input.txt");

  CMonitoringStation monStation;

  monStation.parseMap(ifile);
  monStation.calcCandidates();

  monStation.plotAsteroidMap();
  monStation.plotCandidatesdMap();

}
