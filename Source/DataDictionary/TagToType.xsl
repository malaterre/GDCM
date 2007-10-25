<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into
     C++ template code
-->
<!--
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
  <xsl:template name="VMStringToVMType">
    <xsl:param name="vmstring"/>
    <xsl:choose>
      <xsl:when test="$vmstring = 1">
        <xsl:text>VM1</xsl:text>
      </xsl:when>
      <xsl:when test="$vmstring = 2">
        <xsl:text>VM2</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 3">
        <xsl:text>VM3</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 4">
        <xsl:text>VM4</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 5">
        <xsl:text>VM5</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 6">
        <xsl:text>VM6</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 8">
        <xsl:text>VM8</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 16">
        <xsl:text>VM16</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = 24">
        <xsl:text>VM24</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '1-2'">
        <xsl:text>VM1_2</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '1-3'">
        <xsl:text>VM1_3</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '1-8'">
        <xsl:text>VM1_8</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '1-32'">
        <xsl:text>VM1_32</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '1-99'">
        <xsl:text>VM1_99</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '1-n'">
        <xsl:text>VM1_n</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '2-2n'">
        <xsl:text>VM2_2n</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '2-n'">
        <xsl:text>VM2_n</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '3-3n'">
        <xsl:text>VM3_3n</xsl:text>
      </xsl:when>
       <xsl:when test="$vmstring = '3-n'">
        <xsl:text>VM3_n</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>VM0</xsl:text>
      </xsl:otherwise>
      </xsl:choose>
    </xsl:template>
 
<!-- The main template that loop over all dict/entry -->
  <xsl:template match="/">
    <xsl:text>
// GENERATED FILE DO NOT EDIT
// $ xsltproc TagToType.xsl GDCM2.xml > gdcmTagToType.h

/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmTagToType_h
#define __gdcmTagToType_h

#include "gdcmVR.h"
#include "gdcmVM.h"

namespace gdcm {
// default template:
template &lt;uint16_t,uint16_t&gt; struct TagToType;
// template for group length:
template &lt;uint16_t group&gt; struct TagToType&lt;group,0x0000&gt; { typedef VRToType&lt;VR::UL&gt;::Type Type; enum { VRType = VR::UL }; enum { VMType = VM::VM1 }; };
</xsl:text>
    <xsl:for-each select="dict/entry">
      <xsl:if test="substring(@group,3) != 'xx' and substring(@element,3) != 'xx' and @vr">
      <xsl:text>template &lt;&gt; struct TagToType&lt;0x</xsl:text>
      <xsl:value-of select="@group"/>
      <xsl:text>,0x</xsl:text>
      <xsl:value-of select="@element"/>
      <xsl:text>&gt; {</xsl:text>
      <xsl:text>
</xsl:text>
      <xsl:text>typedef VRToType&lt;VR::</xsl:text>
      <xsl:value-of select="@vr"/>
      <xsl:text>&gt;::Type Type;</xsl:text>
      <xsl:text>
</xsl:text>
      <xsl:text>enum { VRType = VR::</xsl:text>
      <xsl:value-of select="@vr"/>
      <xsl:text> };</xsl:text>
      <xsl:text>
</xsl:text>
      <xsl:text>enum { VMType = VM::</xsl:text>
        <xsl:call-template name="VMStringToVMType">
          <xsl:with-param name="vmstring" select="@vm"/>
        </xsl:call-template>
      <xsl:text> };</xsl:text>
      <xsl:text>
</xsl:text>
      <xsl:text>};</xsl:text>
      <xsl:text>
</xsl:text>
</xsl:if>
    </xsl:for-each>
    <xsl:text>
} // end namespace gdcm
#endif // __gdcmTagToType_h
</xsl:text>
  </xsl:template>
</xsl:stylesheet>

