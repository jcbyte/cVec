<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" encoding="UTF-8"/>

  <xsl:template match="/CUNIT_TEST_RUN_REPORT">
    <html>
      <head>
        <title>CUnit Test Report</title>
        <style>
          body { font-family: Arial, sans-serif; }
          .summary-box { border: 1px solid #ccc; border-radius: 5px; padding: 15px; text-align: center; width: 180px; box-shadow: 0 2px 8px rgba(0, 0, 0, 0.4); }
          .percentage { font-size: 30px; }
        </style>
      </head>
      <body>
        <h1>CUnit Test Results</h1>

        <div style="display: flex; gap: 20px;">
          <xsl:for-each select="CUNIT_RUN_SUMMARY">
            <xsl:for-each select="CUNIT_RUN_SUMMARY_RECORD[TYPE=' Suites ']">
              <div class="summary-box">
                <h3>Suites</h3>
                <p>
                  <xsl:value-of select="RUN" /> Total
                </p>
              </div>
            </xsl:for-each>

            <xsl:for-each select="CUNIT_RUN_SUMMARY_RECORD[TYPE=' Test Cases ']">
              <xsl:variable name="total" select="TOTAL"/>
              <xsl:variable name="succeeded" select="SUCCEEDED"/>
              <div class="summary-box">
                <xsl:attribute name="style">
                  background: <xsl:choose>
                    <xsl:when test="$succeeded = $total">#abffab</xsl:when>
                    <xsl:otherwise>#ffabab</xsl:otherwise>
                  </xsl:choose>;
                </xsl:attribute>
                <h3>Tests</h3>
                <div class="percentage">
                  <xsl:value-of select="format-number(($succeeded div $total) * 100, '0.0')"/>%
                </div>
                <div>
                  <xsl:value-of select="$succeeded" />/<xsl:value-of select="$total" /> Passed
                </div>
              </div>
            </xsl:for-each>

            <xsl:for-each select="CUNIT_RUN_SUMMARY_RECORD[TYPE=' Assertions ']">
              <xsl:variable name="total" select="TOTAL"/>
              <xsl:variable name="succeeded" select="SUCCEEDED"/>
              <div class="summary-box">
                <xsl:attribute name="style">
                  background: <xsl:choose>
                    <xsl:when test="$succeeded = $total">#abffab</xsl:when>
                    <xsl:otherwise>#ffabab</xsl:otherwise>
                  </xsl:choose>;
                </xsl:attribute>
                <h3>Assertions</h3>
                <div class="percentage">
                <xsl:value-of select="format-number(($succeeded div $total) * 100, '0.0')"/>%
                </div>
                <div>
                  <xsl:value-of select="$succeeded" />/<xsl:value-of select="$total" /> Passed
                </div>
              </div>
            </xsl:for-each>

          </xsl:for-each >
        </div>

 <!-- todo list failed tests -->
        <!-- Test Suite Listing -->
        <h2>Test Suites</h2>
        <table>
          <tr>
            <th>Suite Name</th>
            <th>Test Cases</th>
          </tr>
          <xsl:for-each select="//CUNIT_RUN_SUITE">
            <tr>
              <td>
                <xsl:value-of select="CUNIT_RUN_SUITE_SUCCESS/SUITE_NAME" />
              </td>
              <td>
                <ul>
                  <xsl:for-each select="CUNIT_RUN_SUITE_SUCCESS/CUNIT_RUN_TEST_RECORD">
                    <li>
                      <xsl:value-of select="CUNIT_RUN_TEST_SUCCESS/TEST_NAME" />
                    </li>
                  </xsl:for-each>
                </ul>
              </td>
            </tr>
          </xsl:for-each>
        </table>

      </body>
    </html>
  </xsl:template>

</xsl:stylesheet>
