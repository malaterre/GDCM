############################################################################
#
#  Program: GDCM (Grassroots DICOM). A DICOM library
#  Module:  $URL$
#
#  Copyright (c) 2006-2008 Mathieu Malaterre
#  All rights reserved.
#  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.
#
#     This software is distributed WITHOUT ANY WARRANTY; without even
#     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#     PURPOSE.  See the above copyright notice for more information.
#
############################################################################

import gdcm
import sys

r = gdcm.Reader()
r.SetFileName('test.acr')
r.Read()

f = gdcm.PythonFilter()
f.SetFile( r.GetFile() )
t = gdcm.Tag( 0x8, 0x8 )
print f.ToPyObject( t )
t = gdcm.Tag( 0x8, 0x1010 )
print f.ToPyObject( t )
t = gdcm.Tag( 0x20, 0x32 )
print f.ToPyObject( t )
t = gdcm.Tag( 0x28, 0x10 )
print f.ToPyObject( t )
