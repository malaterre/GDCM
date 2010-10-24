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
#ifndef GDCMCOMMANDDATASET_H
#define GDCMCOMMANDDATASET_H

#include "gdcmDataSet.h"
#include "gdcmDataElement.h"

namespace gdcm
{
/**
 * \brief Class to represent a Command DataSet
 *
 * \see DataSet
 */
class GDCM_EXPORT CommandDataSet : public DataSet
{
public:
  CommandDataSet() {}
 ~CommandDataSet() {}

  friend std::ostream &operator<<(std::ostream &_os, const CommandDataSet &_val);

  // FIXME: no virtual function means: duplicate code...
  void Insert(const DataElement& de) {
    if( de.GetTag().GetGroup() == 0x0000 )
      {
      InsertDataElement( de );
      }
    else
      {
      gdcmErrorMacro( "Cannot add element with group != 0x0000 in the command dataset : " << de );
      }
  }
  void Replace(const DataElement& de) {
    Remove(de.GetTag());
    Insert(de);
  }

  /// Read
  std::istream &Read(std::istream &is);

  /// Write
  std::ostream &Write(std::ostream &os) const;

protected:
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const CommandDataSet &val)
{
  val.Print( os );
  return os;
}

} // end namespace gdcm

#endif //GDCMFILEMETAINFORMATION_H
