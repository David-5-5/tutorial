# Fundamental Algorithms
[TOC]

## 1.基本概念
 
### 1.1 算法

### 1.2 数学准备

### 1.2.5 排列与阶乘

10！ = 3-628-800 

在一定意义下，计算是否可行大致以此为界。

n! 与数学中的其他量有什么关系。能否判断1000！究竟有多大？詹姆斯.斯特林找到了这个问题的答案：

$$
n! \approx \sqrt{2\pi n} \Big( \frac{n}{e} \Big) ^n
$$

误差约为 1/(12n)

n! 分解为素因子的准确值。素数 p 是 n！ 的因子，重数为
```math
\mu = \lceil \frac{n}{p} \rceil + \lceil \frac{n}{p^2} \rceil + \lceil \frac{n}{p^3} \rceil + ...  = \sum_{k>0}\lceil \frac{n}{p^k} \rceil
```

例如，如果 n = 1000, p = 3, 那么

$$
\mu = \lceil \frac{1000}{3} \rceil + \lceil \frac{1000}{9} \rceil + \lceil \frac{1000}{27} \rceil + \lceil \frac{1000}{81} \rceil + \lceil \frac{1000}{243} \rceil + \lceil \frac{1000}{729} \rceil \\
= 333 + 111 + 37 + 12 + 4 + 1= 498
$$

所以1000！ 能被 $3^{498}$ 整除，但不能被  $3^{499}$  整除

斯特林试图把 n! 推广到非整数 n， 差不多在同一时期，欧拉思考了同一问题，率先找到了正确的推广：

$$
n! = \lim_{x\to\infty} \frac{m^nm!}{(n+1)(n+2)\cdots(n+m)}
$$

然而，当 n 不是整数时，通常不用记号 n!， 改用勒让德提出的记号：
```math
n! = \Gamma(n+1) = n\Gamma(n)
```

后面太难了，o(╥﹏╥)o ，略过........


### 1.2.6 二项式系数

从 n 个对象中选取 k 个进行排列，有 $n(n-1)\dots(n-k-1)$ 种方法，其中每个 k 元组合在这些排列中恰好出现 k！ 次。用$` \binom{n}{k} `$ 表示组合数。

$$
\binom{n}{k} = \frac{n(n-1)\cdots(n-k-1)}{k(k-1)\cdots1}   \qquad \qquad (2)
$$

分子 $n(n-1)\cdots(n-k-1)$ 表示从 n 个对象中选取 k 个进行排列的数量
分子 $k(k-1)\cdots1$ 表示每个 k 元组合在这些排列中恰好出现 k! 次

对于所有实数 r 和所有整数 k ，我们定义符号 $\binom{r}{k}$

$$
\binom{r}{k} = \frac{r(r-1)\cdots(r-k-1)}{k(k-1)\cdots1} = \frac{r^{\underline{k}}}{k!} = \prod_{j=1}^k \frac{r+1-j}{j}, k \geq 0  \\
 \binom{r}{k} = 0, k < 0 \qquad \qquad (3)
$$


二项式系数历史悠久：
- 1653年，出现在帕斯卡的算术三角论中，称为帕斯卡三角
- 1303年，元代数学家朱世杰
- 1261年，杨辉把它归为贾宪的发现，称为杨辉三角
- 850年，印度数学家马哈维拉解释 $`\binom{n}{k}`$ 的计算规则


#### A. 用阶乘表示二项式系数

$$
\binom{n}{k} = \frac{n!}{k!(n-k)!} , \qquad n \geq 0 , k \geq 0 \qquad \qquad (5)
$$

#### B. 对称性条件

$$
\binom{n}{k} = \binom{n}{n-k} \qquad \qquad (6)
$$

#### C. 移进括号和移出括号

$$
\binom{r}{k} = \frac{r}{k}\binom{r-1}{k-1}, k \neq 0 \qquad \qquad (7)
$$

这个公式非常有用，可以用来把一个表达式中的二项式系数同其他部分结合起来，通过初等变换，得到规则：

