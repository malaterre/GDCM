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
</xsl:stylesheet>
