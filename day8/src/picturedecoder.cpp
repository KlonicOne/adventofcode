/*
 * picturedecoder.cpp
 */

#include "picturedecoder.h"

#include <math.h>

// Constructor
CPictureDecoder::CPictureDecoder()
{
}

// Destructor
CPictureDecoder::~CPictureDecoder(void)
{
}

void CPictureDecoder::setRowSize(unsigned rows)
{
  this->mRowSize = rows;
}

void CPictureDecoder::setColSize(unsigned cols)
{
  this->mColSize = cols;
}

std::vector<std::vector<int> > CPictureDecoder::decodeImageFromInStream(istream &input)
{
  string codeElement;
  std::vector<int> codeVector;
  unsigned rowCounter = 0;
  unsigned colCounter = 0;

  char c;

  while (input.get(c))
  {
    // Fill matrix
    std::cout << c;
    mImageMatrix[rowCounter][colCounter] = (int)c - 48;

    // Next row pos
    rowCounter++;
    // Check for next line
    if(rowCounter >= mRowSize)
    {
      rowCounter = 0;
      colCounter++;
      if(colCounter >= mColSize)
      {
        break;
      }
    }
  }

  return (mImageMatrix);

}

void CPictureDecoder::initImageMatrix(int initValue)
{
  // Cols
  mImageMatrix.resize(mRowSize);
  // Rows and init with value
  for (unsigned i = 0; i < mImageMatrix.size(); i++)
  {
    mImageMatrix[i].resize(mColSize, initValue);
  }
}
