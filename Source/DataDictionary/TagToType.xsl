<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into
     C++ template code
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
// $ xsltproc TagToType.xsl DICOMV3.xml > gdcmTagToType.h

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
      <xsl:variable name="group" select="translate(@group,'xx','00')"/>
      <xsl:variable name="element" select="translate(@element,'xx','00')"/>
      <xsl:if test="contains($group,'x') = false and contains($element,'x') = false and @vr != '' and @vr != 'US_SS' and @vr != 'US_SS_OW' and @vr != 'OB_OW'">
        <xsl:text>template &lt;&gt; struct TagToType&lt;0x</xsl:text>
        <xsl:value-of select="$group"/>
        <xsl:text>,0x</xsl:text>
        <xsl:value-of select="$element"/>
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
