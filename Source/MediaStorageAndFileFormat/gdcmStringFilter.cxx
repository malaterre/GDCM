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
#include "gdcmElement.h"
#include "gdcmByteValue.h"

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
  if( de.GetTag().IsPrivate() )
    {
    return NULL;
    }
  assert( de.GetTag().IsPublic() );
  const DictEntry &entry = dicts.GetDictEntry(de.GetTag());

  static std::string s;
  VR vr = entry.GetVR();
  if( de.GetVR() != VR::UN )
    {
    vr = de.GetVR();
    }
  if( VR::IsASCII( vr ) )
    {
    const ByteValue *bv = de.GetByteValue();
    assert( bv /*|| bv->IsEmpty()*/ );
    s = std::string( bv->GetPointer(), bv->GetLength() );
    return s.c_str();
    }
  else
    {
    const ByteValue *bv = de.GetByteValue();
    std::ostringstream os;
    if( bv )
      {
      VM::VMType vm = entry.GetVM();
      assert( vm == VM::VM1 );
      std::ostringstream os;
      switch(vr)
        {
      case VR::SS:
          {
          gdcm::Element<VR::SS,VM::VM1> el;
          el.Set( de.GetValue() );
          os << el.GetValue();
          s = os.str();
          return s.c_str();
          }
      case VR::US:
          {
          gdcm::Element<VR::US,VM::VM1> el;
          el.Set( de.GetValue() );
          os << el.GetValue();
          s = os.str();
          return s.c_str();
          }
      default:
        break;
        }
      }
    }
  return NULL;
}

}
