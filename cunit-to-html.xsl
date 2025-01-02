<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- Output HTML -->
  <xsl:output method="html" encoding="UTF-8"/>

  <!-- Template for the root element -->
  <xsl:template match="/">
    <html>
      <head>
        <title>CUnit Test Report</title>
        <style>
          body {
            font-family: Arial, sans-serif;
          }
          table {
            width: 100%;
            border-collapse: collapse;
          }
          th, td {
            padding: 8px;
            text-align: left;
            border: 1px solid #ddd;
          }
          th {
            background-color: #f2f2f2;
          }
          .passed {
            background-color: #d4edda;
          }
          .failed {
            background-color: #f8d7da;
          }
        </style>
      </head>
      <body>
        <h1>CUnit Test Results</h1>

        <!-- Test Suite Listing -->
        <h2>Test Suites</h2>
        <table>
          <tr>
            <th>Suite Name</th>
            <th>Test Cases</th>
          </tr>
          <xsl:for-each select="//CUNIT_RUN_SUITE">
            <tr>
              <td><xsl:value-of select="CUNIT_RUN_SUITE_SUCCESS/SUITE_NAME" /></td>
              <td>
                <ul>
                  <xsl:for-each select="CUNIT_RUN_SUITE_SUCCESS/CUNIT_RUN_TEST_RECORD">
                    <li><xsl:value-of select="CUNIT_RUN_TEST_SUCCESS/TEST_NAME" /></li>
                  </xsl:for-each>
                </ul>
              </td>
            </tr>
          </xsl:for-each>
        </table>

        <!-- Test Summary -->
        <h2>Test Summary</h2>
        <table>
          <tr>
            <th>Type</th>
            <th>Total</th>
            <th>Run</th>
            <th>Succeeded</th>
            <th>Failed</th>
            <th>Inactive</th>
          </tr>
          <xsl:for-each select="//CUNIT_RUN_SUMMARY_RECORD">
            <tr>
              <td><xsl:value-of select="TYPE" /></td>
              <td><xsl:value-of select="TOTAL" /></td>
              <td><xsl:value-of select="RUN" /></td>
              <td><xsl:value-of select="SUCCEEDED" /></td>
              <td><xsl:value-of select="FAILED" /></td>
              <td><xsl:value-of select="INACTIVE" /></td>
            </tr>
          </xsl:for-each>
        </table>

        <!-- Footer -->
        <div>
          <p><xsl:value-of select="//CUNIT_FOOTER" /></p>
        </div>
      </body>
    </html>
  </xsl:template>

</xsl:stylesheet>
