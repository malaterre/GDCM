<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into
     C++ template code
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
// GENERATED FILE DO NOT EDIT
// $ xsltproc TagToType.xsl GDCM2.xml > gdcmTagToType.h

#ifndef __gdcmTagToType_h
#define __gdcmTagToType_h

#include "gdcmVR.h"

namespace gdcm {
// default template:
template &lt;uint16_t,uint16_t&gt; struct TagToType;
// template for group length:
template &lt;uint16_t group&gt; struct TagToType&lt;group,0x0000&gt; { typedef VRToType&lt;VR::UL&gt;::Type Type; };
</xsl:text>
    <xsl:for-each select="dict/entry">
      <xsl:if test="substring(@group,3) != 'xx' and substring(@element,3) != 'xx' and representations/representation/@vr">
      <xsl:text>template &lt;&gt; struct TagToType&lt;0x</xsl:text>
      <xsl:value-of select="@group"/>
      <xsl:text>,0x</xsl:text>
      <xsl:value-of select="@element"/>
      <xsl:text>&gt; { typedef VRToType&lt;VR::</xsl:text>
      <xsl:value-of select="representations/representation/@vr"/>
      <xsl:text>&gt;::Type Type; };</xsl:text>
      <xsl:text>
</xsl:text>
</xsl:if>
    </xsl:for-each>
    <xsl:text>
} // end namespace gdcm
#endif
</xsl:text>
  </xsl:template>
</xsl:stylesheet>

