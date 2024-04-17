# Homework 2
### [標靶治療](https://www.novelgames.com/zh-HK/targetedtherapy)

- Student ID: 41047035S
- Name: 林昕鋭
- Instructor: 林順喜
- Due: 2023-04-14

## Q1
- Hardware & System
    - Model: MacBook Air (M1, 2020), 16 GB ram
    - System: MacOS (Darwin root:xnu-8020.240.14~1/RELEASE_ARM64_T8101 arm64)
- Language
    - C
- Compiler
    - gcc
    - clang 
> 建議在 unix-like 系統執行

## Q2
測資儲存於 ./data/input/IDS 和 ./data/input/IDASTAR 資料夾中，每以依序為 x.txt 檔名命名，其中有連續為 1 測資與不連續為 1 的隨機測資，每筆測資資料長度逐漸擴增測試，以下為每筆測資內容：

### Testcase for IDS

### 1.txt 
- 1 1 1

### 2.txt
- 1 0 1

### 3.txt
- 1 1 0 1

### 4.txt
- 1 0 0 1 1

### 5.txt
- 0 0 1 0 0 1

### 6.txt
- 1 1 1 1 1 1 1

### 7.txt
- 1 1 1 1 1 1 1 1

### 8.txt
- 0 1 0 1 0 1 0 1

### 9.txt
- 1 0 1 0 1 0 1 0

### 10.txt
- 1 1 1 1 1 1 1 1 1

---
### Testcase for IDA*

### 1.txt 
- 1 1 1

### 2.txt
- 1 1 1 1 1

### 3.txt
- 1 1 1 1 1 1 1 1

### 4.txt
- 1 0 0 1 0 1 1 0

### 5.txt
- 1 1 1 1 1 1 1 1 1

### 6.txt
- 0 1 1 0 1 1 1 0 0 1 1

### 7.txt
- 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1

### 8.txt
- 1 0 0 1 1 1 1 1 0 0 1 0 1 0 0 0 0 1 0 0 0

### 9.txt
- 1 x 60

### 10.txt
- 1 x 32

> 測資皆為手動輸入

## Q3
編譯請下指令：
```
make
```

執行 IDS 程式請下指令：
```
./IDS < data/input/IDS/x.txt > data/output/IDS/x.txt
```

執行 IDA* 程式請下指令：
```
./IDASTAR < data/input/IDASTAR/x.txt > data/output/IDASTAR/x.txt
```

輸出檔案皆儲存於 ./data/output/IDS 和 ./data/output/IDASTAR 資料夾中
> x 為第幾個測資

## Q4
- 方法與技術：IDS 演算法，逐步加深層數，盤面中病毒所在位置即為嘗試的 move ，每一節點皆搜尋直到盤面為空。
- 資料結構：Bitboard 儲存盤面資訊（詳細參見 Q8 ）

可以看見 IDS 演算法在處理長度為 8 連續為 1 的測資明顯速度變慢，但也因使用 Bitboard 能較快速輸出答案，而在多一點的測資將花費更多時間可能無法跑完，以下為跑過每筆測資的詳細資訊：

### 1.txt
- 輸出：2 2 
- 時間：0.000090s
- 耗能：62% cpu 0.004 total

### 2.txt
- 輸出：3 2 
- 時間：0.000034s
- 耗能：51% cpu 0.005 total

### 3.txt：
- 輸出：1 3 2 
- 時間：0.000035s
- 耗能：63% cpu 0.004 total

### 4.txt：
- 輸出：4 4 3 2 
- 時間：0.000045s
- 耗能：64% cpu 0.004 total

### 5.txt：
- 輸出：3 5 
- 時間：0.000053s
- 耗能：64% cpu 0.004 total

### 6.txt：
- 輸出：1.214439s
- 時間：6 5 4 3 2 6 5 4 3 2 
- 耗能：99% cpu 1.218 total

### 7.txt：
- 輸出：7 6 5 4 3 2 2 3 4 5 6 7 
- 時間：266.977208s
- 耗能：99% cpu 4:27.20 total

