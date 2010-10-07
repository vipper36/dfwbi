<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="text" indent="no" encoding="utf-8"/>


    <xsl:param name="drereference" />
    <xsl:param name="xmlname" />
    <xsl:param name="colname" />
    <xsl:param name="jobname" />
    <xsl:param name="pdate" />
    <xsl:param name="sdate" />
    <xsl:template name="extract" match="/">
        <xsl:for-each select="PageInfoFile/ArticleList/Article">
#DREREFERENCE <xsl:value-of select="string($drereference)"/>#<xsl:value-of select="string($xmlname)"/>#<xsl:value-of select="position()"/>
#DRETITLE <xsl:value-of select="Title"/>
#DREDATE <xsl:value-of select="$sdate"/>
#DREFIELD AUTHOR="<xsl:value-of select="Author"/>"
#DREFIELD SOURCENAME="<xsl:value-of select="Source"/>"
#DREFIELD EPAPERCHANNEL="<xsl:value-of select="$colname"/>"
#DREFIELD JOBNAME="<xsl:value-of select="$jobname"/>"
#DREFIELD PUBLISHDATE="<xsl:value-of select="$pdate"/>"
#DREDBNAME NEWS
#DRECONTENT
<xsl:value-of select="Content"/>
#DREENDDOC
        </xsl:for-each>
#DREENDDATA


    </xsl:template>
</xsl:stylesheet>
