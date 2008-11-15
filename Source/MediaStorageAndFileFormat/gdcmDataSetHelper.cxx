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
#include "gdcmSequenceOfItems.h"
#include "gdcmImplicitDataElement.h"
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
  const VR &refvr = entry.GetVR();
  //const VM &vm = entry.GetVM();

  // not much we can do...
  if( refvr == VR::INVALID || refvr == VR::UN )
    {
    // postcondition says it cannot be VR::INVALID, so return VR::UN
    return VR::UN;
    }

  VR vr = refvr;

  // Special handling of US or SS vr:
  if( vr == VR::US_SS )
    {
    // I believe all US_SS VR derived from the value from 0028,0103 ... except 0028,0071
    if( t != Tag(0x0028,0x0071) )
      {
      // In case of SAX parser, we would have had to process Pixel Representation already:
      Tag pixelrep(0x0028,0x0103);
      assert( pixelrep < t );
      const DataSet &rootds = file.GetDataSet();
      // FIXME
      // PhilipsWith15Overlays.dcm has a Private SQ with public elements such as
      // 0028,3002, so we cannot look up element in current dataset, but have to get the root dataset
      // to loop up...

      // FIXME:
      // gdcmDataExtra/gdcmSampleData/ImagesPapyrus/TestImages/wristb.pap
      // It's the contrary: root dataset does not have a Pixel Representation, but each SQ do...
      assert( rootds.FindDataElement( pixelrep ) || ds.FindDataElement( pixelrep ) );
      Attribute<0x0028,0x0103> at;
      if( ds.FindDataElement( pixelrep ) )
        {
        at.SetFromDataElement( ds.GetDataElement( pixelrep ) );
        }
      else if( rootds.FindDataElement( pixelrep ) )
        {
        at.SetFromDataElement( rootds.GetDataElement( pixelrep ) );
        }
      else
        {
        //throw Exception( "Unhandled" );
        gdcmWarningMacro( "Unhandled" );
        vr = VR::INVALID;
        }
      assert( at.GetValue() == 0 || at.GetValue() == 1 );
      if( at.GetValue() )
        {
        vr = VR::SS;
        }
      else
        {
        vr = VR::US;
        }
      }
    else
      {
      // FIXME ???
      vr = VR::US;
      }
    }
  else if( vr == VR::OB_OW )
    {
    /*
    For the Value Representations OB and OW, the encoding shall meet the following
    specification depending on the Data Element Tag:
    - Data Element (7FE0,0010) Pixel Data has the Value Representation OW and shall
    be encoded in Little Endian.
    - Data Element (60xx,3000) Overlay Data has the Value Representation OW and shall
    be encoded in Little Endian.

    See PS 3.5 - 2004
    - Data Element (50xx,3000) Curve Data has the Value Representation OB with its
    component points (n-tuples) having the Value Representation specified in Data
    Value Representation (50xx,0103). The component points shall be encoded in Little
    Endian.
    */
    Tag pixeldata(0x7fe0,0x0010);
    Tag overlaydata(0x6000,0x3000);
    Tag curvedata(0x5000,0x3000);
    Tag variablepixeldata(0x7f00,0x0010);
    Tag bitsallocated(0x0028,0x0100);
    //assert( ds.FindDataElement( pixeldata ) );
    assert( ds.FindDataElement( bitsallocated ) );
    Attribute<0x0028,0x0100> at;
    at.SetFromDataElement( ds.GetDataElement( bitsallocated ) );

    if( pixeldata == t || t.IsGroupXX(overlaydata) )
      {
      vr = VR::OW;
      }
    else if ( t.IsGroupXX(curvedata) )
      {
      vr = VR::OB;
      }
    else if ( t.IsGroupXX(variablepixeldata) )
      {
      vr = VR::OB;
      }
    else
      {
      assert( 0 && "Should not happen" );
      vr = VR::INVALID;
      }
    }
  else if( vr == VR::US_SS_OW )
    {
    vr = VR::OW;
    }
  // TODO need to treat US_SS_OW too

  // \postcondition:
  assert( vr.IsVRFile() );
  assert( vr != VR::INVALID );
  return vr;
}


/*
SequenceOfItems* DataSetHelper::ComputeSQFromByteValue(File const & file, DataSet const &ds, const Tag &tag)
{
  const TransferSyntax &ts = file.GetHeader().GetDataSetTransferSyntax();
  assert( ts != TransferSyntax::DeflatedExplicitVRLittleEndian );
  const DataElement &de = ds.GetDataElement( tag );
  if( de.IsEmpty() )
    {
    return 0;
    }
  Value &v = const_cast<Value&>(de.GetValue());
  SequenceOfItems *sq = dynamic_cast<SequenceOfItems*>(&v);
  if( sq ) // all set !
    {
    SmartPointer<SequenceOfItems> sqi = sq;
    return sqi;
    }

  try
    {
    if( ts.GetSwapCode() == SwapCode::BigEndian )
      {
      abort();
      }
    else
      {
      if( ts.GetNegociatedType() == TransferSyntax::Implicit )
        {
        assert( de.GetVR() == VR::INVALID );
        const ByteValue *bv = de.GetByteValue();
        assert( bv );
        SequenceOfItems *sqi = new SequenceOfItems;
        sqi->SetLength( bv->GetLength() );
        std::stringstream ss;
        ss.str( std::string( bv->GetPointer(), bv->GetLength() ) );
        sqi->Read<ImplicitDataElement,SwapperNoOp>( ss );
        return sqi;
        }
      else
        {
        assert( de.GetVR() == VR::UN ); // cp 246, IVRLE SQ
        const ByteValue *bv = de.GetByteValue();
        assert( bv );
        SequenceOfItems *sqi = new SequenceOfItems;
        sqi->SetLength( bv->GetLength() );
        std::stringstream ss;
        ss.str( std::string( bv->GetPointer(), bv->GetLength() ) );
        sqi->Read<ImplicitDataElement,SwapperNoOp>( ss );
        return sqi;
        }
      }
    }
  catch( ParseException &pex )
    {
    gdcmDebugMacro( pex.what() );
    }
  catch( Exception &ex )
    {
    gdcmDebugMacro( ex.what() );
    }
  catch( ... )
    {
    gdcmWarningMacro( "Unknown exception" );
    }

  return 0;
}
*/

}