$$
k\binom{r}{k} = r\binom{r-1}{k-1}, \frac{1}{r}\binom{r}{k} = \frac{1}{k}\binom{r-1}{k-1} 
$$

第一条规则对于所有整数 k 成立，第二条规则当除数不为0时成立，还有一个类似的关系式：

$$
\binom{r}{k} = \frac{r}{r-k}\binom{r-1}{k} , r \neq k \qquad \qquad (8)
$$

#### D. 加法公式

$$
\binom{r}{k} = \binom{r-1}{k} + \binom{r-1}{k-1} , k \in Z \qquad \qquad (9)
$$

根据等式 (3) ，很容易证明上式是普遍成立的。等式 (7) (8)

$$
r \binom{r-1}{k} + r\binom{r-1}{k-1} = (r-k)\binom{r}{k} + k \binom{r}{k} = r \binom{r}{k}
$$

#### E. 求和公式

$$
\binom{r}{k} = \binom{r-1}{k} + \binom{r-1}{k-1} = \binom{r-1}{k} + \binom{r-2}{k-1} + \binom{r-2}{k-2} = \cdots
$$
及
$$
\binom{r}{k} = \binom{r-1}{k-1} + \binom{r-1}{k} = \binom{r-1}{k-1}  + \binom{r-2}{k-1} + \binom{r-2}{k} = \cdots
$$

于是导出了两个重要的求和公式：
```math
\sum_{k=0}^{n}\binom{r+k}{k} = \binom{r}{0} + \binom{r+1}{1}  + \cdots + \binom{r+n}{n} = \binom{r+n+1}{n}  \qquad (10) 
```
和
```math
\sum_{k=0}^{n}\binom{k}{m} = \binom{0}{m} + \binom{1}{m} + \cdots + \binom{n}{m} = \binom{n+1}{m+1} \qquad (11)
```

等式(11) 的应用非常频繁。事实上，当 m=1 时，就是等差数列之和：

$$
\binom{0}{1} + \binom{1}{1} + \cdots + \binom{n}{1} = \binom{n+1}{2}  = \frac{(n+1)n}{2} \qquad (12)
$$


#### F. 二项式定理
```math
(x+y)^r = \sum_k \binom{r}{k} x^ky^{r-k} , 整数 r\geq 0 \qquad (13)      
```
在等式中用的是 $`\sum_k`$ 而不是 $`\sum_{k=0}^r`$，如果对 k 不加限制，我们是对所有整数 k 求和。等式(13)给出了 $`0^0 = 1 \qquad (14)`$。我们将采用这个约定。

在等式(13)中 y=1 的特例很重要，特别给出
```math
\sum_k \binom{r}{k} x^k  = (1+x)^r, 整数 r\geq 0 或 |x| < 0 \qquad (15)      
```

二项式定理是牛顿1676年发现的，但是没有给出证明。欧拉在1774年首次试图证明，不过他的证明并不完整。最后高斯于1812年首次给出了真正的证明。尼尔斯.阿尔贝发现了二项式等式(13)的一个推广：
```math
(x+y)^n = \sum_k \binom{n}{k} x(x-kz)^{k-1}(y+kz)^{n-k}  , 整数 n\geq 0, x \neq 0 \qquad (16)
```
这是三个变量 x, y, z 的恒等式。


#### G. 上标取反
由定义(3)，对分子的每一项加负号，直接推出基本恒等式
```math
\binom{r}{k} = (-1)^k \binom{k - r -1}{k}, k \in Z \qquad (17)
```
这对上标取相反数的变换经常很有用，等式(17)的一个简单推论是求和公式
```math
\sum_{k \leq n}\binom{r}{k}(-1)^k = \binom{r}{0} - \binom{r}{1} +  \cdots + (-1)^n\binom{r}{n} = (-1)^n\binom{r-1}{n}, n \in Z \qquad (18)
```
等式(18)可以利用等式(9)用归纳法证明，也可以直接利用等式(17)和(10)证明。
等式(17)中令 r 取整数可获得另外一个重要的应用：
```math
\binom{n}{m} = (-1)^{n-m} \binom{-(m+1)}{n-m}, n \geq 0, m \in Z \qquad (19)
```
等式(17), 令 r = n，k = n - m，利用等式(6),把 n 从上标的位置移到下标的位置。


