#ifndef _PICTUREDECODER_
#define _PICTUREDECODER_

#include <iostream>
#include <vector>

using namespace std;

class CPictureDecoder
{
public:
  CPictureDecoder();
  ~CPictureDecoder();

  void setRowSize(unsigned rows);
  void setColSize(unsigned cols);
  void setImages(unsigned images);
  void initImageMatrix(int initValue);
  void printImageMatrix(std::vector<std::vector<std::vector<int>>> imageMatrix);
  void combineImageMatrix(std::vector<std::vector<std::vector<int>>> imageMatrix);
  std::vector<std::vector<std::vector<int>>> decodeImageFromInStream(istream& input);

private:
  unsigned mRowSize;
  unsigned mColSize;
  unsigned mImages;
  std::vector<std::vector<std::vector<int>>> mImageMatrix;
};

#endif // _PICTUREDECODER_
