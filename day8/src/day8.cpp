// --------------------------
// file : day1.cpp
// --------------------------

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

#include "picturedecoder.h"
using namespace std;

#define IMAGECOLS 25
#define IMAGEROWS 6

int main()
{
  std::ifstream ifile("input.txt");
  std::vector<std::vector<int>> decodedImage;

  CPictureDecoder cPicDec;

  cPicDec.setColSize(IMAGECOLS);
  cPicDec.setRowSize(IMAGEROWS);
  cPicDec.initImageMatrix(0);

  decodedImage = cPicDec.decodeImageFromInStream(ifile);

}
