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

import gdcm
import os,sys

def TestKakadu(filename):
  fn = gdcm.Filename(filename)
  testdir = fn.GetPath()
  testbasename = fn.GetName()
  ext = fn.GetExtension()
  #print ext
  kakadu_path = '/home/mmalaterre/Software/Kakadu60'
  kdu_expand = kakadu_path + '/kdu_expand'
  kdu_args = ' -quiet -i '
  output_dcm = testdir + '/kakadu/' + testbasename
  output_j2k = output_dcm + '.j2k'
  output_raw = output_dcm + '.rawl' # FIXME: little endian only...
  kdu_expand += kdu_args + output_j2k + ' -o ' + output_raw
  # $ ./bin/gdcmraw -i .../TestImageChangeTransferSyntax2/012345.002.050.dcm -o toto.j2k
  executable_output_path = gdcm.GDCM_EXECUTABLE_OUTPUT_PATH
  gdcmraw = executable_output_path + '/gdcmraw'
  outputfilename = output_j2k
  gdcmraw_args = ' -i ' + filename + ' -o ' + outputfilename
  gdcmraw += gdcmraw_args
  #print gdcmraw
  ret = os.system( gdcmraw )
  #print "ret:",ret
  #print kdu_expand
  os.environ["LD_LIBRARY_PATH"]=kakadu_path
  ret = os.system( kdu_expand )
  #print "ret:",ret
  md5 = gdcm.Testing.ComputeFileMD5( output_raw ) 
  # ok this is the md5 as computed after decompression using kdu_expand
  # let see if it match out previously (stored) md5:
  ref = gdcm.Testing.GetMD5FromFile(filename)
  #print ref
  retval = 0
  if ref != md5:
    print "md5 are different: %s should be: %s for file %s"%(md5,ref,filename)
    retval = 1

  return retval

if __name__ == "__main__":
  sucess = 0
  try:
    filename = os.sys.argv[1]
    sucess += TestKakadu( filename )
  except:
    # loop over all files:
    #t = gdcm.Testing()
    #nfiles = t.GetNumberOfFileNames()
    #for i in range(0,nfiles):
    #  filename = t.GetFileName(i)
    #  sucess += TestKakadu( filename )
    d = gdcm.Directory()
    tempdir = gdcm.Testing.GetTempDirectory()
    j2ksubdir = 'TestImageChangeTransferSyntax2' # FIXME hardcoded !
    nfiles = d.Load( tempdir + '/' + j2ksubdir )
    # make sure the output dir for temporary j2k files exists:
    md = gdcm.System.MakeDirectory( tempdir + '/' + j2ksubdir + '/kakadu' ); 
    if not md:
      sys.exit(1)
    files = d.GetFilenames()
    for i in range(0,nfiles):
      filename = files[i]
      sucess += TestKakadu( filename )

  # Test succeed ?
  sys.exit(sucess)

