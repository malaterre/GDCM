/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/


#include "gdcmULWritingCallback.h"
#include "gdcmFile.h"
#include "gdcmWriter.h"
#include "gdcmTrace.h"

namespace gdcm {
  namespace network {

    //writes the data set to disk immediately, rather than keeping it memory.
    //could have potential timing issues if datasets come over the network faster than
    //they can be written, which could be the case on very fast connections with slow disks
void ULWritingCallback::HandleDataSet(const DataSet& inDataSet)
{
  if (inDataSet.FindDataElement(gdcm::Tag(0x0008,0x0018)))
    {
    gdcm::DataElement de = inDataSet.GetDataElement(gdcm::Tag(0x0008,0x0018));
    std::string sopclassuid_str( de.GetByteValue()->GetPointer(), de.GetByteValue()->GetLength() );
    gdcm::Writer w;
    std::string theLoc = mDirectoryName + "/" + sopclassuid_str + ".dcm";
    w.SetFileName(theLoc.c_str());
    gdcm::File &f = w.GetFile();
    f.SetDataSet(inDataSet);
    gdcm::FileMetaInformation &fmi = f.GetHeader();
    fmi.SetDataSetTransferSyntax( gdcm::TransferSyntax::ImplicitVRLittleEndian );
    w.SetCheckFileMetaInformation( true );
    if (!w.Write())
      {
      gdcmErrorMacro("Failed to write " << sopclassuid_str << std::endl);
      }
    else 
      {
      gdcmWarningMacro("Wrote " << sopclassuid_str << " to disk. " << std::endl);
      }
    }
  else 
    {
      gdcmErrorMacro( "Failed to write data set, could not find tag 0x0008, 0x0018" << std::endl);
    }
  DataSetHandled();
}
  }
}
