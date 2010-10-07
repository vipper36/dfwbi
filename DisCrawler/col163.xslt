<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:variable name="box" select="//div[@class='colL']|//div[@class='colLM']"/> 
  <xsl:template match="/">
    <columns>
      <xsl:for-each select="$box">
        <xsl:variable name="boxfilter" select="div[contains(@class,'titleBar')]"/> 
	
	<xsl:variable name="boxtitle" select="div[contains(@class,'titleBar')]/h2/a"/> 
	
	<xsl:variable name="boxurl" select="div[contains(@class,'titleBar')]/h2/a/@href"/>
	
	<xsl:variable name="sub" select=".//div[@class='content']//a" />
	
	<xsl:if test="$boxfilter"> 
	  <column>
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
	    <xsl:for-each select="$sub">
              <xsl:variable name="suburl" select="./@href"/> 
	      <xsl:variable name="subtitle" select=".|.//*"/> 
	      <subitem>
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
	      </subitem>
	    </xsl:for-each>
	  </column>
	</xsl:if>
      </xsl:for-each>
    </columns>
  </xsl:template>
</xsl:stylesheet>
