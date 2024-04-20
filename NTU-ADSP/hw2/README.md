# Homework 2 (Due: 4/10)
![](https://img.shields.io/badge/Name-林昕鋭-blue?logo=apple)
![](https://img.shields.io/badge/ID-ntnu41047035S-blue?logo=apple) 

([0328_1-00:00](https://cool.ntu.edu.tw/courses/34012/modules/items/1498479))

1. By main.py (page 106 ~ 116) ([0321_2-32:24](https://cool.ntu.edu.tw/courses/34012/modules/items/1491517))

2. (page 81 ~ 82) ([0328_1-20:13](https://cool.ntu.edu.tw/courses/34012/modules/items/1498479))
    
$$\delta_1 = 0.01$$

$$\delta_2 = 0.01$$

$$f_s = \frac{1}{0.00005} = 20000$$

$Normalized \space Frequency:$

$$\Delta_F = \frac{(f_2-f_1)}{f_s}$$

$$\Delta_F = \frac{(6000 - 5000)}{20000} = 0.05$$

$Calculate \space N:$

$$N = \frac{2}{3}\frac{1}{\Delta_F}\log_{10}{\frac{1}{10\delta_1\delta_2}}$$

$$N = \frac{2}{3}\frac{1}{0.05}\log_{10}{\frac{1}{10 * 0.01 * 0.01}}$$

$$N = \frac{2}{3}\frac{1}{0.05}\log_{10}{\frac{1}{0.001}}$$

$$N = \frac{2}{3}\frac{1}{0.05} * 3$$

$$N = 40$$

3. (page 118) ([0321_3-26:58](https://cool.ntu.edu.tw/courses/34012/modules/items/1491518))
    運算量太大 large computation loading，因為傅立葉轉換的運算複雜度為 $O(N\log{N})$ ，所以當 $N$ 過大時，運算量會變得非常大。

4. (page 90)
    
5.  
    - (a) Hilbert transform $x[n]=1+sin⁡(n)x[n]$:

        $Transform:$

        $$H\{x[n]\}=−cos(n)$$

    - (b) 對應於 $x[n]$ 的解析信號:
        $$x_a[n]=1+sin⁡(n)−jcos⁡(n)$$

6. (page 43) ([0306_3-23:49](https://cool.ntu.edu.tw/courses/34012/modules/items/1475300))
    - (a) Edge Detection, Odd symmetry: $h[n] = -h[-n]$, filters:
        - (ii) the Hilbert transform
        - (iii) the matched filter
        - (iv) the difference

    - (b) Prediction, Even symmetry: $h[n] = h[-n]$, filters:
        - (i) Notch filter
        - (v) Kalman filter
        - (vi) particle filter
        - (vii) the Wiener filter

7.
    - (a) Two main advantages of the minimum phase filter
        - Sability and Causality
        - Reduced filter length 
        - Minimum group delay

    - (b) Two main advantages of the cepstrum
to deal with the multipath problem
        - Deconvolution Ability
        - Echo Identification:
        
8. 
    - (a) Determine the cepstrum of h[n]
    
        $Let$  

        $$H(z) = \frac{1 + z^{-1} - 1.5z^{-2} + z^{-3}}{1 - 0.3z^{-1} - 0.4z^{-2}}$$
        
        the complex cepstrum of $h[n]$ is given by the inverse Z-transform of: 
        
        $$\log(H(z)) = \log\left(\frac{1 + z^{-1} - 1.5z^{-2} + z^{-3}}{1 - 0.3z^{-1} - 0.4z^{-2}}\right)$$

    - (b) Convert the IIR filter into the minimum phase filter

        The given IIR filter can be made minimum phase by ensuring all zeros of  $H(z)$  are inside the unit circle. If $H(z)$ has zeros at $z = z_i$, then the minimum phase filter $H_{min}(z)$ will have zeros at: 

        $$z = \frac{1}{z_i^*} \text{ for } |z_i| > 1$$



9. (Extra Question) (page 118, 75, 76)([0321_3-24:12~26:06](https://cool.ntu.edu.tw/courses/34012/modules/items/1491518))

    1. 
    
    $$10000\frac{400000}{f_s}=399999$$
    $$f = 10000\frac{400000}{399999} = 10000.025$$
    $$10000.025 \leq m \leq 399999$$

    2. 

    $$10000 = m\frac{40000}{400000}$$
    $$m = 100000$$
