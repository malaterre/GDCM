/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
//#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
//#include "gdcmAttribute.h"
#include "gdcmVR.h"

#include <typeinfo> // for typeid

namespace gdcm
{
//-----------------------------------------------------------------------------
Printer::Printer():PrintStyle(Printer::VERBOSE_STYLE)
{
}
//-----------------------------------------------------------------------------
Printer::~Printer()
{
}

#if 1
//-----------------------------------------------------------------------------
void PrintExplicitDataElement(std::ostream& _os, const ExplicitDataElement &_val, bool printVR, VR::VRType dictVR, Printer::PrintStyles pstyle)
{
  const Tag &t = _val.GetTag();
  const VR::VRType vr = _val.GetVR();
  const uint32_t vl = _val.GetVL();
  const Value& value = _val.GetValue();
  (void)printVR;
  if( pstyle == Printer::CONDENSED_STYLE )
    {
    _os << t << " " << vr;
    }
  else
    {
    _os << t << " VR=" << vr;
    }
  if( dictVR != VR::INVALID && !(vr & dictVR) ) //printVR )
    {
    gdcmErrorMacro( "Wrong VR should be " << dictVR );
    // LEADTOOLS_FLOWERS-8-PAL-RLE.dcm has (0040,0253) : CS instead of SH
    //abort();
    }
  if( pstyle == Printer::CONDENSED_STYLE )
    {
    (void)vl;
    _os /*<< "\t " << std::dec << vl  */
      << " [" << value << "]";
    }
  else
    {
    _os << "\tVL=" << std::dec << vl <<
      "\t ValueField=[" << value << "]";
    }
}
//-----------------------------------------------------------------------------
void PrintImplicitDataElement(std::ostream& _os, const ImplicitDataElement &_val, bool printVR, VR::VRType dictVR)
{
  const Tag &t = _val.GetTag();
  const uint32_t vl = _val.GetVL();
  const Value& value = _val.GetValue();
  _os << t;
  if ( printVR )
    {
    _os << " ?VR=" << dictVR;
    }
  _os << "\tVL=" << std::dec << vl
    << "\tValueField=[" << value << "]";
}

//-----------------------------------------------------------------------------
void PrintImplicitDataElements(Printer &is)
{
  ImplicitDataElement de;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  (void)pstyle;
  bool printVR = false; //is.GetPrintVR();

  std::ostream &_os = std::cout;
  //static const Dicts dicts;
  //const Dict &d = dicts.GetPublicDict();
  static const Dict d;
  static const GroupDict gd;
  try
    {
    //while( is.Read(de) )
      {
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      VR::VRType vr = entry.GetVR();
      VM::VMType vm = entry.GetVM();
      if( de.GetTag().GetGroup()%2 && de.GetTag().GetElement() == 0 )
        {
        assert( vr == VR::INVALID );
        vr = VR::UL;
        vm = VM::VM1;
        }
      if( VR::IsASCII( vr ) || VR::IsBinary(vr) || vr == VR::INVALID )
        {
        PrintImplicitDataElement(_os, de, printVR, entry.GetVR());
        }
      else
        {
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if ( printVR )
          {
          _os << " ?VR=" << vr;
          }
        _os << "\tVL=" << std::dec << de.GetVL() << "\tValueField=[";

        // Use super class of the template stuff
        //Attribute af;
        //// Last minute check, is it a Group Length:
        //af.SetVR(vr);
        //af.SetVM(vm);
        //af.SetLength( val.GetLength() );
        //std::istringstream iss;
        //iss.str( std::string( val.GetPointer(), val.GetLength() ) );
        //af.Read( iss );
        //af.Print( _os );
        _os << "]";
        }
      if( de.GetTag().GetElement() == 0x0 )
        {
        _os << "\t\t# (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
        }
      else
        {
        _os << "\t\t# " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}

//-----------------------------------------------------------------------------
void PrintExplicitDataElements(Printer &is)
{
  ExplicitDataElement de;

  std::ostream &_os = std::cout;
  static const Dict d;
  static const GroupDict gd;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  bool printVR = false; //is.GetPrintVR();
  try
    {
    //while( !is.eof() && is.Read(de) )
      {
      //is.Read(de);
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      const VR::VRType vr = entry.GetVR();
      const VR::VRType vr_read = de.GetVR();
      if( VR::IsASCII(vr_read) || VR::IsBinary(vr_read) )
        {
        PrintExplicitDataElement(_os, de, printVR, vr, pstyle);
        }
      else
        {
        const VM::VMType vm = entry.GetVM();
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if( pstyle == Printer::CONDENSED_STYLE )
          {
          _os << " " << vr_read;
          }
        else
          {
          _os << " VR=" << vr_read;
          }
        if( vr != VR::INVALID && !(vr_read & vr) )
          {
          gdcmErrorMacro( "Wrong VR should be " << vr );
          // PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
          // 0008,0040 VR=SS VR(?)=US
          // After posting to dicom newsgroup there were reasons for doing SS
          // but in this case user should really do US...
          }
        if( pstyle == Printer::CONDENSED_STYLE )
          {
        _os << /*"\t " << std::dec << de.GetVL() << */
          " ";
        }
        else
          {
        _os << "\tVL=" << std::dec << de.GetVL() 
          << "\tValueField=[";
          }

        // Use super class of the template stuff
        //Attribute af;
        //af.SetVR(vr_read);
        //af.SetVM(vm);
        //af.SetLength( val.GetLength() );
        //std::istringstream iss;
        //iss.str( std::string( val.GetPointer(), val.GetLength() ) );
        //af.Read( iss );
        //af.Print( _os );
        if( pstyle == Printer::CONDENSED_STYLE )
          {
        _os << "]";
        }
        }
      if( de.GetTag().GetElement() == 0x0 )
        {
        _os << "\t\t# (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
        }
      else
        {
        _os << "\t\t# " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}
#endif

//-----------------------------------------------------------------------------
void Printer::Print(std::ostream& os)
{
  const gdcm::DataSet &ds = *DS;
  os << ds << std::endl;
  //DataSet::Iterator it = ds.Begin();
}

}

