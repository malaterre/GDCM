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
#ifndef __gdcmFileExplicitFilter_h
#define __gdcmFileExplicitFilter_h

#include "gdcmFile.h"

namespace gdcm
{

/**
 * \brief FileExplicitFilter class
 * \warning changing an implicit dataset to an explicit dataset is NOT a trivial task of
 * simply changing the VR to the dict one:
 *   - One has to make sure SQ is properly set
 *   - One has to recompute the explicit length SQ
 *   - One has to make sure that Vr is valid for the encoding
 *   - One has to make sure that VR 16bits can store the original value length
 */
class Dicts;
class GDCM_EXPORT FileExplicitFilter
{
public:
  FileExplicitFilter():F(new File),ChangePrivateTags(false),UseVRUN(true),RecomputeItemLength(false),RecomputeSequenceLength(false) {}
  ~FileExplicitFilter() {}

  /// Decide whether or not to VR'ify private tags
  void SetChangePrivateTags(bool b) { ChangePrivateTags = b;}

  /// When VR=16bits in explicit but Implicit has a 32bits length, use VR=UN
  void SetUseVRUN(bool b) { UseVRUN = b; }

  /// By default set Sequence & Item length to Undefined to avoid recomputing length:
  void SetRecomputeItemLength(bool b);
  void SetRecomputeSequenceLength(bool b);

  /// Set FMI Transfer Syntax

  /// Change
  bool Change();

  /// Set/Get File
  void SetFile(const File& f) { F = f; }
  File &GetFile() { return *F; }

protected:
  bool ProcessDataSet(DataSet &ds, Dicts const & dicts);
  bool ChangeFMI();

private:
  SmartPointer<File> F;
  bool ChangePrivateTags;
  bool UseVRUN;
  bool RecomputeItemLength;
  bool RecomputeSequenceLength;
};


} // end namespace gdcm

#endif //__gdcmFileExplicitFilter_h

