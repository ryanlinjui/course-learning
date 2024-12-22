const memberList = document.getElementById('member-list');
const bookList = document.getElementById('book-list');
const tempMembers = [];
const tempBooks = [];

// 加載 XML 文件
document.getElementById('load-xml').addEventListener('click', function () {
    const fileInput = document.getElementById('xml-file');
    const file = fileInput.files[0];

    if (!file) {
        alert('請選擇 XML 文件！');
        return;
    }

    const reader = new FileReader();
    reader.onload = function (e) {
        const parser = new DOMParser();
        const xmlDoc = parser.parseFromString(e.target.result, 'application/xml');

        // 清空現有數據
        tempMembers.length = 0;
        tempBooks.length = 0;
        memberList.innerHTML = '';
        bookList.innerHTML = '';

        // 加載會員數據
        const members = xmlDoc.getElementsByTagName('member');
        Array.from(members).forEach(member => {
            const id = member.getAttribute('id');
            const name = member.getElementsByTagName('name')[0].textContent;

            tempMembers.push({ id, name });

            const listItem = document.createElement('li');
            listItem.textContent = `ID: ${id}, Name: ${name}`;
            memberList.appendChild(listItem);
        });

        // 加載書籍數據
        const books = xmlDoc.getElementsByTagName('book');
        Array.from(books).forEach(book => {
            const id = book.getAttribute('id');
            const title = book.getElementsByTagName('title')[0].textContent;
            const author = book.getElementsByTagName('author')[0].textContent;
            const price = book.getElementsByTagName('price')[0].textContent;

            tempBooks.push({ id, title, author, price });

            const listItem = document.createElement('li');
            listItem.textContent = `ID: ${id}, Title: ${title}, Author: ${author}, Price: ${price}`;
            bookList.appendChild(listItem);
        });

        alert('XML 數據加載成功！');
    };
    reader.readAsText(file);
});

// 新增會員功能
document.getElementById('add-member').addEventListener('click', () => {
    const memberId = document.getElementById('member-id').value;
    const memberName = document.getElementById('member-name').value;

    if (!memberId || !memberName) {
        alert('請輸入會員 ID 和名稱！');
        return;
    }

    if (tempMembers.some(member => member.id === memberId)) {
        alert('會員 ID 已存在，請輸入唯一的 ID！');
        return;
    }

    tempMembers.push({ id: memberId, name: memberName });

    const newMember = document.createElement('li');
    newMember.textContent = `ID: ${memberId}, Name: ${memberName}`;
    memberList.appendChild(newMember);

    document.getElementById('member-id').value = '';
    document.getElementById('member-name').value = '';
});

// 修改會員功能
document.getElementById('update-member').addEventListener('click', () => {
    const memberId = document.getElementById('member-id').value;
    const memberName = document.getElementById('member-name').value;

    if (!memberId || !memberName) {
        alert('請輸入會員 ID 和名稱！');
        return;
    }

    const member = tempMembers.find(member => member.id === memberId);
    if (member) {
        member.name = memberName;

        const listItem = Array.from(memberList.children).find(
            item => item.textContent.includes(`ID: ${memberId},`)
        );
        if (listItem) {
            listItem.textContent = `ID: ${memberId}, Name: ${memberName}`;
        }

        alert('會員更新成功！');
    } else {
        alert('未找到該會員！');
    }
});

// 刪除會員功能
document.getElementById('delete-member').addEventListener('click', () => {
    const memberId = document.getElementById('member-id').value;

    const memberIndex = tempMembers.findIndex(member => member.id === memberId);
    if (memberIndex > -1) {
        tempMembers.splice(memberIndex, 1);

        const listItem = Array.from(memberList.children).find(
            item => item.textContent.includes(`ID: ${memberId},`)
        );
        if (listItem) {
            memberList.removeChild(listItem);
        }

        alert('會員已刪除！');
    } else {
        alert('未找到該會員！');
    }
});

// 查詢會員功能
document.getElementById('search-member').addEventListener('click', () => {
    const memberId = document.getElementById('member-id').value;

    const member = tempMembers.find(member => member.id === memberId);
    if (member) {
        alert(`找到會員：ID: ${member.id}, Name: ${member.name}`);
    } else {
        alert('未找到該會員！');
    }
});

