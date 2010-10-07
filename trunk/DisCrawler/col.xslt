<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" indent="yes" /> 
  <xsl:param name="docurl" />
  <xsl:param name="urlid" />
  <xsl:variable name="box" select="//div[@class='list_l']"/> 
  <xsl:template match="/">
    <Result type="2">
      <xsl:attribute name="url">
	<xsl:value-of select="$docurl"/>
      </xsl:attribute>
      <Column>
	<xsl:attribute name="uid">
	  <xsl:value-of select="$urlid"/>
	</xsl:attribute>
	<xsl:for-each select="$box">
	  <xsl:variable name="boxfilter" select="div[@class='l_t' and string-length(text())>0]"/> 
	  <xsl:variable name="boxtitle" select="div[@class='l_t']"/> 
	  <xsl:variable name="boxurl" select="./@href"/> 
	  <xsl:variable name="sub" select=".//*[contains(@href,'content')]"/> 
	  <xsl:if test="$boxfilter"> 
	    <xsl:for-each select="$sub">
	      <xsl:variable name="suburl" select="./@href"/>
	      <xsl:variable name="subtitle" select=".|.//*"/>
	      <SubItem>
		<xsl:attribute name="url">
		  <xsl:value-of select="$suburl"/>
		</xsl:attribute>
		<xsl:for-each select="$subtitle">
                  <xsl:choose>       
                    <xsl:when test="name() = 'SCRIPT' "> 
		      <xsl:text/>
		    </xsl:when> 
		    <xsl:otherwise> 
		      <xsl:value-of select="text()"/>
		    </xsl:otherwise> 
		  </xsl:choose> 
		</xsl:for-each>
	      </SubItem>
	    </xsl:for-each>
	  </xsl:if>
	</xsl:for-each>
      </Column>
    </Result>
  </xsl:template>
</xsl:stylesheet>
