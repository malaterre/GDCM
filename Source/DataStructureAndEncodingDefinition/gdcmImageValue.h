/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmImageValue_h
#define __gdcmImageValue_h

#include "gdcmImage.h"
#include "gdcmSmartPointer.h"
#include "gdcmTS.h"
#include "gdcmValue.h"

#include <vector>

namespace gdcm
{

/**
 * \brief Image from a gdcm::Value type
 * \note
 * Can be ByteValue or SequenceOfFragments and nothing else AFAIK
 */
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

