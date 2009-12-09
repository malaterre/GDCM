<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML Part4.xml UIDs into C++ code -->
<!--
  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL: https://gdcm.svn.sourceforge.net/svnroot/gdcm/trunk/Source/DataDictionary/TagToType.xsl $

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
  <xsl:template match="/dicts">
    <xsl:text>
// GENERATED FILE DO NOT EDIT
// $ xsltproc Part4ToC++.xsl Part4.xml &gt; gdcmPart4.cxx

/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL: https://gdcm.svn.sourceforge.net/svnroot/gdcm/trunk/Source/DataDictionary/TagToType.xsl $

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
</xsl:text>

<xsl:text>
#ifndef __gdcmPart4_h
#define __gdcmPart4_h

  typedef enum {
</xsl:text>
    <xsl:for-each select="standard-sop-classes/mapping">
        <xsl:value-of select="@sop-class-uid"/>
        <xsl:text> = </xsl:text>
        <xsl:value-of select="@iod"/>
<xsl:text>
</xsl:text>
    </xsl:for-each>
<xsl:text>
} TSType;

#endif //__gdcmPArt4_cxx
</xsl:text>
  </xsl:template>
</xsl:stylesheet>
