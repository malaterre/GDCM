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
#include "gdcmAnonymizer.h"
#include "gdcmDicts.h"
#include "gdcmGlobal.h"

namespace gdcm
{

Anonymizer::~Anonymizer()
{
}

void Anonymizer::Empty( Tag const &t)
{
  Replace(t, "", 0);
}

void Anonymizer::Remove( Tag const &t )
{
  DataSet &ds = F->GetDataSet();
  ds.Remove( t );
}

bool Anonymizer::Replace( Tag const &t, const char *value )
{
  size_t len = 0;
  if( value )
    {
    len = strlen( value );
    }
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  DataSet &ds = F->GetDataSet();
  // Let's do the private tag:
  bool ret = false;
  if ( t.IsPrivate() )
    {
    // Only one operation is allowed: making a private tag empty ...
    if ( len == 0 )
      {
      if( ds.FindDataElement( t ) )
        {
        DataElement de ( ds.GetDataElement(t) );
        if ( de.GetVR() != VR::INVALID )
          {
          assert( de.GetVR() != VR::SQ );
          }
        de.SetByteValue( "", len );
        ds.Insert( de );
        ret = true;
        }
      else
        {
        // TODO
        assert( 0 && "TODO" );
        }
      }
    }
  else
    {
    // Ok this is a public element
    assert( t.IsPublic() );
    const DictEntry &dictentry = dicts.GetDictEntry(t);
    if ( dictentry.GetVR() == VR::INVALID 
      || dictentry.GetVR() == VR::UN 
      || dictentry.GetVR() == VR::SQ
    )
      {
      // Let's give up !
      gdcmWarningMacro( "Cannot process tag: " << t << " with vr: " << dictentry.GetVR() );
      }
    else if ( dictentry.GetVR() & VR::VRBINARY )
      {
      gdcmWarningMacro( "You need to explicitely specify the length for this type of vr: " << dictentry.GetVR() );
      }
    else
      {
      // vr from dict seems to be ascii, so it seems resonable to write a ByteValue here:
      assert( dictentry.GetVR() & VR::VRASCII );
      assert( value );
      std::string padded( value, len );
      // All ASCII VR needs to be padded with a space
      if( len % 2 )
        {
        if( dictentry.GetVR() == VR::UI )
          {
          // \0 is automatically added when using a ByteValue
          }
        else
          {
          padded += " ";
          }
        }
      if( ds.FindDataElement( t ) )
        {
        DataElement de ( ds.GetDataElement(t) );
        de.SetByteValue( padded.c_str(), padded.size() );
        ds.Replace( de );
        }
      else
        {
        DataElement de( t );
        de.SetVR( dictentry.GetVR() );
        de.SetByteValue( padded.c_str(), padded.size() );
        ds.Replace( de );
        }
      ret = true;
      }
    }
  return true;
}

bool Anonymizer::Replace( Tag const &t, const char *value, VL const & vl )
{
  return true;
}

bool Anonymizer::Anonymize()
{
  return true;
}

} // end namespace gdcm

