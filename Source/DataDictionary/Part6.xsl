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
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

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

  <xsl:apply-templates select="*/*/dk:table[@xml:id='table_6-1']" />
</xsl:template>

<xsl:template match="dk:tr">
  <xsl:variable name="tag" select="dk:td[1]/dk:para/text()"/>
  <xsl:variable name="group" select="substring-after(substring-before($tag,','), '(')"/>
  <xsl:variable name="element" select="substring-after(substring-before($tag,')'), ',')"/>
  <xsl:variable name="name" select="dk:td[2]/dk:para/text()"/>
  <xsl:variable name="keyword" select="translate(dk:td[3]/dk:para/text(),'&#x200B;','')"/>
  <xsl:variable name="vr" select="dk:td[4]/dk:para/text()"/>
  <!--xsl:variable name="vm" select="dk:td[5]/dk:para/text()"/-->
  <xsl:variable name="vm">
    <xsl:choose>
      <xsl:when test="dk:td[5]/dk:para/dk:emphasis">
        <xsl:value-of select="dk:td[5]/dk:para/dk:emphasis/text()"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="dk:td[5]/dk:para/text()"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:variable>
  <xsl:variable name="ret" select="dk:td[6]/dk:para/text()"/>
  <!--xsl:if test="$group != ''"-->
  <entry group="{$group}" element="{$element}" keyword="{$keyword}" vr="{$vr}" vm="{$vm}" retired="{$ret}" name="{$name}"/>
  <!--/xsl:if-->
</xsl:template>

<!-- remove thread -->
<xsl:template match="dk:thead"/>

<xsl:template match="dk:emphasis">
   <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="dk:tbody">
   <xsl:apply-templates select="*"/>
</xsl:template>

<xsl:template match="dk:caption"/>

<xsl:template match="dk:table">
  <xsl:variable name="caption" select="dk:caption"/>
<dicts edition="2011">
<dict ref="6" name="{$caption}">
   <xsl:apply-templates select="*"/>
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
