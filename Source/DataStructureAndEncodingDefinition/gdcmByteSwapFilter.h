/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmByteSwapFilter_h
#define __gdcmByteSwapFilter_h

#include "gdcmDataSet.h"

namespace gdcm
{

/*
 * In place byte-swapping of a dataset
 * FIXME: FL status ??
 */
class Dicts;
class GDCM_EXPORT ByteSwapFilter
{
public:
  ByteSwapFilter(DataSet& ds):DS(ds),ByteSwapTag(false) {}
  ~ByteSwapFilter();

  void UseDictAlways(bool use) {}

  // Allow user to pass in there own dicts
  void SetDicts(const Dicts &dicts);

  bool ByteSwap();
  void SetByteSwapTag(bool b) { ByteSwapTag = b; }

private:
  DataSet &DS;
  bool ByteSwapTag;
};

} // end namespace gdcm

#endif //__gdcmByteSwapFilter_h
