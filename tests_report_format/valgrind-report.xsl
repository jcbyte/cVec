<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" indent="yes" />

  <xsl:template match="/valgrindoutput">
    <html>
      <head>
        <title>Valgrind Report</title>
        <style>
          body { font-family: Arial, sans-serif; }
        </style>
      </head>
      <body>
        <h1>Valgrind Report</h1>
        <div>
          <xsl:value-of select="args/argv/exe" />
        </div>

        <h2>Status</h2>
        <ol>
          <xsl:apply-templates select="status" />
        </ol>

        <h2>Errors</h2>
        <xsl:choose>
          <xsl:when test="error">
            <ul style="color: red">
              <xsl:apply-templates select="error" />
            </ul>
          </xsl:when>
          <xsl:otherwise>
            <p style="color: green;">
              <strong>No errors found.</strong>
            </p>
          </xsl:otherwise>
        </xsl:choose>

        <h2>Valgrind Details</h2>
        <xsl:apply-templates select="preamble" />
      </body>
    </html>
  </xsl:template>

  <xsl:template match="status">
    <li>
      <strong><xsl:value-of select="state" /></strong> - <xsl:value-of select="time" />
    </li>
  </xsl:template>

  <xsl:template match="error">
    <li style="margin-bottom: 25px;">
      <div>
        <strong><xsl:value-of select="kind" /></strong>
      </div>
      <div>
        <xsl:value-of select="xwhat/text" />
      </div>
      <div style="margin-bottom: 5px;">Trace:</div>
      <div style="margin-left: 20px;">
        <xsl:apply-templates select="stack" />
      </div>
    </li>
  </xsl:template>

  <xsl:template match="stack">
    <xsl:for-each select="frame[fn and dir and file and line]">
      <div>
        <strong><xsl:value-of select="fn" /></strong> in <xsl:value-of select="dir" />/<strong><xsl:value-of select="file" /></strong> on line <strong>
      <xsl:value-of select="line" />
    </strong>
  </div>
</xsl:for-each>

</xsl:template>

<xsl:template match="preamble">
<xsl:for-each select="line">
  <div>
    <xsl:value-of select="." />
  </div>
</xsl:for-each>
</xsl:template>
</xsl:stylesheet>