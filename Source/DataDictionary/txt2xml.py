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
    patt = re.compile("^\s*([A-Za-z0-9 ()>-]+)\s+\(([0-9A-Z]+),([0-9A-Zx]+)\)\s+([A-Z][A-Z])\s+([1-9Nn-]+)\s*$")
    patt2 = re.compile( "^\s*(Table [A-Z1-9-]+).\s*([A-Za-z -]+)\s*\(([A-Z0-9_]+)\)$")
    m = patt.match(line)
    m2 = patt2.match(line)
    #print line
    if m:
      # <entry group="0001" element="0001" vr="LO" vm="1" owner="Private Creator"/>
      dicom = "<entry group=\"%s\" element=\"%s\" vr=\"%s\" vm=\"%s\">"%(m.group(2),m.group(3),m.group(4),m.group(5))
      #dicom = m.group(1) + ' ' + m.group(2) + ' ' + m.group(3) + ' ' + m.group(4)
      #print dicom
      dicom += '\n'
      dicom += "<description>%s</description>\n</entry>\n"%m.group(1).rstrip()
      outLines.append( dicom )
    elif m2:
      # <dict edition="2007" url="http://??" ref="Table A-16" name="Private Creator Identification - Xeleris" owner="GEMS_GENIE_1">
      s = "<dict ref=\"%s\" name=\"%s\" owner=\"%s\">"%(m2.group(1),m2.group(2).rstrip(),m2.group(3))
      s += '\n'
      outLines.append( s )
    else:
      print line
    #print self.Reformat(line)
    #outLines.append( self.Reformat(line) + '\n' )
  outfile = file(outputfilename, 'w')
  outfile.writelines( outLines )
  outfile.close()

