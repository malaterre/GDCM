/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
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
#include "gdcmTransferSyntax_.h"

namespace gdcm
{

namespace network
{

/**
 Table 9-13
 PRESENTATION CONTEXT ITEM FIELDS
 */
class PresentationContext
{
public:
  PresentationContext();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  size_t Size() const;

  void SetAbstractSyntax( AbstractSyntax const & as );
  AbstractSyntax const &GetAbstractSyntax() const { return SubItems; }

  void AddTransferSyntax( TransferSyntax_ const &ts );

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
  std::vector<TransferSyntax_> TransferSyntaxes;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXT_H
