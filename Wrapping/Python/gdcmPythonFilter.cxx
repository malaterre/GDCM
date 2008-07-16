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

#include <sstream>

namespace gdcm
{
// Py_BuildValue:
// http://www.python.org/doc/1.5.2p2/ext/buildValue.html

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
  VM vm = entry.GetVM();
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
      // http://mail.python.org/pipermail/python-list/2002-April/137612.html
        unsigned int count = VM::GetNumberOfElementsFromArray(bv->GetPointer(), bv->GetLength());
        //CSComp el[4];
        std::stringstream ss;
        ss << s;
/*
        unsigned int i = 0;
        while( i < count && ss >> el[i] )
        {
                ++i;
        }
*/
        Element<VR::CS,VM::VM4> el;
        el.Set( de.GetValue() );
//std::cout << "DEBUG:" << el[0] << std::endl;
//std::cout << "DEBUG:" << el[1] << std::endl;
//std::cout << "DEBUG:" << el[2] << std::endl;
//std::cout << "DEBUG:" << el[3] << std::endl;
//std::cout << "DEBUG:" << count << std::endl;
        //ss >> el[0];
        //ss >> el[1];
        //ss >> el[2];
      //PyObject *o = Py_BuildValue("s", s.c_str() );
      //PyObject *o = Py_BuildValue("s", el[0].c_str() );
PyObject* tuple = PyTuple_New(count);

    for (int i = 0; i < count; i++) {
        //double rVal = data[i];
        //PyTuple_SetItem(tuple, i, Py_BuildValue("d", rVal));
        const char *s = el[i];
        PyTuple_SetItem(tuple, i, Py_BuildValue("s", s));
    }
PyObject *o = tuple;


      Py_INCREF(o);
      return o;
    }
    }
 
      PyObject *o = Py_BuildValue("s", "unhandled" );
      Py_INCREF(o);

   return o;
}

}
