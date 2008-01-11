<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- share common code to transform a VM Part 6 string into a gdcm::VM type
-->
<!--
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
  <xsl:include href="VM.xsl"/>
<!-- The main template that loop over all dict/entry -->
  <xsl:template match="/">
    <xsl:text>
// GENERATED FILE DO NOT EDIT
// $ xsltproc DefaultDict.xsl DICOMV3.xml &gt; gdcmDefaultDicts.cxx

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

#ifndef __gdcmDefaultDicts_cxx
#define __gdcmDefaultDicts_cxx

#include "gdcmDicts.h"
#include "gdcmVR.h"
#include "gdcmDict.h"
#include "gdcmDictEntry.h"

namespace gdcm {
typedef struct
{
  uint16_t group;
  uint16_t element;
  VR::VRType vr;
  VM::VMType vm;
  const char *name;
} DICT_ENTRY;

static const DICT_ENTRY DICOMV3DataDict [] = {
</xsl:text>
    <xsl:for-each select="dict/entry">
      <xsl:variable name="group" select="translate(@group,'x','0')"/>
      <xsl:variable name="element" select="translate(@element,'x','0')"/>
      <xsl:choose>
        <xsl:when test="substring($group,3) != 'xx' and substring($element,3) != 'xx' ">
          <xsl:text>  {0x</xsl:text>
          <xsl:value-of select="$group"/>
          <xsl:text>,0x</xsl:text>
          <xsl:value-of select="$element"/>
          <xsl:text>,VR::</xsl:text>
          <xsl:if test="@vr = ''">
            <xsl:text>INVALID</xsl:text>
          </xsl:if>
          <xsl:if test="@vr != ''">
            <xsl:value-of select="@vr"/>
          </xsl:if>
          <xsl:text>,VM::</xsl:text>
          <xsl:call-template name="VMStringToVMType">
            <xsl:with-param name="vmstring" select="@vm"/>
          </xsl:call-template>
          <xsl:text>,"</xsl:text>
          <xsl:value-of select="@name"/>
          <xsl:text>" },</xsl:text>
          <xsl:text>
</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:message>PROBLEM:(<xsl:value-of select="$group"/>,<xsl:value-of select="$element"/>)
</xsl:message>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:for-each>
    <xsl:text>
  {0x0000,0x0000,VR::INVALID,VM::VM0,0 } // Gard
};

void Dict::LoadDefault()
{
   unsigned int i = 0;
   DICT_ENTRY n = DICOMV3DataDict[i];
   while( n.name != 0 )
   {
      Tag t(n.group, n.element);
      DictEntry e( n.name, n.vr, n.vm );
      AddDictEntry( t, e );
      n = DICOMV3DataDict[++i];
   }
   //Tag t(0, 0);
   //DictEntry e("", VR::INVALID, VM::VM0);
   //AddDictEntry( t, e );
}

void PrivateDict::LoadDefault()
{
  // TODO
}

} // end namespace gdcm
#endif // __gdcmDefaultDicts_cxx
</xsl:text>
  </xsl:template>
</xsl:stylesheet>
