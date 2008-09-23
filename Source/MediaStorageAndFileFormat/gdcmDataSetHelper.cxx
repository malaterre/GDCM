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
#include "gdcmDataSetHelper.h"
#include "gdcmFile.h"
#include "gdcmDataSet.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmAttribute.h"

namespace gdcm
{

VR DataSetHelper::ComputeVR(File const &file, DataSet const &ds, const Tag& tag)
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict();

  std::string strowner;
  const char *owner = 0;
  const Tag& t = tag;
  if( t.IsPrivate() && !t.IsPrivateCreator() )
    { 
    strowner = ds.GetPrivateCreator(t);
    owner = strowner.c_str();
    }
  const DictEntry &entry = dicts.GetDictEntry(t,owner);
  const VR &vr = entry.GetVR();
  const VM &vm = entry.GetVM();

  VR outvr;

  if( vr == VR::US_SS )
    {
    // I believe all US_SS VR derived from the value from 0028,0103 ... except 0028,0071
    if( t != Tag(0x0028,0x0071) )
      {
      // In case of SAX parser, we would have had to process Pixel Representation already:
      Tag pixelrep(0x0028,0x0103);
      assert( pixelrep < t );
      const DataSet &rootds = file.GetDataSet();
      assert( ds.FindDataElement( pixelrep ) );
      Attribute<0x0028,0x0103> at;
      at.SetFromDataElement( ds.GetDataElement( pixelrep ) );
      assert( at.GetValue() == 0 || at.GetValue() == 1 );
      if( at.GetValue() )
        {
        outvr = VR::SS;
        }
      else
        {
        outvr = VR::US;
        }
      }
    }

  return outvr;
}



}
