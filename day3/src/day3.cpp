/*
 * day3.cpp
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Grid.h"

// function declarations
void part1(Grid& cache);
void part2(Grid& cache);
void writeString(std::string filename, std::string data);
int getManhattanDistance(Vector2 pos1, Vector2 pos2);

// used variable
std::vector<InputChain> getInput(std::string filename);

int main(int argc, char* argv[])
{
  Grid cache; // new grid
  std::cout << "Start program" << std::endl;

  // call part 1 and 2
  part1(cache);
  //part2(cache);
}

void part1(Grid& grid)
{
  std::vector<InputChain> input = getInput("input.txt");
  input[0].owner = WIRE1;
  input[1].owner = WIRE2;

  std::cout << "Walking Paths...\n";

  grid.walkPath(input[0]);
  grid.walkPath(input[1]);

  std::cout << "2 Paths Walked. New Grid Size: " << grid.getGridSize().x << " " << grid.getGridSize().y << "\n";
  std::cout << "Searching for Overlaps...\n";

  std::vector<std::vector<Field>>& result = grid.getGrid();
  std::vector<Vector2> validOverlaps;

  for (int x = 0; x < grid.getGridSize().x; x++)
  {
    for (int y = 0; y < grid.getGridSize().y; y++)
    {
      if (result[x][y].owner == OVERLAP)
      {
        Vector2 n;
        n.x = x;
        n.y = y;

        validOverlaps.push_back(n);
      }
    }
  }

  std::cout << "Searching Closest Overlap...\n";

  int closestDistance = -1;
  Vector2 center = grid.getCenterPort();

  for (Vector2 vec : validOverlaps)
  {
    int distance = getManhattanDistance(center, vec);
    if (closestDistance == -1 || distance < closestDistance)
    {
      closestDistance = distance;
    }
  }

  std::cout << "Closest Overlap Distance: " << closestDistance << "\n";

  /*std::cout << "Writing Output...\n";
   writeString("output.txt", grid.renderAscii());*/
}

void part2(Grid& grid)
{
  std::cout << "Calculating Results...\n";
  std::vector<std::vector<Field>>& result = grid.getGrid();

  int fewestSteps = -1;
  for (int x = 0; x < grid.getGridSize().x; x++)
  {
    for (int y = 0; y < grid.getGridSize().y; y++)
    {
      if (result[x][y].owner == OVERLAP)
      {
        int steps = result[x][y].nWIRE1 + result[x][y].nWIRE2;
        if (fewestSteps == -1 || steps < fewestSteps)
        {
          fewestSteps = steps;
        }
      }
    }
  }

  std::cout << "Fewest Steps: " << fewestSteps << "\n";
}

std::vector<InputChain> getInput(std::string filepath)
{
  std::vector<InputChain> ret;
  std::string line;
  std::ifstream file(filepath);

  if (!file.is_open())
  {
    std::cout << "Failed opening file: " << filepath << "\n";
    file.close();
    return ret;
  }

  while (getline(file, line))
  {
    InputChain chain;
    std::istringstream iss(line);
    std::string val;
    while (getline(iss, val, ','))
    {
      Direction dir;
      switch (val[0])
      {
      case 'U':
        dir = UP;
        break;
      case 'D':
        dir = DOWN;
        break;
      case 'L':
        dir = LEFT;
        break;
      case 'R':
        dir = RIGHT;
        break;
      }

      Movement mov;
      mov.dir = dir;
      mov.distance = stoi(val.substr(1, val.size() - 1));
      chain.movements.push_back(mov);
    }

    ret.push_back(chain);
  }

  file.close();
  return ret;
}

void writeString(std::string filename, std::string data)
{
  std::ofstream ofs;
  ofs.open(filename);
  ofs.write(data.c_str(), data.size());
  ofs.close();
}

int getManhattanDistance(Vector2 pos1, Vector2 pos2)
{
  return abs((pos1.x - pos2.x)) + abs((pos1.y - pos2.y));
}

