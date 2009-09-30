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
#include "gdcmVR.h"
#include "gdcmAttribute.h"
#include "gdcmByteValue.h"

#include <sstream>
#include <iostream>
#include <iomanip>

#include <math.h> // atof

#define MIN_EXP 5

template < typename Float >
std::string to_string ( Float data ) {
 std::stringstream in;
 // in.imbue(std::locale::classic()); // This is not required AFAIK

 unsigned long digits = 15; // 16 - 1 (dot)

 if (data < 0)
   digits -= 1; // (minus)
 if (data != 0) {
   Float ldata = log10(fabs(data));
   if ( ldata > MIN_EXP || ldata < -MIN_EXP+1 ) {
     in << std::scientific;
     digits -= 5; // (first digit + exponential)
   } else if( ldata < 0) {
     digits += ldata; // (zeros before first significant digit)
   }
 }

// I don't know if you really need this check
 unsigned long const max_digits =
   static_cast< unsigned long >(
   - std::log( std::numeric_limits<Float>::epsilon() )
   / std::log( 10.0 ) );
 digits = (digits > max_digits) ? max_digits : digits;


 if ( in << std::dec << std::setprecision(digits) << data )
   return ( in.str() );
 else
   throw "Impossible Conversion"; // should not happen ...
}

/*
 * Test to make sure that double precision ieee 'double' is ok for DICOM VR = 'DS'
 */
int TestDS(int, char *[])
{

  const double d1 = -118.242525316066;
  const double d2 = 0.00149700609543456;
  const double d3 = 0.059303515816892;

  // I need to test equality to 16 to check maximum precision for those
  std::string s1 = to_string( d1 );
  std::cout << s1 << std::endl;
  if( s1.size() != 16 ) return 1;
  std::string s2 = to_string( d2 );
  std::cout << s2 << std::endl;
  if( s2.size() != 16 ) return 1;
  std::string s3 = to_string( d3 );
  std::cout << s3 << std::endl;
  if( s3.size() != 16 ) return 1;


  // "5.93035158168e-4" -> 16
  // "0.000593035158168" -> 17
  const double d4 = 0.000593035158168;
  std::string s4 = to_string( d4 );
  std::cout << s4 << std::endl;
//  if( s4.size() != 16 ) return 1;

  const double d5 = 5.1e-4;
  std::string s5 = to_string( d5 );
  std::cout << s5 << std::endl;
//  if( s5.size() > 6 ) return 1;

  const double d6 = 5.1e-10;
  std::string s6 = to_string( d6 );
  std::cout << s6 << std::endl;
  if( s6.size() != 16 ) return 1;

  const double d7 = 1234567890123456.; // 16 bytes
  std::string s7 = to_string( d7 );
  std::cout << s7 << std::endl;
//  if( s7.size() != 16 ) return 1;
  const double d7_error = d7 - atof( s7.c_str() );
  std::cout << "Absoulte Error is: " << d7_error << std::endl;

  return 0;
}

