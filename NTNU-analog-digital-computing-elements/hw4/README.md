# Homework 4
![](https://img.shields.io/badge/Name-林昕鋭-blue?logo=arduino)  
![](https://img.shields.io/badge/ID-41047035S-blue?logo=arduino)

## Problem 1
> by hw4.hdl

## Bonus Task

### (1)
$11001100 - 00000001 = 11001011$

Reverse: $00110100$

Decimal: $52$

Two's complement of $11001100 = -52$

Two's complement of $00011110 = 30$

```math
(11001100)_2 + (00011110)_2 = (-52)_{10} + (30)_{10} = (-22)_{10}
```

### (2)

1. **Two's complement representation**: For any integer $i$, its $n$-bit two's complement representation $\text{code}(i)$ is defined as:
   - If $i \geq 0$:  
     $$\text{code}(i) = i$$
   - If $i < 0$:  
     $$\text{code}(i) = 2^n + i$$
   Here, $2^n + i$ ensures the representation remains non-negative and fits within $n$ bits.

2. **Range of two's complement**:  
   An $n$-bit two's complement can represent integers within the range:  
   $$-2^{n-1} \leq i \leq 2^{n-1} - 1$$

We consider three cases based on the signs of $x$ and $y$.

##### Case 1: $x \geq 0$, $y \geq 0$
1. Since both $x$ and $y$ are non-negative, their two's complement encodings are simply:
   $$\text{code}(x) = x, \quad \text{code}(y) = y$$
2. Their sum $z = x + y$.  
   If $z$ fits in the $n$-bit range (i.e., $z \leq 2^{n-1} - 1$), its encoding is:
   $$\text{code}(z) = z$$
3. Adding their encodings gives:
   $$\text{code}(x) + \text{code}(y) = x + y = z = \text{code}(z)$$

##### Case 2: $x < 0$, $y \geq 0$
1. Since $x$ is negative and $y$ is non-negative, their encodings are:
   $$\text{code}(x) = 2^n + x, \quad \text{code}(y) = y$$
2. Their sum $z = x + y$:
   - If $z \geq 0$, then $\text{code}(z) = z$.
   - If $z < 0$, then $\text{code}(z) = 2^n + z$.
3. Adding their encodings:
   $$\text{code}(x) + \text{code}(y) = (2^n + x) + y = 2^n + (x + y)$$
   - If $z \geq 0$, we can ignore the carry $2^n$ since it wraps around in modular arithmetic:
     $$\text{code}(x) + \text{code}(y) = z = \text{code}(z)$$
   - If $z < 0$, then:
     $$\text{code}(x) + \text{code}(y) = 2^n + z = \text{code}(z)$$

##### Case 3: $x < 0$, $y < 0$
1. Since both $x$ and $y$ are negative, their encodings are:
   $$\text{code}(x) = 2^n + x, \quad \text{code}(y) = 2^n + y$$
2. Their sum $z = x + y$:
   - If $z \geq 0$, then $\text{code}(z) = z$.
   - If $z < 0$, then $\text{code}(z) = 2^n + z$.
3. Adding their encodings:
   $$\text{code}(x) + \text{code}(y) = (2^n + x) + (2^n + y) = 2^{n+1} + (x + y)$$
4. In two's complement arithmetic, the extra carry $2^n$ is discarded (modulo $2^n$), so:
   $$2^{n+1} + (x + y) \mod 2^n = x + y$$
   - If $z \geq 0$, then $\text{code}(z) = z$, and:
     $$\text{code}(x) + \text{code}(y) = z = \text{code}(z)$$
   - If $z < 0$, then $\text{code}(z) = 2^n + z$, and:
     $$\text{code}(x) + \text{code}(y) = 2^n + z = \text{code}(z)$$

Finnally, In all cases, we have shown that if $z = x + y$ fits within the $n$-bit two's complement range, then:
$$\text{code}(z) = \text{code}(x) + \text{code}(y)$$
