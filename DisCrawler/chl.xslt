<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" indent="yes" />
  <xsl:param name="docurl" />
  <xsl:param name="urlid" />
  <xsl:variable name="box" select="//div[@class='list_l']"/> 
  <xsl:template match="/">
    <Result type="1">
      <xsl:attribute name="url">
	<xsl:value-of select="$docurl"/>
      </xsl:attribute>
      <Columns>
	<xsl:attribute name="uid">
	  <xsl:value-of select="$urlid"/>
	</xsl:attribute>
	<xsl:for-each select="$box">
	  <xsl:variable name="boxfilter" select="div[@class='l_t' and string-length(text())>0]"/> 
	  <xsl:variable name="boxtitle" select="div[@class='l_t']"/> 
	  <xsl:variable name="boxurl" select="./@href"/> 
	  <xsl:if test="$boxfilter"> 
	    <Column>
	      <xsl:attribute name="name">
		<xsl:for-each select="$boxtitle">
		  <xsl:choose>       
                    <xsl:when test="img[string-length(@alt)>0]"> 
		      <xsl:value-of select="img/@alt"/>
		    </xsl:when> 
		    <xsl:otherwise> 
		      <xsl:value-of select="text()"/>
		    </xsl:otherwise> 
		  </xsl:choose> 
		</xsl:for-each>
	      </xsl:attribute>
	      <xsl:attribute name="url">
		<xsl:value-of select="$boxurl"/>
	      </xsl:attribute>
	    </Column>
	  </xsl:if>
	</xsl:for-each>
      </Columns>
    </Result>
  </xsl:template>
</xsl:stylesheet>
