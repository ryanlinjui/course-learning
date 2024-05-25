# Homework 4 (Due: 5/29)
![](https://img.shields.io/badge/Name-林昕鋭-blue?logo=apple)
![](https://img.shields.io/badge/ID-ntnu41047035S-blue?logo=apple) 

### 作業說明 ([0515-1-01:47](https://cool.ntu.edu.tw/courses/34012/modules/items/1542980))

#### 1. By main.py (page 338) ([0508-1-21:14](https://cool.ntu.edu.tw/courses/34012/modules/items/1537273))

#### 2.

##### (a) (page 313)

可以根據以下程式碼來求 entropy:

```python
import numpy as np

n_values = np.arange(1, 80001)

# Chinese characters model
P_n = (np.exp(0.002) - 1) * np.exp(-0.002 * n_values)

entropy = np.sum(P_n * np.log2(1 / P_n))

print(entropy)
```

輸出結果 entropy 為 `10.408479566000363`

##### (b) (page 314 ~ 315)

可以根據以下程式碼來求 Huffman code range of the coding length:

```python
import math

N = 10 ** 5
k = 2
entropy = 10.408479566000363

ln_k = math.log(k)
lower_bound = math.ceil(N * entropy / ln_k)
upper_bound = math.floor(N * entropy / ln_k) + N

print((lower_bound, upper_bound))`
```

輸出結果為 `(1501627, 1601626)`

##### (c) (page 326)

可以根據以下程式碼來求 Arithmetic code range of the coding length:

```python
import math

N = 10 ** 5
k = 2
entropy = 10.408479566000363

lower_bound = math.ceil(N * entropy / ln_k)
upper_bound = math.floor(N * entropy / ln_k + math.log(2, k) + 1)

print((lower_bound, upper_bound))
```

輸出結果為 `(1501627, 1501628)`

#### 3. (page 348) ([0508-2-35:41](https://cool.ntu.edu.tw/courses/34012/modules/items/1537279))

$$ exp(j \theta) = c + id$$

$$ exp(j \theta) = \cos(\theta) + j \sin(\theta)$$

$$ x = a + jb$$

$$ x exp(j \theta) = (a + jb)(\cos(\theta) + j \sin(\theta))$$

$$ = a \cos(\theta) - jb \sin(\theta) + j b \cos(\theta) + a \sin(\theta)$$

$$
\begin{bmatrix}
c \\
d 
\end{bmatrix} = 
\begin{bmatrix}
\cos \theta & -\sin \theta \\
\sin \theta & \cos \theta 
\end{bmatrix}
\begin{bmatrix}
a \\
b
\end{bmatrix}
$$

- 當 $\theta = \frac{\pi}{4}$ 或 $\theta = \frac{5\pi}{4}$ 時， $\cos(\theta) = \sin(\theta) = \frac{1}{\sqrt{2}}$ 或 $-\frac{1}{\sqrt{2}}$ 。此時可以重組為:
   
   $$c = a \cos(\theta) - b \sin(\theta) = \frac{a - b}{\sqrt{2}}$$
  
   $$d = b \cos(\theta) + a \sin(\theta) = \frac{b + a}{\sqrt{2}}$$
   
   得出需要計算 $a-b$ 和 $a+b$ 兩個實數乘法，再乘以 $\frac{1}{\sqrt{2}}$ 。

- 當 $\theta = \frac{3\pi}{4}$ 或 $\theta = \frac{7\pi}{4}$ 時， $\cos(\theta) = -\sin(\theta) = -\frac{1}{\sqrt{2}}$ 或 $\frac{1}{\sqrt{2}}$ 。此時可以重組為:
   
   $$c = a \cos(\theta) - b \sin(\theta) = \frac{a + b}{\sqrt{2}}$$

   $$d = b \cos(\theta) + a \sin(\theta) = \frac{-a + b}{\sqrt{2}}$$
   
   得出只需要計算 $a+b$ 和 $-a+b$ 兩個實數乘法。

#### 4. (page 293, 358) ([0515-1-18:07](https://cool.ntu.edu.tw/courses/34012/modules/items/1542980))

三維 DFT 的複雜度對於一個 $M \times N \times P$ 的 volume 可以透過每個維度獨立進行 DFT 所需的操作，然後把這些操作總和得到總複雜度來推導:

- 一維 DFT 的複雜度:
    - 對長度為 $n$ 的一維序列進行 DFT 的複雜度是 $O(n \log n)$.

- 將所有維度 apply 一維 DFT:
   - $M$ 維: 每一維 DFT 被 apply $N \times P$ 次 (對其他兩個維度的每種組合)。
   - $N$ 維: 每一維 DFT 被 apply $M \times P$ 次。
   - $P$ 維: 每一維 DFT 被 apply $M \times N$ 次。

- 總複雜度: 三維 DFT 的總複雜度是每個維度複雜度的總和

依據 $M$ 維度對所有 $N$ 和 $P$ 的組合進行 DFT:

$$M \log M \times N \times P = MNP \log M$$

依據 $N$ 維度對所有 $M$ 和 $P$ 的組合進行 DFT:

$$N \log N \times M \times P = MNP \log N$$

依據 $P$ 維度對所有 $M$ 和 $N$ 的組合進行 DFT:

$$P \log P \times M \times N = MNP \log P$$

根據以上，三維 DFT 的總複雜度為:

$$O(MNP \log M + MNP \log N + MNP \log P)$$

$$= O(MNP (\log M + \log N + \log P))$$

$$= O(MNP \log (MNP))$$

#### 5. (page 346 ~ 352) ([0508-2-12:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1537279))

可以將矩陣拆成兩個 2x2 的子矩陣 $A$ 和 $B$:

$$
A = \begin{bmatrix}
a & b \\
b & a
\end{bmatrix}
$$

$$
B = \begin{bmatrix}
b & a \\
-a & -b
\end{bmatrix}
$$

將輸入向量 $x$ 分成兩部分:

$$
\begin{bmatrix}
x[1] \\
x[4]
\end{bmatrix}
$$

和

$$
\begin{bmatrix}
x[2] \\
x[3]
\end{bmatrix}
$$

分別計算兩個子矩陣與相應部分的乘積:

- 計算 $A$ 與 $x[1]$ 和 $x[4]$ 的乘積 (Case 3, MUL2):

$$
\begin{bmatrix}
a & b \\
b & a
\end{bmatrix}
\begin{bmatrix}
x[1] \\
x[4]
\end{bmatrix} =
\begin{bmatrix}
a \cdot x[1] + b \cdot x[4] \\
b \cdot x[1] + a \cdot x[4]
\end{bmatrix} =
\begin{bmatrix}
y_1 \\
y_2
\end{bmatrix}
$$

- 計算 $B$ 與 $x[2]$ 和 $x[3]$ 的乘積 (Case 3, MUL2):

$$
\begin{bmatrix}
b & a \\
-a & -b
\end{bmatrix}
\begin{bmatrix}
x[2] \\
x[3]
\end{bmatrix} =
\begin{bmatrix}
b \cdot x[2] + a \cdot x[3] \\
-a \cdot x[2] - b \cdot x[3]
\end{bmatrix} =
\begin{bmatrix}
y_3 \\
y_4
\end{bmatrix}
$$

將兩部分的結果合併成最終的 DST-I 變換結果:

$$
X = \begin{bmatrix}
y_1 \\
y_2 \\
y_3 \\
y_4
\end{bmatrix}
$$

$$
X[1] = a \cdot x[1] + b \cdot x[4]
$$

$$
X[2] = b \cdot x[1] + a \cdot x[4]
$$

$$
X[3] = b \cdot x[2] + a \cdot x[3]
$$

$$
X[4] = -a \cdot x[2] - b \cdot x[3]
$$

因此 $2MUL + 2MUL = 4MUL$ 共需要 4 個乘法。

#### 6. (page 371 ~ 373, 384, 387) ([0512-2-53:36](https://cool.ntu.edu.tw/courses/34012/modules/items/1542975))

##### (a)

$$MUL_{143}$$

$$= 11 MUL_{13} + 13 MUL_{11}$$

$$= 11 \times 52 + 13 \times 40$$

$$= 1092$$

##### (b)

$$MUL_{195}$$

$$= 13 MUL_{15} + 15 MUL_{13}$$

$$= 13 \times 40 + 15 \times 52$$

$$= 1300$$

##### (c)

$$MUL_{196}$$

$$= 14 MUL_{14} + 14 MUL_{14} + 3 \times (14 - 1)(14 - 1)$$

$$= 2 \times 14 \times 32 + 3 \times 13 \times 13$$

$$= 1403$$

#### 7. (NTT all page) ([0522-1-00:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1548711))

##### (a)

選擇一個本原根 $\alpha$ ，對於 $M = 11$ 的本原根，可以找到 $\alpha = 2$ 。

建構 5 點 NTT 的前向變換矩陣，前向 NTT 的矩陣 $W$ 的元素定義如下:

$$ W_{jk} = \alpha^{jk} \mod M $$

其中 $j$ 和 $k$ 是矩陣從 0 到 4 的行和列的 index。

讓 $\alpha = 2$ 且 $M = 11$，可以計算:

$$
W = \begin{bmatrix}
\alpha^{0 \cdot 0} & \alpha^{0 \cdot 1} & \alpha^{0 \cdot 2} & \alpha^{0 \cdot 3} & \alpha^{0 \cdot 4} \\
\alpha^{1 \cdot 0} & \alpha^{1 \cdot 1} & \alpha^{1 \cdot 2} & \alpha^{1 \cdot 3} & \alpha^{1 \cdot 4} \\
\alpha^{2 \cdot 0} & \alpha^{2 \cdot 1} & \alpha^{2 \cdot 2} & \alpha^{2 \cdot 3} & \alpha^{2 \cdot 4} \\
\alpha^{3 \cdot 0} & \alpha^{3 \cdot 1} & \alpha^{3 \cdot 2} & \alpha^{3 \cdot 3} & \alpha^{3 \cdot 4} \\
\alpha^{4 \cdot 0} & \alpha^{4 \cdot 1} & \alpha^{4 \cdot 2} & \alpha^{4 \cdot 3} & \alpha^{4 \cdot 4}
\end{bmatrix} \mod 11
$$

結果如下:

$$
W = \begin{bmatrix}
1 & 1 & 1 & 1 & 1 \\
1 & 2 & 4 & 8 & 5 \\
1 & 4 & 5 & 9 & 3 \\
1 & 8 & 9 & 6 & 4 \\
1 & 5 & 3 & 4 & 9
\end{bmatrix}
$$

##### (b)

逆向 NTT 的矩陣 $W^{-1}$ 的元素定義如下:

$$ W^{-1}_{jk} = \alpha^{-jk} \mod M $$

需要計算 $\alpha^{-1} \mod 11$，根據費馬小定理:

$$ \alpha^{-1} \equiv \alpha^{M-2} \mod M $$

所以 $2^{-1} \mod 11 = 2^{9} \mod 11$。

計算結果如下:

$$ 2^9 \mod 11 = 6 $$

因此逆變換矩陣的元素 $W^{-1}_{jk}$ 可以計算如下:

$$
W^{-1} = \begin{bmatrix}
\alpha^{-0 \cdot 0} & \alpha^{-0 \cdot 1} & \alpha^{-0 \cdot 2} & \alpha^{-0 \cdot 3} & \alpha^{-0 \cdot 4} \\
\alpha^{-1 \cdot 0} & \alpha^{-1 \cdot 1} & \alpha^{-1 \cdot 2} & \alpha^{-1 \cdot 3} & \alpha^{-1 \cdot 4} \\
\alpha^{-2 \cdot 0} & \alpha^{-2 \cdot 1} & \alpha^{-2 \cdot 2} & \alpha^{-2 \cdot 3} & \alpha^{-2 \cdot 4} \\
\alpha^{-3 \cdot 0} & \alpha^{-3 \cdot 1} & \alpha^{-3 \cdot 2} & \alpha^{-3 \cdot 3} & \alpha^{-3 \cdot 4} \\
\alpha^{-4 \cdot 0} & \alpha^{-4 \cdot 1} & \alpha^{-4 \cdot 2} & \alpha^{-4 \cdot 3} & \alpha^{-4 \cdot 4}
\end{bmatrix} \mod 11
$$

代入 $\alpha^{-1} = 6$ 計算結果如下:

$$
W^{-1} = \begin{bmatrix}
1 & 1 & 1 & 1 & 1 \\
1 & 6 & 3 & 7 & 5 \\
1 & 3 & 9 & 10 & 4 \\
1 & 7 & 10 & 5 & 2 \\
1 & 5 & 4 & 2 & 8
\end{bmatrix}
$$

#### 8. (Extra Question, number 0, 5) (page ) ([0515-2-01:02:35](https://cool.ntu.edu.tw/courses/34012/modules/items/1542975))

$$MUL_{400}$$

$$= 20 MUL_{20} + 20 MUL_{20} + 3 \times (20 - 1)(20 - 1)$$

$$= 2 \times 20 \times 40 + 3 \times 19 \times 19$$

$$= 2683$$
