/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDataSet.h"
#include "gdcmPrivateTag.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include "gdcmElement.h"
#include "gdcmGlobal.h"
#include "gdcmAttribute.h"


namespace gdcm
{
DataElement DataSet::DEEnd = DataElement( Tag(0xffff,0xffff) );

const DataElement& DataSet::GetDEEnd() const
{
  return DEEnd;
}

std::string DataSet::GetPrivateCreator(const Tag &t) const
{
  if( t.IsPrivate() && !t.IsPrivateCreator() )
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
      if( de.IsEmpty() ) return "";
      const ByteValue *bv = de.GetByteValue();
      assert( bv );
      std::string owner = std::string(bv->GetPointer(),bv->GetLength());
      // There should not be any trailing space character...
      // TODO: tmp.erase(tmp.find_last_not_of(' ') + 1);
      while( owner.size() && owner[owner.size()-1] == ' ' )
        {
        // osirix/AbdominalCT/36382443
        owner.erase(owner.size()-1,1);
        }
      assert( owner.size() == 0 || owner[owner.size()-1] != ' ' );
      return owner;
      }
    }
  return "";
}

Tag DataSet::ComputeDataElement(const PrivateTag & t) const
{
  gdcmDebugMacro( "Entering ComputeDataElement" );
  //assert( t.IsPrivateCreator() ); // No this is wrong to do the assert: eg. (0x07a1,0x000a,"ELSCINT1")
  // is valid because we have not yet done the mapping, so 0xa < 0x10 fails but might not later on
  const Tag start(t.GetGroup(), 0x0010 ); // First possible private creator (0x0 -> 0x9 are reserved...)
  const DataElement r(start);
  ConstIterator it = DES.lower_bound(r);
  const char *refowner = t.GetOwner();
  assert( refowner );
  bool found = false;
  while( it != DES.end() && it->GetTag().GetGroup() == t.GetGroup() && it->GetTag().GetElement() < 0x100 )
    {
    //assert( it->GetTag().GetOwner() );
    const ByteValue * bv = it->GetByteValue();
    assert( bv );
    //std::cout << std::string(bv->GetPointer(), bv->GetLength() ) << std::endl;
    //if( strcmp( bv->GetPointer(), refowner ) == 0 )
    std::string tmp(bv->GetPointer(),bv->GetLength());
    // trim trailing whitespaces:
    tmp.erase(tmp.find_last_not_of(' ') + 1);
    assert( tmp.size() == 0 || tmp[ tmp.size() - 1 ] != ' ' ); // FIXME
    if( System::StrCaseCmp( tmp.c_str(), refowner ) == 0 )
      {
      // found !
      found = true;
      break;
      }
    ++it;
    }
  gdcmDebugMacro( "In compute found is:" << found );
  if (!found) return GetDEEnd().GetTag();
  // else
  // ok we found the Private Creator Data Element, let's construct the proper data element
  Tag copy = t;
  copy.SetPrivateCreator( it->GetTag() );
  gdcmDebugMacro( "Compute found:" << copy );
  return copy;
}

bool DataSet::FindDataElement(const PrivateTag &t) const
{
  return FindDataElement( ComputeDataElement(t) );
}

const DataElement& DataSet::GetDataElement(const PrivateTag &t) const
{
  return GetDataElement( ComputeDataElement(t) );
}


void DataSet::SQ_XML_Write(std::ostream &os,const Dicts &dicts, DataElement de) const
{
  SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();
  if( !sqi ) return;
  assert(sqi);
  const DataSet &ds =(*this);
  SequenceOfItems::ItemVector::const_iterator it = sqi->Items.begin();
  for(; it != sqi->Items.end(); ++it)
    {
      const Item &item = *it;
      //*this = item.GetNestedDataSet();
      const DataElement &deitem = item;
      WriteXML(os);
      if( deitem.GetVL().IsUndefined() )
        {
        // print this const Tag itemDelItem(0xfffe,0xe00d);
        
        }
    }
  if( sqi->GetLength().IsUndefined() )
    {
    //print this const Tag seqDelItem(0xfffe,0xe0dd);
    
    }
    //*this = ds;
}

void DataSet::WriteXML(std::ostream &os) const
{
  
  const Global& G = GlobalInstance;
  const Dicts &dicts = G.GetDicts();
  //std::cout<< "I get called";
  DataElement de;
  VR ret;
  Iterator it = DES.begin();
  for( ; it != DES.end(); ++it)
    {
     de = *it;
     os << "\n<DicomAttribute   " ;
     ret=de.WriteXML(os, dicts);      
     
     if(ret == VR::SQ)
       SQ_XML_Write(os,dicts,de);
     os << "\n<\\DicomAttribute>";  
     
    }
    
}



} // end namespace gdcm
