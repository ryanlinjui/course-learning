document.getElementById('xml-file').addEventListener('change', async function (event) {
    const file = event.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = function (e) {
        const parser = new DOMParser();
        const xmlDoc = parser.parseFromString(e.target.result, "application/xml");

        const xmlContentElement = document.getElementById('xml-content');
        if (xmlDoc.querySelector('parsererror')) {
            xmlContentElement.textContent = "無法解析 XML 文件，請檢查格式是否正確。";
        } else {
            xmlContentElement.textContent = new XMLSerializer().serializeToString(xmlDoc);
        }

        applyXSLTransform(e.target.result, 'assets/sample.xsl');
    };
    reader.readAsText(file);
});

async function applyXSLTransform(xmlContent, xslPath) {
    const xslResponse = await fetch(xslPath);
    const xslContent = await xslResponse.text();

    const parser = new DOMParser();
    const xmlDoc = parser.parseFromString(xmlContent, "application/xml");
    const xslDoc = parser.parseFromString(xslContent, "application/xml");

    const xsltProcessor = new XSLTProcessor();
    xsltProcessor.importStylesheet(xslDoc);

    const resultDocument = xsltProcessor.transformToDocument(xmlDoc);
    const iframe = document.getElementById('data-island-view');
    const iframeDoc = iframe.contentDocument || iframe.contentWindow.document;
    iframeDoc.open();
    iframeDoc.write(new XMLSerializer().serializeToString(resultDocument));
    iframeDoc.close();
}