#### H. 简化乘积
当出现二项式系数的乘积时，通常可以利用等式(5)把它们展成阶乘再写回二项式系数，从而用多种方式重新表示它们。例如
```math
\binom{r}{m}\binom{m}{k} = \binom{r}{k} \binom{r-k}{m-k}, n \in Z, k \in Z \qquad (20)
```
等式(7)是等式(20)在 k=1 时的特例。当 $`r \geq m`$ 的整数时，等式(8)足以证明等式(20)成立；当 $`0 \leq k \leq m`$ 时也可以，于是有：
```math
\binom{r}{m}\binom{m}{k} = \frac{r!m!}{m!(r-m)!k!(m-k)!} = \frac{r!(r-k)!}{k!(r-k)!(m-k)!(r-m)!} = \binom{r}{k} \binom{r-k}{m-k}
```


#### I. 乘积之和
下面列出几个常见的恒等式，如何对两个二项式系数的乘积求和，其中操作变量 k 分别出现在各种不同的位置。

```math
\sum_k \binom{r}{k}\binom{s}{n-k} = \binom{r+s}{n} , n \in Z \qquad (21)
```
```math
\sum_k \binom{r}{m+k}\binom{s}{n+k} = \binom{r+s}{r-m+n} ,   m,n,r \in Z \geq 0 \qquad (22)
```
```math
\sum_k \binom{r}{k}\binom{s+k}{n}(-1)^{r-k} = \binom{s}{n-r} , n,r \in Z \qquad (23)
```
```math
\sum_{k=0}^r \binom{r-k}{m}\binom{s}{k-t}(-1)^{k-t} = \binom{r-t-s}{r-t-m} , t,r,m \in Z \geq 0 \qquad (24) 
```
```math
\sum_{k=0}^r \binom{r-k}{m}\binom{s+k}{n} = \binom{r+s+1}{m+n+1} , n,s,m,r \in Z  \geq 0 \qquad (25) 
```
```math
\sum_{k\geq 0} \binom{r-tk}{k}\binom{s-t(n-k)}{n-k}\frac{r}{r-tk} = \binom{r+s-tn}{n} , n \in Z \qquad (26) 
```
在这些恒等式中，等式(21)是迄今为止最重要的一个，通常成为范德蒙德恒等式。范德蒙德1772年发表，然而这个恒等式早已出现在1303年朱世杰的专著中。

在等式(26)中，如果 r=tk，可以消去分子中的一个因式，从而避免 0 作分母。所以等式(26)是关于变量 r,s,t 的多项式恒等式。显然等式(21)是等式(26)取 t=0 的一个特例。

等式(23)和等式(25)有一种不是一目了然的用法：用左端更复杂的表达式代替右端简单的二项式系数，交换求和的顺序，再进行简化。我们可以把两式左端视为
```math
\binom{s}{n+a} 用 \binom{s+k}{n} 
```
表示的表达式。等式(23)用于取值为负的a，等式(25)用于取值为正的a。


__例4 证明__
```math
\sum A_k(r,t)A_{n-k}(s,t) = A_n(r+s,t), n \in Z, n\geq 0 \qquad (30) 
```
其中 $`A_n(x,t)`$ 是x的n次多项式，满足
```math
A_n(x,t) = \binom{x-nt}{n}\frac{x}{x-nt}, x\neq nt
```
__解__ 
假定 $`0 \leq k \leq n`$ 时，有 $`r \neq kt \neq s`$，我们求解的问题为：
```math
\sum_k \binom{r-kt}{k} \binom{s-(n-k)t}{k}\frac{r}{r-kt}\frac{s}{s-(n-k)t}
```
我们有
```math
\frac{r}{r-kt}\frac{s}{s-(n-k)t} = \frac{1}{r+s-nt}(\frac{1}{r-kt}+\frac{1}{s-(n-k)t})
```
待人需要求解的式子得到
```math
\frac{s}{r+s-nt} \sum_k \binom{r-kt}{k} \binom{s-(n-k)t}{k} \frac{r}{r-kt} + \\
\frac{r}{r+s-nt} \sum_k \binom{r-kt}{k} \binom{s-(n-k)t}{k} \frac{s}{s-(n-k)t} 
```
在第二个和式中把 k 改为 n-k，等式(26)可求出这两个和的值，由此立即推出所求的结果。

