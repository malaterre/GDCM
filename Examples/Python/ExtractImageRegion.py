############################################################################
#
#  Program: GDCM (Grassroots DICOM). A DICOM library
#
#  Copyright (c) 2006-2011 Mathieu Malaterre
#  All rights reserved.
#  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.
#
#     This software is distributed WITHOUT ANY WARRANTY; without even
#     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#     PURPOSE.  See the above copyright notice for more information.
#
############################################################################

"""

 This small code shows how to use the gdcm.ImageRegionReader API
 In this example we are taking each frame by frame and dump them to
 /tmp/frame.raw.

 Usage:
 $ ExtractImageRegion.py input.dcm

 Example:
 $ ExtractImageRegion.py gdcmData/012345.002.050.dcm
 $ md5sum /tmp/frame.raw
 d594a5e2fde12f32b6633ca859b4d4a6  /tmp/frame.raw
 $ gdcminfo --md5sum gdcmData/012345.002.050.dcm
 [...]
 md5sum: d594a5e2fde12f32b6633ca859b4d4a6
"""

import gdcm

if __name__ == "__main__":
  import sys
  filename = sys.argv[1]

  file_size = gdcm.System.FileSize(filename);

  # instantiate the reader:
  reader = gdcm.ImageRegionReader();
  reader.SetFileName( filename );

  # pull DICOM info:
  if not reader.ReadInformation():
    sys.exit(1)

  # store current offset:
  cur_pos = reader.GetStreamCurrentPosition();

  remaining = file_size - cur_pos;

  print("Remaining bytes to read (Pixel Data): %d" % remaining );

  # Get file infos
  f = reader.GetFile();

  # get some info about image
  dims = gdcm.ImageHelper.GetDimensionsValue(f);
  print(dims)
  pf = gdcm.ImageHelper.GetPixelFormatValue (f);
  pixelsize = pf.GetPixelSize();
  pi = gdcm.ImageHelper.GetPhotometricInterpretationValue(f);
  print( pi );

  # buffer to get the pixels
  buffer = bytearray( dims[0] * dims[1] * pixelsize )

  # define a simple box region.
  box = gdcm.BoxRegion();
  for z in range(0, dims[2]):
    # Define that I want the image 0, full size (dimx x dimy pixels)
    # and do that for each z:
    box.SetDomain(0, dims[0] - 1, 0, dims[1] - 1, z, z);
    #print( box.toString() );
    reader.SetRegion( box );

    # reader will try to load the uncompressed image region into buffer.
    # the call returns an error when buffer.Length is too small. For instance
    # one can call:
    # uint buf_len = reader.ComputeBufferLength(); // take into account pixel size
    # to get the exact size of minimum buffer
    if reader.ReadIntoBuffer(buffer):
      open('/tmp/frame.raw', 'wb').write(buffer)
    else:
      #throw new Exception("can't read pixels error");
      sys.exit(1)
