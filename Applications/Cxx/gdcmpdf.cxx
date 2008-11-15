/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 */
#include <poppler/poppler-config.h>
#include <poppler/PDFDoc.h>
#include <poppler/UnicodeMap.h>
#include <poppler/PDFDocEncoding.h>
#include <poppler/GlobalParams.h>

static void printInfoString(Dict *infoDict, const char *key, const char *text, UnicodeMap *uMap)
{
  Object obj;
  GooString *s1;
  GBool isUnicode;
  Unicode u;
  char buf[8];
  int i, n;

  if (infoDict->lookup((char*)key, &obj)->isString())
    {
    fputs(text, stdout);
    s1 = obj.getString();
    if ((s1->getChar(0) & 0xff) == 0xfe &&
      (s1->getChar(1) & 0xff) == 0xff)
      {
      isUnicode = gTrue;
      i = 2;
      }
    else 
      {
      isUnicode = gFalse;
      i = 0;
      }
    while (i < obj.getString()->getLength())
      {
      if (isUnicode)
        {
        u = ((s1->getChar(i) & 0xff) << 8) |
          (s1->getChar(i+1) & 0xff);
        i += 2;
        }
      else
        {
        u = pdfDocEncoding[s1->getChar(i) & 0xff];
        ++i;
        }
      n = uMap->mapUnicode(u, buf, sizeof(buf));
      fwrite(buf, 1, n, stdout);
      }
    fputc('\n', stdout);
    }
  obj.free();
}

int main (int argc, char *argv[])
{
  GooString *ownerPW, *userPW;
  GooString *fileName;
  PDFDoc *doc;
  Object info;
  UnicodeMap *uMap;
  ownerPW = NULL;
  userPW = NULL;
  globalParams = new GlobalParams(0);
  uMap = globalParams->getTextEncoding();

  fileName = new GooString(argv[1]);
  Object obj;

  obj.initNull();
  doc = new PDFDoc(fileName, ownerPW, userPW);

  if (!doc->isOk())
    {
    return 1;
    }

  doc->getDocInfo(&info);
  if (info.isDict())
    {
    printInfoString(info.getDict(), "Title",        "Title:          ", uMap);
    printInfoString(info.getDict(), "Subject",      "Subject:        ", uMap);
    printInfoString(info.getDict(), "Keywords",     "Keywords:       ", uMap);
    printInfoString(info.getDict(), "Author",       "Author:         ", uMap);
    printInfoString(info.getDict(), "Creator",      "Creator:        ", uMap);
    printInfoString(info.getDict(), "Producer",     "Producer:       ", uMap);
    //printInfoDate(info.getDict(),   "CreationDate", "CreationDate:   ");
    //printInfoDate(info.getDict(),   "ModDate",      "ModDate:        ");
    }
  info.free();

  return 0;
}

