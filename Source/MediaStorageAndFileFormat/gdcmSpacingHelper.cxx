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
  case MediaStorage::CTImageStorage:
  case MediaStorage::MRImageStorage:
    // (0028,0030) DS [2.0\2.0]                                #   8, 2 PixelSpacing
    t = Tag(0x0028,0x0030);
    break;
  default:
    gdcmWarningMacro( "Do not handle: " << ms );
    t = Tag(0xffff,0xffff);
    break;
    }
  return t;
}

Tag SpacingHelper::GetZSpacingTagFromMediaStorage(MediaStorage const &ms)
{
  Tag t;

  switch(ms)
    {
  case MediaStorage::MRImageStorage:
    // (0018,0088) DS [3]                                      #   2, 1 SpacingBetweenSlices
    t = Tag(0x0018,0x0088);
    break;
  default:
    gdcmDebugMacro( "Do not handle: " << ms );
    t = Tag(0xffff,0xffff);
    break;
    }
  return t;
}

std::vector<double> SpacingHelper::GetSpacingValue(DataSet const & ds)
{
  std::vector<double> sp;
  MediaStorage ms;
  ms.SetFromDataSet(ds);
  assert( MediaStorage::IsImage( ms ) );

  Tag spacingtag = GetSpacingTagFromMediaStorage(ms);
  if( spacingtag != Tag(0xffff,0xffff) && ds.FindDataElement( spacingtag ) )
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
      abort();
      break;
      }
    }
  // Do Z:
  Tag zspacingtag = SpacingHelper::GetZSpacingTagFromMediaStorage(ms);
  if( zspacingtag != Tag(0xffff,0xffff) && ds.FindDataElement( zspacingtag ) )
    {
    const DataElement& de = ds.GetDataElement( zspacingtag );
    const Global &g = gdcm::GlobalInstance;
    const Dicts &dicts = g.GetDicts();
    const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
    const VR & vr = entry.GetVR();
    assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
    assert( entry.GetVM() == VM::VM1 );
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
        //assert( sp.size() == entry.GetVM() );
        }
      break;
    default:
      abort();
      break;
      }
    }

  return sp;
}

void SpacingHelper::SetSpacingValue(DataSet & ds, const double * spacing)
{
  MediaStorage ms;
  ms.SetFromDataSet(ds);
  assert( MediaStorage::IsImage( ms ) );

  Tag spacingtag = GetSpacingTagFromMediaStorage(ms);
  if( spacingtag != Tag(0xffff,0xffff) )
    {
    DataElement de( spacingtag );
    const Global &g = gdcm::GlobalInstance;
    const Dicts &dicts = g.GetDicts();
    const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
    const VR & vr = entry.GetVR();
    const VM & vm = entry.GetVM();
    assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
    switch(vr)
      {
    case VR::DS:
        {
        gdcm::Element<VR::DS,VM::VM1_n> el;
        el.SetLength( entry.GetVM().GetLength() );
        for( int i = 0; i < entry.GetVM().GetLength(); ++i)
          {
          el.SetValue( spacing[i], i );
          }
        assert( el.GetValue(0) == spacing[0] && el.GetValue(1) == spacing[1] );
        std::stringstream os;
        el.Write( os );
        de.SetByteValue( os.str().c_str(), os.str().size() );
        ds.Insert( de );
        }
      break;
    default:
      abort();
      }
    }

}


}
