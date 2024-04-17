# Homework 3

- Student ID: 41047035S
- Name: 林昕鋭
- Instructor: 林順喜
- Due: 2023-05-15

## Q1
- Hardware & System
    - Model: MacBook Air (M1, 2020), 16 GB ram
    - System: MacOS (Darwin root:xnu-8020.240.14~1/RELEASE_ARM64_T8101 arm64)
- Language
    - Python3 (Version 3.10)
- Requriement
    - numpy 1.24.2

## Q2
執行程式請下指令：
```sh
python3 main.py < data/input/x.txt > data/output/x.txt
```

## Q3
測資儲存於 ./data/input 資料夾中，前三個測資為依序變大的隨機位置測資，最後兩筆測資則為最大極限臨界測資，每個測資依序為 x.txt 檔名命名，以下為每筆測資內容：

### 1.txt
3 4  
1 0 0 1  
0 0 0 1  
1 1 1 1  

### 2.txt
3 4  
1 1 1 1  
0 0 0 0  
1 1 1 1  

### 3.txt
4 8  
1 1 1 1 0 0 0 0  
0 0 0 1 1 1 1 1  
0 0 0 1 1 1 1 1  
1 1 1 1 0 0 0 0

### 4.txt
8 8  
1 1 1 1 0 1 1 1   
1 0 1 1 1 1 0 1  
1 0 1 1 0 1 1 0  
1 1 0 1 1 1 1 1  
1 1 1 1 1 0 1 1  
1 0 1 1 0 1 1 1  
0 1 1 0 1 1 1 0  
1 0 1 1 1 0 1 1  

### 5.txt
8 8  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  
1 1 1 1 1 1 1 1  

## Q4
使用 Alpha-Beta pruning 演算法實作，測資執行結果儲存於 ./data/ouput 資料夾中，每以依序為 x.txt 檔名命名，以下為各個測資的執行結果：

### 1.txt
Row # : 3  
3 points   
Totle run time = 0.00179 seconds.

### 2.txt
Row # : 1  
0 points  
Totle run time = 0.00137 seconds.

### 3.txt
Column # : 4  
2 points  
Totle run time = 0.19931 seconds.

### 4.txt
極限測資因無法將節點全部跑完，因此 depth 設為 8 層進行測試：  
Column # : 3  
1 points  
Totle run time = 5.25087 seconds. 

### 5.txt
極限測資因無法將節點全部跑完，因此 depth 設為 8 層進行測試：  
Row # : 1  
0 points  
Totle run time = 5.00074 seconds.

## Q5
- Alpha-Beta purning algorithm: https://www.chessprogramming.org/Alpha-Beta
- Numpy Slicing: https://www.zmonster.me/2016/03/09/numpy-slicing-and-indexing.html

## Q6
這次花了一些時間去看縱橫殺棋對抗賽這款遊戲的規則，作業不只是要寫 Alpha-Beta pruning 演算法去實作，也要想出一個審局函數的策略去驅動演算法，因此自己也要對這遊戲有一定的認知。Alpha-Beta pruning 演算法與Min-Max 演算法概念是類似的，其中的差別是 Alpha-Beta pruning 演算法 有剪枝的概念可以減少搜索時間。這次主要學習了下棋 AI 的基本演算法，對於這塊有更多的認知。