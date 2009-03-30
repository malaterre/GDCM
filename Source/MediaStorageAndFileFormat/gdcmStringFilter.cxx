/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmStringFilter.h"
#include "gdcmGlobal.h"
#include "gdcmElement.h"
#include "gdcmByteValue.h"
#include "gdcmAttribute.h"
#include "gdcmDataSetHelper.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
StringFilter::StringFilter():F(new File)
{
}
//-----------------------------------------------------------------------------
StringFilter::~StringFilter()
{
}

void StringFilter::SetDicts(const Dicts &dicts)
{
  abort(); // FIXME
}

std::string StringFilter::ToString(const Tag& t) const
{
  return ToStringPair(t).second;
}

/*
std::string StringFilter::ToMIME64(const Tag& t) const
{
  return ToStringPair(t).second;
          // base64 streams have to be a multiple of 4 bytes long
          int encodedLengthEstimate = 2 * bv->GetLength();
          encodedLengthEstimate = ((encodedLengthEstimate / 4) + 1) * 4;

          char *bin = new char[encodedLengthEstimate];
          unsigned int encodedLengthActual = static_cast<unsigned int>(
            itksysBase64_Encode(
              (const unsigned char *) bv->GetPointer(),
              static_cast< unsigned long>( bv->GetLength() ),
              (unsigned char *) bin,
              static_cast< int >( 0 ) ));
          std::string encodedValue(bin, encodedLengthActual);

}
*/

#define StringFilterCase(type) \
  case VR::type: \
    { \
      Element<VR::type,VM::VM1_n> el; \
      if( !de.IsEmpty() ) { \
      el.Set( de.GetValue() ); \
      if( el.GetLength() ) { \
      os << el.GetValue(); \
      for(unsigned long i = 1; i < el.GetLength(); ++i) os << "\\" << el.GetValue(i); \
      ret.second = os.str(); } } \
    } break

std::pair<std::string, std::string> StringFilter::ToStringPair(const Tag& t) const
{
  std::pair<std::string, std::string> ret;
  const Global &g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const DataSet &ds = GetFile().GetDataSet();
  if( ds.IsEmpty() || !ds.FindDataElement(t) )
    {
    gdcmDebugMacro( "DataSet is empty or does not contains tag:" );
    return ret;
    }
  if( t.IsPrivate() )
    {
    return ret;
    }
  const DataElement &de = ds.GetDataElement( t );
  assert( de.GetTag().IsPublic() );
  const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
  if( entry.GetVR() == VR::INVALID )
    {
    // FIXME This is a public element we do not support...
    //throw Exception();
    return ret;
    }

  VR vr = entry.GetVR();
  // If Explicit override with coded VR:
  if( de.GetVR() != VR::INVALID && de.GetVR() != VR::UN )
    {
    vr = de.GetVR();
    }
  assert( vr != VR::UN && vr != VR::INVALID );
  //std::cerr << "Found " << vr << " for " << de.GetTag() << std::endl;
  ret.first = entry.GetName();
  if( VR::IsASCII( vr ) )
    {
    assert( vr & VR::VRASCII );
    const ByteValue *bv = de.GetByteValue();
    if( de.GetVL() )
      {
      assert( bv /*|| bv->IsEmpty()*/ );
      ret.second = std::string( bv->GetPointer(), bv->GetLength() );
      // Let's remove any trailing \0 :
      ret.second.resize( std::min( ret.second.size(), strlen( ret.second.c_str() ) ) ); // strlen is garantee to be lower or equal to ::size()
      }
    else
      {
      //assert( bv == NULL );
      ret.second = ""; // ??
      }
    }
  else
    {
    assert( vr & VR::VRBINARY );
    const ByteValue *bv = de.GetByteValue();
    std::ostringstream os;
    if( bv )
      {
      VM::VMType vm = entry.GetVM();
      //assert( vm == VM::VM1 );
      if( vr.IsDual() ) // This mean vr was read from a dict entry:
        {
        vr = DataSetHelper::ComputeVR(GetFile(),ds, t);
        }
      std::ostringstream os;
      switch(vr)
        {
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
        StringFilterCase(UT);
      case VR::UN:
      case VR::US_SS:
        abort();
        break;
      case VR::OB:
      case VR::OW:
      case VR::OB_OW:
      case VR::SQ:
        gdcmWarningMacro( "Unhandled: " << vr << " for tag " << de.GetTag() );
        ret.second = "";
        break;
      default:
        abort();
        break;
        }
      }
    }
  return ret;
}

std::string StringFilter::FromString(const Tag&t, const char * value, VL const & vl)
{
  const Global &g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const DictEntry &entry = dicts.GetDictEntry(t);
  const VM &vm = entry.GetVM();
  const VR &vr = entry.GetVR();
  if( vl != vm.GetLength() * vr.GetSizeof() )
    {
    abort();
    }

  std::string s(value,value+vl);
  std::istringstream is;
  is.str( s );
  std::ostringstream os;
  switch(vr)
    {
  case VR::US:
      {
      Element<VR::US,VM::VM1_n> el;
      el.SetLength( vl );
      for(unsigned int i = 0; i < vm.GetLength(); ++i)
        is >> el.GetValue(i);
      el.Write(os);
      }
    break;
  default:
    gdcmErrorMacro( "Not implemented" );
    abort();
    }
  return os.str();
}

}
