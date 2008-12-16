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

"""
Usage:

 python 
"""

import vtkgdcm
import vtk
import sys
import gdcm

filename = sys.argv[1]
outfilename = sys.argv[2]
tmpfile = "/tmp/philips_rescaled.dcm"

vtkreader = vtkgdcm.vtkGDCMImageReader()
vtkreader.SetFileName( filename )
vtkreader.Update()


# (2005,1409)     DS      4       0.0
# (2005,140a)     DS      16      1.52283272283272

# (2005,0014)     LO      26      Philips MR Imaging DD 005
tag1 = gdcm.PrivateTag(0x2005,0x09,"Philips MR Imaging DD 005")
tag2 = gdcm.PrivateTag(0x2005,0x0a,"Philips MR Imaging DD 005")



# Need to access some private tags, reread the file (for now):
reader = gdcm.Reader()
reader.SetFileName( filename )
if not reader.Read():
  sys.exit(1)

ds = reader.GetFile().GetDataSet()

el1 = ds.GetDataElement( tag1 )
el2 = ds.GetDataElement( tag2 )


#pf = gdcm.PythonFilter()
#pf.SetFile( reader.GetFile() )
#print el1.GetTag()

print el1.GetByteValue()
v1 = eval(el1.GetByteValue().GetBuffer())
print el2.GetByteValue()
v2 = eval(el2.GetByteValue().GetBuffer())

print v1
shift = v1
print v2
scale = v2

ss = vtk.vtkImageShiftScale()
ss.SetInput( vtkreader.GetOutput() )
# because VTK image shift / scale convention is inverted from DICOM make sure shift is 0
assert shift == 0
ss.SetShift( shift )
ss.SetScale( scale )
ss.SetOutputScalarTypeToUnsignedShort ()
ss.Update()

# vtkGDCMImageWriter does not support Sequence, so let's write a tmp file first:
vtkwriter = vtkgdcm.vtkGDCMImageWriter()
vtkwriter.SetFileName( tmpfile )
vtkwriter.SetMedicalImageProperties( vtkreader.GetMedicalImageProperties() )
vtkwriter.SetDirectionCosines( vtkreader.GetDirectionCosines() )
vtkwriter.SetInput( ss.GetOutput() )
#vtkwriter.Update()
vtkwriter.Write()

# ok now rewrite the exact same file as the original (keep all info)
# but use the Pixel Data Element from the written file
tmpreader = gdcm.ImageReader()
tmpreader.SetFileName( tmpfile )
if not tmpreader.Read():
  sys.exit(1)

writer = gdcm.ImageWriter()
writer.SetFileName( outfilename )
# Pass image from vtk written file
writer.SetImage( tmpreader.GetImage() )
# pass dataset from initial 'reader'
writer.SetFile( reader.GetFile() )
if not writer.Write():
  sys.exit(1)

print "success"

