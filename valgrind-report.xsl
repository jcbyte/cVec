<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
    <!-- Template for the root element -->
    <xsl:template match="/">
        <html>
            <head>
                <title>Valgrind Memory Report</title>
                <style>
                    body { font-family: Arial, sans-serif; margin: 20px; }
                    h1 { color: #333; }
                    .error { margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; background-color: #f9f9f9; }
                    .stacktrace { font-family: Courier, monospace; background-color: #f0f0f0; padding: 10px; margin-top: 10px; }
                    .frame { margin-bottom: 5px; }
                </style>
            </head>
            <body>
                <h1>Valgrind Memory Report</h1>
                
                <!-- Preamble Section -->
                <h2>Preamble</h2>
                <ul>
                    <xsl:for-each select="valgrindoutput/preamble/line">
                        <li><xsl:value-of select="."/></li>
                    </xsl:for-each>
                </ul>

                <h2>Memory Errors</h2>
                <xsl:apply-templates select="//error"/>

            </body>
        </html>
    </xsl:template>

    <!-- Template for each error -->
    <xsl:template match="error">
        <div class="error">
            <h3>Error Type: <xsl:value-of select="kind"/></h3>
            <p><strong>Details:</strong> <xsl:value-of select="xwhat/text"/></p>
            <p><strong>Leaked Bytes:</strong> <xsl:value-of select="xwhat/leakedbytes"/> bytes</p>
            <p><strong>Leaked Blocks:</strong> <xsl:value-of select="xwhat/leakedblocks"/> block(s)</p>
            <h4>Stack Trace:</h4>
            <div class="stacktrace">
                <xsl:for-each select="stack/frame">
                    <div class="frame">
                        <p><strong>Function:</strong> <xsl:value-of select="fn"/> (<xsl:value-of select="file"/>, Line: <xsl:value-of select="line"/>)</p>
                        <p><strong>Object:</strong> <xsl:value-of select="obj"/> (IP: <xsl:value-of select="ip"/>)</p>
                    </div>
                </xsl:for-each>
            </div>
        </div>
    </xsl:template>

</xsl:stylesheet>