上述例子可能使读者以为二项式系数是所向披靡的利器，然而应该指出，尽管存在等式(10)(11)(18)，对于类似的和
```math
\sum_{k=0}^n \binom{m}{k} = \binom{m}{0} + \binom{m}{1} + \cdots + \binom{m}{n} \qquad (36) 
```
在 n < m 时却似乎没有简单的求和公式。当 m 为明确给出的副整数时，这个和确实有闭合式，可写成 n 的函数，例如:
```math
\sum_{k=0}^n \binom{-2}{k} = (-1)^n \Big \lceil \frac{n+1}{2} \Big \rceil \qquad (37)
```
还有一个简单公式:
```math
\sum_{k=0}^n \binom{m}{k}(k-\frac{m}{2}) = -\frac{m}{2} \binom{m-1}{n}  \qquad (38)
```
所求和式看起来似乎应当更难，而不是如此容易。


系统化、机械化处理二项式系数求和的主要工具是超几何函数的性质。超几何函数是用阶乘升幂定义的下述无穷级数：
```math
F \begin{pmatrix}
a_1, \cdots, a_m \\
b_1, \cdots, b_n \\ 
\end{pmatrix} = 
\sum_{k \geq 0} \frac{a_1^{\overline k}\cdots a_m^{\overline k}}{b_1^{\overline k}\cdots b_n^{\overline k}} \frac{z^k}{k!} \qquad (39)
```

二项式系数的概念有若干重大的推广，首先可以考虑对 $`\binom{r}{k}`$ 中的下标 k 取任意实数值。另一种推广是：
```math
\binom{r}{k}_q = \frac{(1-q^r)(1-q^{r-1}) \cdots (1-q{r-k+1})}{(1-q^k)(1-q^{k-1}) \cdots (1-q^1))} \qquad (40)
```
当q趋近极限1时，左端系数变成平常的二项式系数 $`\binom{r}{k}_1=\binom{r}{k}`$ ，他可以看成是用 1-q 除以分子和分母中每一项的结果。

最重要的推广是 _多项式系数_：
```math
\binom{k_1+k_2+\cdots+k_m}{k_1,k_2,\cdots,k_m} = \frac{(k_1+k_2+\cdots\ +k_m)}{k_1!k_2!\cdots k_m!}, k \in Z, k \geq 0  \qquad (41)
```

多项式系数的主要性质是等式(13)的推广：
```math
(x_1+x_2+\cdots+x_m)^n = \sum_{k_1+k_2+\cdots+k_m=n} \binom{n}{k_1,k_2,\cdots,k_m} \qquad (42)
```

任何多项式系数都可以通过二项式系数表示：
```math
\binom{k_1+k_2+\cdots+k_m}{k_1,k_2,\cdots,k_m} = \binom{k_1+k_2}{k_1}\binom{k_1+k_2+k_3}{k_1+k_2}\cdots\binom{k_1+k_2+\cdots+k_m}{k_1+k_2+\cdots+k_{m-1}} \qquad (43)
```
所以我们可以应用处理二项式系数的已知方法。等式(20)的两端是三项式系数 $`\binom{r}{k,m-k,r-m}`$

本小节的最后，对多项式从 x 的幂表示到二项式系数表示的变换，做个简要的分析，这个变换用到的系数成为 _斯特林数_，出现在众多的算法的研究中。
斯特林数有两类：分别用以下公式表示：$`\begin{bmatrix} n \\ k \end{bmatrix} `$ 及 $`\begin{Bmatrix} n \\ k \end{Bmatrix} `$。
- 能记住第二类斯特林数 $`\begin{Bmatrix} n \\ k \end{Bmatrix} `$ 中的大括号{}，因为大括号表示集合，而 $`\begin{Bmatrix} n \\ k \end{Bmatrix} `$ 正是把 n 个元素的集合分拆成 k 个不相交子集的分拆数。
- 第一类斯特林数 $`\begin{bmatrix} n \\ k \end{bmatrix} `$ 也可以从组合学角度理解，把 n 个字母排列成 k 个环的排列数。

