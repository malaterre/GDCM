#include "gdcmReader.h"
#include "gdcmTrace.h"
#include "gdcmVR.h"
#include "gdcmFileMetaInformation.h"

namespace gdcm
{

Reader::~Reader()
{
  delete DS;
  delete Header;
}

/// \brief tells us if "DICM" is found as position 128
///        (i.e. the file is a 'true dicom' one)
/// If not found then seek back at beginning of file (could be malinkroft
/// or old ACRNEMA with no preamble
/// \precondition we are at the beginning of file
/// \postcondition we are at the beginning of the DataSet or
/// Meta Information Header
bool Reader::ReadPreamble()
{
  bool r = false;
  char dicm[128+4];
  Stream.Read(dicm, 128+4);
  if( dicm[128+0] == 'D'
   && dicm[128+1] == 'I'
   && dicm[128+2] == 'C'
   && dicm[128+3] == 'M')
    {
    r = true;
    }
  if(!r)
    {
    gdcmDebugMacro( "Not a DICOM V3 file" );
    // Seek back
    Stream.Seekg(0, std::ios::beg);
    }

  return r;
}

/// \brief read the DICOM Meta Information Header
/// Find out the TransferSyntax used (default: Little Endian Explicit)
/// \precondition we are at the start of group 0x0002 (well after preamble)
/// \postcondition we are at the beginning of the DataSet
bool Reader::ReadMetaInformation()
{
  if( !Header )
    {
    Header = new FileMetaInformation;
    }
  return Header->Read(Stream);
}

bool Reader::ReadDataSet()
{
  if( !DS )
    {
    TS::TSType ts = Header->GetTSType();
    //std::cerr << ts << std::endl;
    if( TS::GetNegociatedType(ts) == TS::Explicit )
      {
      DS = new DataSet(TS::Explicit);
      }
    else // default to instanciating an implicit one (old ACRNEMA...)
      {
      DS = new DataSet(TS::Implicit);
      }
    }
  return DS->Read(Stream);
}

bool Reader::Read()
{
  //Stream.Open();
  if( !ReadPreamble() )
    {
    gdcmWarningMacro( "No Preamble" );
    }
  ReadMetaInformation();
  std::cerr << *Header << std::endl;
  ReadDataSet();

  Stream.Close();

  return true;
}

} // end namespace gdcm
