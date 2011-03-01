/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMPRESENTATIONCONTEXT_H
#define GDCMPRESENTATIONCONTEXT_H

#include "gdcmTypes.h"
#include "gdcmAbstractSyntax.h"
#include "gdcmTransferSyntaxSub.h"
#include "gdcmDataSet.h"

namespace gdcm
{

namespace network
{

/**
 * \brief PresentationContext
 * Table 9-13
 * PRESENTATION CONTEXT ITEM FIELDS
 * \see PresentationContextAC
 */
class GDCM_EXPORT PresentationContext
{
public:
  PresentationContext();

  /// Initialize Presentation Context with AbstractSyntax set to asname
  /// and with a single TransferSyntax set to tsname (dfault to Implicit VR
  /// LittleEndian when not specified ).
  PresentationContext( UIDs::TSName asname, UIDs::TSName tsname =
    UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM  );

  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  size_t Size() const;

  void SetAbstractSyntax( AbstractSyntax const & as );
  AbstractSyntax const &GetAbstractSyntax() const { return SubItems; }
  AbstractSyntax &GetAbstractSyntax() { return SubItems; }

  void AddTransferSyntax( TransferSyntaxSub const &ts );
  typedef std::vector<TransferSyntaxSub>::size_type SizeType;
  TransferSyntaxSub const & GetTransferSyntax(SizeType i) const { return TransferSyntaxes[i]; }
  TransferSyntaxSub & GetTransferSyntax(SizeType i) { return TransferSyntaxes[i]; }
  std::vector<TransferSyntaxSub> const & GetTransferSyntaxes() const {return TransferSyntaxes; }

  void SetPresentationContextID( uint8_t id );
  uint8_t GetPresentationContextID() const;

  void Print(std::ostream &os) const;

  //this function will return the appropriate ID from the above
  //list, after querying the appropriate tag in the dataset.  If the tag above
  //does not exist, then the result is a pure verification ID.
  //if the operation is something other than an echo, that should be interpreted
  //as a failure; echos themselves take a null dataset.
  //it is assumed that Find will do the Right Thing, or that the find class is unimportant.
  //however, this function could be extended in the future to validate that a given
  //dataset conforms to the expectations of a particular FIND SOP abstract syntax, if necessary.
  //current tests (7 oct 2010) show that for our test queries, find SOP didn't
  //change the outcome of the search.
  //if it's not a verification context ID, then you can also get the UID associated with the data set.
  //static uint8_t AssignPresentationContextID(const DataSet& inDS, std::string& outUIDString);

  bool operator==(const PresentationContext & pc) const
    {
    assert( TransferSyntaxes.size() == 1 ); // TODO
    assert( pc.TransferSyntaxes.size() == 1 );
    return SubItems == pc.SubItems && TransferSyntaxes == pc.TransferSyntaxes;
    }

private:
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength; // len of last transfer syntax
  uint8_t /*PresentationContext*/ID;
  static const uint8_t Reserved6;
  static const uint8_t Reserved7;
  static const uint8_t Reserved8;
/*
This variable field shall contain the following sub-items: one Abstract
Syntax and one or more Transfer Syntax(es). For a complete
description of the use and encoding of these sub-items see Sections
9.3.2.2.1 and 9.3.2.2.2.
*/

  AbstractSyntax SubItems;
  std::vector<TransferSyntaxSub> TransferSyntaxes;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXT_H
