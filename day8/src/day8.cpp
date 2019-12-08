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
#define IMAGES 100

int main()
{
  std::ifstream ifile("input.txt");
  std::vector<std::vector<std::vector<int>>> decodedImages;

  CPictureDecoder cPicDec;

  cPicDec.setColSize(IMAGECOLS);
  cPicDec.setRowSize(IMAGEROWS);
  cPicDec.setImages(IMAGES);
  cPicDec.initImageMatrix(0);

  decodedImages = cPicDec.decodeImageFromInStream(ifile);

  // Output
  cPicDec.combineImageMatrix(decodedImages);

}
