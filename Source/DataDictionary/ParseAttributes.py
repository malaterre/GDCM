#! /usr/bin/env python
"""
$ pdftotext -layout -nopgbrk -f 303 -l 305 07_03pu.pdf page303.txt
"""
import re,os

"""

"""
class Attribute:
  # Cstor
  def __init__(self):
    self._Name = ''
    self._Tag = '(0000,0000)'
    self._Type = ''
    self._Description= ''
  def SetName(self,s):
    self._Name = s
  def AppendName(self,s):
    self._Name += s
  def SetTag(self,s):
    self._Tag = s
  def SetType(self,s):
    self._Type = s
  def SetDescription(self,s):
    self._Description = s
  def AppendDescription(self,s):
    self._Description += s

class Part3Parser:
  # Cstor
  def __init__(self):
    self._InputFilename = ''
    self._OutputFilename = ''
    self._Buffer = ''
    self._CurrentAttribute = Attribute()
    self._IsInTable = False
    self._Shift = 0

  def SetInputFileName(self,s):
    self._InputFilename = s

  def SetOutputFileName(self,s):
    self._OutputFilename = s
  
  def IsComment(self,s):
    if len(s) == 0:
      return True
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
    assert self._IsInTable != True
    self._IsInTable = False
    if(m):
      print "Start", s
      self._IsInTable = True
      return True
    return False

  def IsEndTable(self,s):
    assert self._IsInTable == True
    assert not self.IsComment(s)
    self._IsInTable = False
    return True

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
    patt = re.compile("^\s*(.*)\\([0-9A-F]+,[0-9A-F]+\\)\s+([1-3C]+).*\s*$") #MACRO/MODULE
    m = patt.match(s)
    if(m):
      s1 = m.group(1).strip()
      if s1 == '':
        return False
      print "First Line Attribute:", s1, s
      return True
    #print "No:", s
    return False

  def IsNextLineAttribute(self,s):
    # Need to support : "Include `Image Pixel Macro' Table C.7-11b"
    if self._Shift == 0:
      patt = re.compile("^Include `(.*)' Table C.[0-9a-z-]+$")
      m = patt.match(s)
      return m
    assert self._Shift != 0
    if len(s) <= self._Shift:
      return False
    blank = s[0:self._Shift]
    blank = blank.strip()
    #print "BLANK:", blank
    if blank == '':
      return True
    " The following is really ugly ... need to be fixed"
    if blank == 'Descriptor':
      return True
    if blank == 'Data':
      return True

  def FindShiftValue(self,s):
    # Line should look like:
    # Bits Stored ... (0028,0101) ... 1 ... Number of bits stored for each pixel
    patt = re.compile("^[A-Za-z ]+\s+\\([0-9A-F]+,[0-9A-F]+\\)\s+[1-3][C]*\s+(.*)$")
    m = patt.match(s)
    if(m):
      self._Shift = s.find( m.group(1) ) - 10
      return self._Shift
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
            self._Shift = 0
            for subline_ori in cmd_input:
              subline = subline_ori[:-1]
              if( self.IsFirstLineAttribute(subline)):
                print "Previous Buffer was: ", buffer
                if( buffer != '' ):
                  outfile.write( buffer )
                  outfile.write( '\n' )
                self.FindShiftValue(subline)
                assert self._Shift != 0
                buffer = subline
              else:
                if( self.IsComment(subline) ):
                  print "Found Comment"
                else:
                  if( self.IsNextLineAttribute(subline) ):
                    buffer += ' ' + subline.strip()
                  else:
                    print "Wotsit:", subline
                    self._Shift = 0
                    self._IsInTable = False
                    if( buffer != '' ):
                      outfile.write( buffer )
                      outfile.write( '\n' )
                    break
              #print "Working on: ", subline
              if not subline_ori:
                break
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