第一类斯特林数用来把阶乘幂转换为普通的幂：
```math
x^{\underline n} = x(x-1)\cdots(x-n+1)\\
= \begin{bmatrix} n \\ n \end{bmatrix} x^n - \begin{bmatrix} n \\ n-1 \end{bmatrix} x^{n-1} + \cdots + (-1)^n \begin{bmatrix} n \\ 0 \end{bmatrix} \\
= \sum_k (-1)^{n-k} \begin{bmatrix} n \\ k \end{bmatrix} x^k \qquad (44)
```
例如：
```math
\binom{x}{5} = \frac{x^5}{5!} = \frac{1}{120}(x^5-10x^4+35x^3-50x^2+24x)
```

第二类斯特林数用来把普通的幂转换为阶乘幂：
```math
x^n = \begin{Bmatrix} n \\ n \end{Bmatrix}x^{\underline n} + \cdots + \begin{Bmatrix} n \\ 0 \end{Bmatrix} x^{\underline 0} = \sum_k \begin{Bmatrix} n \\ k \end{Bmatrix}x^{\underline k} \qquad (45)
```
例如：
```math
x^5 = x^{{\underline 5}} + 10x^{{\underline 4}} + 25x^{{\underline 3}}+15x^{{\underline 2}}+x^{{\underline 1}} \\
=120\binom{x}{5} + 240\binom{x}{4} + 150\binom{x}{3} + 30\binom{x}{2} + \binom{x}{1}
```


现在罗列包含斯特林数的重要恒等式。在这些恒等式中，变量 m 和 n 总是表示非负整数。
加法公式(46)：
```math
\begin{bmatrix} n+1 \\ m \end{bmatrix} = n \begin{bmatrix} n \\ m \end {bmatrix} + \begin{bmatrix} n \\ m-1\end {bmatrix} \\
\begin{Bmatrix} n+1 \\ m \end{Bmatrix} = n \begin{Bmatrix} n \\ m \end {Bmatrix} + \begin{Bmatrix} n \\ m-1\end {Bmatrix}  
```

反演公式(47)(同等式(33)比较)
```math
\sum_k \begin{bmatrix} n \\ k \end{bmatrix}\begin{Bmatrix} k \\ m \end{Bmatrix}(-1)^{n-k} = \delta_{mn} \\
\sum_k \begin{Bmatrix} n \\ k \end{Bmatrix}\begin{bmatrix} k \\ m \end{bmatrix}(-1)^{n-k} = \delta_{mn} 
```

特殊值(48)~(50)
```math
\binom{0}{n} = \begin{bmatrix} 0 \\ n \end{bmatrix} = \begin{Bmatrix} 0 \\ n \end{Bmatrix} = \delta_{n0} ,
\binom{n}{n} = \begin{bmatrix} n \\ n \end{bmatrix} = \begin{Bmatrix} n \\ n \end{Bmatrix} = 1
```

```math
\begin{bmatrix} n \\ n-1 \end{bmatrix} = \begin{Bmatrix} n \\ n-1\end{Bmatrix} =  \binom{n}{2} 
```

```math
\begin{bmatrix} n+1 \\ 0 \end{bmatrix} = \begin{Bmatrix} n+1 \\ 0\end{Bmatrix} = 0 ,
\begin{bmatrix} n+1 \\ 1 \end{bmatrix} = n!,
\begin{Bmatrix} n+1 \\ 1\end{Bmatrix} = 1,
 \begin{Bmatrix} n+1 \\ 2\end{Bmatrix} = 2^n-1
```


