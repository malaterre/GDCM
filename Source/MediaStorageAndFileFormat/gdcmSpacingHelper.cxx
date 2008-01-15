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
#include "gdcmSpacingHelper.h"
#include "gdcmMediaStorage.h"
#include "gdcmDataSet.h"
#include "gdcmGlobal.h"
#include "gdcmDictEntry.h"
#include "gdcmDicts.h"

namespace gdcm
{

Tag SpacingHelper::GetSpacingTagFromMediaStorage(MediaStorage const &ms)
{
  Tag t;

  switch(ms)
    {
  case MediaStorage::MRImageStorage:
    // (0028,0030) DS [2.0\2.0]                                #   8, 2 PixelSpacing
    t = Tag(0x0028,0x0030);
    break;
  default:
    t = Tag(0xffff,0xffff);
    break;
    }
  return t;
}

std::vector<double> SpacingHelper::GetSpacingValue(DataSet const & ds)
{
  std::vector<double> sp;
  const Tag tsopclassuid(0x0008, 0x0016);
  const ByteValue *sopclassuid = ds.GetDataElement( tsopclassuid ).GetByteValue();
  std::string sopclassuid_str(
    sopclassuid->GetPointer(),
    sopclassuid->GetLength() );
  assert( sopclassuid_str.find( ' ' ) == std::string::npos );
  MediaStorage ms = MediaStorage::GetMSType(sopclassuid_str.c_str());
  assert( MediaStorage::IsImage( ms ) );

  Tag spacingtag = GetSpacingTagFromMediaStorage(ms);
  if( ds.FindDataElement( spacingtag ) )
    {
    const DataElement& de = ds.GetDataElement( spacingtag );
    const Global &g = gdcm::GlobalInstance;
    const Dicts &dicts = g.GetDicts();
    const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
    const VR & vr = entry.GetVR();
    assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
    switch(vr)
      {
    case VR::DS:
        {
        gdcm::Element<VR::DS,VM::VM1_n> el;
        std::stringstream ss;
        const ByteValue *bv = de.GetByteValue();
        assert( bv );
        std::string s = std::string( bv->GetPointer(), bv->GetLength() );
        ss.str( s );
        el.SetLength( entry.GetVM().GetLength() * entry.GetVR().GetSizeof() );
        el.Read( ss );
        for(unsigned long i = 0; i < el.GetLength(); ++i) 
          sp.push_back( el.GetValue(i) );
        assert( sp.size() == entry.GetVM() );
        }
      break;
    default:
      break;
      }
    }

  return sp;
}

}
