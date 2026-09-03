/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMVALUELENGTHCHECK_H
#define GDCMVALUELENGTHCHECK_H

#include "gdcmParseException.h"
#include "gdcmTrace.h"

#include <istream>

namespace gdcm_ns
{

/**
 * \brief Reject a declared Value Length the stream cannot supply.
 *
 * Every data element reader sizes its value buffer from the length written
 * in the file and only then reads the value, so a small crafted file that
 * declares a large element makes GDCM allocate that much before the read
 * fails (CVE-2026-3650). Call this before SetLength() on a ByteValue.
 *
 * Throws ParseException rather than Exception on purpose: the fallback
 * parser chain in Reader::InternalReadCommon only catches ParseException,
 * so a plain Exception here would skip the CP246 / UN / VR16 /
 * ExplicitImplicit readers and fail files GDCM can otherwise recover.
 *
 * A stream that cannot report its size is left alone, so non-seekable
 * inputs keep their previous behaviour.
 */
inline void CheckValueLengthAgainstStream(std::istream &is,
                                          const DataElement &de,
                                          uint32_t vl)
{
  // 0xffffffff is the undefined-length sentinel, not a size.
  if( vl == 0xffffffff ) return;

  const std::streampos cur = is.tellg();
  if( cur == std::streampos(-1) ) return;

  is.seekg(0, std::ios::end);
  const std::streampos end = is.tellg();
  is.clear();
  is.seekg(cur);
  if( end == std::streampos(-1) || !is.good() ) return;

  if( static_cast<uint64_t>(end - cur) < static_cast<uint64_t>(vl) )
    {
    gdcmWarningMacro( "Value Length " << vl
      << " exceeds remaining stream size for tag " << de.GetTag() );
    ParseException pe;
    pe.SetLastElement( de );
    throw pe;
    }
}

/**
 * \brief Cap a declared Value Length at what the stream still holds.
 *
 * For the recovery readers (CP246 / UN / VR16 / ExplicitImplicit), which
 * exist precisely to make sense of files whose lengths and VRs are already
 * wrong. Throwing there would end the fallback chain and reject files GDCM
 * can still read -- see SIEMENS_MAGNETOM-12-MONO2-GDCM12-VRUN.dcm, whose
 * (0009,1214) carries a Value Length of 0x20202020, four ASCII spaces.
 *
 * A value can never be longer than the bytes that remain, so capping costs
 * nothing that was readable anyway, and it removes the allocation. This is
 * the same idiom ExplicitImplicitDataElement already uses when it reads a
 * trailing element to end of stream.
 *
 * Returns vl unchanged when the stream cannot report its size.
 */
inline uint32_t ClampValueLengthToStream(std::istream &is, uint32_t vl)
{
  // 0xffffffff is the undefined-length sentinel, not a size: clamping it
  // would destroy the marker the parsers key off.
  if( vl == 0xffffffff ) return vl;

  const std::streampos cur = is.tellg();
  if( cur == std::streampos(-1) ) return vl;

  is.seekg(0, std::ios::end);
  const std::streampos end = is.tellg();
  is.clear();
  is.seekg(cur);
  if( end == std::streampos(-1) || !is.good() ) return vl;

  const uint64_t remaining = static_cast<uint64_t>(end - cur);
  if( remaining < static_cast<uint64_t>(vl) )
    {
    gdcmWarningMacro( "Capping Value Length " << vl << " at remaining stream size "
      << remaining );
    return static_cast<uint32_t>(remaining);
    }
  return vl;
}

} // end namespace gdcm_ns

#endif // GDCMVALUELENGTHCHECK_H
