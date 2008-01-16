<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" indent="yes" encoding="UTF-8"/>
<!-- XSL to convert XML GDCM2 data dictionay into the old 
     GDCM1 data dictionary -->
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
<!-- The main template that loop over all dict/entry -->
<xsl:template match="text()|comment()|processing-instruction()"><xsl:copy/></xsl:template>
  <xsl:template match="/">
<xsl:element name="dict">
<xsl:copy-of select="dict/@*" /> 
<xsl:apply-templates/>
</xsl:element>
  </xsl:template>

  <xsl:template match="dict">
    <xsl:for-each select="entry">
      <xsl:sort select="@group"/>
      <xsl:sort select="@element"/>
<xsl:element name="entry">
<xsl:copy-of select="@*" /> 
</xsl:element>

    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
