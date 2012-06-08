/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDataElement.h"

#include "gdcmByteValue.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmTrace.h"

/*Need to access Dictionary to write Keyword attribute in WriteXML() */

#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmGroupDict.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include "gdcmElement.h"
#include "gdcmGlobal.h"
#include "gdcmAttribute.h"



namespace gdcm
{
  void DataElement::SetVLToUndefined() {
    assert( VRField == VR::SQ || VRField == VR::INVALID
      || (VRField == VR::UN /*&& IsUndefinedLength()*/ ) );
    SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if( sqi )
      {
      sqi->SetLengthToUndefined();
      assert( GetValueAsSQ()->IsUndefinedLength() );
      }
    ValueLengthField.SetToUndefined();
  }

  /*
	inline std::ostream& operator<<(std::ostream &os, const DataElement &val)
{
  os << val.TagField;
  os << "\t" << val.VRField;
  os << "\t" << val.ValueLengthField;
  if( val.ValueField )
    {
    val.ValueField->Print( os << "\t" );
    }
  return os;
}


  */

  VR DataElement::WriteXML(std::ostream &os,const Dicts &dicts)
  {

     const Tag& t = GetTag();
     const Value &value = GetValue();
     const DictEntry &entry = dicts.GetDictEntry(t,NULL);//private owner correction needed
     const VR &vr_dict = entry.GetVR(); // read from dictionary
     const VM &vm_dict = entry.GetVM();
     const char *name = entry.GetName();
     bool retired = entry.GetRetired();
     const ByteValue *bv = GetByteValue();
     const SequenceOfItems *sqi = 0; //de.GetSequenceOfItems();
     const VR &vr_read = GetVR(); // read from data element
     const VL &vl_read = GetVL();
     
     std::string strowner;
     const char *owner = 0;
     
     /*if( t.IsPrivate() && !t.IsPrivateCreator() )
    {
    strowner = ds.GetPrivateCreator(t);
    owner = strowner.c_str();
    }*/
    
    //Printing Tag
    os << "tag = \"" << std::hex << std::setw(4) << std::setfill('0') <<
      t.GetGroup() <<  std::setw(4) << ((uint16_t)(t.GetElement() << 8) >> 8) << "\" ";
      

    
    
    VR refvr;
  
    if( vr_read == VR::INVALID )
    {
    refvr = vr_dict;
    }
    else if ( vr_read == VR::UN && vr_dict != VR::INVALID ) // File is explicit, but still prefer vr from dict when UN
    {
    refvr = vr_dict;
    }
    else // cool the file is Explicit !
    {
    refvr = vr_read;
    }

    assert( refvr != VR::US_SS );
    assert( refvr != VR::OB_OW );

    if( dynamic_cast<const SequenceOfItems*>( &value ) )
    {
    sqi = GetValueAsSQ();
    refvr = VR::SQ;
    assert( refvr == VR::SQ );
    } 
    
    if( (vr_read == VR::INVALID || vr_read == VR::UN ) && vl_read.IsUndefined() )
    {
    assert( refvr == VR::SQ );
    }
    
    if( vr_dict != VR::INVALID && (!vr_dict.Compatible( vr_read ) || vr_read == VR::INVALID || vr_read == VR::UN ) )
    {
    assert( vr_dict != VR::INVALID );
    
    if( vr_dict == VR::US_SS || vr_dict == VR::OB_OW )
      {
      //os << "(" << vr << " => " << refvr << ") ";
      //print
      }
    else
      {
      //os << "(" << vr << ") ";
      //print
      }
    
    }
    else if( sqi /*de.GetSequenceOfItems()*/ && refvr == VR::INVALID )
    {
    // when vr == VR::INVALID and vr_read is also VR::INVALID, we have a seldom case where we can guess
    // the vr
    // eg. CD1/647662/647663/6471066 has a SQ at (2001,9000)
    
    //os << "(SQ) ";
    //Print SQ
   
    assert( refvr == VR::INVALID );
    refvr = VR::SQ;
    }
    
    
    
     // Printing the VR -- Value Representation
     os << "VR=\"" << refvr << "\" ";

    
    
    
    
    
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
      
      os << name;
      
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
   os << "\" ";
    
    
    
    
    
  
  
  
  
  
  
  
  
  
  
  
  
  
    
// Print Value now:
  if( refvr & VR::VRASCII )
    {
    //assert( !sqi && !sqf );
    if( bv )
      {
      VL l = bv->GetLength();
      //os << "[";
      //Print value tag IMP
      //os << "\n<value
      if( bv->IsPrintable(l) )
        {
        bv->PrintASCII(os,l);
        }
      else
        {
        bv->PrintASCII(os,l);
        
        }
      //os << "]";
      //Print value closing tag IMP
      }
    else
      {
      assert( IsEmpty() );
      
      os << "(no value)";
      
      }
    }
  else
    {
    assert( refvr & VR::VRBINARY || (vr_dict == VR::INVALID && refvr == VR::INVALID) );
    //std::ostringstream os;
    std::string s;
    switch(refvr)
      {
      
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
          VL l = bv->GetLength();
          //VL l = std::min( (int)bv->GetLength(), 0xF );
          //int width = (vr == VR::OW ? 4 : 2);
          //os << std::hex << std::setw( width ) << std::setfill('0');
          bv->PrintHex(os, l / 4);
          //os << std::dec;
          }
        /*else if ( sqf )
          {
          assert( t == Tag(0x7fe0,0x0010) );
          //os << *sqf;
          }*/
        else if ( sqi )
          {
          // gdcmDataExtra/gdcmSampleData/images_of_interest/illegal_UN_stands_for_SQ.dcm
          gdcmErrorMacro( "Should not happen: VR=UN but contains a SQ" );
          //os << *sqi;
          }
        else
          {
          //assert( !sqi && !sqf );
          assert( IsEmpty() );
          //os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL;
          //Print no value tag IMP
          }
        }
      break;
    case VR::US_SS:
      // impossible...
      assert( refvr != VR::US_SS );
      break;
    case VR::SQ:
      if( !sqi /*!de.GetSequenceOfItems()*/ && !IsEmpty() && GetValue().GetLength() )
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
        {/*
        if( vl_read.IsUndefined() )
          {
          os << "(Sequence with undefined length)";
          }
        else
          {
          os << "(Sequence with defined length)";
          }*/
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
            //os << "[";
            //Print value tag IMP
            bv->PrintASCII(os,l);
            //os << "]";
            //Print value tag IMP
            }
          else if( t == Tag(0xfffe,0xe000) ) bv->PrintHex(os, l / 8);
          else
            {
            
            // << "(non-printable character found)"
            bv->PrintHex(os, l / 8);
            
            }
          }
        else
          {
          //assert( !sqi && !sqf );
          assert( IsEmpty() );
          //os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL;
          }
        }
      break;
    default:
      assert(1);
      break;
      }
    os << s;
    }
   
   

  
  
    
  return refvr;


 
     
		
     
     
     
     /* Printing the keyword after lookup from dictionary
        Checks whether it is from public dictionary or private
     os << " keyword=\"" << GetKeywordFromTag(TagField) << "\"";
     
     
     
     
     /*Add attributes for private creator, value --after checks to handle pixel data and SQ*/	
      
    
     
  }

