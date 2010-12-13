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
#ifndef GDCMSERVICECLASSUSER_H
#define GDCMSERVICECLASSUSER_H

#include "gdcmSubject.h"

namespace gdcm
{
class ServiceClassUserInternals;
/**
 * \brief ServiceClassUser
 */
class GDCM_EXPORT ServiceClassUser : public Subject
{
public:
  /// Construct a SCU with default:
  /// - hostname = localhost
  /// - port = 104
  ServiceClassUser();
  ~ServiceClassUser();

  /// set calling ae title
  void SetAETitle(const char *aetitle);
  const char *GetAETitle() const;

  /// set called ae title
  void SetCalledAETitle(const char *aetitle);
  const char *GetCalledAETitle() const;

  /// set/get Timeout
  void SetTimeout(time_t t);
  time_t GetTimeout(time_t t) const;

  void Receive();
  void Send();

private:
  ServiceClassUserInternals *Internals;
};

}

#endif // GDCMSERVICECLASSUSER_H
