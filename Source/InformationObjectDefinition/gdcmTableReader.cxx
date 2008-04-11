/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTableReader.h"
#include "gdcmTable.h"

#include <iostream>
#include <fstream>
//#include "expat/lib/expat.h"

#include <stdio.h> // for stderr
#include <string.h>

namespace gdcm
{
#if 0
#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif

static void XMLCALL startElement(void *userData, const char *name, const char **atts)
{
  TableReader *tr = reinterpret_cast<TableReader*>(userData);
  tr->StartElement(name, atts);
}

static void XMLCALL endElement(void *userData, const char *name)
{
  TableReader *tr = reinterpret_cast<TableReader*>(userData);
  tr->EndElement(name);
}

static void XMLCALL characterDataHandler(void* userData, const char* data,
  int length)
{
  TableReader *tr = reinterpret_cast<TableReader*>(userData);
  tr->CharacterDataHandler(data,length);
}


void TableReader::StartElement(const char *name, const char **atts)
{
  int i;
  //int *depthPtr = (int *)userData;
//  for (i = 0; i < *depthPtr; i++)
//    putchar('\t');
  std::cout << name << " : " << atts[0] << "=" << atts[1] << std::endl;
  if( strcmp(name, "Table" ) == 0 )
    {
    //*depthPtr += 1;
    }
  else
    {
    }
}

void TableReader::EndElement(const char *name)
{
//  int *depthPtr = (int *)userData;
//  *depthPtr -= 1;
}

void TableReader::CharacterDataHandler(const char *data, int length)
{
}

int TableReader::Read()
{
  std::ifstream is( Filename.c_str() );

  char buf[BUFSIZ];
  XML_Parser parser = XML_ParserCreate(NULL);
  int done;
  //int depth = 0;
  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characterDataHandler);
  int ret = 0;
  do {
    is.read(buf, sizeof(buf));
    size_t len = is.gcount();
    done = len < sizeof(buf);
    if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
      fprintf(stderr,
        "%s at line %" XML_FMT_INT_MOD "u\n",
        XML_ErrorString(XML_GetErrorCode(parser)),
        XML_GetCurrentLineNumber(parser));
      ret = 1; // Mark as error
      done = 1; // exit while
    }
  } while (!done);
  XML_ParserFree(parser);
  is.close();
  return ret;
}

#else
void TableReader::StartElement(const char *name, const char **atts) {}
void TableReader::EndElement(const char *name) {}
void TableReader::CharacterDataHandler(const char *data, int length) {}
int TableReader::Read() { return 0; }
#endif
} // end namespace gdcm
