/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDataSetHelper.h"
#include "gdcmPrinter.h"
#include "gdcmReader.h"
#include "gdcmGlobal.h"
#include "gdcmTesting.h"

namespace gdcm
{
class Printer2 : public Printer
{
public:
  VR PrintDataElement(std::ostringstream & os, const Dicts &dicts, const DataSet & ds, const DataElement &de, std::ostream &out, std::string const & indent ) {
    const VR vr = Printer::PrintDataElement(os, dicts, ds, de, out, indent );
    const VR vr2 = DataSetHelper::ComputeVR(*F, ds, de.GetTag());
    assert( vr == vr2 );
    return vr;
  }
void PrintSQ(const SequenceOfItems *sqi, std::ostream & os, std::string const & indent)
{
  if( !sqi ) return;
  SequenceOfItems::ItemVector::const_iterator it = sqi->Items.begin();
  for(; it != sqi->Items.end(); ++it)
    {
    const Item &item = *it;
    const DataSet &ds = item.GetNestedDataSet();
    const DataElement &deitem = item;
    std::string nextindent = indent + "  ";
    os << nextindent << deitem.GetTag();
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
    PrintDataSet(ds, os, nextindent + "  ");
    if( deitem.GetVL().IsUndefined() )
      {
      const Tag itemDelItem(0xfffe,0xe00d);
      os << nextindent << itemDelItem << "\n";
      }
    }
  if( sqi->GetLength().IsUndefined() )
    {
    const Tag seqDelItem(0xfffe,0xe0dd);
    os << indent << seqDelItem << "\n";
    }
}
void PrintDataSet(const DataSet &ds, std::ostream &out, std::string const & indent = "" )
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();

  DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;

    const SequenceOfFragments *sqf = de.GetSequenceOfFragments();

    std::ostringstream os;

    VR refvr = PrintDataElement(os, dicts, ds, de, out, indent);

    if( refvr == VR::SQ /*|| sqi*/ )
      {
      SmartPointer<SequenceOfItems> sqi2 = de.GetValueAsSQ(); // may throw
      PrintSQ(sqi2, os, indent);
      }
    else if ( sqf )
      {
      std::string nextindent = indent + "  ";
      const BasicOffsetTable & table = sqf->GetTable();
      PrintDataElement(os,dicts,ds,table,out,nextindent);
      size_t numfrag = sqf->GetNumberOfFragments();
      for(size_t i = 0; i < numfrag; ++i)
        {
        const Fragment& frag = sqf->GetFragment(i);
        PrintDataElement(os,dicts,ds,frag,out,nextindent);
        }
      const Tag seqDelItem(0xfffe,0xe0dd);
      VL zero = 0;
      os << /*nextindent <<*/ seqDelItem;
      os << " " << zero << "\n";
      }
    else
      {
      // This is a byte value, so it should have been already treated
      }
    out << os.str();
    }
}
void Print(std::ostream& os)
{
  os << "# Dicom-File-Format\n";
  os << "\n";
  os << "# Dicom-Meta-Information-Header\n";
  os << "# Used TransferSyntax: \n";

  const FileMetaInformation &meta = F->GetHeader();
    PrintDataSet(meta, os);

  os << "\n# Dicom-Data-Set\n";
  os << "# Used TransferSyntax: ";
  const TransferSyntax &metats = meta.GetDataSetTransferSyntax();
  os << metats;
  os << std::endl;
  const DataSet &ds = F->GetDataSet();
    PrintDataSet(ds, os);
}


};
} // namespace gdcm

static int TestDataSetHelperFunc(const char *filename, bool verbose= false)
{
  gdcm::Reader r;
  r.SetFileName( filename );
  if( !r.Read() )
    {
    std::cerr << "Could not read: " << filename << std::endl;
    return 1;
    }

  const gdcm::Global &g = gdcm::GlobalInstance;
  const gdcm::Dicts &dicts = g.GetDicts();
  const gdcm::File & file = r.GetFile();
  gdcm::Printer2 print;
  print.SetFile( file );
  std::ostringstream out;
  if( verbose )
    print.Print( std::cout );
  print.Print( out );
  return 0;
}

int TestDataSetHelper(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestDataSetHelperFunc(filename, true);
    }

  // else
  int r = 0, i = 0;
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  gdcm::Trace::ErrorOff();
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestDataSetHelperFunc( filename );
    ++i;
    }

  return r;
}
