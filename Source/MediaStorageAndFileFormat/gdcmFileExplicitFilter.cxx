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
#include "gdcmFileExplicitFilter.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFragment.h"
#include "gdcmGlobal.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include "gdcmDataSetHelper.h"

namespace gdcm
{

bool FileExplicitFilter::ProcessDataSet(DataSet &ds, Dicts const & dicts)
{
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

    //assert( de.GetVR() == VR::INVALID );
    VR cvr = DataSetHelper::ComputeVR(*F,ds, t);
    de.SetVR( cvr );
    SequenceOfItems *sqi = de.GetSequenceOfItems();
    if( de.GetByteValue() )
      {
      // all set
      assert( cvr != VR::SQ && cvr != VR::UN );
      }
    else if( sqi )
      {
      assert( cvr == VR::SQ );
      sqi->SetLengthToUndefined();
      de.SetVLToUndefined();
      // recursive
      SequenceOfItems::ItemVector::iterator it = sqi->Items.begin();
      for(; it != sqi->Items.end(); ++it)
        {
        //Item &item = const_cast<Item&>(*it);
        Item &item = *it;
        item.SetVLToUndefined();
        DataSet &nds = item.GetNestedDataSet();
        //const DataElement &deitem = item;
        ProcessDataSet(nds, dicts);
        }
      }
    else if( de.GetSequenceOfFragments() )
      {
      assert( cvr & VR::OB_OW );
      }
    ++it;
    ds.Replace( de );
    }
  return true;
}

bool FileExplicitFilter::Change()
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

  bool b = ProcessDataSet(ds, dicts);

  return b;
}


} // end namespace gdcm

