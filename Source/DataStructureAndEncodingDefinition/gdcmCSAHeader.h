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
#ifndef __gdcmCSAHeader_h
#define __gdcmCSAHeader_h

#include "gdcmTypes.h"
#include "gdcmDataSet.h"
#include "gdcmCSAElement.h"

namespace gdcm
{
/*
 * Everything done in this code is for the sole purpose of writing interoperable 
 * software under Sect. 1201 (f) Reverse Engineering exception of the DMCA.
 * If you believe anything in this code violates any law or any of your rights, 
 * please contact us (gdcm-developers@lists.sourceforge.net) so that we can 
 * find a solution. 
 */
//-----------------------------------------------------------------------------

class GDCM_EXPORT CSAElementNameException : public std::exception {};

class DataElement;
class PrivateTag;
/**
 * \brief Class for CSAHeader
 *
 * \warning:
 * Everything you do with this code is at your own risk, since decoding process
 * was not written from specification documents.
 *
 * \WARNING: the API of this class might change.
 *
 * \TODO:
 * MrEvaProtocol in 29,1020 contains ^M that would be nice to get rid of on UNIX system...
 *
 * \See also
 * 5.1.3.2.4.1 MEDCOM History Information
 * and 5.1.4.3 CSA Non-Image Module
 * in 
 * http://tamsinfo.toshiba.com/docrequest/pdf/E.Soft_v2.0.pdf
 */
class GDCM_EXPORT CSAHeader
{
public :
  CSAHeader():InternalDataSet(),InternalType(UNKNOWN) {};
  ~CSAHeader() {};

  typedef enum {
    UNKNOWN = 0,
    SV10,
    NOMAGIC,
    DATASET_FORMAT,
    ZEROED_OUT
  } CSAHeaderType;

  template <typename TSwap>
  std::istream &Read(std::istream &is);

  template <typename TSwap>
  const std::ostream &Write(std::ostream &os) const;

  bool LoadFromDataElement(DataElement const &de);

  void Print(std::ostream &os) const;

  const DataSet& GetDataSet() const { return InternalDataSet; }

  CSAHeaderType GetFormat() const;

  static const PrivateTag & GetCSAImageHeaderInfoTag();
  static const PrivateTag & GetCSASeriesHeaderInfoTag();

  /// Return the CSAElement corresponding to name 'name'
  /// \warning Case Sensitive
  /// Throw a CSAElementNameException if not found
  const CSAElement &GetCSAElementByName(const char *name);

  /// Return true if the CSA element matching 'name' is found or not
  bool FindCSAElementByName(const char *name);

private:
  CSAElement Dummy;
  std::set<CSAElement> InternalCSADataSet;
  DataSet InternalDataSet;
  CSAHeaderType InternalType;
  Tag DataElementTag;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmCSAHeader_h
