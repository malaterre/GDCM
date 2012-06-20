/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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

#include "gdcmDataSet.h"

#include <typeinfo> // for typeid


namespace gdcm
{
//-----------------------------------------------------------------------------
XMLPrinter::XMLPrinter():PrintStyle(XMLPrinter::LOADBULKDATA),F(0)
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
  
  if( t.IsPrivate() && !t.IsPrivateCreator() )
    {
    strowner = ds.GetPrivateCreator(t);
    owner = strowner.c_str();
    }
    
  const DictEntry &entry = dicts.GetDictEntry(t,owner);
  const VR &vr = entry.GetVR();
  const VM &vm = entry.GetVM();
  const char *name = entry.GetName();
  bool retired = entry.GetRetired();
  
  const VR &vr_read = de.GetVR();
  const VL &vl_read = de.GetVL();
  
  //Printing Tag
  os << " tag = \"" << std::hex << std::setw(4) << std::setfill('0') <<
      t.GetGroup() <<  std::setw(4) << ((uint16_t)(t.GetElement() << 8) >> 8) << "\" ";
  
  
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
    // No owner case !
    if( t.IsPrivate() && (owner == 0 || *owner == 0 ) && !t.IsPrivateCreator() )
      {
      
      os << name;
      
      }
    // retired element
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
      // What ? A public element that we do not know about !!!
      
      }
    os << "GDCM:UNKNOWN"; // Special keyword
    
    }  
   os << "\">\n   ";  
    
    
    
    
    
    
    
    

  // Print Value now:
  
  if( refvr & VR::VRASCII )
    {
    //assert( !sqi && !sqf);
    assert(!sqi);
    if( bv )
      {
      VL l = bv->GetLength();         
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
      {/*
      StringFilterCase(AT);
      StringFilterCase(FL);
      StringFilterCase(FD);
      //StringFilterCase(OB);
      StringFilterCase(OF);
      //StringFilterCase(OW);
      StringFilterCase(SL);
      //StringFilterCase(SQ);
      StringFilterCase(SS);
      StringFilterCase(UL);
      //StringFilterCase(UN);
      StringFilterCase(US);
      //StringFilterCase(UT);*/
    case VR::OB:
    case VR::OW:
    case VR::OB_OW:
    case VR::UN:
    case VR::US_SS_OW: // TODO: check with ModalityLUT.dcm
      /*
      VR::US_SS_OW:
      undefined_length_un_vr.dcm
      GDCMFakeJPEG.dcm
      PhilipsWith15Overlays.dcm
       */
        {
        if ( bv )
          {
          //VL l = std::min( bv->GetLength(), MaxPrintLength );
          //VL l = std::min( (int)bv->GetLength(), 0xF );
          //int width = (vr == VR::OW ? 4 : 2);
          //os << std::hex << std::setw( width ) << std::setfill('0');
          //bv->PrintHex(os, bv->GetLength()/*MaxPrintLength / 4*/);
          //os << std::dec;
          }
        else if ( sqf )
          {
          assert( t == Tag(0x7fe0,0x0010) );
          //os << *sqf;
          }
        else if ( sqi )
          {
          // gdcmDataExtra/gdcmSampleData/images_of_interest/illegal_UN_stands_for_SQ.dcm
          gdcmErrorMacro( "Should not happen: VR=UN but contains a SQ" );
          //os << *sqi;
          }
        else
          {
          assert( !sqi && !sqf );
          assert( de.IsEmpty() );
          
          }
        }
      break;
    case VR::US_SS:
      // impossible...
      assert( refvr != VR::US_SS );
      break;
    case VR::SQ:
      if( !sqi /*!de.GetSequenceOfItems()*/ && !de.IsEmpty() && de.GetValue().GetLength() )
        {
        // This case is insane, this is an implicit file, with a defined length SQ.
        // Since this is a private element there is no way to guess that, and to
        // make it even worse the binary blob does not start with item start...
        // Bug_Philips_ItemTag_3F3F.dcm
        //os << GDCM_TERMINAL_VT100_BACKGROUND_RED;
        //bv->PrintHex(os, MaxPrintLength / 4);
        //os << GDCM_TERMINAL_VT100_NORMAL;
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
      // Let's be a little more helpful and try to print anyway when possible:
    case VR::INVALID:
        {
        
        if( bv )
          {
          VL l = bv->GetLength();
          if( bv->IsPrintable(l) )
            {
           
            bv->PrintASCII(os,l);
           
             }
          else if( t == Tag(0xfffe,0xe000) );// bv->PrintHex(os, bv->GetLength()/*MaxPrintLength / 8*/);
          else
            {
            //os << GDCM_TERMINAL_VT100_INVERSE;
            // << "(non-printable character found)"
            //bv->PrintHex(os, bv->GetLength()/*MaxPrintLength / 8*/);
            //os << GDCM_TERMINAL_VT100_NORMAL;
            }
          }
        else
          {
          assert( !sqi && !sqf );
          assert( de.IsEmpty() );
          //os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL;
          }
        }

        
      break;
    default:
      //assert(0);CHECK
      break;
      }
    
    }
    
  /*
  ***************VL AND VM PRINTING NOT REQUIRED************
  // Append the VL
  if( vl_read.IsUndefined() )
    {
    os << "u/l";
    }
  else
    {
    os << std::dec << vl_read;
    }
  if( vl_read.IsOdd() )
    {
    os << GDCM_TERMINAL_VT100_FOREGROUND_GREEN;
    os << " (" << (vl_read + 1) << ")";
    os << GDCM_TERMINAL_VT100_NORMAL;
    }
  os << ",";
  // Append the VM
  if( vm != VM::VM0 )
    {
    os << vm;
    }
  else
    {
    os << GDCM_TERMINAL_VT100_FOREGROUND_RED;
    os << "?";
    os << GDCM_TERMINAL_VT100_NORMAL;
    }
  VM guessvm = VM::VM0;
  if( refvr & VR::VRASCII )
    {
    assert( refvr != VR::INVALID );
    assert( refvr & VR::VRASCII );
    if( bv )
      {
      unsigned int count = VM::GetNumberOfElementsFromArray(bv->GetPointer(), bv->GetLength());
      guessvm = VM::GetVMTypeFromLength(count, 1); // hackish...
      }
    }
  else if( refvr & VR::VRBINARY )
    {
    assert( refvr != VR::INVALID );
    assert( refvr & VR::VRBINARY );
    if( refvr & VR::OB_OW || refvr == VR::SQ )
      {
      guessvm = VM::VM1;
      }
    else if ( refvr == VR::UN && sqi )
      {
      // This is a SQ / UN
      guessvm = VM::VM1;
      }
    else if( bv )
      {
      guessvm = VM::GetVMTypeFromLength(bv->GetLength(), refvr.GetSize() );
      }
    else
      {
      if( de.IsEmpty() ) guessvm = VM::VM0;
      else assert( 0 && "Impossible" );
      }
    }
  else if( refvr == VR::INVALID )
    {
    refvr = VR::UN;
    guessvm = VM::VM1;
    }
  else
    {
    // Burst into flames !
    assert( 0 && "Impossible happen" );
    }
  if( !vm.Compatible( guessvm ) )
    {
    os << GDCM_TERMINAL_VT100_FOREGROUND_RED;
    os << " (" << guessvm << ") ";
    os << GDCM_TERMINAL_VT100_NORMAL;
    }
  */
  os << "\n";
  return refvr;
}

void XMLPrinter::PrintSQ(const SequenceOfItems *sqi, std::ostream & os)
{
  
  /* RESEARCH ABOUT ITEM START END TAGS, ADD XML NODES APPROPRIATELY */
  
  if( !sqi ) return;
  SequenceOfItems::ItemVector::const_iterator it = sqi->Items.begin();
  for(; it != sqi->Items.end(); ++it)
    {
    const Item &item = *it;
    const DataSet &ds = item.GetNestedDataSet();
    const DataElement &deitem = item;
    
    os << deitem.GetTag();
    os << " ";
    os << "na"; //deitem.GetVR();
    os << " ";
    if( deitem.GetVL().IsUndefined() )
      {
      os << "(Item with undefined length)";
      }
    else
      {
      os << "(Item with defined length)";
      }
    os << "\n";
    PrintDataSet(ds, os);
    if( deitem.GetVL().IsUndefined() )
      {
      const Tag itemDelItem(0xfffe,0xe00d);
      os << itemDelItem << "\n";
      }
    }
  if( sqi->GetLength().IsUndefined() )
    {
    const Tag seqDelItem(0xfffe,0xe0dd);
    os << seqDelItem << "\n";
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

    //std::ostringstream os;
    os << "\n<DicomAttribute   " ;
    VR refvr = PrintDataElement(os, dicts, ds, de);

    if( refvr == VR::SQ /*|| sqi*/ )
      {
      //SmartPointer<SequenceOfItems> sqi2 = DataSetHelper::ComputeSQFromByteValue( *F, ds, de.GetTag() );
      SmartPointer<SequenceOfItems> sqi2 = de.GetValueAsSQ();
      PrintSQ(sqi2, os);
      /*
      const SequenceOfItems *sqi = de.GetSequenceOfItems();
      if( sqi ) // empty SQ ?
      {
      assert( sqi );
      PrintSQ(sqi, os, indent);
      }
      else
      {
      if( !de.IsEmpty() )
      {
      // Ok so far we know:
      // 1. VR is SQ sqi == NULL
      // 2. DataElement is not empty ...
      // => This is a VR:UN or Implicit SQ with defined length.
      // let's try to interpret this sequence
      SequenceOfItems *sqi2 = DataSetHelper::ComputeSQFromByteValue( *F, ds, de.GetTag() );
      if(sqi2) PrintSQ(sqi2, os, indent);
      delete sqi2;
      }
      }
       */
      }
    else if ( sqf )
      {
      
      const BasicOffsetTable & table = sqf->GetTable();
     
      PrintDataElement(os,dicts,ds,table);
      unsigned int numfrag = sqf->GetNumberOfFragments();
      for(unsigned int i = 0; i < numfrag; i++)
        
        {        
        const Fragment& frag = sqf->GetFragment(i);
        PrintDataElement(os,dicts,ds,frag);        
        }
        
      const Tag seqDelItem(0xfffe,0xe0dd);
      VL zero = 0;
      os << seqDelItem;
      os << " " << zero << "\n";
      }
    else
      {
      // This is a byte value, so it should have been already treated
      }
    
    os << "\n</DicomAttribute>";
    }
}










//-----------------------------------------------------------------------------
void XMLPrinter::Print(std::ostream& os)
{
  os << "# Dicom-File-Format\n";
  os << "\n";
  os << "# Dicom-Meta-Information-Header\n";
  os << "# Used TransferSyntax: \n";

  
  /*os << "\n# Dicom-Data-Set\n";
  os << "# Used TransferSyntax: ";
  const TransferSyntax &metats = meta.GetDataSetTransferSyntax();
  os << metats;
  os << std::endl;     ADD META INFO FOR XML here*/
  
  const DataSet &ds = F->GetDataSet();
  
  PrintDataSet(ds, os);
  
}

}