// 新增書籍功能
document.getElementById('add-book').addEventListener('click', () => {
    const bookId = document.getElementById('book-id').value;
    const bookTitle = document.getElementById('book-title').value;
    const bookAuthor = document.getElementById('book-author').value;
    const bookPrice = document.getElementById('book-price').value;

    if (!bookId || !bookTitle || !bookAuthor || !bookPrice) {
        alert('請輸入書籍的所有信息！');
        return;
    }

    if (tempBooks.some(book => book.id === bookId)) {
        alert('書籍 ID 已存在，請輸入唯一的 ID！');
        return;
    }

    tempBooks.push({ id: bookId, title: bookTitle, author: bookAuthor, price: bookPrice });

    const newBook = document.createElement('li');
    newBook.textContent = `ID: ${bookId}, Title: ${bookTitle}, Author: ${bookAuthor}, Price: ${bookPrice}`;
    bookList.appendChild(newBook);

    document.getElementById('book-id').value = '';
    document.getElementById('book-title').value = '';
    document.getElementById('book-author').value = '';
    document.getElementById('book-price').value = '';
});

// 修改書籍功能
document.getElementById('update-book').addEventListener('click', () => {
    const bookId = document.getElementById('book-id').value;
    const bookTitle = document.getElementById('book-title').value;
    const bookAuthor = document.getElementById('book-author').value;
    const bookPrice = document.getElementById('book-price').value;

    if (!bookId || !bookTitle || !bookAuthor || !bookPrice) {
        alert('請填寫所有書籍信息！');
        return;
    }

    const book = tempBooks.find(book => book.id === bookId);
    if (book) {
        book.title = bookTitle;
        book.author = bookAuthor;
        book.price = bookPrice;

        const listItem = Array.from(bookList.children).find(
            item => item.textContent.includes(`ID: ${bookId},`)
        );
        if (listItem) {
            listItem.textContent = `ID: ${bookId}, Title: ${bookTitle}, Author: ${bookAuthor}, Price: ${bookPrice}`;
        }

        alert('書籍更新成功！');
    } else {
        alert('未找到該書籍！');
    }
});

// 刪除書籍功能
document.getElementById('delete-book').addEventListener('click', () => {
    const bookId = document.getElementById('book-id').value;

    if (!bookId) {
        alert('請輸入書籍 ID！');
        return;
    }

    const bookIndex = tempBooks.findIndex(book => book.id === bookId);
    if (bookIndex > -1) {
        tempBooks.splice(bookIndex, 1);

        const listItem = Array.from(bookList.children).find(
            item => item.textContent.includes(`ID: ${bookId},`)
        );
        if (listItem) {
            bookList.removeChild(listItem);
        }

        alert('書籍已刪除！');
    } else {
        alert('未找到該書籍！');
    }
});

// 查詢書籍功能
document.getElementById('search-book').addEventListener('click', () => {
    const bookId = document.getElementById('book-id').value;

    if (!bookId) {
        alert('請輸入書籍 ID！');
        return;
    }

    const book = tempBooks.find(book => book.id === bookId);
    if (book) {
        alert(`找到書籍：\nID: ${book.id}\n標題: ${book.title}\n作者: ${book.author}\n價格: ${book.price}`);
    } else {
        alert('未找到該書籍！');
    }
});

// 下載 XML 文件
document.getElementById('download-xml').addEventListener('click', () => {
    const membersXML = tempMembers
        .map(member => `  <member id="${member.id}">\n    <name>${member.name}</name>\n  </member>`)
        .join('\n');

    const booksXML = tempBooks
        .map(book => `  <book id="${book.id}">\n    <title>${book.title}</title>\n    <author>${book.author}</author>\n    <price>${book.price}</price>\n  </book>`)
        .join('\n');

    const xmlContent = `<?xml version="1.0" encoding="UTF-8"?>\n<data>\n<members>\n${membersXML}\n</members>\n<books>\n${booksXML}\n</books>\n</data>`;

    const blob = new Blob([xmlContent], { type: 'application/xml' });
    const a = document.createElement('a');
    a.href = URL.createObjectURL(blob);
    a.download = 'data.xml';
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(a.href);
});
