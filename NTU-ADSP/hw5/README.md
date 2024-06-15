# Homework 5 (Due: 6/19)
![](https://img.shields.io/badge/Name-林昕鋭-blue?logo=apple)
![](https://img.shields.io/badge/ID-ntnu41047035S-blue?logo=apple) 

### 作業說明 ([0605-1-05:31](https://cool.ntu.edu.tw/courses/34012/modules/items/1558447))

#### 1. By main.py (page 451) ([0529-3-27:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1554405))

#### 2. (page 371, 433 ~ 447) ([0529-2-00:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1554407))

##### (a)

- (i) sectioned convolution ($30 < 1200$)
- (ii) $2048 (\because 2^{11} = 2048 > 1200+300−1 = 1499)$
- (iii) $O(2048 \log{2048})$

##### (b)

- (i) non-sectioned convolution ($30 << 1200$)
- (ii) $1501 = 1200 + 300 − 1$
- (iii) $3760 = 2 \times \frac{1200}{30} \times 80 + 3 \times \frac{1200}{30}\times 30$

##### (c)

- (i) direct (M is a very small integer)
- (ii) no needed by direct
- (iii) $1200 \times 8 = 9600$

##### (d)

- (i) direct (M is a very small integer)
- (ii) no needed by direct
- (iii) $1200 \times 2 = 2400$

#### 3.

##### (a) (page 466, 470, 472) ([0605-2-09:49](https://cool.ntu.edu.tw/courses/34012/modules/items/1558446))

- Number of entries equal to 1:
k=2 -> 3
k=4 -> 10
k=8 -> 36

$$\frac{k(k+1)}{2}$$

- Number of entries equal to -1:
k=2 -> 1
k=4 -> 6
k=8 -> 28

$$\frac{k(k-1)}{2}$$

##### (b) (page 487 ~ 488) ([0605-2-50:38](https://cool.ntu.edu.tw/courses/34012/modules/items/1558446))

- Number of entries equal to 1:
    
    > By [Recurrence Equation Solution Webpage](https://www.wolframalpha.com/input?i=T%5Bn%5D%3D%3D2*T%5Bn%2F2%5D%2Bn%2F2)

    k=2 -> 3
    k=4 -> 8
    k=8 -> 20
    k=16 -> 48

    $$T(k) = 2 \times T\left(\frac{k}{2}\right) + \frac{k}{2}$$

    $$\Rightarrow k + \frac{k}{2} \log_2{k}$$

- Number of entries equal to -1:
    
    k=2 -> 1
    k=4 -> 4
    k=8 -> 12
    k=16 -> 32

    $$k(\log_4{k})$$

- Number of entries equal to 0:
    > Calculate by subtracting the number of entries equal to 1 and -1 from the total number of entries.

    k=2 -> 0
    k=4 -> 4
    k=8 -> 32
    k=16 -> 176

$$k^2 - (k + \frac{k}{2} \log_2{k}) - k(\log_4{k})$$

##### (c) (page 485) ([0605-2-48:51](https://cool.ntu.edu.tw/courses/34012/modules/items/1558446))

CDMA (code division multiple access)
- Using the basis (rows) of the Walsh transform to perform modulation.
- Modulation: Using some man-made waveform to represent a data. 

##### (d) (page 490) ([0605-3-01:01](https://cool.ntu.edu.tw/courses/34012/modules/items/1558445))

1. Fast (but this advantage is no longer important)

2. Analysis of the local high frequency component (Edges of different locations and scales) (The wavelet transform is a generalization of the Haar transform)

3. Extracting local features (Example: Adaboost face detection)

#### 4. (page 466 ~ 473, 514 ~ 522) ([0605-3-23:46](https://cool.ntu.edu.tw/courses/34012/modules/items/1558445))

##### (a)

> By [Matrix Addition Webpage](https://www.wolframalpha.com/input?i=matrix+addition)

Walsh 碼第一個 row:

$$[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]$$

將 0 變為 -1:

$$[1, 0, 1] \Rightarrow [1, -1, 1]$$

$[1, -1, -1]$ modulate by 第一個 row:

$$[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,$$

$$-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,$$

$$1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]$$

Walsh 碼第四個 row:

$$[1, 1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1]$$

將 0 變為 -1:

$$[1, 1, 0] \Rightarrow [1, 1, -1]$$

$[1, 1, -1]$ modulate by 第四個 row:

$$[1, 1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1,$$

$$1, 1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1,$$

$$-1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1]$$

Walsh 碼第十個 row:

$$[1, -1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1, 1]$$

將 0 變為 -1:

$$[0, 1, 1] \Rightarrow [-1, 1, 1]$$

$[-1, 1, 1]$ modulate by 第十個 row:

$$[-1, 1, -1, 1, -1, 1, -1, 1, 1, -1, 1, -1, 1, -1, 1, -1,$$

$$1, -1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1, 1,$$

$$1, -1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1, 1]$$

以上相加得到:

$$[1, 3, 1, 3, -1, 1, -1, 1, 3, 1, 3, 1, 1, -1, 1, -1,$$

$$1, -1, 1, -1, -1, -3, -1, -3, -1, 1, -1, 1, -3, -1, -3, -1,$$

$$1, -1, 1, -1, 3, 1, 3, 1, -1, 1, -1, 1, 1, 3, 1, 3]$$

##### (b)

依據 (a) 結果，分割成三個 Walsh 碼:

$$y_1 = [1, 3, 1, 3, -1, 1, -1, 1, 3, 1, 3, 1, 1, -1, 1, -1]$$

$$y_2 = [1, -1, 1, -1, -1, -3, -1, -3, -1, 1, -1, 1, -3, -1, -3, -1]$$

$$y_3 = [1, -1, 1, -1, 3, 1, 3, 1, -1, 1, -1, 1, 1, 3, 1, 3]$$

使用 Inner Product 來 recover 原始資料:

$$<x, y> = \sum x_i \cdot y_i$$

Recovers 第一個 Original data:

$$\frac{<y_1,1^{st}>}{16} = \frac{16}{16} > 0 \Rightarrow 1$$

$$\frac{<y_2,1^{st}>}{16} = \frac{-16}{16} < 0 \Rightarrow -1$$

$$\frac{<y_3,1^{st}>}{16} = \frac{16}{16} > 0 \Rightarrow 1$$

$$[1, -1, 1] \Rightarrow [1, 0, 1]$$

Recovers 第二個 Original data:

$$\frac{<y_1,4^{th}>}{16} = \frac{16}{16} > 0 \Rightarrow 1$$

$$\frac{<y_2,4^{th}>}{16} = \frac{16}{16} > 0 \Rightarrow 1$$

$$\frac{<y_3,4^{th}>}{16} = \frac{-16}{16} < 0 \Rightarrow -1$$

$$[1, 1, -1] \Rightarrow [1, 1, 0]$$

Recovers 第三個 Original data:

$$\frac{<y_1,10^{th}>}{16}= \frac{-16}{16} < 0 \Rightarrow -1$$

$$\frac{<y_2,10^{th}>}{16} = \frac{16}{16} > 0 \Rightarrow 1$$

$$\frac{<y_3,10^{th}>}{16} = \frac{16}{16} > 0 \Rightarrow 1$$

$$[-1, 1, 1] \Rightarrow [0, 1, 1]$$

So that, we can recover the original data.

#### 5. (NTT all page) ([0522-1-00:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1548711))

計算 $\alpha^k \mod 11$，其中:

$$\alpha = 8 + 6i, k = 0, 1, 2, \ldots, 11$$

計算前幾個次冪:

$$\alpha^0 = 1$$

$$\alpha^1 = 8 + 6i$$

計算 $\alpha^2$:

$$\alpha^2 = (8 + 6i)^2 = 64 + 96i - 36 = 28 + 96i \equiv 28 + 96i \mod 11$$

$$28 \mod 11 = 6$$

$$96 \mod 11 = 8$$

$$\alpha^2 \equiv 6 + 8i$$

計算 $\alpha^3$:

$$\alpha^3 = (8 + 6i) \cdot (6 + 8i)$$

$$\alpha^3 = 8 \cdot 6 + 8 \cdot 8i + 6i \cdot 6 + 6i \cdot 8i = 48 + 64i + 36i - 48 = 48 + 100i \equiv 48 + 100i \mod 11$$

$$48 \mod 11 = 4$$

$$100 \mod 11 = 1$$

$$\alpha^3 \equiv 4 + i$$

計算到 $\alpha^{11}$ 得出:
$$\alpha^0 \equiv 1$$

$$\alpha^1 \equiv 8 + 6i$$

$$\alpha^2 \equiv 6 + 8i$$

$$\alpha^3 \equiv 4 + i$$

$$\alpha^4 \equiv (4 + i) \cdot (8 + 6i)$$

$$\ldots$$

$$\alpha^{11} \equiv -1$$

計算 $CNT_k$

$$CNT_k = \sum_{j=0}^{N-1} x_j \cdot (\alpha^k)^j \mod M$$

$$x = [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1]$$

計算每個 $k$ 的 CNT 值，對於每個 $k$ ，將 $x$ 的每個元素乘以對應的 $\alpha^k$ 的次冪，對所有結果求和:

$$CNT_0 = x_0 \cdot \alpha^0 + x_1 \cdot \alpha^0 + x_2 \cdot \alpha^0 + \ldots + x_{11} \cdot \alpha^0 \mod 11$$

$$CNT_0 = 0 \cdot 1 + 1 \cdot 1 + 0 \cdot 1 + \ldots + 1 \cdot 1 \mod 11$$

$$CNT_0 = 4 \mod 11 = 4$$

$$CNT_1 = x_0 \cdot \alpha^1 + x_1 \cdot \alpha^1 + x_2 \cdot \alpha^1 + \ldots + x_{11} \cdot \alpha^1 \mod 11$$

$$CNT_1 = 0 \cdot (8 + 6i) + 1 \cdot (8 + 6i) + 0 \cdot (8 + 6i) + \ldots + 1 \cdot (8 + 6i) \mod 11$$
    
$$CNT_1 = (8 + 6i) + (8 + 6i) + (8 + 6i) + (8 + 6i) \mod 11$$

簡化後，虛部和實部分別模 11，繼續計算到 $CNT_{11}$ 最後得出:

$$CNT = [4, 0, 2, 0, -2, 0, -4, 0, -2, 0, 2, 0]$$

#### 6. (NTT all page) ([0522-1-00:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1548711))

##### (a)

費馬小定理:

如果 $p$ 是質數且 $a$ 是任意整數且 $a$ 不是 $p$ 的倍數: 

$$a^{p-1} \equiv 1 \mod p$$

將 2049 分解成:

$$2049 = 102 \times 20 + 9$$

$$3^{102} \equiv 1 \mod 103$$

$$3^{2049} = 3^{102 \times 20 + 9} = (3^{102})^{20} \times 3^9$$

$$(3^{102})^{20} \equiv 1^{20} \equiv 1 \mod 103$$

$$3^{2049} \equiv 3^9 \mod 103$$

所以只需要計算 $3^9 \mod 103$ :

$$3^9 = 19683$$

$$19683 \mod 103 = 10$$

因此:

$$3^{2049} \mod 103 = 10$$

##### (b)

因為 43 與 67 互質，分開處理，先得出 $a$:

$$a \mod 43 = 0$$

$$a \mod 67 = 13$$

$$(43 \times 53) \mod 67 = 1$$

$$43 \times 13 \times 53 = 29627$$

得出 $b$:

$$b \mod 43 = 2$$

$$b \mod 67 = 0$$

$$(67 \times 9) \mod 43 = 1$$

$$67 \times 2 \times 9 = 1206$$

所以:

$$x = a + b = 29627 + 1206 = 30833$$
$$x \mod 2881 = 2023$$

##### (c)

Wilson’s Theorem:

對於一個質數 $p$ :

$$(p-1)! \equiv -1 \mod p$$

根據題目中 $p = 43$ :

$$42! \equiv -1 \mod 43$$

$$42! \equiv 42 \times 41 \times 40 \times 39! \mod 43$$

$$42 \equiv -1 \mod 43$$

$$41 \equiv -2 \mod 43$$

$$40 \equiv -3 \mod 43$$

$$42! \equiv (-1) \times (-2) \times (-3) \times 39! \mod 43$$

$$-1 \equiv (-1) \times (-2) \times (-3) \times 39! \mod 43$$

$$-1 \equiv (-6) \times 39! \mod 43$$

因為 $37\equiv -6 \mod 43$，得出:

$$-1 \equiv 37 \times 39! \mod 43$$

Extended Euclidean algorithm:

$$43 = 37 \times 1 + 6$$

$$37 = 6 \times 6 + 1$$

$$6 = 6 \times 1 + 0$$

$$1 = 37 - 6 \times 6$$

$$1 = 37 - 6 \times (43 - 37)$$

$$1 = 37 \times 7 - 43 \times 1$$

因此從原式得出:

$$37^{-1} \equiv 7 \mod 43$$

$$-1 \equiv 37 \times 39! \mod 43$$

$$39! \equiv (-1) \times 37^{-1} \mod 43$$

$$39! \equiv -7 \mod 43$$

$$39! \equiv 36 \mod 43$$

所以:

$$39! \mod 43 = 36$$

#### 7. (Extra Question, number 0, 5)
> None