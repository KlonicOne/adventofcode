/*
 * monitoringstation.h
 *
 *  Created on: 6 Jan 2020
 *      Author: nico
 */

#ifndef CMONITORINGSTATION_H_
#define CMONITORINGSTATION_H_

#include <fstream>
#include <vector>

using namespace std;

class CMonitoringStation
{
public:
  CMonitoringStation();
  virtual ~CMonitoringStation();

  void parseMap(istream &input);
  void calcCandidates(void);

  void plotAsteroidMap(void);
  void plotCandidatesdMap(void);

private:
  unsigned mSizeX;
  unsigned mSizeY;

  std::vector<std::vector<int>> mAsteroidMap;
  std::vector<std::vector<int>> mAsteroidCountMap;
  std::vector<std::vector<int>> mAsteroidSightMap;
};

#endif /* CMONITORINGSTATION_H_ */
