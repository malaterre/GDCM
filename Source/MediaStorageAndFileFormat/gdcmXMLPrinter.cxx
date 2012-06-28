/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/* TO DO

1) Checking characters
2) Handling PN

*/
#include "gdcmXMLPrinter.h"
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
#include "gdcmDataSetHelper.h"
#include "gdcmUIDGenerator.h"

#include "gdcmDataSet.h"

#include <typeinfo> // for typeid


namespace gdcm
{
//-----------------------------------------------------------------------------
XMLPrinter::XMLPrinter():PrintStyle(XMLPrinter::OnlyUUID),F(0)
{
}

//-----------------------------------------------------------------------------
XMLPrinter::~XMLPrinter()
{
}

// TODO / FIXME
// SIEMENS_GBS_III-16-ACR_NEMA_1.acr is a tough kid: 0009,1131 is supposed to be VR::UL, but
// there are only two bytes...

VR XMLPrinter::PrintDataElement(std::ostream &os, const Dicts &dicts, const DataSet & ds,
  const DataElement &de)
  
{

  const ByteValue *bv = de.GetByteValue();
  const SequenceOfItems *sqi = 0; //de.GetSequenceOfItems();
  const Value &value = de.GetValue();
  const SequenceOfFragments *sqf = de.GetSequenceOfFragments();

  std::string strowner;
  const char *owner = 0;
  const Tag& t = de.GetTag();
  UIDGenerator UIDgen;
  
  const DictEntry &entry = dicts.GetDictEntry(t,owner);
  const VR &vr = entry.GetVR();
  const VM &vm = entry.GetVM();
  const char *name = entry.GetName();
  bool retired = entry.GetRetired();
  
  const VR &vr_read = de.GetVR();
  const VL &vl_read = de.GetVL();
  
  //Printing Tag
  os << " tag = \"" << std::hex << std::setw(4) << std::setfill('0') <<
      t.GetGroup() <<  std::setw(4) << ((uint16_t)(t.GetElement() << 8) >> 8) << "\"" << std::dec;
      
  if( t.IsPrivate() && !t.IsPrivateCreator() )
    {
    strowner = ds.GetPrivateCreator(t);
    owner = strowner.c_str();
    os << " PrivateCreator = \"" << owner << "\" ";
    }
  
  
  VR refvr;
  
  // always prefer the vr from the file:
  if( vr_read == VR::INVALID )
    {
    refvr = vr;
    }
  else if ( vr_read == VR::UN && vr != VR::INVALID ) // File is explicit, but still prefer vr from dict when UN
    {
    refvr = vr;
    }
  else // cool the file is Explicit !
    {
    refvr = vr_read;
    }
  if( refvr.IsDual() ) // This mean vr was read from a dict entry:
    {
    refvr = DataSetHelper::ComputeVR(*F,ds, t);
    }

  assert( refvr != VR::US_SS );
  assert( refvr != VR::OB_OW );

  if( dynamic_cast<const SequenceOfItems*>( &value ) )
    {
    sqi = de.GetValueAsSQ();
    refvr = VR::SQ;
    assert( refvr == VR::SQ );
    }
#if 0
  else if( vr == VR::SQ && vr_read != VR::SQ )
    {
    sqi = de.GetValueAsSQ();
    refvr = VR::SQ;
    assert( refvr == VR::SQ );
    }
#endif

  if( (vr_read == VR::INVALID || vr_read == VR::UN ) && vl_read.IsUndefined() )
    {
    assert( refvr == VR::SQ );
    }

//  if( vr_read == VR::SQ || vr_read == VR::UN )
//    {
//    sqi = de.GetValueAsSQ();
//    }
  if( vr != VR::INVALID && (!vr.Compatible( vr_read ) || vr_read == VR::INVALID || vr_read == VR::UN ) )
    {
    assert( vr != VR::INVALID );
    
    /*
    No need as will save only the VR to which it is stored by GDCM
    
    if( vr == VR::US_SS || vr == VR::OB_OW )
      {
      os << "(" << vr << " => " << refvr << ") ";
      }
    else
      {
      os << "(" << vr << ") ";
      }
     */ 
    
    }
  else if( sqi /*de.GetSequenceOfItems()*/ && refvr == VR::INVALID )
    {
    // when vr == VR::INVALID and vr_read is also VR::INVALID, we have a seldom case where we can guess
    // the vr
    // eg. CD1/647662/647663/6471066 has a SQ at (2001,9000)

    assert( refvr == VR::INVALID );
    refvr = VR::SQ;
    }

  
  // Printing the VR -- Value Representation
  os << " VR = \"" << refvr << "\" ";
  
  
  
  
  // Add the keyword attribute :  
    
  os <<"keyword = \"";  
    
    
  if( name && *name )
    {
    
    /*  No owner */
    if( t.IsPrivate() && (owner == 0 || *owner == 0 ) && !t.IsPrivateCreator() )
      {
      
      os << name;
      
      }
    
    /* retired element */
    else if( retired )
      {
      
      assert( t.IsPublic() || t.GetElement() == 0x0 ); // Is there such thing as private and retired element ?
      os << name;
      
      }
      
    else
      {
      
      os << name;//Public element
      
      }
    }
    
  else
    {
    
    if( t.IsPublic() )
      {
      
      //An unknown public element.
      
      }
    os << "GDCM:UNKNOWN"; // Special keyword
    
    }  
   os << "\">\n   ";  
    
#define StringFilterCase(type) \
  case VR::type: \
    { \
      Element<VR::type,VM::VM1_n> el; \
      if( !de.IsEmpty() ) { \
      el.Set( de.GetValue() ); \
      if( el.GetLength() ) { \
      os << "<Value number = \"1\" >" ;os << "" << el.GetValue();os << "</Value>\n"; \
      VL l = (long) el.GetLength(); \
      for(unsigned long i = 2; i <= l; ++i) \
      { \
      os << "<Value number = \"" << i << "\" >" ;\
      os << "\\" << el.GetValue(i);os << "</Value>\n";} \
      os << ""; } \
      else { if( de.IsEmpty() )  \
                 ; } } \
      else { assert( de.IsEmpty());  } \
    } break    

/*
#define StringFilterCase(type) \
  case VR::type: \
    { \
      Element<VR::type,VM::VM1_n> el; \ 
      if( !de.IsEmpty() ) \
      { \      
        el.Set( de.GetValue() ); \
          if( el.GetLength() ) \
          { \
            os << "" << el.GetValue(); \
            VL l = (long) el.GetLength(); \
            for(unsigned long i = 1; i < l; ++i) \
            {\
            os << "<Value number = \"" << i << "\" >" ;\
            os << "\\" << el.GetValue(i); \
            os << "</Value>"; \
            }             \
          }          \
      }      \
      else { assert( de.IsEmpty());}      \
    }break \
*/

  // Print Value now:
  
  //Handle PN first, acc. to Standard
  if(refvr == VR::PN)
    {
    if( bv )
      {        
      bv->PrintPN_XML(os);    //new function to print each value in new child tag  
      }
    else
      {
      assert( de.IsEmpty() );      
      }

    }
  else if( refvr & VR::VRASCII )
    {
    //assert( !sqi && !sqf);
    assert(!sqi);
    if( bv )
      {              
      bv->PrintASCII_XML(os);    //new function to print each value in new child tag  
      }
    else
      {
      assert( de.IsEmpty() );      
      }
    }
  
  else
    {
    assert( refvr & VR::VRBINARY || (vr == VR::INVALID && refvr == VR::INVALID) );
    
    std::string s;
    switch(refvr)
      {
    
      StringFilterCase(AT);
      StringFilterCase(FL);
      StringFilterCase(FD);      
      StringFilterCase(OF);      
      StringFilterCase(SL);      
      StringFilterCase(SS);
      StringFilterCase(UL);      
      StringFilterCase(US);
        
    case VR::OB:
    case VR::OW:
    case VR::OB_OW:
    case VR::UN:
    case VR::US_SS_OW: 
      {
        
        if ( bv )
          {
                    
          if(PrintStyle)
          {
             bv->PrintHex_XML(os);
          }
          
          else          
          {
             os << "<BulkData UID = \""<<      
             UIDgen.Generate() << "\" />";  
          }
          
          
          }
          
        else if ( sqf )
          {
          assert( t == Tag(0x7fe0,0x0010) );          
          }
          
        else if ( sqi )
          {          
          gdcmErrorMacro( "Should not happen: VR=UN but contains a SQ" );          
          }
          
        else
          {
          assert( !sqi && !sqf );
          assert( de.IsEmpty() );          
          }
          
        }
      break;
    
    case VR::US_SS:
      assert( refvr != VR::US_SS );
      break;
      
    case VR::SQ:
      if( !sqi && !de.IsEmpty() && de.GetValue().GetLength() )
        {
        }
      else
        {
        if( vl_read.IsUndefined() )
          {
          //os << "(Sequence with undefined length)";
          }
        else
          {
          //os << "(Sequence with defined length)";
          }
        }
      break;
      
    case VR::INVALID:
        
        
        if( bv )
          {
            
            if(PrintStyle)
             bv->PrintHex_XML(os);
            else
             {
             os << "<BulkData UID = \""<<      
             UIDgen.Generate() << "\" />";  
             }
            
            
          }
          
        else
          {
          assert( !sqi && !sqf );
          assert( de.IsEmpty() );          
          }        
      break;
      
    default:
      assert(0 && "No Match! Impossible!!");
      break;
      }
    
    }
    
  
  os << "\n";
  return refvr;
}

void XMLPrinter::PrintSQ(const SequenceOfItems *sqi, std::ostream & os)
{
      
  if( !sqi ) return;
  SequenceOfItems::ItemVector::const_iterator it = sqi->Items.begin();
  for(; it != sqi->Items.end(); ++it)
    {
    const Item &item = *it;
    const DataSet &ds = item.GetNestedDataSet();
    const DataElement &deitem = item;
        
    os << "<DicomAttribute  tag = \"";
    os << std::hex << std::setw(4) << std::setfill('0') <<
      deitem.GetTag().GetGroup() <<  std::setw(4) << ((uint16_t)(deitem.GetTag().GetElement() << 8) >> 8) << "\" ";
    os << " VR = \"UN\"  keyword = ";     

    if( deitem.GetVL().IsUndefined() )
      {
      os << "\"Item with undefined length\"";
      }
    else
      {
      os << "\"Item with defined length\"";
      }
    os << ">\n";
    PrintDataSet(ds, os);
    if( deitem.GetVL().IsUndefined() )
      {
            os << "<DicomAttribute    tag = \"fffee00d\"  VR = \"UN\" keyword = \"Item Delimitation Item\"/>\n";
      }
    os << "</DicomAttribute>\n\n";  
    }
  if( sqi->GetLength().IsUndefined() )
    {
        os << "<DicomAttribute    tag = \"fffee0dd\"  VR = \"UN\" keyword = \"Sequence Delimitation Item\"/>\n";
    }
}

void XMLPrinter::PrintDataSet(const DataSet &ds, std::ostream &os)
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict(); (void)d;

  DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;

    //const ByteValue *bv = de.GetByteValue();
    const SequenceOfFragments *sqf = de.GetSequenceOfFragments();

    
    os << "<DicomAttribute  " ;
    VR refvr = PrintDataElement(os, dicts, ds, de);

    if( refvr == VR::SQ /*|| sqi*/ )
      {
      
      
      SmartPointer<SequenceOfItems> sqi2 = de.GetValueAsSQ();
      PrintSQ(sqi2, os);
     
      }
    else if ( sqf )
      {
      
      const BasicOffsetTable & table = sqf->GetTable();
      os << "<DicomAttribute  ";
      PrintDataElement(os,dicts,ds,table);
      os << "</DicomAttribute>\n\n";
      unsigned int numfrag = sqf->GetNumberOfFragments();
      for(unsigned int i = 0; i < numfrag; i++)
        
        {        
        const Fragment& frag = sqf->GetFragment(i);
        os << "<DicomAttribute  ";
        PrintDataElement(os,dicts,ds,frag); 
        os << "</DicomAttribute>\n\n";       
        }
        
      os << "<DicomAttribute    tag = \"fffee0dd\"  VR = \"UN\" keyword = \"Sequence Delimitation Item\"/>\n";
      }
    else
      {
      // This is a byte value, so it should have been already treated
      }
    
    os << "</DicomAttribute>\n\n";
    }
}



//-----------------------------------------------------------------------------
void XMLPrinter::Print(std::ostream& os)
{
  os << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
  os << "<NativeDicomModel xml:space=\"preserve\">\n\n";
   
  const DataSet &ds = F->GetDataSet();
  
  PrintDataSet(ds, os);
  
  os << "\n</NativeDicomModel>";  
}

}//end namespace gdcm
