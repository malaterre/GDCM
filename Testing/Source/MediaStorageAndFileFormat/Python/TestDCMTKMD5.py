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
import os,sys,re

def TestDCMTKMD5( filename, verbose = False ):
  #print filename
  dcmdump_exec = "dcmdump -dc -E +P 2,10 -s " + filename + " 2> /dev/null"
  #print dcmdump_exec
  f = os.popen(dcmdump_exec)
  ret = f.read()
  #assert ret == 0
  #print ret
  jpegre = re.compile('^.*JPEGLossless.*$')
  rlere = re.compile('^.*RLELossless.*$')
  lexre = re.compile('^.*LittleEndianExplicit.*$')
  leire = re.compile('^.*LittleEndianImplicit.*$')
  testing = gdcm.Testing()
  outputdir = testing.GetTempDirectory( "TestDCMTKMD5" )
  gdcm.System.MakeDirectory( outputdir )
  outputfilename = testing.GetTempFilename( filename, "TestDCMTKMD5" )
  executable_output_path = gdcm.GDCM_EXECUTABLE_OUTPUT_PATH
  gdcmraw = executable_output_path + '/gdcmraw'

  if not ret:
    print "empty, problem with:", filename
    return 0
  elif type(ret) != type(''):
    print "problem of type with:", filename
    return 0
  #print ret
  #print ret.__class__
  elif( jpegre.match( ret ) ):
    #print "jpeg: ",filename
    dcmdjpeg_exec = "dcmdjpeg " + filename + " " + outputfilename
    ret = os.system( dcmdjpeg_exec )

    gdcmraw_args = ' -i ' + outputfilename + ' -o ' + outputfilename + ".raw"
    gdcmraw += gdcmraw_args
    #print gdcmraw
    ret = os.system( gdcmraw )
    md5 = gdcm.Testing.ComputeFileMD5( outputfilename + ".raw" ) 
    ref = gdcm.Testing.GetMD5FromFile(filename)
    #print md5
    retval  = 0
    if ref != md5:
      print "md5 are different: %s should be: %s for file %s"%(md5,ref,filename)
      retval = 1
    #print outputfilename
    return retval
  elif( rlere.match( ret ) ):
    #print "rle: ",filename
    dcmdrle_exec = "dcmdrle " + filename + " " + outputfilename
    ret = os.system( dcmdrle_exec )

    gdcmraw_args = ' -i ' + outputfilename + ' -o ' + outputfilename + ".raw"
    gdcmraw += gdcmraw_args
    #print gdcmraw
    ret = os.system( gdcmraw )
    md5 = gdcm.Testing.ComputeFileMD5( outputfilename + ".raw" ) 
    ref = gdcm.Testing.GetMD5FromFile(filename)
    #print md5
    retval  = 0
    if ref != md5:
      print "md5 are different: %s should be: %s for file %s"%(md5,ref,filename)
      retval = 1
    #print outputfilename
    return retval
  elif( lexre.match( ret ) or leire.match(ret) ):
    #print "rle: ",filename
    #dcmdrle_exec = "dcmdrle " + filename + " " + outputfilename
    #ret = os.system( dcmdrle_exec )

    gdcmraw_args = ' -i ' + filename + ' -o ' + outputfilename + ".raw"
    gdcmraw += gdcmraw_args
    #print gdcmraw
    ret = os.system( gdcmraw )
    md5 = gdcm.Testing.ComputeFileMD5( outputfilename + ".raw" ) 
    ref = gdcm.Testing.GetMD5FromFile(filename)
    #print md5
    retval  = 0
    if ref != md5:
      print "md5 are different: %s should be: %s for file %s"%(md5,ref,filename)
      retval = 1
    #print outputfilename
    return retval
  #else
  print "Unhandled:",filename
  return 1

if __name__ == "__main__":
  sucess = 0
  try:
    filename = os.sys.argv[1]
    sucess += TestDCMTKMD5( filename, True )
  except:
    # loop over all files:
    t = gdcm.Testing()
    nfiles = t.GetNumberOfFileNames()
    for i in range(0,nfiles):
      filename = t.GetFileName(i)
      sucess += TestDCMTKMD5( filename )
  
  
  # Test succeed ?
  sys.exit(sucess)


