#! /usr/bin/env python

import re,os

if __name__ == "__main__":
  argc = len(os.sys.argv )
  if ( argc < 3 ):
    print "Sorry, wrong list of args"
    os.sys.exit(1) #error

  inputfilename = os.sys.argv[1]
  outputfilename = os.sys.argv[2]

  infile = file(inputfilename, 'r')
  outLines = []
  owner = "GEMS_GENIE_1"
  for line in infile.readlines():
    patt = re.compile("^\s*([A-Za-z0-9 ()-]+)\s+\(([0-9A-Z]+),([0-9A-Zx]+)\)\s+([A-Z][A-Z])\s+([1-9Nn-]+)\s*$")
    m = patt.match(line)
    #print line
    if m:
      # <entry group="0001" element="0001" vr="LO" vm="1" owner="Private Creator"/>
      dicom = "<entry group=\"%s\" element=\"%s\" vr=\"%s\" vm=\"%s\" owner=\"%s\"/>"%(m.group(2),m.group(3),m.group(4),m.group(5),owner)
      #dicom = m.group(1) + ' ' + m.group(2) + ' ' + m.group(3) + ' ' + m.group(4)
      print dicom
    #else:
    #  print line
    #print self.Reformat(line)
    #outLines.append( self.Reformat(line) + '\n' )
  outfile = file(outputfilename, 'w')
  outfile.writelines( outLines )
  outfile.close()

