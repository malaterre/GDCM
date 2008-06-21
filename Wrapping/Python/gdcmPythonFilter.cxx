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
#include "gdcmPythonFilter.h"
#include "gdcmGlobal.h"
#include "gdcmElement.h"
#include "gdcmByteValue.h"
#include "gdcmAttribute.h"


namespace gdcm
{

PythonFilter::PythonFilter():F(new File)
{
}
//-----------------------------------------------------------------------------
PythonFilter::~PythonFilter()
{
}

void PythonFilter::SetDicts(const Dicts &dicts)
{
  abort(); // FIXME
}

PyObject *PythonFilter::ToPyObject(const Tag& t) const
{
  const Global &g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const DataSet &ds = GetFile().GetDataSet();
  if( ds.IsEmpty() || !ds.FindDataElement(t) )
    {
    gdcmWarningMacro( "DataSet is empty or does not contains tag:" );
    return 0;
    }
  if( t.IsPrivate() )
    {
    return 0;
    }

  const DataElement &de = ds.GetDataElement( t );
  assert( de.GetTag().IsPublic() );
  const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
  if( entry.GetVR() == VR::INVALID )
    {
    // FIXME This is a public element we do not support...
    //throw Exception();
    return 0;
    }

  VR vr = entry.GetVR();
  // If Explicit override with coded VR:
  if( de.GetVR() != VR::INVALID && de.GetVR() != VR::UN )
    {
    vr = de.GetVR();
    }
  assert( vr != VR::UN && vr != VR::INVALID );
  //std::cerr << "Found " << vr << " for " << de.GetTag() << std::endl;
  if( VR::IsASCII( vr ) )
    {
    assert( vr & VR::VRASCII );
    if( de.IsEmpty() )
    {
	    return 0;
    }
    else
    {
    const ByteValue *bv = de.GetByteValue();
      std::string s( bv->GetPointer(), bv->GetLength() );
      s.resize( std::min( s.size(), strlen( s.c_str() ) ) ); // strlen is garantee to be lower or equal to ::size()
      // http://www.python.org/doc/current/ext/buildValue.html
      PyObject *o = Py_BuildValue("s", s.c_str() );
      Py_INCREF(o);
      return o;
    }
    }
 
      PyObject *o = Py_BuildValue("s", "unhandled" );
      Py_INCREF(o);

   return o;
}

}
