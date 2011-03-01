/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMPRESENTATIONCONTEXTGENERATOR_H
#define GDCMPRESENTATIONCONTEXTGENERATOR_H

#include "gdcmDirectory.h"
#include "gdcmPresentationContext.h"

namespace gdcm
{

namespace network
{

/**
 * \brief PresentationContextGenerator
 * \see PresentationContext
 */
class GDCM_EXPORT PresentationContextGenerator
{
public:
  PresentationContextGenerator();

  bool GenerateFromUID(UIDs::TSName tsname);
  bool GenerateFromFilenames(const Directory::FilenamesType &files);

  typedef std::vector<PresentationContext> PresentationContextArrayType;
  typedef PresentationContextArrayType::size_type SizeType;
  PresentationContextArrayType const &GetPresentationContexts() { return PresContext; }

protected:
  bool AddPresentationContext( AbstractSyntax const & as, TransferSyntaxSub const & ts );

private:
  std::vector<PresentationContext> PresContext;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXTGENERATOR_H
