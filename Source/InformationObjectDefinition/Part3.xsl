<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
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
<!--
TODO:
* Make sure a <include/> is indeed a Include `' ...
  eg. Fix RAW DATA KEYS, Key are recognized as `Include`

Usage: (you need a XSLT 2.0 processor)

$ java -jar ~/Software/saxon/saxon8.jar  08_03pu.xml Part3.xsl > ModuleAttributes.xml
-->
  <xsl:output method="xml" indent="yes" encoding="UTF-8"/>
  <xsl:variable name="apos">'</xsl:variable>
  <xsl:variable name="linebreak">
    <xsl:text>
</xsl:text>
  </xsl:variable>
<!--

Function to parse a row from an informaltable specifically for a Macro/Module table:

-->
  <xsl:template match="row" mode="macro">
    <xsl:variable name="name">
      <xsl:for-each select="entry[1]/para">
        <xsl:value-of select="normalize-space(.)"/>
        <xsl:if test="position() != last()">
          <xsl:text> </xsl:text>
        </xsl:if>
      </xsl:for-each>
    </xsl:variable>
    <xsl:variable name="tag" select="normalize-space(string-join(entry[2]/para,' '))"/>
    <xsl:choose>
      <xsl:when test="substring($tag,1,1) = '(' and substring($tag,11,1) = ')'">
        <xsl:variable name="group" select="substring-after(substring-before($tag,','), '(')"/>
        <xsl:variable name="element" select="substring-after(substring-before($tag,')'), ',')"/>
<!--used internally to find out if type is indeed type of if column type was missing ... not full proof -->
        <xsl:variable name="internal_type" select="normalize-space(string-join(entry[3]/para,' '))"/>
        <xsl:variable name="type">
          <xsl:value-of select="entry[3]/para" separator="{$linebreak}"/>
        </xsl:variable>
<!-- some funny quote is in the way, replace it: -->
        <xsl:variable name="single_quote1">’</xsl:variable>
        <xsl:variable name="single_quote2">'</xsl:variable>
        <xsl:variable name="description_tmp">
          <xsl:value-of select="entry[4]/para" separator="{$linebreak}"/>
        </xsl:variable>
        <xsl:variable name="name_translate" select="normalize-space(translate($name,$single_quote1,$single_quote2))"/>
        <xsl:variable name="description" select="translate($description_tmp,$single_quote1,$single_quote2)"/>
<!-- Attribute Name  Tag  Type  Attribute Description -->
        <xsl:choose>
<!-- Try to figure if this table is busted (missing Type column -->
          <xsl:when test="string-length($internal_type) &gt;= 0 and string-length($internal_type) &lt;= 2">
            <entry group="{$group}" element="{$element}" name="{translate($name_translate,'','µ')}" type="{normalize-space($type)}">
              <description>
                <xsl:value-of select="translate($description,' ­',' µ')"/>
              </description>
            </entry>
          </xsl:when>
          <xsl:otherwise>
            <entry group="{$group}" element="{$element}" name="{$name_translate}">
<!-- type ?? -->
              <description>
                <xsl:variable name="desc" select="translate($type,'–­','=')"/>
<!-- very specific -->
                <xsl:value-of select="translate($desc,'’',$apos)"/>
              </description>
            </entry>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:when test="$name = 'Attribute Name' or $name = 'Attribute name' or $name = 'Key'">
<!-- This is supposed to be the very first line of each table -->
<!-- someday I might add more stuff here... -->
      </xsl:when>
      <xsl:otherwise>
<!-- I should check if this is indeed a Include line or not... -->
        <xsl:variable name="include" select="normalize-space(translate(translate(string-join(entry,' '),'‘',$apos),'’',$apos))"/>
        <include ref="{$include}"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
<!--

Function to parse an entry from a row in an IOD table
Take the ie name as input

-->
  <xsl:template match="entry" mode="iod">
    <xsl:param name="ie_name"/>
    <xsl:for-each select="entry">
      <xsl:if test="(position() mod 3 = 1)">
        <xsl:variable name="usage" select="translate(normalize-space(following-sibling::entry[2]/para),'–','-')"/>
        <entry ie="{$ie_name}" name="{normalize-space(para)}" ref="{normalize-space(following-sibling::entry[1]/para)}" usage="{$usage}"/>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>
<!--


-->
  <xsl:template match="entry" mode="iod2">
    <xsl:for-each select="entry">
      <xsl:variable name="usage" select="translate(entry[3]/para,'–','-')"/>
      <entry ie="{normalize-space(para)}" name="{normalize-space(following-sibling::entry[1]/para)}" ref="{normalize-space(following-sibling::entry[2]/para)}" usage="{$usage}"/>
    </xsl:for-each>
  </xsl:template>
<!--

Function to parse a row from an informaltable specifically for an IOD table:
For instance:
Table A.2-1 (CR Image IOD Modules) to A.51-1 (Segmentation IOD Modules).
-->
  <xsl:template match="row" mode="iod">
    <xsl:choose>
<!--
Some tables have a specific layout, when namest='c2' and nameend='c4', deals with them properly
as they do not repeat the ie name each time:
-->
      <xsl:when test="entry[2]/@namest = 'c2'">
        <xsl:apply-templates select="entry" mode="iod">
          <xsl:with-param name="ie_name" select="entry[1]/para"/>
        </xsl:apply-templates>
      </xsl:when>
      <xsl:when test="entry[5]/para = 'Module Description'">
        <xsl:apply-templates select="entry" mode="iod2"/>
      </xsl:when>
<!-- Get rid of the first line in the table: IE / Reference / Usage / ... -->
      <xsl:when test="entry[1]/para = 'IE' or entry[1]/para = 'Module'">
      </xsl:when>
<!--
Most of the IE table simply have an empty entry[1]/para to avoid duplicating the ie name
over and over. We need to get the last ie name we found to fill in the blank:
-->
      <xsl:otherwise>
        <xsl:variable name="ref_joined">
          <xsl:value-of select="entry[3]/para" separator=" "/>
<!-- actually space is the default separator for value-of -->
        </xsl:variable>
        <xsl:variable name="usage_joined">
          <xsl:value-of select="entry[4]/para" separator=" "/>
        </xsl:variable>
        <xsl:variable name="usage" select="translate($usage_joined,'–','-')"/>
        <xsl:variable name="ie" select="normalize-space((entry[1]/para[. != ''] , reverse(preceding-sibling::row/entry[1]/para[. != ''])[1])[1])"/>
        <entry ie="{$ie}" name="{normalize-space(entry[2]/para)}" ref="{normalize-space($ref_joined)}" usage="{normalize-space($usage)}"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
<!--


-->
<!-- Table C.2-1PATIENT RELATIONSHIP MODULE ATTRIBUTES -->
<!-- function to extract the table ref (ie: Table C.2-1) -->
  <xsl:template name="get-table-reference">
    <xsl:param name="reference"/>
    <xsl:param name="table_name"/>
    <xsl:variable name="title">
      <xsl:choose>
<!-- need to do it first, since most of the time $reference is busted and contains garbage misleading us... -->
        <xsl:when test="substring($table_name,1,5) = 'Table'">
          <xsl:value-of select="$table_name"/>
        </xsl:when>
        <xsl:when test="substring($reference,1,5) = 'Table'">
          <xsl:value-of select="$reference"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>NO TABLE REF</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:analyze-string select="$title" regex="(Table [ABFC.]*[0-9a-z\.\-]+)\s*(.*)">
      <xsl:matching-substring>
        <xsl:value-of select="regex-group(1)"/>
      </xsl:matching-substring>
      <xsl:non-matching-substring>
        <xsl:text>ERROR: </xsl:text>
        <xsl:value-of select="$title"/>
      </xsl:non-matching-substring>
    </xsl:analyze-string>
  </xsl:template>
<!--


-->
<!-- function to extract the table ref (ie: PATIENT RELATIONSHIP MODULE ATTRIBUTES) -->
  <xsl:template name="get-table-name">
    <xsl:param name="reference"/>
    <xsl:param name="table_name"/>
    <xsl:variable name="ret">
      <xsl:analyze-string select="$table_name" regex="(Table [ABFC.]*[0-9a-z\.\-]+)\s*(.+)">
        <xsl:matching-substring>
          <xsl:value-of select="regex-group(2)"/>
        </xsl:matching-substring>
        <xsl:non-matching-substring>
          <xsl:value-of select="$table_name"/>
        </xsl:non-matching-substring>
      </xsl:analyze-string>
    </xsl:variable>
    <xsl:variable name="garbage">—</xsl:variable>
    <xsl:variable name="clean">
      <xsl:value-of select="translate($ret,$garbage,' ')"/>
    </xsl:variable>
    <xsl:call-template name="removedash">
      <xsl:with-param name="text" select="$clean"/>
    </xsl:call-template>
  </xsl:template>
<!--

Function to remove the dash from a text:
-->
  <xsl:template name="removedash">
    <xsl:param name="text"/>
    <xsl:choose>
      <xsl:when test="starts-with($text, '-')">
        <xsl:value-of select="normalize-space(substring-after($text, '-'))"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="normalize-space($text)"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
<!--


-->
<!-- main template -->
  <xsl:template match="/">
    <xsl:processing-instruction name="xml-stylesheet">
type="text/xsl" href="ma2html.xsl"
</xsl:processing-instruction>
    <xsl:comment> to produce output use:
$ xsltproc ma2html.xsl ModuleAttributes.xml
    </xsl:comment>
    <xsl:comment>
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
</xsl:comment>
    <tables edition="2008">
      <xsl:for-each select="//informaltable">
        <xsl:variable name="table_ref_raw" select="preceding::para[2]"/>
<!-- might contain the Table ref or not ... -->
        <xsl:variable name="table_name_raw" select="preceding::para[1]"/>
        <xsl:variable name="table_ref">
          <xsl:call-template name="get-table-reference">
            <xsl:with-param name="reference" select="normalize-space($table_ref_raw)"/>
            <xsl:with-param name="table_name" select="normalize-space($table_name_raw)"/>
          </xsl:call-template>
        </xsl:variable>
        <xsl:variable name="table_name">
          <xsl:call-template name="get-table-name">
            <xsl:with-param name="reference" select="normalize-space($table_ref_raw)"/>
            <xsl:with-param name="table_name" select="normalize-space($table_name_raw)"/>
          </xsl:call-template>
        </xsl:variable>
<!-- most of the time it should be equal to 4: -->
        <xsl:variable name="tgroup_cols" select="tgroup/@cols"/>
<!--xsl:for-each select="tgroup/thead"-->
        <xsl:for-each select="tgroup/tbody">
          <xsl:variable name="attribute_name" select="normalize-space(string-join(row[1]/entry[1]/para,' '))"/>
          <xsl:choose>
            <xsl:when test="$attribute_name = 'Attribute Name' or $attribute_name = 'Attribute name' or (starts-with($table_ref,'Table') and ends-with($table_name,'ATTRIBUTES') )">
              <macro ref="{$table_ref}" name="{$table_name}">
                <xsl:apply-templates select="row" mode="macro"/>
              </macro>
            </xsl:when>
            <xsl:when test="$attribute_name = 'Key'">
              <module ref="{$table_ref}" name="{$table_name}">
                <xsl:apply-templates select="row" mode="macro"/>
              </module>
            </xsl:when>
<!--
Table A.2-1 (CR Image IOD Modules) to A.51-1 (Segmentation IOD Modules).
-->
            <xsl:when test="$attribute_name = 'IE' or $attribute_name = 'Module'">
              <iod ref="{$table_ref}" name="{$table_name}">
                <xsl:apply-templates select="row" mode="iod"/>
              </iod>
            </xsl:when>
            <xsl:otherwise>
              <xsl:message>
                <xsl:text>
ref=</xsl:text>
                <xsl:value-of select="$table_ref_raw"/>
                <xsl:text>
name=</xsl:text>
                <xsl:value-of select="$table_name_raw"/>
                <xsl:text>
att name=</xsl:text>
                <xsl:value-of select="$attribute_name"/>
              </xsl:message>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </xsl:for-each>
    </tables>
  </xsl:template>
</xsl:stylesheet>
