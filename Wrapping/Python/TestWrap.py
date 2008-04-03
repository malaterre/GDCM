import sys
import os
import gdcm

if __name__ == "__main__":
  dirname = os.sys.argv[1]

  gdcmclasses = dir(gdcm)
  for file in os.listdir(dirname):
    #print file[-2:]
    if file[-2:] != '.h': continue
    #print file[4:-2]
    gdcmclass = file[4:-2]
    if gdcmclass in gdcmclasses:
      print "ok:", gdcmclass
    else:
      print "not wrapped:",gdcmclass
