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
#include "gdcmStringFilter.h"
#include "gdcmGlobal.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
StringFilter::StringFilter()
{
}
//-----------------------------------------------------------------------------
StringFilter::~StringFilter()
{
}

void StringFilter::SetDicts(const Dicts &dicts)
{
  abort(); // FIXME
}

const char* StringFilter::ToString(const DataElement& de)
{
  const gdcm::Global &g = gdcm::GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  assert( de.GetTag().IsPublic() );
  const DictEntry &entry = dicts.GetDictEntry(de.GetTag());

    const VR &vr = entry.GetVR();
  if( VR::IsASCII( vr ) )
    {
    const ByteValue *bv = de.GetByteValue();
    assert( bv );
    return bv->GetPointer();
    }
  else
    {
    const ByteValue *bv = de.GetByteValue();
    assert( bv );
    VM::VMType vm = entry.GetVM();
    assert( vm == VM::VM1 );
    std::ostringstream os;
    switch(vr)
      {
    case VR::US:
      break;
      
      }
    }
  return NULL;
}

}