#if !defined(GDCM_LEGACY_REMOVE)
  SequenceOfItems* DataElement::GetSequenceOfItems() {
    GDCM_LEGACY_REPLACED_BODY(DataElement::GetSequenceOfItems, "GDCM 2.2",
                              DataElement::GetValueAsSQ);
    SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if(!sqi)
      {
      // Was the element loaded as a byte value ? Let's check:
      assert( IsEmpty() );
      }
    return sqi;
  }
  const SequenceOfItems* DataElement::GetSequenceOfItems() const {
    GDCM_LEGACY_REPLACED_BODY(DataElement::GetSequenceOfItems, "GDCM 2.2",
                              DataElement::GetValueAsSQ);
    const SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if(!sqi)
      {
      // Was the element loaded as a byte value ? Let's check:
      assert( IsEmpty() );
      }
    return sqi;
  }
#endif
  const SequenceOfFragments* DataElement::GetSequenceOfFragments() const {
    const SequenceOfFragments *sqf = dynamic_cast<SequenceOfFragments*>(ValueField.GetPointer());
    return sqf;
  }

  /*
   *  Two cases are handled:
   *  - Simple ones:
   *     Explicit file with VR::SQ (defined or undefined length)
   *     Implicit file with undefined length (clearly a SQ)
   *  - If not in the previous case then we are in the second case: complex one (hidden SQ)
   *     Implicit file with defined length SQ
   *     Explicit file with SQ declared as UN + undefined length
   */
  SmartPointer<SequenceOfItems> DataElement::GetValueAsSQ() const
    {
    if( IsEmpty() /*|| GetByteValue()*/ || GetSequenceOfFragments() )
      {
      return 0;
      }
    SequenceOfItems *sq = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if( sq ) // all set !
      {
      //assert( GetVR() == VR::SQ );
      SmartPointer<SequenceOfItems> sqi = sq;
      return sqi;
      }

    const Tag itemStart(0xfffe, 0xe000);
      {
        {
        if( GetVR() == VR::INVALID )
          {
          const ByteValue *bv = GetByteValue();
          assert( bv );
          SequenceOfItems *sqi = new SequenceOfItems;
          sqi->SetLength( bv->GetLength() );
          std::string s( bv->GetPointer(), bv->GetLength() );
          try
            {
            std::stringstream ss;
            ss.str( s );
            sqi->Read<ImplicitDataElement,SwapperNoOp>( ss );
            }
          catch(Exception &ex)
            {
            const Tag itemPMSStart(0xfeff, 0x00e0);
            const Tag itemPMSStart2(0x3f3f, 0x3f00);

            // same player ...
            //this to fix a broken dicom implementation
            //for philips medical systems
            std::stringstream ss;
            ss.str(s);
            Tag item;
            item.Read<SwapperNoOp>(ss);
            assert( item == itemPMSStart );
            ss.seekg(-4,std::ios::cur);
            sqi->Read<ExplicitDataElement,SwapperDoOp>( ss );
			(void)ex;  //to avoid unreferenced variable warning on release
			gdcmErrorMacro(ex.what());
            }
          return sqi;
          }
        else if  ( GetVR() == VR::UN ) // cp 246, IVRLE SQ
          {
          assert( GetVR() == VR::UN ); // cp 246, IVRLE SQ
          const ByteValue *bv = GetByteValue();
          assert( bv );
          SequenceOfItems *sqi = new SequenceOfItems;
          sqi->SetLength( bv->GetLength() );
          std::string s( bv->GetPointer(), bv->GetLength() );
          try
            {
            std::stringstream ss;
            ss.str( s );
            sqi->Read<ImplicitDataElement,SwapperNoOp>( ss );
            }
          catch ( Exception & )
            {
            // Some people like to skew things up and write invalid SQ in VR:UN field
            // if conversion fails, simply keep the binary VR:UN stuff as-is
            // eg. AMIInvalidPrivateDefinedLengthSQasUN.dcm";
            //const char *s = e.what();
            // s -> gdcm::ImplicitDataElement -> Impossible (more)
            std::stringstream ss;
            ss.str(s);
            try
              {
              sqi->Read<ExplicitDataElement,SwapperDoOp>( ss );
              }
            catch ( Exception & )
              {
              gdcmErrorMacro( "Could not read SQ. Giving up" );
              throw "Could not decode this SQ";
              return NULL;
              }
            }
          return sqi;
          }
        else
          {
          assert( GetVR().IsVRFile() );
          assert( GetByteValue() );
          return 0;
          }
        }
      }
    //    catch( ParseException &pex )
    //      {
    //      gdcmDebugMacro( pex.what() );
    //      }
    //    catch( Exception &ex )
    //      {
    //      gdcmDebugMacro( ex.what() );
    //      }
    //    catch( ... )
    //      {
    //      gdcmWarningMacro( "Unknown exception" );
    //      }

    return 0;
    }

} // end namespace gdcm
