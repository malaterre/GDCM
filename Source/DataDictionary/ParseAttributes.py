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
  def SetInit(self,s):
    # Should be something like:
    # Blue Palette Color Lookup Table       (0028,1103)     1C   Specifies the format of the Blue Palette
    patt = re.compile("^(.*)(\\([0-9A-F]+,[0-9A-F]+\\))\s+([1-3C]+)\s+(.*)\s*$")
    m = patt.match(s)
    assert m
    self._Name = m.group(1).strip()
    self._Tag = m.group(2).strip()
    self._Type = m.group(3).strip()
    self._Description = m.group(4).strip()
  def SetName(self,s):
    self._Name = s
  def AppendName(self,s):
    self._Name += " "
    self._Name += s.strip()
  def SetTag(self,s):
    self._Tag = s
  def SetType(self,s):
    self._Type = s
  def SetDescription(self,s):
    self._Description = s
  def AppendDescription(self,s):
    self._Description += " "
    self._Description += s.strip()
  def GetAsXML(self):
    return "<entry name=\""+self._Name+"\" tag=\""+self._Tag+"\" type=\""+self._Type+"\" description=\""+self._Description+"\"></entry>"
  def Print(self):
    print self.GetAsXML()

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
      #print "First Line Attribute:", s1, s
      return True
    #print "No:", s
    return False

  def IsIncludeTable(self,s):
    # Need to support : "Include `Image Pixel Macro' Table C.7-11b"
    #assert self._Shift == 0
    patt = re.compile("^Include `(.*)' Table C.[0-9a-z-]+$")
    m = patt.match(s)
    return m

  def IsNextLineAttribute(self,s):
    assert self._Shift != 0
    if len(s) <= self._Shift:
      return False
    blank = s[0:self._Shift]
    blank = blank.strip()
    #print "BLANK:", blank
    if blank == '':
      self._CurrentAttribute.AppendDescription( s )
      return True
    # The following is really ugly ... need to be fixed
    if blank == 'Descriptor' or blank == 'Data':
      self._CurrentAttribute.AppendName( blank )
      self._CurrentAttribute.AppendDescription( s[self._Shift:-1] )
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
            # Ok we found a table
            outfile.write( 
              "<table ref=\""+line.strip()+"\" name=\""+line2.strip()+"\">"
            )
            buffer = ''
            self._CurrentAttribute = Attribute()
            self._Shift = 0
            for subline_ori in cmd_input:
              subline = subline_ori[:-1]
              if( self.IsIncludeTable(subline)):
                #print "Include Table:", subline
                if( subline != '' ):
                  outfile.write( "<entry ref=\""+subline+"\"/>" )
                  outfile.write( '\n' )
              elif( self.IsFirstLineAttribute(subline)):
                #print "Previous Buffer was: ", buffer
                if( buffer != '' ):
                  outfile.write( self._CurrentAttribute.GetAsXML() )
                  outfile.write( '\n' )
                self._CurrentAttribute.SetInit(subline)
                self.FindShiftValue(subline)
                assert self._Shift != 0
                buffer = subline
              else:
                if( self.IsComment(subline) ):
                  print "Found Comment: ", subline
                else:
                  if( self.IsNextLineAttribute(subline) ):
                    buffer += ' ' + subline.strip()
                  else:
                    print "Wotsit:", subline
                    self._Shift = 0
                    self._IsInTable = False
                    if( buffer != '' ):
                      outfile.write( self._CurrentAttribute.GetAsXML() )
                      outfile.write( '\n' )
                    outfile.write( '</table>' )
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


