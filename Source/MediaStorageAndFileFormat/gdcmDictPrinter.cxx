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
#include "gdcmDictPrinter.h"
#include "gdcmDict.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
DictPrinter::DictPrinter()
{
}

//-----------------------------------------------------------------------------
DictPrinter::~DictPrinter()
{
}

VM::VMType GuessVMType(ExplicitDataElement const &de)
{
      const VR &vr = de.GetVR();
      const VL &vl = de.GetVL();
      const Value& value = de.GetValue();
      VM::VMType vm;
      if( VR::IsBinary( vr ) )
      {
	      if( vr & ( VR::OB | VR::OW ) )
	      {
		      vm = VM::VM1;
	      }
	      else
	      {
        vm = VM::GetVMTypeFromLength( value.GetLength(), vr.GetSize() );
	      }
      }
      else
      {
	      assert( VR::IsASCII( vr ) );
	      switch(vr)
	      {
		      case VR::SH: case VR::UI: case VR::LO: case VR::CS:
			      vm = VM::VM1;
			      break;
		      case VR::IS: case VR::DS: case VR::DT:
			      {
			      // Need to count \\ character
			      const ByteValue *bv = dynamic_cast<const ByteValue*>(&value);
			      assert( bv && "not bv" );
                              const char *array = bv->GetPointer();
			      const char *p = array;
			      const char *end = array + vl;
			      unsigned int c=1;
			      while(p != end)
			      {
				      if( *p++ == '\\' ) ++c;
			      }
			      //std::cout << "INVALID: " << c << std::endl;
                        vm = VM::GetVMTypeFromLength( c, 1 );
			      }
			      break;
		      default:
	                vm = VM::VM0;
	      }
      }

      return vm;
}

std::string GetVersion(std::string const &owner)
{
  if( strncmp( "GEMS", owner.c_str(), 4 ) == 0 )
  {
    return "GEM";
  }
  else if( strncmp( "PHILIPS", owner.c_str(), strlen("PHILIPS") ) == 0 
        || strncmp( "SPI-P", owner.c_str(), strlen("SPI-P") ) == 0 
		  )
  {
    return "PSPI";
  }
  else if( strncmp( "SIEMENS", owner.c_str(), strlen("SIEMENS") ) == 0 )
  {
    return "SSPI";
  }
  else if( strncmp( "ELSCINT1", owner.c_str(), strlen("ELSCINT1") ) == 0 )
  {
    return "EL1";
  }
  else
  {
	  std::cerr << "OWNER=" << owner << std::endl;
    assert( 0 && "Unknown owner" );
  }

  return "??";
}

// TODO: make it protected:
std::string GetOwner(StructuredSet<ExplicitDataElement> const &ds, ExplicitDataElement const &de)
{
  const Tag &t = de.GetTag();
  Tag towner(t);
  towner.SetElement( 0x0010 );
  if( !ds.FindDataElement(towner) )
  {
	  return "";
  }
  //std::cout << "REF: " << towner << std::endl;
  const ExplicitDataElement& xde = ds.GetDataElement(towner);
  const Value &value = xde.GetValue();
  const ByteValue *bv = dynamic_cast<const ByteValue*>(&value);
  assert( bv && "not bv" );
  const char *array = bv->GetPointer();
  return std::string(array, bv->GetLength());

}

//-----------------------------------------------------------------------------
void DictPrinter::Print(std::ostream& os)
{
  static const Dict d;
  const DataSet &ds = F->GetDataSet();
  const StructuredSet<ExplicitDataElement> &exds = ds.GetInternal();
     StructuredSet<ExplicitDataElement>::ConstIterator it = exds.Begin();
     os << "<dict>\n";
    for( ; it != exds.End(); ++it )
      {
      const ExplicitDataElement &de = *it;
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // FIXME: stupid code does not work:
      if( de.GetTag().IsPrivate() /*!entry.IsValid()*/ )
      {
      const Tag &t = de.GetTag();
      const VR &vr = de.GetVR();
      VM::VMType vm = GuessVMType(de);
 
      std::string owner = GetOwner(exds,de);
      std::string version = GetVersion(owner);
      os << 
      "<entry group=\"" << std::hex << std::setw(4) << std::setfill('0') << 
      t.GetGroup() << "\" element=\"" << std::setw(4) << t.GetElement() << 
      "\" retired=\"false\" owner=\"" << owner
      << "\" version=\"" << version << "\">\n";
      os << "  <description>Unknown ";
      os << (t.IsPrivate() ? "Private" : "Public");
      os << " Tag & Data</description>\n";
      os << "  <representations>\n";
      os << "    <representation vr=\"" << vr << "\" vm=\"" << 
	      VM::GetVMString(vm) << "\"/>\n";
      os << "  </representations>\n";
       os << "</entry>\n";
      }
      else
      {
	      //os << entry.GetVR() << std::endl;
      }
      }
     os << "</dict>\n";
 }

}

