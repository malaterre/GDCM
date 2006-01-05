#! /usr/bin/env python

import re,os

argc = len(os.sys.argv )
if ( argc < 2 ):
  print "Sorry, wrong list of args"
  os.sys.exit(1) #error

inputfilename = os.sys.argv[1]
infile = file(inputfilename, 'r')

for line in infile.readlines():
  line = line[:-1] # remove '\n'
  patt = re.compile('^\\(([0-9a-fx]+),([0-9a-fx]+)\\)[ \t]+VERS=.*[ \t]+VR="(.*)"[ \t]+VM="(.*)"[ \t]+Keyword=.*[ \t]+Name="(.*)"$')
  if( patt.match(line) ):
    m = patt.match(line)
    ss = m.group(1) + ' ' + m.group(2) + ' ' + m.group(3) + ' ' + m.group(4) + ' ' + m.group(5)
    print ss
  else:
    print 'Impossible', line
