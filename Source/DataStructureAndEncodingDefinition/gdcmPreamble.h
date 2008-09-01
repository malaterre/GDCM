/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmPreamble_h
#define __gdcmPreamble_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief DICOM Preamble (Part 10)
 */
class GDCM_EXPORT Preamble
{
public:
  Preamble();
  ~Preamble();

  friend std::ostream &operator<<(std::ostream &_os, const Preamble &_val);

  // Clear
  void Clear();

  // Set Preamble to the default one
  void Valid();
  void Create();
  void Remove();

 // Read
  std::istream &Read(std::istream &is);

  // Write
  std::ostream const &Write(std::ostream &os) const;

  void Print(std::ostream &os) const;

  const char *GetInternal() const { return Internal; }

  bool IsEmpty() const { return !Internal; }

  Preamble(Preamble const &preamble)
    {
    (void)preamble;
    }
protected:
  //
  bool IsValid() const { 
    // is (IsValid == true) => Internal was read
    return true; 
  }

 
private:
  char *Internal; 
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const Preamble &val)
{
  os << val.Internal;
  return os;
}


} // end namespace gdcm

#endif //__gdcmPreamble_h