### 8.txt：
- 輸出：2 3 4 5 6 7 
- 時間：0.000356s
- 耗能：64% cpu 0.005 total

### 9.txt：
- 輸出：7 6 5 4 3 2 
- 時間：0.000133s
- 耗能：56% cpu 0.004 total

### 10.txt：
- 輸出：無法估計
- 時間：無法估計
- 耗能：99% cpu 1:08.61 total

> 耗能計算皆使用 time 指令

## Q5
- 方法與技術：IDA* 演算法，與 Q4 方法相似，加入了 A* 演算法特色，heuristic 函數與 Threshold 形成剪枝減少搜尋節點，大幅提升速度。
- 資料結構：Bitboard 儲存盤面資訊（詳細參見 Q8 ）
- heuristic 函數：(病毒數量 - 頭尾病毒) x 2 - 1

IDA* 演算法比起 IDS 演算法速度快了許多，也可以跑更大長度的測資，經過測試可以跑最大長度為 32 連續為 1 的測資，而 60 長度連續為 1 的測資將花費更多時間可能無法跑完，以下為跑過每筆測資的詳細資訊：

### 1.txt
- 輸出：2 2 
- 時間：0.000033s
- 耗能：63% cpu 0.004 total

### 2.txt：
- 輸出：4 3 2 4 3 2 
- 時間：0.000090s
- 耗能：66% cpu 0.004 total

### 3.txt：
- 輸出：7 6 5 4 3 2 2 3 4 5 6 7 
- 時間：0.000108s
- 耗能：65% cpu 0.004 total

### 4.txt：
- 輸出：7 2 2 3 4 5 6 7 
- 時間：0.000099s
- 耗能：65% cpu 0.004 total

### 5.txt：
- 輸出：8 7 6 5 4 3 2 8 7 6 5 4 3 2 
- 時間：0.000099s
- 耗能：66% cpu 0.004 total

### 6.txt：
- 輸出：10 7 6 5 4 3 2 10 9 8 7 6 5 4 3 2 
- 時間：0.000128s
- 耗能：65% cpu 0.004 total

### 7.txt：
- 輸出：15 14 13 12 11 10 9 8 7 6 5 4 3 2 
- 時間：0.000108s
- 耗能：64% cpu 0.005 total

### 8.txt：
- 輸出：18 9 8 7 6 5 4 3 2 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 
- 時間：0.001998s
- 耗能：77% cpu 0.006 total

### 9.txt：
- 輸出：無法估計
- 時間：無法估計
- 耗能：99% cpu 4.862 total

### 10.txt：
- 輸出：2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 
- 時間：0.007224s
- 耗能：79% cpu 0.013 total

> 耗能計算皆使用 time 指令

## Q6
這次作業主要是要想出處理速度與策略上的想法，IDS搜尋演算法雖然簡單單純，但是以結合了 DFS 與 BFS 近乎將所有可能的結果搜尋過一遍實在是非常花時間，因此我有想說使用 Bitboard 的資料結構來做處理速度必將可以快非常多，也因此在這方面想出方法花了非常多的時間，是較棘手的部分，而 IDA* 演算法加入了一些策略與經驗法則，在理解 IDA* 演算法花比較多時間，但是有範例 Code 與圖表更好理解一些。

## Q7 
- ChatGPT： https://chat.openai.com/chat/
- IDS 介紹：https://www.educative.io/answers/what-is-iterative-deepening-search
- IDA* 範例 Code：https://wuli.wiki/online/IDAs.html
- IDA* 介紹：https://www.geeksforgeeks.org/iterative-deepening-a-algorithm-ida-artificial-intelligence/
- Bit "1" counter：https://stackoverflow.com/questions/8871204/count-number-of-1s-in-binary-representation

## Q8
資料處理利用 Bitboard 技術加快運算速度，處理方式如下：

1.  盤面資訊為 0 1 呈現，而 n < 60 ，因此可以以 uint64_t 來做運算，Ex：0111 儲存為 7

2. 盤面與 move 做 XOR 運算更新盤面

3. 利用迴圈將每一病毒的 mask 值做 OR 運算

> 相關程式碼請參考 update_board() 函式


