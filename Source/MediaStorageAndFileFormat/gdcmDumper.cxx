/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDumper.h"

#include "gdcmStructuredSet.h"
#include "gdcmDataElement.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
Dumper::Dumper():/*PrintStyle(Dumper::VERBOSE_STYLE),*/F(0)
{
}
//-----------------------------------------------------------------------------
Dumper::~Dumper()
{
}

//-----------------------------------------------------------------------------
void DumpDataSet(std::ostream &os, const StructuredSet &ds)
{
  StructuredSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;
    const Tag& t = de.GetTag();
    const VR& vr = de.GetVR();
    os << de << std::endl;
    //if( VR::IsASCII( vr ) )
    //  {
    //  }
    }
}

//-----------------------------------------------------------------------------
void Dumper::Print(std::ostream& os)
{
  std::cout << "# Dicom-File-Format\n";
  std::cout << "\n";
  std::cout << "# Dicom-Meta-Information-Header\n";
  std::cout << "# Used TransferSyntax: \n";

  const FileMetaInformation &meta = F->GetHeader();
  DumpDataSet(os, meta);

  std::cout << "\n# Dicom-Data-Set\n";
  std::cout << "# Used TransferSyntax: \n";
  const DataSet &ds = F->GetDataSet();
  const StructuredSet &exds = ds.GetInternal();
  DumpDataSet(os, exds);
}

}

