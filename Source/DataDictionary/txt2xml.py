#! /usr/bin/env python

import re,os

"""
This parser parse a table formatted like this:
Attribute Name Tag VR VM
"""
class TextParser:
  def __init__(self, inputfilename, outputfilename):
    self._InputFilename = ''
    self._OutputFilename = ''
  def Parse(self):
    infile = file(inputfilename, 'r')
    outLines = []
    for line in infile.readlines():
      patt = re.compile("^\s*([A-Za-z0-9 #()./,_:>-]+)\s+\(([0-9A-Z]+),\s?([0-9A-ZxX]+)\)\s+([A-Z][A-Z])\s+([0-9Nn-]+)\s*$")
      patt1 = re.compile("^\s*([A-Za-z0-9 #()./,_:>-]+)\s+\(([0-9A-Z]+),\s?([0-9A-ZxX]+)\)\s+([1-3C]+)\s+([A-Z][A-Z])\s+([0-9Nn-]+)\s*$")
      patt2 = re.compile( "^\s*([Table ]*[A-Z1-9.-]+).?\s*([A-Za-z -]+)\s*\(([A-Z0-9_]+)\)$")
      #patt3 = re.compile( '^\s*Private Creator Identification\s*\((["A-Za-z0-9() ./])\)\s*$' )
      patt3 = re.compile( '^\s*Private Creator Identification\s*\("(.*)"\)\)?\s*$' )
      patt4 = re.compile( '^\s*Private Creator Identification\s*([A-Z0-9_]+)\s*$' )
      m = patt.match(line)
      m1 = patt1.match(line)
      m2 = patt2.match(line)
      m3 = patt3.match(line)
      m4 = patt4.match(line)
      #print line
      if m:
        # <entry group="0001" element="0001" vr="LO" vm="1" owner="Private Creator"/>
        dicom = "<entry group=\"%s\" element=\"%s\" vr=\"%s\" vm=\"%s\">"%(m.group(2),m.group(3),m.group(4),m.group(5))
        #dicom = m.group(1) + ' ' + m.group(2) + ' ' + m.group(3) + ' ' + m.group(4)
        #print dicom
        dicom += '\n'
        dicom += "<description>%s</description>\n</entry>\n"%m.group(1).rstrip()
        outLines.append( dicom )
      elif m1:
        # <entry group="0001" element="0001" vr="LO" vm="1" type="1C"/>
        dicom = "<entry group=\"%s\" element=\"%s\" vr=\"%s\" vm=\"%s\" type=\"%s\">"%(m1.group(2),m1.group(3),m1.group(5),m1.group(6),m1.group(4))
        #dicom = m.group(1) + ' ' + m.group(2) + ' ' + m.group(3) + ' ' + m.group(4)
        #print dicom
        dicom += '\n'
        dicom += "<description>%s</description>\n</entry>\n"%m1.group(1).rstrip()
        outLines.append( dicom )
      elif m2:
        # <dict edition="2007" url="http://??" ref="Table A-16" name="Private Creator Identification - Xeleris" owner="GEMS_GENIE_1">
        s = "<dict ref=\"%s\" name=\"%s\" owner=\"%s\">"%(m2.group(1),m2.group(2).rstrip(),m2.group(3))
        s += '\n'
        outLines.append( s )
      elif m3:
        s = "<dict ref=\"%s\" name=\"%s\" owner=\"%s\">"%("??","??",m3.group(1))
        s += '\n'
        outLines.append( s )
      elif m4:
        s = "<dict ref=\"%s\" name=\"%s\" owner=\"%s\">"%("??","??",m4.group(1))
        s += '\n'
        outLines.append( s )
      else:
        print line
      #print self.Reformat(line)
      #outLines.append( self.Reformat(line) + '\n' )
    outfile = file(outputfilename, 'w')
    outfile.writelines( outLines )
    outfile.close()

"""
This parser parse a table formatted like this:
Grp Elm VR VM Type Definition
"""
class TextParser2:
  def __init__(self, inputfilename, outputfilename):
    self._InputFilename = ''
    self._OutputFilename = ''
  def Parse(self):
    infile = file(inputfilename, 'r')
    outLines = []
    for line in infile.readlines():
      patt = re.compile("^\s*([0-9A-Z]+)\s+([0-9A-Zx]+)\s+([A-Z][A-Z])\s+([1-9SNn-]+)\s+([1-9])\s+([A-Za-z0-9 ()._,/#>-]+)\s*$")
      patt2 = re.compile( "^\s*([A-Z1-9.-]+)\s*([A-Za-z -]+)\s*$")
      m = patt.match(line)
      m2 = patt2.match(line)
      #print line
      if m:
        # <entry group="0001" element="0001" vr="LO" vm="1" owner="Private Creator"/>
        dicom = "<entry group=\"%s\" element=\"%s\" vr=\"%s\" vm=\"%s\" type=\"%s\">"%(m.group(1),m.group(2),m.group(3),m.group(4),m.group(5))
        #dicom = m.group(1) + ' ' + m.group(2) + ' ' + m.group(3) + ' ' + m.group(4)
        #print dicom
        dicom += '\n'
        dicom += "<description>%s</description>\n</entry>\n"%m.group(6).rstrip()
        outLines.append( dicom )
      elif m2:
        # <dict edition="2007" url="http://??" ref="Table A-16" name="Private Creator Identification - Xeleris" owner="GEMS_GENIE_1">
        s = "<dict ref=\"%s\" name=\"%s\" owner=\"%s\">"%(m2.group(1),m2.group(2).rstrip(),"")
        s += '\n'
        outLines.append( s )
      else:
        print line
      #print self.Reformat(line)
      #outLines.append( self.Reformat(line) + '\n' )
    outfile = file(outputfilename, 'w')
    outfile.writelines( outLines )
    outfile.close()

if __name__ == "__main__":
  argc = len(os.sys.argv )
  if ( argc < 3 ):
    print "Sorry, wrong list of args"
    os.sys.exit(1) #error

  inputfilename = os.sys.argv[1]
  outputfilename = os.sys.argv[2]
  tp = TextParser(inputfilename,outputfilename);
  tp.Parse()


