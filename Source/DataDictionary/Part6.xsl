<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:dk="http://docbook.org/ns/docbook" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" exclude-result-prefixes="dk">
<!--
  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
<!--
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes" doctype-system="../dtds/docbookx.dtd" doctype-public="-//OASIS//DTD DocBook XML//EN"/>
-->
<xsl:output method="xml" omit-xml-declaration="no" encoding="UTF-8" indent="no" />

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
  <xsl:apply-templates select="*/*/dk:table[@xml:id='table_6-1']" mode="m1"/>
  <xsl:apply-templates select="*/*/*/*/*/dk:table[@xml:id='table_9.3-1']" mode="m2"/>
</xsl:template>

<xsl:template match="dk:tr" mode="m2">
  <xsl:variable name="name" select="dk:td[1]/dk:para/text()"/>
  <xsl:variable name="tag" select="translate(dk:td[2]/dk:para/text(),'ABCDEF','abcdef')"/>
  <xsl:variable name="group" select="substring-after(substring-before($tag,','), '(')"/>
  <xsl:variable name="element" select="substring-after(substring-before($tag,')'), ',')"/>
  <xsl:variable name="keyword" select="translate(dk:td[3]/dk:para/text(),'&#x200B;','')"/>
  <xsl:variable name="vr" select="dk:td[3]/dk:para/text()"/>
  <xsl:variable name="vm" select="dk:td[4]/dk:para/text()"/>
  <entry group="{$group}" element="{$element}" keyword="{$keyword}" vr="{$vr}" vm="{$vm}" retired="false" name="{$name}"/>
</xsl:template>

<xsl:template match="dk:tr" mode="m1">
  <xsl:variable name="tagUpper">
<!--
 select="translate(dk:td[1]/dk:para/text(),'ABCDEF','abcdef')"/>
-->
    <xsl:apply-templates select="dk:td[1]/dk:para/dk:emphasis | dk:td[1]/dk:para[not(dk:emphasis)]"/>
  </xsl:variable>
  <xsl:variable name="tagLower" select="translate($tagUpper,'ABCDEF','abcdef')"/>
  <xsl:variable name="group" select="substring-after(substring-before($tagLower,','), '(')"/>
  <xsl:variable name="element" select="substring-after(substring-before($tagLower,')'), ',')"/>
  <xsl:variable name="name">
    <xsl:apply-templates select="dk:td[2]/dk:para/dk:emphasis | dk:td[2]/dk:para[not(dk:emphasis)]"/>
  </xsl:variable>
  <xsl:variable name="keyword" >
    <xsl:variable name="temp" >
      <xsl:apply-templates select="dk:td[3]/dk:para/dk:emphasis | dk:td[3]/dk:para[not(dk:emphasis)]"/>
    </xsl:variable>
    <xsl:value-of select="translate($temp,'&#x200B;','')"/>
  </xsl:variable>
  <xsl:variable name="vr">
    <xsl:apply-templates select="dk:td[4]/dk:para/dk:emphasis | dk:td[4]/dk:para[not(dk:emphasis)]"/>
  </xsl:variable>
  <xsl:variable name="vm">
    <xsl:apply-templates select="dk:td[5]/dk:para/dk:emphasis | dk:td[5]/dk:para[not(dk:emphasis)]"/>
  </xsl:variable>
  <xsl:variable name="retString">
    <xsl:apply-templates select="dk:td[6]/dk:para/dk:emphasis | dk:td[6]/dk:para[not(dk:emphasis)]"/>
  </xsl:variable>
  <xsl:variable name="ret" select="$retString = 'RET'"/>
<!--
  <xsl:choose>
  <xsl:when test="$ret">
  <entry group="{$group}" element="{$element}" keyword="{$keyword}" vr="{$vr}" vm="{$vm}" retired="{$ret}" name="{$name}"/>
  </xsl:when>
  <xsl:otherwise>
-->
  <entry group="{$group}" element="{$element}">
    <xsl:if test="$keyword != ''">
    <xsl:attribute name="keyword"><xsl:value-of select="$keyword"/></xsl:attribute>
    </xsl:if>
    <xsl:attribute name="vr"><xsl:value-of select="$vr"/></xsl:attribute>
    <xsl:attribute name="vm"><xsl:value-of select="$vm"/></xsl:attribute>
    <xsl:if test="$ret">
    <xsl:attribute name="retired"><xsl:value-of select="$ret"/></xsl:attribute>
    </xsl:if>
    <xsl:if test="$name != ''">
    <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
    </xsl:if>

  </entry>
<!--
  </xsl:otherwise>
  </xsl:choose>
-->
</xsl:template>

<!-- remove thread -->
<xsl:template match="dk:thead"/>

<!--
<xsl:template match="dk:para">
   <xsl:apply-templates select="./node()"/>
</xsl:template>

<xsl:template match="dk:emphasis">
   <xsl:value-of select="./text()"/>
</xsl:template>
-->

<xsl:template match="dk:tbody">
   <xsl:apply-templates select="*"/>
</xsl:template>

<xsl:template match="dk:caption" mode="m1"/>

<xsl:template match="dk:table[@xml:id='table_6-1']" mode="m1">
<xsl:text>
</xsl:text>
<xsl:comment>
This file was automatically created from a docbook version of PS 3.6-2011, which was then process by Part67.xsl

Manual changes:

1. DateTime -> Date Time (0008,002a)
</xsl:comment>
<xsl:text disable-output-escaping="yes">
&lt;!DOCTYPE doc [
  &lt;!ENTITY part7 SYSTEM "Part7.xml"&gt;
  ]&gt;
</xsl:text>
  <xsl:variable name="caption" select="dk:caption"/>
<dicts edition="2011">
<xsl:text disable-output-escaping="yes">
  &amp;part7;
</xsl:text>
  <dict ref="6" name="{$caption}">
   <xsl:apply-templates select="*" mode="m1"/>
</dict>
</dicts>
</xsl:template>

<!--
<xsl:template match="@*|node()">
  <xsl:copy>
   <xsl:apply-templates select="@*|node()" />
  </xsl:copy>
</xsl:template>
-->

<!-- http://stackoverflow.com/questions/5268182/how-to-remove-namespaces-from-xml-using-xslt -->
    <!-- template to copy elements -->
    <xsl:template match="*">
        <xsl:element name="{local-name()}">
            <xsl:apply-templates select="@* | node()"/>
        </xsl:element>
    </xsl:template>

    <!-- template to copy attributes -->
    <xsl:template match="@*">
        <xsl:attribute name="{local-name()}">
            <xsl:value-of select="."/>
        </xsl:attribute>
    </xsl:template>

    <!-- template to copy the rest of the nodes -->
    <xsl:template match="comment() | text() | processing-instruction()">
        <xsl:copy/>
    </xsl:template>


</xsl:stylesheet>
