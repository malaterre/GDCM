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
#include "gdcmRescaler.h"
#include <limits>
#include <stdlib.h> // abort

namespace gdcm
{

// parameter 'size' is in bytes
template <typename TOut, typename TIn>
void RescaleFunction(TOut *out, const TIn *in, double intercept, double slope, size_t size)
{
  size /= sizeof(TIn);
  for(size_t i = 0; i != size; ++i)
  {
    out[i] = (TOut)(slope * in[i] + intercept);
    //assert( out[i] == (TOut)(slope * in[i] + intercept) ); // will really slow down stuff...
  }
}

PixelFormat::ScalarType ComputeBestFit(const PixelFormat &pf, double intercept, double slope)
{
  PixelFormat::ScalarType st = PixelFormat::UNKNOWN;
  assert( slope == (int)slope && intercept == (int)intercept);
  
  double min = slope * pf.GetMin() + intercept;
  double max = slope * pf.GetMax() + intercept;
  assert( min <= max );
  if( min >= 0 ) // unsigned
  {
	  if( max <= std::numeric_limits<uint8_t>::max() )
	  {
		  st = PixelFormat::UINT8;
	  }
	  else if( max <= std::numeric_limits<uint16_t>::max() )
	  {
		  st = PixelFormat::UINT16;
	  }
	  else if( max <= std::numeric_limits<uint32_t>::max() )
	  {
		  st = PixelFormat::UINT32;
	  }
	  else
	  {
		  abort();
	  }
  }
  else
  {
	  if( max <= std::numeric_limits<int8_t>::max() )
	  {
		  st = PixelFormat::INT8;
	  }
	  else if( max <= std::numeric_limits<int16_t>::max() )
	  {
		  st = PixelFormat::INT16;
	  }
	  else if( max <= std::numeric_limits<int32_t>::max() )
	  {
		  st = PixelFormat::INT32;
	  }
	  else
	  {
		  abort();
	  }
   }
	assert( st != PixelFormat::UNKNOWN );
  return st;
}

PixelFormat::ScalarType Rescaler::ComputeInterceptSlopePixelType()
{
  PixelFormat::ScalarType output = PixelFormat::UNKNOWN;
  if( Slope != (int)Slope || Intercept != (int)Intercept)
  {
	  return PixelFormat::FLOAT32;
  }
  double intercept = Intercept;
  double slope = Slope;
  output = ComputeBestFit (PF,intercept,slope);
  assert( output != PixelFormat::UNKNOWN );
  return output;
}


template <typename TIn>
void Rescaler::RescaleFunctionIntoBestFit(char *out, const TIn *in, size_t n)
{
	double intercept = Intercept;
	double slope = Slope;
  PixelFormat::ScalarType output = ComputeInterceptSlopePixelType();
  switch(output)
    {
  case PixelFormat::UINT8:
    RescaleFunction<uint8_t,TIn>((uint8_t*)out,in,intercept,slope,n);
    break;
  case PixelFormat::INT8:
    RescaleFunction<int8_t,TIn>((int8_t*)out,in,intercept,slope,n);
    break;
  case PixelFormat::UINT16:
    RescaleFunction<uint16_t,TIn>((uint16_t*)out,in,intercept,slope,n);
    break;
  case PixelFormat::INT16:
    RescaleFunction<int16_t,TIn>((int16_t*)out,in,intercept,slope,n);
    break;
  case PixelFormat::UINT32:
    RescaleFunction<uint32_t,TIn>((uint32_t*)out,in,intercept,slope,n);
    break;
  case PixelFormat::INT32:
    RescaleFunction<int32_t,TIn>((int32_t*)out,in,intercept,slope,n);
    break;
  case PixelFormat::FLOAT32:
    RescaleFunction<float,TIn>((float*)out,in,intercept,slope,n);
    break;
  default:
    abort();
    break;
    }
 }


bool Rescaler::Rescale(char *out, const char *in, size_t n)
{
  // check if we are dealing with floating point type
  if( Slope != (int)Slope || Intercept != (int)Intercept)
  {
  // need to rescale as float (32bits) as slope/intercept are 32bits
  //abort();
  }
  // else integral type
  switch(PF)
    {
  case PixelFormat::UINT8:
    RescaleFunctionIntoBestFit<uint8_t>(out,(uint8_t*)in,n);
    break;
  case PixelFormat::INT8:
    RescaleFunctionIntoBestFit<int8_t>(out,(int8_t*)in,n);
    break;
  case PixelFormat::UINT12:
    //RescaleFunctionIntoBestFit<uint12_t>(out,in,n);
    abort();
    break;
  case PixelFormat::INT12:
    //RescaleFunctionIntoBestFit<int12_t>(out,in,n);
    abort();
    break;
  case PixelFormat::UINT16:
    RescaleFunctionIntoBestFit<uint16_t>(out,(uint16_t*)in,n);
    break;
  case PixelFormat::INT16:
    RescaleFunctionIntoBestFit<int16_t>(out,(int16_t*)in,n);
    break;
  case PixelFormat::UINT32:
    RescaleFunctionIntoBestFit<uint32_t>(out,(uint32_t*)in,n);
    break;
  case PixelFormat::INT32:
    RescaleFunctionIntoBestFit<int32_t>(out,(int32_t*)in,n);
    break;
  default:
    abort();
    break;
    }
 
  return true;
}

} // end namespace gdcm

