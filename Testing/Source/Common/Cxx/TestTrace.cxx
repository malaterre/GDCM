/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTrace.h"

#include <iostream>

int TestTrace(int, char *[])
{
  gdcm::Trace t; //initializes all macros to 'off'

  gdcmDebugMacro( "DebugKO" );
  gdcmWarningMacro( "WarningKO" );
  gdcmErrorMacro( "ErrorKO" );

  // test the SetStream interface
  std::ostringstream useros;
  gdcm::Trace::SetStream( useros );

  gdcmDebugMacro( "DebugOK_OFF" );
  gdcmWarningMacro( "WarningOK_OFF" );
  gdcmErrorMacro( "ErrorOK_OFF" );

  gdcm::Trace::DebugOn();
  gdcm::Trace::WarningOn();
  gdcm::Trace::ErrorOn();

  gdcmDebugMacro( "DebugOK_ON" );
  gdcmWarningMacro( "WarningOK_ON" );
  gdcmErrorMacro( "ErrorOK_ON" );

  //in release mode, tracing just doesn't work any more, so this test isn't valid.
#ifndef NDEBUG
  std::string result = useros.str();
  if( result.find( "KO" ) != std::string::npos )
    {
    std::cerr << result << std::endl;
    return 1;
    }
  if( result.find( "OFF" ) != std::string::npos )
    {
    std::cerr << result << std::endl;
    return 1;
    }

  // opposite:
  if( result.find( "OK" ) == std::string::npos )
    {
    std::cerr << result << std::endl;
    return 1;
    }
  if( result.find( "ON" ) == std::string::npos )
    {
    std::cerr << result << std::endl;
    return 1;
    }
#endif
  return 0;
}
