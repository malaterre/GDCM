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
#include "gdcmImplicitToExplicitFilter.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFragment.h"
#include "gdcmGlobal.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
#include "gdcmVR.h"
#include "gdcmVM.h"

namespace gdcm
{

bool ImplicitToExplicitFilter::Change()
{
  if( !UseVRUN)
    {
    gdcmErrorMacro( "Not implemented" );
    return false;
    }
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict();

  DataSet &ds = F->GetDataSet();
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    DataElement de = *it;
    std::string strowner;
    const char *owner = 0;
    const Tag& t = de.GetTag();
    if( t.IsPrivate() && !t.IsPrivateCreator() )
      { 
      strowner = ds.GetPrivateCreator(t);
      owner = strowner.c_str();
      }
    const DictEntry &entry = dicts.GetDictEntry(t,owner);
    const VR &vr = entry.GetVR();
    const VM &vm = entry.GetVM();

    de.SetVR( vr );
    ++it;
    ds.Replace( de );
    }

  return true;
}


} // end namespace gdcm

