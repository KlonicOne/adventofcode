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

void CPictureDecoder::setImages(unsigned images)
{
  this->mImages = images;
}

std::vector<std::vector<std::vector<int>>> CPictureDecoder::decodeImageFromInStream(istream &input)
{
  string codeElement;
  std::vector<int> codeVector;
  unsigned rowCounter = 0;
  unsigned colCounter = 0;
  unsigned imageCounter = 0;

  unsigned numZeros = 0;
  unsigned numOnes = 0;
  unsigned numTwos = 0;

  char c;

  while (input.get(c))
  {
    int numValue = (int) c - 48;
    // Fill matrix
    //std::cout << c;
    mImageMatrix[imageCounter][rowCounter][colCounter] = numValue;
    // Done quick and dirty directly in function
    if (numValue == 0)
    {
      numZeros++;
    }
    if (numValue == 1)
    {
      numOnes++;
    }
    if (numValue == 2)
    {
      numTwos++;
    }

    // Next row pos
    rowCounter++;
    // Check for next line
    if (rowCounter >= mRowSize)
    {
      rowCounter = 0;
      colCounter++;
      if (colCounter >= mColSize)
      {
        colCounter = 0;

        // Out the parameter
        std::cout << "Image: " << imageCounter << ", Zeros: " << numZeros << ", Ones: " << numOnes << ", Twos: " << numTwos
            << std::endl;

        numZeros = 0;
        numOnes = 0;
        numTwos = 0;

        imageCounter++;
        if (imageCounter >= mImages)
        {
          break;
        }
      }
    }
  }

  return (mImageMatrix);

}

void CPictureDecoder::initImageMatrix(int initValue)
{
  // Images
  mImageMatrix.resize(mImages);

  for (unsigned i = 0; i < mImageMatrix.size(); i++)
  {
    // Cols
    mImageMatrix[i].resize(mRowSize);

    // Rows and init with value
    for (unsigned j = 0; j < mImageMatrix[i].size(); j++)
    {
      mImageMatrix[i][j].resize(mColSize, initValue);
    }
  }
}

void CPictureDecoder::printImageMatrix(std::vector<std::vector<std::vector<int> > > imageMatrix)
{
  for (unsigned i = 0; i < mImages; i++)
  {
    for (unsigned j = 0; j < mRowSize; j++)
    {
      for (unsigned k = 0; k < mColSize; k++)
      {
        std::cout << imageMatrix[i][j][k];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
}

void CPictureDecoder::combineImageMatrix(std::vector<std::vector<std::vector<int> > > imageMatrix)
{
  std::vector<std::vector<int>> finalImage;
  int check = 0;
  // Init finalImage
  // Cols
  finalImage.resize(mRowSize);
  // Rows and init with value
  for (unsigned k = 0; k < finalImage.size(); k++)
  {
    // All are transparent at the beginning
    finalImage[k].resize(mColSize, 2);
  }

  for (unsigned i = 0; i < mImages; i++)
  {
    for (unsigned j = 0; j < mRowSize; j++)
    {
      for (unsigned k = 0; k < mColSize; k++)
      {
        // Take over values into final image
        if ((finalImage[j][k] == 2) && (imageMatrix[i][j][k] != 2))
        {
          finalImage[j][k] = imageMatrix[i][j][k];
          check++;
          std::cout << check << std::endl;
        }
      }
    }
  }

  // Print final image
  for (unsigned j = 0; j < mRowSize; j++)
  {
    for (unsigned k = 0; k < mColSize; k++)
    {
      std::cout << finalImage[j][k];
    }
    std::cout << std::endl;
  }

}
