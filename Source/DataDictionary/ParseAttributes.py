#! /usr/bin/env python
"""
$ pdftotext -layout -nopgbrk -f 303 -l 305 07_03pu.pdf page303.txt
"""
import re,os

"""

"""
class Part3Parser:
  # Cstor
  def __init__(self):
    self._InputFilename = ''
    self._OutputFilename = ''
    self._Buffer = ''

  def SetInputFileName(self,s):
    self._InputFilename = s

  def SetOutputFileName(self,s):
    self._OutputFilename = s
  
  def IsComment(self,s):
    patt1 = re.compile("^\s+- Standard -\s*$")
    patt2 = re.compile("^\s+PS 3.3 - 2007\s*")
    patt3 = re.compile("^\s+Page [0-9]+\s*$")
    m1 = patt1.match(s)
    m2 = patt2.match(s)
    m3 = patt3.match(s)
    if(m1 or m2 or m3):
      print "Comment:", s
      return True
    return False

  def IsStartTable(self,s):
    #patt = re.compile("^\s+Table C[0-9a-z\.-]+.*\s+$")
    patt = re.compile("^\s+Table\s+C.[0-9a-z-]+\s*$")
    m = patt.match(s)
    if(m):
      print "Start", s
      return True
    return False

  def IsTableName(self,s):
    patt = re.compile("^\s+[A-Z\s]+ ATTRIBUTES\s*$") #MACRO/MODULE
    m = patt.match(s)
    if(m):
      print "Table Name", s
      return True
    return False

  def IsTableDescription(self,s):
    patt  = re.compile("^\s*Attribute Name\s+Tag\s+Type\s+Attribute Description\s*$")
    m = patt.match(s)
    if(m):
      print "Table Description:", s
      return True
    return False

  def IsFirstLineAttribute(self,s):
    # Line should look like:
    # Bits Stored ... (0028,0101) ... 1 ... Number of bits stored for each pixel
    patt = re.compile("^\s*.*\\([0-9A-F]+,[0-9A-F]+\\).*\s*$") #MACRO/MODULE
    m = patt.match(s)
    if(m):
      print "First Line Attribute:", s
      return True
    #print "No:", s
    return False

  def IsNextLineAttribute(self,s,shift):
    blank = s[0:shift]
    blank = blank.strip()
    #print "BLANK:", blank
    return blank == ''
    
  def FindShiftValue(self,s):
    # Line should look like:
    # Bits Stored ... (0028,0101) ... 1 ... Number of bits stored for each pixel
    patt = re.compile("^[A-Za-z ]+\s+\\([0-9A-F]+,[0-9A-F]+\\)\s+[1-3][C]*\s+(.*)$")
    m = patt.match(s)
    if(m):
      shift = s.find( m.group(1) )
      return shift
    print "OUCH:", s
    return 0
  
  def Open(self):
    #self._Infile = file(self._InputFilename, 'r')
    #for line in self._Infile.readlines():
    #  line = line[:-1] # remove '\n'
    #  if( self.IsStartTable(line) ):
    #    print line.next()
    cmd_input = open(self._InputFilename,'r')
    outfile = open(self._OutputFilename, 'w')
    for line in cmd_input:
      #while  line.startswith('%') : # skip comment lines
      #print "!!!",line
      #line= cmd_input.next() 
      line = line[:-1]
      if( self.IsStartTable(line) ):
        line2 = cmd_input.next()[:-1]
        if(self.IsTableName(line2)):
          line3 = cmd_input.next()[:-1]
          if( self.IsTableDescription(line3) ):
            #line4 = cmd_input.next()[:-1]
            buffer = ''
            shift = 0
            for subline in cmd_input:
              subline = subline[:-1]
              if( self.IsFirstLineAttribute(subline)):
                print "Previous Buffer was: ", buffer
                if( buffer != '' ):
                  outfile.write( buffer )
                  outfile.write( '\n' )
                shift = self.FindShiftValue(subline)
                assert shift != 0
                buffer = subline
              else:
                if( self.IsComment(subline) ):
                  print "Found Comment"
                else:
                  if( self.IsNextLineAttribute(subline,shift) ):
                    buffer += ' ' + subline.strip()
                  else:
                    print "Wotsit:", subline
              print "Working on: ", subline
              if not subline: break
        else:
          print "Problem with:", line, line2
      line = cmd_input.next()
      if not line: break
    cmd_input.close() 
    self.Write()

  def Write(self):
   print "Write"
 
  # Main function to call for parsing
  def Parse(self):
    self.Open()


if __name__ == "__main__":
  argc = len(os.sys.argv )
  if ( argc < 3 ):
    print "Sorry, wrong list of args"
    os.sys.exit(1) #error

  inputfilename = os.sys.argv[1]
  outputfilename = os.sys.argv[2]
  tempfile = "/tmp/mytemp2"

  dp = Part3Parser()
  dp.SetInputFileName( inputfilename )
  dp.SetOutputFileName( tempfile )
  dp.Parse()


