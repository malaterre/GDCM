############################################################################
#
#  Program: GDCM (Grass Root DICOM). A DICOM library
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

from vtk import vtkStringArray
from vtk import vtkDirectory
from vtk import vtkStructuredPointsWriter
from vtk.util import vtkConstants as vtkType
import vtkgdcm
import os,sys

def PrintProgress(object, event):
  assert event == "ProgressEvent"
  print "Progress:", object.GetProgress()

# Helper function to extract image dimension and type
# this info could also be coming from a database for example instead of read from a particular file
def ExecuteInformation(reader, filenames):
  import gdcm
  assert filenames.GetNumberOfValues() # Need at least one file
  reffile = filenames.GetValue(0) # Take first image as reference
  #print reader
  r = gdcm.ImageReader()
  r.SetFileName( reffile )
  sucess = r.Read()
  assert sucess
  #print r.GetImage().Print()
  image = r.GetImage()
  assert image.GetNumberOfDimensions() == 2 or image.GetNumberOfDimensions() == 3
  dims = [0,0,0]
  dims[0] = image.GetDimension(0)
  dims[1] = image.GetDimension(1)
  dims[2] = filenames.GetNumberOfValues()
  #print dims
  #print image.GetPixelFormat().GetTPixelFormat()
  pixelformat = image.GetPixelFormat().GetScalarType()
  datascalartype = vtkType.VTK_VOID # dummy should not happen
  if pixelformat == gdcm.PixelFormat.INT8:
    datascalartype = vtkType.VTK_SIGNED_CHAR
  elif pixelformat == gdcm.PixelFormat.UINT8:
    datascalartype = vtkType.VTK_UNSIGNED_CHAR
  elif pixelformat == gdcm.PixelFormat.INT16:
    datascalartype = vtkType.VTK_SHORT
  elif pixelformat == gdcm.PixelFormat.UINT16:
    datascalartype = vtkType.VTK_UNSIGNED_SHORT
  else:
    print "Unhandled PixelFormat: ", pixelformat
    sys.exit(1)
  #print datascalartype
  numberOfScalarComponents = image.GetPixelFormat().GetSamplesPerPixel()
  #print numberOfScalarComponents
  #print gdcm.PhotometricInterpretation.GetPIString( image.GetPhotometricInterpretation().PIType() )
  #reader.SetDataExtent( dataextent );
  reader.SetDataExtent( 0, dims[0] - 1, 0, dims[1] - 1, 0, dims[2] - 1 )
  reader.SetDataScalarType ( datascalartype )

if __name__ == "__main__":
  try:
    filename = os.sys.argv[1]
  except:
    # failure
    print "Need a filename"
    sys.exit(1)
  
  # setup reader
  r = vtkgdcm.vtkGDCMThreadedImageReader()
  r.FileLowerLeftOn()
  dir = vtkDirectory()
  
  # Did user pass in a directory:
  if dir.FileIsDirectory( filename ):
    dir.Open( filename )
    files = dir.GetFiles()
    # Need to construct full path out of the simple filename
    fullpath = vtkStringArray()
    for i in range(0, files.GetNumberOfValues()):
      if files.GetValue(i) != '.' and files.GetValue(i) != '..': # sigh !
        fullpath.InsertNextValue( os.path.join(filename, files.GetValue(i) ))
    r.SetFileNames( fullpath )
    ExecuteInformation(r, fullpath)
    #r.AddObserver("ProgressEvent", PrintProgress)
    r.Update()
    print r.GetOutput()
    # Write output
    writer = vtkStructuredPointsWriter()
    writer.SetInput( r.GetOutput() )
    writer.SetFileName( "TestvtkGDCMThreadedImageReaderPython.vtk" )
    writer.SetFileTypeToBinary()
    #writer.Write()
  else:
    # TODO
    sys.exit(1)
  
  
  # Test succeed ?
  #sys.exit(sucess != 1)

