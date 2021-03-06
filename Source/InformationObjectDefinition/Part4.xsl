<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
  <xsl:output method="xml" indent="yes" encoding="UTF-8"/>
<!--
  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL: https://gdcm.svn.sourceforge.net/svnroot/gdcm/tags/gdcm-2-0-12/Source/InformationObjectDefinition/Part4.xsl $

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
<xsl:template match="text()" />
  <xsl:template match="informaltable">
	  <xsl:if test="tgroup/tbody/row/entry/para = 'SOP Class Name'">
    <xsl:apply-templates/>
	  </xsl:if>
  </xsl:template>

  <xsl:template match="para">
    <!--xsl:apply-templates/-->
  </xsl:template>

  <xsl:template match="tgroup">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="tbody">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="article">
    <xsl:variable name="section-number" select="'Table B.5-1STANDARD SOP CLASSES'"/>
    <xsl:variable name="section-anchor" select="para[starts-with(normalize-space(.),$section-number)]"/>
    <xsl:message><xsl:value-of select="$section-anchor"/></xsl:message>
    <standard-sop-classes>
	    <!--xsl:apply-templates select="article/sect1/sect2/informaltable"/-->
	    <!--xsl:apply-templates select="informaltable"/-->
	    <xsl:apply-templates select="sect1/sect2/informaltable"/>
    </standard-sop-classes>
  </xsl:template>
 
  <xsl:template match="row">
    <!--xsl:apply-templates/-->
    <xsl:variable name="classname" select="entry[1]/para"/>
    <xsl:variable name="classuid" select="entry[2]/para"/>
    <xsl:variable name="iod" select="entry[3]/para"/>
    <xsl:if test="$classname != 'SOP Class Name'">
    <mapping sop-class-name="{$classname}" sop-class-uid="{normalize-space($classuid)}" iod="{$iod}" />
    </xsl:if>
  </xsl:template>

  <!--
  <xsl:template match="entry">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="para">
    <xsl:value-of select="."/>
  </xsl:template>
  -->
 
  <xsl:template match="/">
    <xsl:comment>
  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL: https://gdcm.svn.sourceforge.net/svnroot/gdcm/tags/gdcm-2-0-12/Source/InformationObjectDefinition/Part4.xsl $

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
</xsl:comment>
     <xsl:apply-templates select="article"/>
 </xsl:template>
</xsl:stylesheet>

