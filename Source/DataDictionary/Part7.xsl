<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into the old 
     GDCM1 data dictionary -->
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
  <xsl:template match="row">
  <entry group="{substring-before(substring-after(entry[2],'('),',')}"
  element="{substring-after(substring-before(entry[2],')'),',')}"
  vr="{entry[3]}"
  vm="{entry[4]}"
  retired="true"
  version="2"
  >
  <description><xsl:value-of select="entry[1]"/></description>
  </entry>
  </xsl:template>

  <xsl:template match="/informaltable/tgroup/tbody">
    <xsl:apply-templates/>
  </xsl:template>
</xsl:stylesheet>
