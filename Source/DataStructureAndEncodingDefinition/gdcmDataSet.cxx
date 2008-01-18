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
#include "gdcmDataSet.h"


namespace gdcm
{

std::string DataSet::GetPrivateCreator(const Tag &t) const
{
  Tag pc = t.GetPrivateCreator();
  if( pc.GetElement() )
    {
    const DataElement r(pc);
    ConstIterator it = DES.find(r);
    if( it == DES.end() )
      {
      // FIXME, could this happen ?
      return "";
      }
    const DataElement &de = *it;
    const Value &v = de.GetValue();
    const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
    std::ostringstream os;
    bv.WriteBuffer( os );
    return os.str();
    }
  return "";
}

} // end namespace gdcm

