/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// Implementation detail was shamelessly borowed from the VTK excellent 
// implementation of debug leak manager singleton:
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkDebugLeaks.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmGlobal_h
#define __gdcmGlobal_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Global
 * \note bla
 * Global should be included in any translation unit
 * that will use Dict or that implements the singleton
 * pattern.  It makes sure that the Dict singleton is created
 * before and destroyed after all other singletons in VTK.
 * 
 */
class GlobalInternal;
class Dicts;
class GDCM_EXPORT Global // why expose the symbol I think I only need to expose the instance...
{
public:
  Global();
  ~Global();

  // retrieve the default/internal dicts 
  Dicts const &GetDicts() const;

  // return the singleton instance
  static const Global& GetInstance();

private:
  Global &operator=(const Global &_val); // purposely not implemented
  Global(const Global &_val); // purposely not implemented
  // PIMPL:
  // but we could have also directly exposed a Dicts *Internals;
  static GlobalInternal *Internals;
};

// This instance will show up in any translation unit that uses
// Global or that has a singleton.  It will make sure
// Global is initialized before it is used and is the last
// static object destroyed.
static Global GlobalInstance;

} // end namespace gdcm

#endif //__gdcmGlobal_h

