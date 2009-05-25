/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmCommand_h
#define __gdcmCommand_h

#include "gdcmSubject.h"

namespace gdcm
{
class Event;
/**
 * \class Command
 * \brief superclass for callback/observer methods
 *
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Command : public Subject
{
public :
  /// Abstract method that defines the action to be taken by the command.
  virtual void Execute(Subject *caller, const Event & event ) = 0;

  /** Abstract method that defines the action to be taken by the command.
   * This variant is expected to be used when requests comes from a 
   * const Object */
  virtual void Execute(const Subject *caller, const Event & event ) = 0;

protected:
  Command();
  ~Command();

private:
  Command(const Command&);  // Not implemented.
  void operator=(const Command&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmCommand_h
