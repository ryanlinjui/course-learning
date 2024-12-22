async function validateXML(xmlContent, xsdContent) {
    try {
        // 使用 DOMParser 解析 XML 和 XSD
        const parser = new DOMParser();
        const xmlDoc = parser.parseFromString(xmlContent, 'application/xml');
        const xsdDoc = parser.parseFromString(xsdContent, 'application/xml');

        // 檢查 XML 格式錯誤
        if (xmlDoc.querySelector('parsererror')) {
            alert('XML 格式錯誤，請檢查內容。');
            return;
        }
        if (xsdDoc.querySelector('parsererror')) {
            alert('XSD 格式錯誤，請檢查內容。');
            return;
        }

        // 驗證邏輯
        const isValid = validateDataStructure(xmlDoc, xsdDoc);
        if (isValid) {
            alert('XML 文件通過驗證！');
        } else {
            alert('XML 文件未通過驗證，請檢查內容是否符合結構要求。');
        }
    } catch (error) {
        console.error('驗證錯誤：', error);
        alert('驗證過程中發生錯誤，請檢查文件格式或邏輯。');
    }
}

function validateDataStructure(xmlDoc, xsdDoc) {
    try {
        // 確認根節點名稱是否正確
        const xmlRoot = xmlDoc.documentElement.nodeName;
        if (xmlRoot !== 'data') {
            console.error(`根節點名稱不匹配：XML(${xmlRoot}) 必須為 'data'`);
            return false;
        }

        // 檢查 members 和 books 是否符合需求
        const membersNode = xmlDoc.getElementsByTagName('members')[0];
        const booksNode = xmlDoc.getElementsByTagName('books')[0];

        if (!membersNode && !booksNode) {
            console.error('XML 文件至少需要包含 members 或 books 節點。');
            return false;
        }

        // 如果有 members，檢查其結構
        if (membersNode) {
            const members = membersNode.getElementsByTagName('member');
            for (const member of members) {
                if (!member.getAttribute('id') || !member.getElementsByTagName('name')[0]) {
                    console.error('會員節點缺少 id 屬性或 name 元素。');
                    return false;
                }
            }
        }

        // 如果有 books，檢查其結構
        if (booksNode) {
            const books = booksNode.getElementsByTagName('book');
            for (const book of books) {
                if (
                    !book.getAttribute('id') ||
                    !book.getElementsByTagName('title')[0] ||
                    !book.getElementsByTagName('author')[0] ||
                    !book.getElementsByTagName('price')[0]
                ) {
                    console.error('書籍節點缺少 id 屬性或其他必要元素（title, author, price）。');
                    return false;
                }
            }
        }

        return true; // 驗證成功
    } catch (error) {
        console.error('驗證結構錯誤：', error);
        return false;
    }
}

document.getElementById('validate-xml').addEventListener('click', async () => {
    const xmlFile = document.getElementById('xml-file').files[0];
    const xsdFile = document.getElementById('xsd-file').files[0];

    if (!xmlFile || !xsdFile) {
        alert('請選擇 XML 和 XSD 文件！');
        return;
    }

    const xmlContent = await xmlFile.text();
    const xsdContent = await xsdFile.text();
    validateXML(xmlContent, xsdContent);
});
