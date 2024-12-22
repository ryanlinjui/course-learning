<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <html>
            <head>
                <title>會員與書籍清單</title>
            </head>
            <body>
                <h2>會員清單</h2>
                <table border="1">
                    <tr>
                        <th>會員 ID</th>
                        <th>名稱</th>
                    </tr>
                    <xsl:for-each select="data/members/member">
                        <tr>
                            <td><xsl:value-of select="@id"/></td>
                            <td><xsl:value-of select="name"/></td>
                        </tr>
                    </xsl:for-each>
                </table>

                <h2>書籍清單</h2>
                <table border="1">
                    <tr>
                        <th>書籍 ID</th>
                        <th>標題</th>
                        <th>作者</th>
                        <th>價格</th>
                    </tr>
                    <xsl:for-each select="data/books/book">
                        <tr>
                            <td><xsl:value-of select="@id"/></td>
                            <td><xsl:value-of select="title"/></td>
                            <td><xsl:value-of select="author"/></td>
                            <td><xsl:value-of select="price"/></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
