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
#ifndef __gdcmPDBHeader_h
#define __gdcmPDBHeader_h

#include "gdcmTypes.h"
#include "gdcmDataSet.h"
#include "gdcmPDBElement.h"

namespace gdcm
{
/**
 * \brief Class for PDBHeader
 *
 * Everything done in this code is for the sole purpose of writing interoperable 
 * software under Sect. 1201 (f) Reverse Engineering exception of the DMCA.
 * If you believe anything in this code violates any law or any of your rights, 
 * please contact us (gdcm-developers@lists.sourceforge.net) so that we can 
 * find a solution. 
 * 
 * \warning:
 * Everything you do with this code is at your own risk, since decoding process
 * was not written from specification documents.
 *
 * \WARNING: the API of this class is subject to change in the near future. DO NOT USE.
 *
 */
//-----------------------------------------------------------------------------
class DataElement;
class PrivateTag;
class GDCM_EXPORT PDBHeader
{
public :
  PDBHeader() {}
  ~PDBHeader() {}

  bool LoadFromDataElement(DataElement const &de);

  void Print(std::ostream &os) const;

  static const PrivateTag & GetPDBInfoTag();

  const PDBElement &GetPDBElementByName(const char *name);

private:
  int readprotocoldatablock(const char *input, size_t inputlen, bool verbose);
  std::vector<PDBElement> InternalPDBDataSet;
  PDBElement Dummy;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmPDBHeader_h
