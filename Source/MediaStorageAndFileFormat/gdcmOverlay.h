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
#ifndef __gdcmOverlay_h
#define __gdcmOverlay_h

#include "gdcmTypes.h"
#include "gdcmObject.h"

namespace gdcm
{
  
class OverlayInternal;
class ByteValue;
class DataSet;
/*
 *  TODO:
 *  Is there actually any way to recognize an overlay ? On images with multiple overlay I do not see
 *  any way to differenciate them (other than the group tag).
 */
class Overlay : public Object
{
public:
  Overlay();
  ~Overlay();
  void Print(std::ostream &) const;

  // Will traverse the dataset in search for overlay elements
  // this is an hybrid method I don't like having it attach to an Overlay object
  static unsigned int GetNumberOfOverlays(DataSet const & ds);

  void SetRows(unsigned short rows);
  unsigned short GetRows() const;
  void SetColumns(unsigned short columns);
  unsigned short GetColumns() const;
  void SetNumberOfFrames(unsigned int numberofframes);
  void SetDescription(const char* description);
  void SetType(const char* type);
  void SetOrigin(const signed short *origin);
  void SetFrameOrigin(unsigned short frameorigin);
  void SetBitsAllocated(unsigned short bitsallocated);
  void SetBitPosition(unsigned short bitposition);
  void SetOverlay(const char *array, unsigned int length);

  bool IsEmpty() const;

  void Decode(std::istream &is, std::ostream &os);

  void Decompress(std::ostream &os);

  Overlay(Overlay const &lut):Object(lut)
    {
    abort();
    }

private:
  OverlayInternal *Internal;
};

} // end namespace gdcm

#endif //__gdcmOverlay_h
