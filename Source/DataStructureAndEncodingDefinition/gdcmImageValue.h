
#ifndef __gdcmImageValue_h
#define __gdcmImageValue_h

#include "gdcmImage.h"
#include "gdcmSmartPointer.h"

#include <vector>

namespace gdcm
{

/**
 * \brief Image from a gdcm::Value type
 * \note
 * Can be ByteValue or SequenceOfFragments and nothing else AFAIK
 */
class Value;
class GDCM_EXPORT ImageValue : public Image
{
public:
  ImageValue():PixelData(0) {}
  ~ImageValue() {}

  bool GetBuffer(char *buffer) const;

private:
  typedef SmartPointer<Value> ValuePtr;
  ValuePtr PixelData; //copied from 7fe0,0010
};

} // end namespace gdcm

#endif //__gdcmImageValue_h

