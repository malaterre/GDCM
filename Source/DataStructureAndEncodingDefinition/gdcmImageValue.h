
#ifndef __gdcmImageValue_h
#define __gdcmImageValue_h

#include "gdcmImage.h"
#include "gdcmSmartPointer.h"
#include "gdcmTS.h"

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

  void SetValue(Value const &v) {
    PixelData = SmartPointer<Value>( const_cast<Value*>(&v) );
  }
  
  // Helper to set Compression based on Transfer Syntax
  // It will find out the compression used and approrpietly call
  // the superclass SetCompressionType
  void SetCompressionFromTransferSyntax(TS const & ts)
    {
    Compression::Types type = ts.GetCompressionType();
    assert( type != Compression::UNKNOWN );
    SetCompressionType( type );
    }

private:
  typedef SmartPointer<Value> ValuePtr;
  ValuePtr PixelData; //copied from 7fe0,0010
};

} // end namespace gdcm

#endif //__gdcmImageValue_h