展开公式：
```math
\sum_k \begin{bmatrix} n \\ k \end{bmatrix}\binom{k}{m}= \begin{bmatrix} n+1 \\ m+1 \end{bmatrix} ,
\sum_k \begin{bmatrix} n+1 \\ k+1 \end{bmatrix}\binom{k}{m}(-1)^{k-m} = \begin{bmatrix} n \\ m \end{bmatrix} \qquad (51)
```

```math
\sum_k \begin{Bmatrix} k \\ m \end{Bmatrix}\binom{n}{k}= \begin{Bmatrix} n+1 \\ m+1 \end{Bmatrix} ,
\sum_k \begin{Bmatrix} k+1 \\ m+1 \end{Bmatrix}\binom{n}{k}(-1)^{n-k} = \begin{Bmatrix} n \\ m \end{Bmatrix} \qquad (52)
```

```math
\sum_k \binom{m}{k}(-1)^{m-k}k^n= m!\begin{Bmatrix} n \\ m \end{Bmatrix} \qquad (53)
```

```math
\sum_k \binom{m-n}{m+k} \binom{m+n}{n+k}\begin{Bmatrix} m+k \\ k \end{Bmatrix}= \begin{bmatrix} n \\ n-m \end{bmatrix} ,\\
\sum_k \binom{m-n}{m+k} \binom{m+n}{n+k}\begin{bmatrix} m+k \\ k \end{bmatrix}= \begin{Bmatrix} n \\ n-m \end{Bmatrix} ;\\ (54)
```

```math
\sum_k \begin{Bmatrix} n+1 \\ k+1 \end{Bmatrix}\begin{bmatrix} k \\ m \end{bmatrix} (-1)^{k-m} = \binom{n}{m};\qquad (55)
```

```math
\sum_{k \leq n} \begin{bmatrix} k \\ m \end{bmatrix} \frac{n!}{k!} = \begin{bmatrix} n+1 \\ m+1 \end{bmatrix}, \\
\sum_{k \leq n} \begin{Bmatrix} k \\ m \end{Bmatrix} (m+1)^{n-k} = \begin{Bmatrix} n+1 \\ m+1 \end{Bmatrix}. \\ (56)
```

等式(49)是一种普遍现象的一个实例: m 为非负整数时，两类斯特林数 $` \begin{bmatrix} n \\ n-m \end{bmatrix} `$ 和 $` \begin{Bmatrix} n \\ n-m \end{Bmatrix} `$ 就是 n 的 2m 次多项式。例如， m = 2 和 m = 3 时，相应的公式为
```math
\begin{bmatrix} n \\ n-2 \end{bmatrix} = \binom{n}{4} + 2\binom{n+1}{4}, \\
\begin{Bmatrix} n \\ n-2 \end{Bmatrix} = \binom{n+1}{4} + 2\binom{n}{4}, \\
\begin{bmatrix} n \\ n-3 \end{bmatrix} = \binom{n}{6} + 8\binom{n+1}{6} + 6\binom{n+2}{6}, \\
\begin{Bmatrix} n \\ n-3 \end{Bmatrix} = \binom{n+2}{6} + 8\binom{n+1}{6} + 6\binom{n}{6} \\ (57)
```
因此对于 r 的任意实数值(或者复数值)定义数 $` \begin{bmatrix} r \\ r-m \end{bmatrix} `$ 和 $` \begin{Bmatrix} r \\ r-m \end{Bmatrix} `$ 是有意义的。采用这个推广，两类斯特林数有一个有趣的对偶定律
```math
\begin{Bmatrix} n \\ m \end{Bmatrix} = \begin{bmatrix} -m \\ -n \end{bmatrix} \qquad (58)
```
统一起来，斯特林的原始讨论中隐含了这个结论。此外，每当 z 的实部为正数时，无穷级数
```math
z^r = \sum_k \begin{Bmatrix} r \\ r-k \end{Bmatrix} z^{\underline{r-k}} \qquad (59)
```
收敛。在这个意义下，一般的等式仍然成立。类似的，对应的式也可以推广到一个具有渐进性的级数:
```math
z^r = \sum_{k=0}^m \begin{bmatrix} r \\ r-k \end{bmatrix} (-1) ^k z^{r-k} + O(z^{r-m-1}) \qquad (60)
```


