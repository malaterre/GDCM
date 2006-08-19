/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmIOS_h
#define __gdcmIOS_h

#include "gdcmSwapCode.h"
#include <assert.h>
//#include <streambuf>

namespace gdcm
{

/**
 * \brief Wrapper around ios
 * \note bla
 */

class GDCM_EXPORT IOS
{
public:
  IOS (SwapCode const &sc = SwapCode::Unknown);
  virtual ~IOS();

  virtual operator void * ( ) const { assert(0); return 0; }

  SwapCode const &GetSwapCode() const { return SwapCodeValue; }
  void SetSwapCode(SwapCode const &sc) { SwapCodeValue = sc; }

private:
  // SwapCode of the file once figured out (can be Unknown)
  SwapCode SwapCodeValue;

  IOS(IOS const&);
  IOS &operator= (IOS const&);
};

}

#endif //__gdcmIOS_h

