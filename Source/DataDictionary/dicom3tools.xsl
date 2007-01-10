<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into the old 
     GDCM1 data dictionary -->

<!--life save xsl script found at:
http://www.thescripts.com/forum/thread86881.html
-->
  <xsl:template name="upperCase">
    <xsl:param name="textToTransform"/>
    <xsl:variable name="head">
      <xsl:choose>
        <xsl:when test="contains($textToTransform, ' ')">
          <xsl:value-of select="substring-before($textToTransform, ' ')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$textToTransform"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:variable name="tail" select="substring-after($textToTransform, ' ')"/>
    <xsl:variable name="firstTransform" select="concat(translate(substring($head, 1, 1), 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'), substring($head, 2))"/>
    <xsl:choose>
      <xsl:when test="$tail">
        <xsl:value-of select="$firstTransform"/>
        <xsl:call-template name="upperCase">
          <xsl:with-param name="textToTransform" select="$tail"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$firstTransform"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

<!-- The main template that loop over all dict/entry -->
  <xsl:template match="/">
    <xsl:for-each select="dict/entry">
      <xsl:text>(</xsl:text>
      <xsl:value-of select="translate(@group,'abcdef','ABCDEF')"/>
      <xsl:text>,</xsl:text>
      <xsl:value-of select="translate(@element,'abcdef','ABCDEF')"/>
      <xsl:text>) VERS="</xsl:text>
      <xsl:choose>
        <xsl:when test="@version = 2">
          <xsl:text>2</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>3</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:if test="@retired != &quot;false&quot;">
        <xsl:text>RET</xsl:text>
      </xsl:if>
      <xsl:text>" VR="</xsl:text>
      <xsl:for-each select="representations/representation">
        <xsl:value-of select="@vr"/>
        <xsl:if test="position() != last()">
          <xsl:text>/</xsl:text>
        </xsl:if>
      </xsl:for-each>
      <xsl:text>" VM="</xsl:text>
      <xsl:for-each select="representations/representation">
        <xsl:value-of select="@vm"/>
        <xsl:if test="position() != last()">
          <xsl:text>/</xsl:text>
        </xsl:if>
      </xsl:for-each>
      <xsl:text>" Keyword="</xsl:text>
      <xsl:variable name="apos">'</xsl:variable>
      <!--translating an apostrophe is a pain ... better solution ? -->
      <xsl:variable name="description_apos">
        <xsl:value-of select="translate(description, $apos, '')"/>
      </xsl:variable>
      <xsl:variable name="description_dash">
        <!-- the dicom3tools is not always consistant with capitalization. 
             Assume that every time there is a - we want capitalization -->
        <xsl:value-of select="translate($description_apos,'-',' ')"/>
      </xsl:variable>
      <xsl:variable name="description_cap">
        <xsl:call-template name="upperCase">
          <xsl:with-param name="textToTransform" select="normalize-space($description_dash)"/>
        </xsl:call-template>
      </xsl:variable>
      <!-- remove remaining extra character -->
      <xsl:value-of select="translate($description_cap,'/(),','')"/>
      <xsl:text>" Name="</xsl:text>
      <xsl:value-of select="description"/>
      <xsl:text>"</xsl:text>
      <xsl:text>
</xsl:text>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
