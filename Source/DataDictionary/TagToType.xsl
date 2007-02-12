<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into
     David Clunie's dicom3tools data dictionary 
Checked against:
     dicom3tools_1.00.snapshot.20061120/libsrc/standard/elmdict/dicom3.tpl
-->
<!--
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
<!-- The main template that loop over all dict/entry -->
  <xsl:template match="/">
    <xsl:text>
#ifndef __gdcmTagToType_h
#define __gdcmTagToType_h
#include "gdcmVR.h"
namespace gdcm {
template &lt;uint16_t,uint16_t&gt; struct TagToType;
</xsl:text>
    <xsl:for-each select="dict/entry">
    <xsl:text>template &lt;&gt; struct TagToType&lt;0x</xsl:text>
    <xsl:value-of select="@group"/><xsl:text>,0x</xsl:text>
    <xsl:value-of select="@element"/>
<xsl:text>&gt; { typedef VRToType&lt;</xsl:text>
    <xsl:value-of select="representations/representation/@vr"/>
<xsl:text>&gt;::Type Type; };</xsl:text>
<xsl:text>
</xsl:text>
    </xsl:for-each>
<xsl:text>
} // end namespace gdcm
#endif
</xsl:text>
  </xsl:template>
</xsl:stylesheet>
