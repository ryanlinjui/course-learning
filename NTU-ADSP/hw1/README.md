# Homework 1 (Due: 3/20)
![](https://img.shields.io/badge/Name-林昕鋭-blue?logo=apple)  
![](https://img.shields.io/badge/ID-ntnu41047035S-blue?logo=apple)  
![](https://img.shields.io/badge/Date-2024/03/20-blue?logo=apple)

### 作業說明 ([0306_1-00:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1475298))  

#### 1. By main.py (page 58 ~ 61, 71) ([0313_2-01:38](https://cool.ntu.edu.tw/courses/34012/modules/items/1483742))

#### 2. (page 31) ([0221_3-09:05](https://cool.ntu.edu.tw/courses/34012/modules/items/1452266))

$Let:$
$$h[n] = 0.8^n u[n] + 0.5^n u[n]$$

$Z transform:$ [Link](https://www.wolframalpha.com/input?i=Z-transform+calculator&assumption=%7B%22F%22%2C+%22ZTransformCalculator%22%2C+%22transformfunction%22%7D+-%3E%220.8%5En%2B0.5%5En%22&assumption=%7B%22F%22%2C+%22ZTransformCalculator%22%2C+%22variable1%22%7D+-%3E%22n%22&assumption=%7B%22F%22%2C+%22ZTransformCalculator%22%2C+%22variable2%22%7D+-%3E%22z%22)

$$0.8^n + 0.5^n => \frac{z(20z - 13)}{(2z - 1)(5z - 4)}$$
$$y[z] = x[z]h[z] = x[z](\frac{z(20z - 13)}{(2z - 1)(5z - 4)})$$
$$x[z] = y[z](\frac{(2z - 1)(5z - 4)}{z(20z - 13)})$$
$Inverse Z:$ [Link](https://www.wolframalpha.com/input?i=inverse+Z+transform+calculator&assumption=%7B%22F%22%2C+%22InverseZTransformCalculator%22%2C+%22transformfunction%22%7D+-%3E%22%28z%2820z-13%29%29%2F%28%282z-1%29%285z-4%29%29%22&assumption=%7B%22F%22%2C+%22InverseZTransformCalculator%22%2C+%22variable1%22%7D+-%3E%22z%22&assumption=%7B%22F%22%2C+%22InverseZTransformCalculator%22%2C+%22variable2%22%7D+-%3E%22n%22)

$$x[n] = \frac{5}{4}^{-y[n]} + 2^{-y[n]}$$

####  3. (page 13) ([0221_2-31:12](https://cool.ntu.edu.tw/courses/34012/modules/items/1452265))

##### (a) two main advantages
- (1) spectrum analysis
- (2) convolution -> multiplication

##### (b) two main problems
- (1) not real operation
- (2) irrational number multiplication

#### 4. DFT(FFT) 頻率和m之間的關係 (page 24) ([0306_1-24:08](https://cool.ntu.edu.tw/courses/34012/modules/items/1475298)) 

##### (a)

$$0.002n = 1, n = 500$$
$$\Delta_t = 0.002, f_s = 1 / 0.002 = 500$$
$$\frac{200}{2000} * 500 = 50 Hz$$

##### (b)

$$\frac{1600}{2000} * 500 = 400 Hz$$

#### 5.
##### (a) the step invariance method (page 34)  ([0306_2-43:43](https://cool.ntu.edu.tw/courses/34012/modules/items/1475299))

因為 aliasing effect 的原因主要是頻率範圍超出了 $-\frac{f_s}{2}$ 到 $\frac{f_s}{2}$ 的範圍之外，這個方法利用積分的方式減少了高頻的部分，透過與 step function 做卷積的運算，後轉為積分方式對 $h_a(t)$ 做積分，後再作取樣，造成 aliasing effect 的效果會變比較小，從而避免此情況。

##### (b) the bilinear transform (page 36 ~ 39) ([0306_3-02:46](https://cool.ntu.edu.tw/courses/34012/modules/items/1475300))

此方法透過了一個叫做 mapping function方式，將範圍內(例如： $-\infty < f_c < +\infty$ ) 把他mapping 至 $-\frac{f_s}{2}$ 到 $-\frac{f_s}{2}$ 之間，實際作法透過 $atan$ 的特性 $-\frac{\pi}{2} < atan(x) < \frac{\pi}{2}$ 變成 $-\frac{\pi}{2} < f_{c,1} < \frac{\pi}{2}, f_{c,1} = \frac{f_s}{\pi}atan(\frac{2\pi}{c}f_c)$ ，這樣子可以完全避免 aliasing effect 的情況。

#### 6. (page 43) ([0306_3-23:49](https://cool.ntu.edu.tw/courses/34012/modules/items/1475300))

- Even symmetry: $h[n] = h[-n]$ , filters:
    - (i) Notch filter
    - (ii) highpass filter (page 27)
    - (v) differentiation 4 times
    - (vii) matched filter 
- Odd symmetry: $h[n] = -h[-n]$ , filters:
    - (iii) edge detector
    - (iv) integral
    - (vi) particle filter 

#### 7. MSE
1. Define the desired frequency response $H_d(f)$:

$$|F|<125, H_d(F) = 1$$

$$0.25<|F|<0.5, H_d(F) = 0$$

2. The filter length is 7 points

3. Compute the desired frequency response values at the chosen frequency points according to the specifications given in step 1.

4. Choose an appropriate window function. The most commonly used window functions for FIR filter design are the Hamming window, Hanning window, and Blackman window.

5. Compute the impulse response of the ideal filter using the inverse discrete Fourier transform (IDFT) of the desired frequency response obtained in step 3.

6. pply the chosen window function to the impulse response obtained in step 5 to obtain the final FIR filter coefficients.

7. Normalize the filter coefficients to ensure that the gain of the filter is equal to 1 at DC (zero frequency).


#### 8. (Extra Question, number 0, 5) (page 13) ([0306_2-32:35](https://cool.ntu.edu.tw/courses/34012/modules/items/1475299))

$$ f = m\frac{f_s}{N}$$
$$ -150Hz = m\frac{6000}{30000}$$
$$ m = -750$$
