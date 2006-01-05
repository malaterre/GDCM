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
  patt = re.compile('^\\(([0-9a-fx]+),([0-9a-fx]+)\\) (.*) ([A-Zor ]+) ([1-9n-]+)$')
  if( patt.match(line) ):
    m = patt.match(line)
    ss = m.group(1)  + ' ' + m.group(2) + ' ' + m.group(4) + ' ' + m.group(5) + ' ' + m.group(3)
    print ss
  else:
    patt = re.compile('^\\(([0-9a-fx]+),([0-9a-fx]+)\\) (.*) ([A-Zor ]+) ([1-9n-]+) (RET|Retired)$')
    if( patt.match(line) ):
      m = patt.match(line)
      ss = m.group(1)  + ' ' + m.group(2) + ' ' + m.group(4) + ' ' + m.group(5) + ' ' + m.group(3) + ' (RET)' #' (' + m.group(6) + ')'
      print ss
    else:
      patt = re.compile('^\\(([0-9a-fx]+),([0-9a-fx]+)\\) (.*) ([US/]+) ([1-9n-]+)$')
      if( patt.match(line) ):
        m = patt.match(line)
        if m.group(4) == 'US/SS':
          ss = m.group(1) + ' ' + m.group(2) + ' US or SS ' + m.group(5) + ' ' + m.group(3)
        else:
          ss = 'Impossible'
        print ss
      else:
        patt = re.compile('^\\(([0-9a-fx]+),([0-9a-fx]+)\\) (.*) (RET|Retired)$')
        if(patt.match(line)):
          m = patt.match(line)
          ss = m.group(1) + ' ' + m.group(2) + ' LO 1 ' + m.group(3) + ' (RET)'
          print ss
        else:
          print 'Impossible:', line

