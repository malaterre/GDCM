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
            gdcmWarningMacro(ex.what());
            (void)ex;  //to avoid unreferenced variable warning on release
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
          catch ( Exception &ex0 )
            {
            // Some people like to skew things up and write invalid SQ in VR:UN field
            // if conversion fails, simply keep the binary VR:UN stuff as-is
            // eg. AMIInvalidPrivateDefinedLengthSQasUN.dcm
            //const char *s = e.what();
            // s -> gdcm::ImplicitDataElement -> Impossible (more)
            try
              {
              std::stringstream ss;
              ss.str(s);
              sqi->Read<ExplicitDataElement,SwapperDoOp>( ss );
              gdcmWarningMacro(ex0.what()); (void)ex0;
              }
            catch ( Exception &ex1 )
              {
              // Let's try again this time but without the byte swapping option:
              // eg. MEDILABInvalidCP246_EVRLESQasUN.dcm
              try
                {
                std::stringstream ss;
                ss.str(s);
                sqi->Read<ExplicitDataElement,SwapperNoOp>( ss );
                gdcmWarningMacro(ex1.what()); (void)ex1;
                }
              catch ( Exception &ex2 )
                {
                gdcmErrorMacro( "Could not read SQ. Giving up" );
                gdcmErrorMacro(ex2.what()); (void)ex2;
                throw "Could not decode this SQ";
                return NULL;
                }
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

//#if !defined(GDCM_LEGACY_REMOVE)
//  ByteValue* DataElement::GetByteValue()
//    {
//    // Get the raw pointer from the gdcm::SmartPointer
//    ByteValue *bv = dynamic_cast<ByteValue*>(ValueField.GetPointer());
//    return bv; // Will return NULL if not ByteValue
//    }
//#endif

} // end namespace gdcm
