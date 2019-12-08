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
  void initImageMatrix(int initValue);
  std::vector<std::vector<int>> decodeImageFromInStream(istream& input);

private:
  unsigned mRowSize;
  unsigned mColSize;
  std::vector<std::vector<int> > mImageMatrix;
};

#endif // _PICTUREDECODER_
