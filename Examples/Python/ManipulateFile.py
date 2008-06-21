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

"""
Usage:

 python ManipulateFile.py input.dcm output.dcm

Footnote:
  GDCM 1.2.x would create incorrect Multiframes MR Image Storage file. Try to recover from
  the issues to recreate a MultiframeGrayscaleByteSecondaryCaptureImageStorage file.
  e.g:

  python ManipulateFile.py Insight/Testing/Temporary/itkGDCMImageIOTest5-j2k.dcm manipulated.dcm 
"""

import sys
import gdcm

if __name__ == "__main__":

  file1 = sys.argv[1]
  file2 = sys.argv[2]

  r = gdcm.Reader()
  r.SetFileName( file1 )
  if not r.Read():
    sys.exit(1)
  
  ano = gdcm.Anonymizer()
  ano.SetFile( r.GetFile() )
  ano.Replace( gdcm.Tag(0x0008,0x0016), "1.2.840.10008.5.1.4.1.1.7.2" )
  ano.Remove( gdcm.Tag(0x0018,0x0020) ) # ScanningSequence
  ano.Remove( gdcm.Tag(0x0018,0x0021) ) # SequenceVariant
  ano.Remove( gdcm.Tag(0x0018,0x0022) ) # ScanOptions
  ano.Remove( gdcm.Tag(0x0018,0x0023) ) # MRAcquisitionType
  ano.Remove( gdcm.Tag(0x0018,0x0050) ) # SliceThickness
  ano.Remove( gdcm.Tag(0x0018,0x0080) ) # RepetitionTime
  ano.Remove( gdcm.Tag(0x0018,0x0081) ) # EchoTime
  ano.Remove( gdcm.Tag(0x0018,0x0088) ) # SpacingBetweenSlices
  ano.Remove( gdcm.Tag(0x0018,0x0091) ) # EchoTrainLength
  ano.Remove( gdcm.Tag(0x0018,0x1164) ) # ImagerPixelSpacing
  
  ano.Remove( gdcm.Tag(0x0020,0x0032) ) # Image Position (Patient)
  ano.Remove( gdcm.Tag(0x0020,0x0037) ) # Image Orientation (Patient)
  ano.Remove( gdcm.Tag(0x0020,0x0052) ) # Frame of Reference UID
  ano.Remove( gdcm.Tag(0x0020,0x1040) ) # Position Reference Indicator
  
  ano.Replace( gdcm.Tag(0x0028,0x0301), "NO" ) # Burned In Annotation
  
  ano.Empty( gdcm.Tag(0x0020,0x0020) )
  
  ano.Remove( gdcm.Tag(0x7fe0,0x0000) )
  
  #ano.Empty( gdcm.Tag(0x0028,0x0009) ) # Frame Increment Pointer
  
  #ano.Empty( gdcm.Tag(0x0028,0x1052) )  #<entry group="0028" element="1052" vr="DS" vm="1" name="Rescale Intercept"/>
  #ano.Empty( gdcm.Tag(0x0028,0x1053) )  #<entry group="0028" element="1053" vr="DS" vm="1" name="Rescale Slope"/>
  #ano.Replace( gdcm.Tag(0x0028,0x1054), "US" )  #<entry group="0028" element="1054" vr="LO" vm="1" name="Rescale Type"/>
  
  ano.Replace( gdcm.Tag(0x2050, 0x0020), "IDENTITY")

  w = gdcm.Writer()
  w.SetFile( ano.GetFile() )
  w.SetFileName( file2 )
  if not w.Write():
    sys.exit(1)
 
