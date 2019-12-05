/*
 * Path.h
 *
 *  Created on: 5 Dec 2019
 *      Author: nico
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include <tuple>
#include <sstream>

class Path
{
public:
  Path();
  virtual ~Path();

  std::vector<std::string> separateWirePath(std::ifstream &inputFile);
  std::vector<std::tuple<int, int>> getPathOfString(std::string &inputString);

private:
  std::tuple<int, int> getNextXYPosition(std::string &pathElement);
  std::vector<std::string> splitPathElement(std::string &pathElement);
  std::string getStringFromCharacter(char singleChar);
};

#endif /* PATH_H_ */
