<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into the old 
     GDCM1 data dictionary -->
<!-- The main template that loop over all dict/entry -->
  <xsl:template match="/">
    <xsl:for-each select="dict/entry">
      <xsl:value-of select="@group"/>
      <xsl:text> </xsl:text>
      <xsl:value-of select="@element"/>
      <xsl:text> </xsl:text>
      <xsl:for-each select="representations/r">
        <xsl:value-of select="@vr"/>
        <xsl:if test="position() != last()">
          <xsl:text> or </xsl:text>
        </xsl:if>
      </xsl:for-each>
      <xsl:text> </xsl:text>
      <xsl:for-each select="representations/r">
        <xsl:value-of select="@vm"/>
        <xsl:if test="position() != last()">
          <xsl:text> or </xsl:text>
        </xsl:if>
      </xsl:for-each>
      <xsl:text> </xsl:text>
      <xsl:value-of select="description"/>
      <!--<xsl:if test="@retired = &quot;true&quot;">-->
      <xsl:if test="@retired != &quot;false&quot;">
        <xsl:text> (RET)</xsl:text>
      </xsl:if>
      <xsl:text>
</xsl:text>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
