<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" indent="yes"/>
<!--
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL: https://gdcm.svn.sourceforge.net/svnroot/gdcm/trunk/Source/DataDictionary/redo.xsl $

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
<!--
cleanup excel HTML:
$ tidy -asxml dicomhdr.html > toto.html
Important specify it's html:

$ xsltproc - -html dicomhdr.xsl toto.html
-->


  <xsl:template match="/">
	  <output>
		  <xsl:for-each select="html/body/table/tr/td">
	    <element>
          <xsl:value-of select="."/>
  </element>
    </xsl:for-each>
	  </output>
  </xsl:template>

</xsl:stylesheet>
