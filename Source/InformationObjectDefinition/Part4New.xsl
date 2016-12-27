<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:dk="http://docbook.org/ns/docbook" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" exclude-result-prefixes="dk">
<xsl:output method="xml" omit-xml-declaration="no" encoding="UTF-8" indent="no" />

<!--
<xsl:template match="/">
    <xsl:comment>
  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
</xsl:comment>
<xsl:text>
</xsl:text>

  <xsl:apply-templates select="*/*/*/*/*/dk:table[@xml:id='table_B.3-3']" />
  <xsl:apply-templates select="*/*/*/dk:table[@xml:id='table_B.5-1']" />
  <xsl:apply-templates select="*/*/*/dk:table[@xml:id='table_I.4-1']" />
</xsl:template>
-->
<xsl:template match="text()" />

<!--
<xsl:template match="@*|node()">
  <xsl:copy>
   <xsl:apply-templates select="@*|node()" />
  </xsl:copy>
</xsl:template>
-->
<xsl:template match="dk:caption" />

<xsl:template match="dk:book" >
  <sop-classes>
   <xsl:apply-templates />
</sop-classes>
</xsl:template>

<xsl:template match="dk:table[@xml:id='table_B.3-3']">
  <xsl:variable name="caption" select="dk:caption"/>
<xsl:text>
</xsl:text>
  <standard-and-related-general-sop-classes>
   <xsl:apply-templates />
  </standard-and-related-general-sop-classes>
</xsl:template>

<xsl:template match="dk:table[@xml:id='table_B.5-1']">
  <xsl:variable name="caption" select="dk:caption"/>
<xsl:text>
</xsl:text>
  <standard-sop-classes>
   <xsl:apply-templates />
  </standard-sop-classes>
</xsl:template>

<xsl:template match="dk:table[@xml:id='table_I.4-1']">
  <xsl:variable name="caption" select="dk:caption"/>
<xsl:text>
</xsl:text>
    <media-storage-standard-sop-classes>
   <xsl:apply-templates />
    </media-storage-standard-sop-classes>
</xsl:template>


<xsl:template match="dk:tr" >
  <xsl:variable name="sopclassname" select="dk:td[1]/dk:para/text()"/>
  <xsl:variable name="classuid" select="dk:td[2]/dk:para/text()"/>
<!--
  <xsl:variable name="iod" select="dk:td[3]/dk:para/dk:emphasis | dk:td[3]/dk:para[not(dk:emphasis)]"/>
-->
  <xsl:variable name="iod" select="dk:td[3]/dk:para"/>
    <xsl:if test="$sopclassname != ''">
  <mapping sop-class-name="{$sopclassname}" sop-class-uid="{$classuid}" iod="{$iod}"/>
</xsl:if>
</xsl:template>

</xsl:stylesheet>
