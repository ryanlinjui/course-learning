# Homework 2
![](https://img.shields.io/badge/Name-林昕鋭-blue?logo=arduino)  
![](https://img.shields.io/badge/ID-41047035S-blue?logo=arduino)

> 請打開這個連結 https://qkmj0mpmrq8svyt035ie9a.on.drv.tw/web/ 以瀏覽我的網站。

# Requirements
- Design a Pure HTML5 Website at least 4 pages
- Include images, hyperlinks, tables, and any form of multimedia contents
- At least one page with SVG or `<canvas>` scalar graphics
- One page show your resume.xml
- Use WCAG 2.1 Web Accessible Design (at least 3 items)
- Use RWD for laptop and mobile devices

----

# Design a Pure HTML5 Website at least 4 pages
網站包含以下 4 個頁面：
- **首頁（index.html）**：介紹網站主題並提供導覽功能。
- **關於頁面（about.html）**：展示個人簡介與 SVG 圖形。
- **圖庫頁面（gallery.html）**：提供圖片、影片、多媒體格式表格。
- **履歷頁面（resume.html）**：動態讀取並顯示 `resume.xml` 的內容。

> **實作說明**：每個頁面使用純 HTML5 語法設計，搭配語意化標籤（如 `<header>`、`<main>`、`<footer>`），符合現代網頁結構最佳實踐。

---

# Include images, hyperlinks, tables, and any form of multimedia contents
1. **圖片（images）**：
   - 圖庫頁面（`gallery.html`）內嵌圖片並附加 `alt` 屬性進行描述：
     ```html
     <img src="images/photo1.jpg" alt="一個寧靜的海灘日落">
     ```

2. **超連結（hyperlinks）**：
   - 所有頁面都有導航列（`<nav>`），可跳轉至其他頁面，並在圖庫頁面添加外部超連結：
     ```html
     <a href="https://www.unsplash.com" target="_blank">Unsplash Gallery</a>
     ```

3. **表格（tables）**：
   - 圖庫頁面包含多媒體格式表格：
     ```html
     <table>
         <tr>
             <th>Type</th>
             <th>Format</th>
             <th>Example</th>
         </tr>
         <tr>
             <td>Image</td>
             <td>JPEG</td>
             <td><a href="images/photo1.jpg" download>Download</a></td>
         </tr>
     </table>
     ```

4. **多媒體內容（multimedia）**：
   - 圖庫頁面嵌入影片（來自 W3Schools 提供的公開影片 URL）：
     ```html
     <video controls>
         <source src="https://www.w3schools.com/html/mov_bbb.mp4" type="video/mp4">
         Your browser does not support the video tag.
     </video>
     ```

---

# At least one page with SVG or `<canvas>` scalar graphics
- **SVG 圖形**：
  - 在 `about.html` 使用簡單的 SVG 向量圖，展示圓形與文字：
    ```html
    <svg width="200" height="100">
        <circle cx="50" cy="50" r="40" fill="blue"></circle>
        <text x="50" y="55" fill="white" font-size="16" text-anchor="middle">SVG 圖形</text>
    </svg>
    ```

- **Canvas 圖形**：
  - 在 `gallery.html` 使用 `<canvas>` 繪製矩形、圓形和文字：
    ```html
    <canvas id="artCanvas" width="400" height="200"></canvas>
    <script>
        const canvas = document.getElementById('artCanvas');
        const ctx = canvas.getContext('2d');
        ctx.fillStyle = 'lightblue';
        ctx.fillRect(50, 50, 150, 100);
        ctx.beginPath();
        ctx.arc(300, 100, 50, 0, Math.PI * 2);
        ctx.fillStyle = 'orange';
        ctx.fill();
    </script>
    ```

---

# One page show your resume.xml
- **履歷頁面（`resume.html`）**：
  - 動態讀取 `resume.xml`，使用 JavaScript 解析內容並顯示於頁面：
    ```javascript
    fetch('resume.xml')
        .then(response => response.text())
        .then(xmlText => {
            const parser = new DOMParser();
            const xmlDoc = parser.parseFromString(xmlText, 'application/xml');
            const name = xmlDoc.querySelector('name').textContent;
            const container = document.getElementById('resume-container');
            container.innerHTML = `<h3>${name}</h3>`;
        });
    ```

---

# Use WCAG 2.1 Web Accessible Design (at least 3 items)
1. **文字替代（Alt Text）**：
   - 圖片與影片均提供 `alt` 或 `track` 元素，例如：
     ```html
     <img src="images/photo1.jpg" alt="一個寧靜的海灘日落">
     ```

2. **鍵盤操作（Keyboard Accessibility）**：
   - 所有超連結和按鈕均可透過鍵盤操作，例如：
     ```html
     <a href="index.html" role="button">返回首頁</a>
     ```

3. **響應式設計（RWD）**：
   - 使用 CSS 媒體查詢和比例寬度確保頁面在不同裝置上的良好顯示：
     ```css
     @media screen and (max-width: 768px) {
         nav a {
             display: block;
             margin: 5px 0;
         }
     }
     ```

---

# Use RWD for laptop and mobile devices
- **CSS 響應式設計**：
  - 使用 `<meta>` 元素和 CSS 媒體查詢調整頁面布局：
    ```html
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    ```
    ```css
    img, video {
        max-width: 100%;
        height: auto;
    }
    ```

- **桌面與手機的顯示效果**：
  - 確保導航列和內容可隨裝置寬度調整，例如：
    ```css
    @media screen and (max-width: 768px) {
        nav a {
            display: block;
            margin: 5px 0;
        }
    }
    ```
