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

k 取特殊值时，有
$$
\binom{r}{0} = 1,  \binom{r}{1} = r, \binom{r}{2} = \frac{r(r-1)}{2}. \qquad (3)
$$


表1 二项式系数表(帕斯卡三角)

r | $`\binom{r}{0}`$ | $`\binom{r}{1}`$ | $`\binom{r}{2}`$ | $`\binom{r}{3}`$ | $`\binom{r}{4}`$ | $`\binom{r}{5}`$ | $`\binom{r}{6}`$ | $`\binom{r}{7}`$ | $`\binom{r}{8}`$ | $`\binom{r}{9}`$ 
|:-:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0
1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0
2 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0
3 | 1 | 3 | 3 | 1 | 0 | 0 | 0 | 0 | 0 | 0
4 | 1 | 4 | 6 | 4 | 1 | 0 | 0 | 0 | 0 | 0
5 | 1 | 5 | 10 | 10 | 5 | 1 | 0 | 0 | 0 | 0
6 | 1 | 6 | 15 | 20 | 15 | 15 | 1 | 0 | 0 | 0
7 | 1 | 7 | 21 | 35 | 35 | 21 | 7 | 1 | 0 | 0
8 | 1 | 8 | 28 | 56 | 70 | 56 | 28 | 8 | 1 | 0
9 | 1 | 9 | 36 | 84 | 126 | 126 | 84 | 36 | 9 | 1


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

#### 斯特林数 stirling number

本小节的最后，对多项式从 x 的幂表示到二项式系数表示的变换，做个简要的分析，这个变换用到的系数成为 _斯特林数_，出现在众多的算法的研究中。
斯特林数有两类：分别用以下公式表示：$`\begin{bmatrix} n \\ k \end{bmatrix} `$ 及 $`\begin{Bmatrix} n \\ k \end{Bmatrix} `$。
- 能记住第二类斯特林数 $`\begin{Bmatrix} n \\ k \end{Bmatrix} `$ 中的大括号{}，因为大括号表示集合，而 $`\begin{Bmatrix} n \\ k \end{Bmatrix} `$ 正是把 n 个元素的集合分拆成 k 个不相交子集的分拆数。
- 第一类斯特林数 $`\begin{bmatrix} n \\ k \end{bmatrix} `$ 也可以从组合学角度理解，把 n 个字母排列成 k 个环的排列数。

表2 两类斯特林数

n | $`\begin{bmatrix} n \\ 0 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 1 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 2 \end{bmatrix} `$ |$`\begin{bmatrix} n \\ 3 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 4 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 5 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 6 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 7 \end{bmatrix} `$ | $`\begin{bmatrix} n \\ 8 \end{bmatrix} `$
|:-:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0
1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0
2 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0
3 | 0 | 2 | 3 | 1 | 0 | 0 | 0 | 0 | 0
4 | 0 | 6 | 11 | 6 | 1 | 0 | 0 | 0 | 0
5 | 0 | 24 | 50 | 35 | 10 | 1 | 0 | 0 | 0
6 | 0 | 120 | 274 | 225 | 85 | 15 | 1 | 0 | 0
7 | 0 | 720 | 1764 | 1624 | 735 | 175 | 21 | 1 | 0
8 | 0 | 5040 | 13068 | 13132 | 6769 | 1960 | 322 | 28 | 1
 |  |  |  |  |  |  |  |  | 
n | $`\begin{Bmatrix} n \\ 0 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 1 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 2 \end{Bmatrix} `$ |$`\begin{Bmatrix} n \\ 3 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 4 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 5 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 6 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 7 \end{Bmatrix} `$ | $`\begin{Bmatrix} n \\ 8 \end{Bmatrix} `$
0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0
1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0
2 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0
3 | 0 | 1 | 3 | 1 | 0 | 0 | 0 | 0 | 0
4 | 0 | 1 | 7 | 6 | 1 | 0 | 0 | 0 | 0
5 | 0 | 1 | 15 | 25 | 10 | 1 | 0 | 0 | 0
6 | 0 | 1 | 31 | 90 | 65 | 15 | 1 | 0 | 0
7 | 0 | 1 | 63 | 301 | 350 | 140 | 21 | 1 | 0
8 | 0 | 1 | 127 | 966 | 1701 | 1050 | 266 | 28 | 1


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


### 1.2.7 调和数
在后面的讨论中，下述和式极为重要：
```math
H_n = 1 + \frac{1}{2} + \frac{1}{3} + \cdots + \frac{1}{n} = \sum_{k=1}^n \frac{1}{k}, n \geq 0\ \qquad (1)
```
字母 H 代表 harmonic，即“调和”，我们将 $`H_n`$ 称为调和数。__早在公元前 186 年以前，中国人已在竹简上写明了 $`H_{10} = \frac{7381}{2520} `$__。

乍看之下，当 n 取很大的值时，$`H_n`$ 似乎不会特别大，因为向级数中加进的数越来越小，但是如果取足够大的 n，$`H_n`$ 的值可以随意增大，因为：
```math
H_{2^m} \geq 1 + \frac{m}{2}, m \geq 0 \qquad (2)
```


$`H_n`$ 大小的近似值可以表示为：
```math
H_n = \ln n + \gamma + \frac{1}{2n} - \frac{1}{12n^2} + \frac{1}{120n^4} - \epsilon, 0 < \epsilon < \frac{1}{252n^6} \qquad (3)
```
这里，$`\gamma = 0.5772156649... `$ 是欧拉提出的 _欧拉常数_。由此看来，$`H_n`$ 同 n 的自然对数是相当接近的。在一定意义上，当 n 越来越大时，$`H_n`$ 仅勉强的趋近无穷大，因为对所有的 n，当 r 为大于 1 的任意实值指数时，类似的和：
```math
1 + \frac{1}{2^r} + \frac{1}{3^r} + \cdots + \frac{1}{n^r} \qquad (4)
```
总是有界的。把式(4)中的和记为 $`H_n^{(r)}`$ 。当式(4)中的指数 r 至少为2时，只要 n 不是太小，$`H_n^{(r)}`$ 的值就非常接近其最大值 $`H_\infty^{(r)}`$。$`H_\infty^{(r)}`$ 在数学上是个非常著名的量，成为黎曼 $`\zeta`$ 函数:
```math
H_\infty^{(r)} = \zeta(r) = \sum_{k \geq 1} \frac{1}{k^r}, \qquad (5)
```
已经知道，如果 r 为偶整数，$`\zeta`$ 的值等于：
```math
H_\infty^{(r)} = \frac{1}{2}|B_r|\frac{(2\pi)^r}{r!}, r/2 \geq 1, \qquad (6)
```
其中 $`B_r`$ 是伯努利数。特别的
```math
H_\infty^{(2)} = \frac{\pi^2}{6}, H_\infty^{(4)} = \frac{\pi^4}{90}, H_\infty^{(6)} = \frac{\pi^6}{945}, H_\infty^{(8)} = \frac{\pi^8}{9450} \qquad (6)
```
这些结果是欧拉得到。1755年欧拉给出了伯努利数的生成函数：
```math
\frac{x}{e^x-1} = \sum_{n=0}^\infty \frac{B_nx^n}{n!}, \qquad (7)
```


现在考察涉及调和数的几个重要的和。首先：
```math
\sum_{k=1}^n H_k = (n+1)H_n - n, \qquad (8)
```
要得到上式只需交换求和次序：
```math
\sum_{k=1}^n \sum_{j=1}^k \frac{1}{j} = \sum_{j=1}^n \sum_{k=j}^n \frac{1}{j} = \sum_{j=1}^n \frac{n+1-j}{j}
```
式(8)是和式 $` \sum_{k=1}^n \binom{k}{m} H_k `$ 的一个特例。现在利用一种重要的方法--分布求和，来确定这个一般的和。只要 $` \sum a_k 和 (b_{k+1} - b_k) `$ 这两个量具有的简单的形式，就适合分部求和计算 $` \sum a_k b_k `$。注意到本例中有
```math
\binom{k}{m} = \binom{k+1}{m+1} - \binom{k}{m+1}
```

因此
```math
\binom{k}{m} H_k = \binom{k+1}{m+1}(H_{k+1}-\frac{1}{k+1}) - \binom{k}{m+1}H_k ,
```

所以
```math
\sum_{k=1}^n \binom{k}{m} H_k = (\binom{2}{m+1} H_2 - \binom{1}{m+1} H_1) + \cdots \\\\\\
+ (\binom{n+1}{m+1} H_{n+1} - \binom{n}{m+1} H_n) - \sum_{k=1}^n \binom{k+1}{m+1} \frac{1}{k+1} \\\\\\
= \binom{n+1}{m+1} H_{n+1} - \binom{1}{m+1} H_1 - \frac{1}{m+1} \sum_{k=0}^n \binom{k}{m} + \frac{1}{m+1} \binom{0}{m} 
```

应用式1.2.6-(11)得到所求公式：
```math
\sum_{k=1}^n \binom{k}{m} H_k = \binom{n+1}{m+1}(H_{n+1}-\frac{1}{m+1}).
```
> [!TIP]
> $`\binom{1}{m+1} H_1 = 0`$, 参见1.2.6-表1 二项式系数表 m+1 > 1时，$`\binom{1}{m+1} = 0`$
> $`\frac{1}{m+1} \binom{0}{m} = 0`$, 同理由于 $`\binom{0}{m+1} = 0`$

最后，考察一种不同类型的和式：$`\sum_k \binom{n}{k} x^kH_k`$。为简单起见，暂时用 $`S_n`$ 表示它。由于

```math
S_{n+1} = \sum_k (\binom{n}{k} + \binom{n}{k-1})x^kH_k \\\\\\
        = S_n + x \sum_{k \geq 1}\binom{n}{k-1}x^{k-1}(H_{k-1}+\frac{1}{k}) \\\\\\
        = S_n + x S_n + \frac{1}{n+1} \sum_{k \geq 1} \binom{n=1}{k}x^k.
```

因此
```math
S_{n+1} = (x+1)S_n + ((x+1)^{n+1}-1)/(n+1),
```

而我们有
```math
\frac{S_{n+1}}{(x+1)^{n+1}} = \frac{S_n}{(x+1)^n} + \frac{1}{n+1} - \frac{1}{(n+1)(x+1)^{n+1}} 
```

这个等式连同 $`S_1=x`$，证明
```math
\frac{S_n}{(x+1)^n} = H_n - \sum_{k=1}^n \frac{1}{k(x+1)^k}.  \qquad (10)
```

这个新的和是无穷级数1.2.9-(17)的一部分，因为 $` \ln(1/(1-1/(x+1))) = \ln(1+1/x)`$, 并且这个级数当 x > 0 时收敛，两者之差为：
```math
\sum_{k>n} \frac{1}{k(x+1)^k} <  \frac{1}{(n+1)(x+1)^{n+1}}\sum_{k \geq 0} \frac{1}{(x+1)^k} = \frac{1}{(n+1)(x+1)^nx}  (10)
```

这就证明了下述定理

__定理A.__ 如果 x>0，那么
```math
\sum_{k=1}^n \binom{n}{k}x^kH_k = (x+1)^n(H_n - \ln(1+\frac{1}{x})) + \epsilon.
```
其中 $`0<\epsilon<1/(x(n+1))`$



### 1.2.8 斐波纳切数
在数列
```math
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, \cdots \qquad (1)
```
中，每个数都是前两个数的和。在后面讨论的十几个看似不相关的算法中，这个数列将扮演重要的角色。用 $`F_n`$ 表示这个数列，并从形式上把它们定位为：
```math
F_0 = 1, F_1 = 1; F_{n+2} = F_{n+1} + F_n, n \geq 0 \qquad (2)
```
这个著名的数列公布于1202年，发明者名叫列昂纳多，也被人称为列昂纳多.斐波纳切(所谓“斐波纳切”，来自拉丁文 Filius Bonaccii)。

在斐波纳切写书之前，印度学者已经讨论过序列<$`F_n`$>。戈帕拉(公元1135年以前)和赫马坎德拉(约公元1150年)都曾明确的提出数列1, 2, 3, 5, 8, 13, 21, 34,...

这个序列也出现在约翰内斯.开普勒在1611的著作中。

$`F_n`$ 与算法之间的密切联系。第一个迹象出现在 1837 年，当时埃米尔莱热利用斐波纳切数列研究欧几里德算法的效率。他指出，如果算法1.1E中的数 m 和 n 不大于 $`F_k`$，那么步骤 E2 最多执行 k-1 次。这是斐波纳切数列的首次实际应用。在 19 世纪 70 年代，数学家卢卡斯获得了有关斐波纳切数的一些非常深奥的结果，特别是利用它证明了 $`2^{127}-1`$ 这个 39 位的数是素数。斐波纳切数把 <$`F_n`$> 命名为“斐波纳切数列”，这个名字一直沿用至今。发现，如果 n 为正整数，且
```math
\phi = \frac{1}{2}(1+\sqrt{5}), \qquad (3)
```
那么 $`\phi^{n-2} \leq F_n \leq \phi^{n-1}`$。$`\phi`$ 这个数与斐波纳切数有紧密的联系。

数 $`\phi`$ 本身有段非常有趣的历史
- 欧几里德把它成为"外内比"，因为如果 A 与 B 之比为 $`\phi`$，那么 A 与 B 之比等于 A+B 与 A 之比。
- 文艺复兴时代，作家们称它为“神圣比例”
- 而从 19 世纪起，它被通称为"黄金分割比"。许多艺术家和作家断言，$`\phi`$ 与 1 之比在美学上是最令人赏心悦目的。

欧洲早期的计算大师西蒙.雅各布早已知道 $`F_{n+1}/F_n`$ 的值趋近 $`\phi`$ 的事实。

高端大气的数学文献往往把 $`F_n`$ 改称为 $`u_n`$，$`\phi`$ 改称为 $`\tau`$。字母 $`\phi`$ 来源于古希腊艺术家菲狄亚斯的名字，据说他在雕刻作品中经常使用黄金分割比。

斐波纳切数满足许多有趣的恒等式。最常见的关系式之一是由开普勒于 1608 年在一封信中提出，但首次公开发表的是乔凡尼.多梅尼科.卡西尼，这个关系式是：
```math
F_{n+1}F_{n-1} - F_n^2 = (-1)^n \qquad (4)
```
它很容易用归纳法证明。还有一种更深奥的证法：首先用简单的归纳法证明矩阵恒等式
```math
\begin{pmatrix} F_{n+1} & F_n \\ F_n & F_{n-1} \end{pmatrix}= 
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \qquad (5)
```
然后对等式两端取行列式。

关系式(4)表明 $`F_n`$ 与 $`F_{n+1}`$ 是互素的，因为它们的公因数必定是 $`(-1)^n`$ 的因数。

从定义(2)立即得到
```math
F_{n+3} = F_{n+2} + F_{n+1} = 2F_{n+1} + F_n;
F_{n+4} = 3F_{n+1} + 2F_n
```
一般地，由归纳法可以证明等式
```math
F_{n+m} = F_{m}F_{n+1} + F_{m-1}F_n.  \qquad (6)
```
对于任何正整数 m 成立。

在等式(6)中取 m 为 n 的倍数，则归纳可知 $`F_{nk}`$ 为 $`F_n`$ 的倍数。

由此在序列 <$`F_n`$> 中每隔 2 项就出现一个偶数，每隔 3 项就出现 3 的倍数，每个 4 项就出现一个 5 的倍数，依此类推。

还有更普遍的结论成立。如果用 gcd(m,n) 代表 m 和 n 的最大公因数，就会出现一个颇为神奇的定理

__定理 A__ 一个数同时整除 $`F_m`$ 和 $`F_n`$，当且仅当它是 $`F_d`$ 的因数，其中 d = gcd(m,n)。特别的，有
```math
gcd(F_m,F_n) = F_{gcd(m,n)}  \qquad (7)
```
证明。 用欧几里德算法证明。根据等式(6), $`F_m`$ 和 $`F_n`$ 的公因数也是 $`F_{n+m}`$ 的因数；反过来，$`F_{n+m}`$ 和 $`F_n`$ 的公因数也是 $`F_mF_{n+1}`$ 的因数。由于 $`F_{n+1}`$ 和 $`F_n`$ 互素，$`F_{n+m}`$ 和 $`F_n`$ 公因数也整除 $`F_m`$。这样，我们证明了对于任何数 d，
```math
d 整除 F_m 和 F_n 当且仅当 d 整除 F_{n+m} 和 F_n \qquad (8)
```

如果任何序列<$`F_n`$>时的命题(8)成立，并且它的首项 $`F_0=0`$ ，那么这个序列满足 __定理 A__。

首先，可以对 k 归纳，把命题(8)扩展为规则
```math
d 整除 F_m 和 F_n 当且仅当 d 整除 F_{kn+m} 和 F_n，
```
其中 k 是任何非负整数，这个结果可以更简洁的陈述为
```math
d 整除 F_{m \mod n} 和 F_n 当且仅当 d 整除 F_m 和 F_n \qquad (9)
```
如果 r 是用 n 除 m 的余数，即 $`r = m \mod n`$，那么 {$`F_m,F_n`$} 的公因数也务是 {$`F_r,F_n`$} 的公因数。

由此推出，在算法1.1E的整个操作过程中，当 m 和 n 改变时， {$`F_m,F_n`$} 的公因数结合操作保持不变。最后当 r=0 时，这些公因数就是  $`F_0=0 和 F_{gcd(m,n)}`$ 的公因数。

有关斐波纳切数的多数重要结果，可以从用 $`\phi`$ 表示的 $`F_n`$ 通式中得到。

首先建立无穷级数
```math
G(z) = F_0 + F_1z + F_2z^2 + F_3z^3 + F_4z^4 + \cdots \\
= z + z^2 + 2z^3 + 3z^4 + \cdots \qquad (10)
```
并无先验的理由指望这个无穷和是存在的。G(z) 用一个函数同时代表了整个斐波纳切序列。如果 G(z) 是一个已知的函数，那么可以确定它的系数。称 G(z) 为序列<$`F_n`$>的生成函数。

对 G(z) 进行考察：
```math
zG(z) = F_0z + F_1z^2 + F_2z^3 + F_3z^4 + F_4z^5 + \cdots,
```
```math
z^2G(z)= \qquad F_0z^2 + F_1z^3 + F_2z^4 + F_3z^5 + \cdots .
```
通过相减得到：
```math
(1-z-z^2)G(z) = F_0 + (F_1-F_0)z + (F_2-F_1-F_0)z^2 \\
 + (F_3-F_2-F_1)z^3 + (F_4-F_3-F_2)z^4 + \cdots,
```
由于 $`F_n`$ 的定义，上式出第二项之外的所有项都变为零。所以这个表达式等于 z 。由此可以看出，如果 G(z) 存在，那么
```math
G(z) = z/(1-z-z^2)  \qquad (11)
```
事实上，可以把这个函数展开成 z 的无穷级数(泰勒级数)。做反向推导，等式(11)的幂级数展开式的系数必定是斐波纳切数。

分母 $`1-z-z^2`$ 是具有两个根的 $`\frac{1}{2}(-1 \pm \sqrt{5})`$ 的二次多项式。在进行少量计算后，可以把 G(z) 展开成：
```math
G(z) = \frac{1}{\sqrt{5}}(\frac{1}{1-\phi z} - \frac{1}{1-\hat\phi z})  \qquad (12)
```
的形式，其中：
```math
\hat\phi = 1 - \phi = \frac{1}{2}(1-\sqrt{5})  \qquad (13)
```
量 $`1/(1-\phi z)`$ 是无穷等比级数 $`1 + \phi z +  \phi^2 z^2 + \cdots`$ 的和，所有有
```math
G(z) = \frac{1}{\sqrt{5}}(1 + \phi z + \phi^2 z^2 + \cdots - 1 - \hat\phi z - \hat\phi^2 z^2) 
```
现在考察 $`z_n`$ 的系数，已知它必定等于 $`F_n`$，因此
```math
F_n = \frac{1}{\sqrt{5}}(\phi^n z^n - \hat\phi^n z^n) \qquad (14)
```
这是斐波纳切数的重要闭合式，最早在 18 世纪初期发现。

可以仅仅叙述等式(14)并用归纳法证明它，然而还是给出了大段推导。意在说明，利用生成函数这种重要的方法，有办法在证明之先发现有这么一个等式存在。生成函数是一种很有价值的方法，能用来求解各种各样的问题。

从等式(14)可以证明许多命题。首先注意到 $`\hat\phi`$ 是一个绝对小于1的负数(-0.61803...)，所以当 n 取很大值时，$`\hat\phi^n`$ 变的非常小。事实上，$`\hat\phi^n/\sqrt{5}`$ 这个数始终很小，因此有
```math
F_n = \phi^n/\sqrt{5} 舍入到最接近的整数  \qquad (15)
```

其他的结果可以直接从 G(z) 得到。例如
```math
G(z)^2 = \frac{1}{5} (\frac{1}{(1-\phi z)^2} + \frac{1}{(1-\hat\phi z)^2} - \frac{2}{1-z-z^2})  \qquad (16)
```
并且 $`G(z)^2`$ 中 $`z_n`$ 的系数是 $`\sum_{k=0}^n F_nF_{n-k}`$。因此推出
```math
\sum_{k=0}^n F_nF_{n-k} = \frac{1}{5} ((n+1)(phi^n + \hat\phi^n)-2F_{n+1}) \\
= \frac{1}{5}((n+1)(F_n+2F_{n-1})-2F_{n+1}) \\
= \frac{1}{5}(n-1)F_n + \frac{2}{5}nF_{n-1}  \qquad (17)
```


### 1.2.9 生成函数

每当想要了解某数列 <$`a_n`$> = $`a_0, a_1, a_2, \cdots`$ 时，总可以建立用“参数” z 表示的无限和
```math
G(z) = a_0 + a_1z + a_2z^2 + \cdots = \sum_{n\geq0} a_nz^n \qquad (1)
```
然后想办法研究函数 G。这个函数就用一个量就表示了整个数列。如果数列<$`a_n`$>是递归定义的，那么这是一个重要的有利条件。此外假定式(1)中的无限和对于 z 的非零值存在，就能用微积分方法重新获得 $`a_0, a_1, a_2, \cdots`$ 的值。

G(z)称为序列 $`a_0, a_1, a_2, \cdots`$ 的 _生成函数_。生成函数带来了一大批新方法，增强了解题能力。
- 棣莫弗引进生成函数是为了求解一般问题的线性递归问题
- 斯特林把棣莫弗理论扩展到更复杂的递归过程，还说明如何利用微积分及算术运算
- 几年之后，欧拉开始从几个新的途径利用生成函数
- 皮埃尔.西蒙.拉普拉斯在其经典著作《概率论的解析理论》中进一步发展了生成函数

无限和(1)的收敛性是很重要的，都需要证明：
- 如果级数对于某个特定的值 <$`z = z_0`$ 收敛，那么它对于 |z| < |$`z_0`$| 的所有数都收敛
- 级数对于某个 <$`z \neq 0`$ 收敛，当且仅当序列<$`\sqrt[n][\lvert a_n\rvert]`$> 是有界的。

当用生成函数时求解问题时，通常不必担心级数的收敛性，因为只是在寻找莫个问题求解的可能途径，无论这一过程多么不严谨，只要设法找到解，也许就能独立证明解的正确性。

此外，可以严格的证明，用生成函数所做的大部分(几乎全部)运算都是正确的，无论级数收敛与否。

现在讨论生成函数的主要方法


#### A. 加法
若G(z)是 <$`a_n`$> = $`a_0, a_1, a_2, \cdots`$ 的生成函数，H(z)是 <$`b_n`$> = $`b_0, b_1, b_2, \cdots`$ 的生成函数，则 $`\alpha G(z)+\beta H(z)`$ 是 <$`\alpha a_n+\beta b_n`$> = $`\alpha a_0+\beta b_0, \alpha a_1+\beta b_1, \alpha a_2+\beta b_2, \cdots`$ 的生成函数：
```math
\alpha \sum_{n\geq 0} a_nz^n + \beta \sum_{n\geq 0} b_nz^n = \sum_{n\geq 0}(\alpha a_n+\beta b_n)z^n. \qquad (2)
```


#### B. 移位
若G(z)是 <$`a_n`$> = $`a_0, a_1, a_2, \cdots`$ 的生成函数，则 $`z^mG(z)`$ 是 <$`a_{n-m}`$> = $`0,\cdots,0,a_0, a_1, a_2, \cdots`$ 的生成函数:
```math
z^m \sum_{n\geq 0} a_nz^n = \sum_{n\geq m} a_{n-m}z^n.  \qquad (3)
```
若 n 为负值时视为 <$`a_n=0`$>，则可以把最后的这个求和扩展到所有 <$`n\geq 0`$>

同样，$`(G(z)- a_0 - a_1z - \cdots - a_{m-1}z^{m-1})/z^m`$ 是 $`a_m, a_{m+1}, \cdots`$ 的生成函数:
```math
z^{-m} \sum_{n\geq m} a_nz^n = \sum_{n\geq 0} a_{n+m}z^n.  \qquad (4)
```

把加法运算 A 和移位运算 B 结合起来求解上节中的斐波纳切问题：
- G(z) 是 <$`F_n`$> 的生成函数，zG(z) 是 <$`F_{n-1}`$> 的生成函数 $`z^2G(z)`$ 是 <$`F_{n-2}`$> 的生成函数
- $`(1-z-z^2)G(z)`$ 是 <$`F_n-F_{n-1}-F_{n-2}`$> 的生产函数
于是，由于 <$`n\geq 2`$> 时，$`F_n-F_{n-1}-F_{n-2}`$ 为零，发现 $`(1-z-z^2)G(z)`$ 是个多项式。

同样，给定任何线性递归序列，即满足 $`a_n = c_1a_{n-1} +\cdots+c_ma_{n-m}`$ 的序列，其生成函数必是一个多项式除以 $`(1-c_1z-c_mz^m)G(z)`$ 的结果。

最简单的例子，如果 G(z) 是常数序列 1,1,1... 的生成函数，那么 zG(z) 生成序列0,1,1,1...，所以 (1-z)G(z) = 1。这个结果给出简单但是非常重要的公式
```math
\frac{1}{1-z} = 1 + z + z^2 + \cdots.  \qquad (5)
```


#### C. 乘法
若G(z)是 <$`a_n`$> = $`a_0, a_1, a_2, \cdots`$ 的生成函数，H(z)是 <$`b_n`$> = $`b_0, b_1, b_2, \cdots`$ 的生成函数，则
$`G(z)H(z)`$ = $`(a_0 + a_1z + a_2z^2 + \cdots)`$ $`(b_0 + b_1z + b_2z^2 + \cdots)`$
= $`a_0b_0 + (a0b_1+a_1b0)z + (a_0b_2+a_1b_1+a_0b_2)z^2 +  + \cdots`$

因此 G(z)H(z) 是序列 $`c_0, c_1, c_2, \cdots`$ 的生成函数，其中
```math
c_n = \sum_{k=0}^n a_kb{n-k}.  \qquad (6)
```
式(3)的是这个结果的一个非常特殊的特例。另外一个重要的特例出现在每个 $`b_n`$ 都等于 1 的时候：
```math
\frac{1}{1-z}G(z) = a_0 + (a_0+a_1)z + (a_0+a_1+a_2)z^2 + \cdots \qquad (7) 
```
得到原序列的部分和序列的生成函数。

对于三个函数的乘积，生成序列的规则由式(6)推出；F(z)G(z)H(z)生成序列 $`d_0, d_1, d_2, \cdots`$，其中
```math
d_n = \sum_{i,j,k\geq 0,i+j+k=n} a_ib_jc_k. \qquad (8) 
```
对于任意多个函数的乘积，生成序列的一般规则是
```math
\prod_{j\geq 0} \sum_{k\geq 0} a_jkz^k = 
\sum_{n\geq 0}z^n \sum_{k_0,k_1,\cdots\geq 0, k_0+k_1+\cdots=n} a_0k_0a_1k_1\cdots.     \qquad (9) 
```
当某个序列的递归公式包含二项式系数时，通常要求获得由
```math
c_n = \sum_k \binom{n}{k} a_kb_{n-k}. \qquad (10) 
```
定义的序列 $`c_0, c_1, c_2, \cdots`$ 的生成函数。在这种情况下，更应该利用序列 <$`a_n/n!`$>, <$`b_n/n!`$>, <$`c_n/n!`$> 的生成函数，因为有：
```math
(\frac{a_0}{0!} + \frac{a_1}{1!}z + \frac{a_2}{2!}z^2 + \cdots)
(\frac{b_0}{0!} + \frac{b_1}{1!}z + \frac{b_2}{2!}z^2 + \cdots)
= (\frac{c_0}{0!} + \frac{c_1}{1!}z + \frac{c_2}{2!}z^2 + \cdots), \qquad (11) 
```
其中 $`c_n`$ 由式(10)给定。


#### D. z 的变换
显然，G(cz) 是序列 $`a_0, ca_1, c^2a_2, \cdots`$ 的生成函数。特例 $`1, c, c^2. c^3 cdots`$ 的生成函数是 1/(1-cz)。

在级数里隔一项取一项时，有一种常见的技巧：
```math
\frac{1}{2}(G(z)+G(-z)) = a_0 + a_2z^2 + a_4z^4 + \cdots,
```
```math
\frac{1}{2}(G(z)-G(-z)) = a_1 + a_3z^3 + a_5z^5 + \cdots,. \qquad (12) 
```
利用单位复根，可以推广这种思想，每个 m - 1项提取第 m 项：令 $`\omega=e^{2\pi i/m} = \cos(2\pi/m)+i\sin(2\pi/m)`$，有
```math
\sum_{n\geq 0,n \mod m=r} a_nz^n = \frac{1}{m} \sum_{0\leq k < m} \omega^{-kr}G(\omega^kz), 0 \leq r < m  \qquad (13) 
```
例如，如果 m=3,r=1，单位复立方根之一是 $`\omega=-\frac{1}{2}+\frac{\sqrt{3}}{2}i`$，由此推出
```math
a_1z + a_4z^4 + a_7z^7 + \cdots = \frac{1}{3}(G(z)+\omega^{-1}G(wz)+\omega^{-2}G(\omega^2z)).
```


#### E. 微分与积分
微积分的方法带来了利用生成函数的更多运算。假定 G(z) 是由式 (1) 给定的，那么它的导数为
```math
G‘(z) = a_1 + 2a_2z + 3a_3z^2 + \cdots = \sum_{k\geq 0}(k+1)a_{k+1}z^k. \qquad (14) 
```
序列 <$`na_n`$> 的生成函数是 $`zG‘(z)`$。因此，通过对生成函数做运算，可以把一个序列的第 n 项同 n 的多项式结合起来。

逆转这个过程，求积分给出另一种有用的运算：
```math
\int_0^z G(t) dt = a_0z + \frac{1}{2}a_1z^2 + \frac{1}{3}a_2z^3 + \cdots = \sum_{k\geq 1} \frac{1}{k} a_{k-1}z^k   \qquad (15) 
```
作为特例，有式(5)的导数和积分：
```math
\frac{1}{(1-z)^2} = 1 + 2z + 3z^2 + \cdots = \sum_{k\geq 0} (k+1)z^k .  \qquad (16)
```
```math
\ln \frac{1}{1-z} = z + \frac{1}{2}z^2 + \frac{1}{3}z^2 + \cdots = \sum_{k\geq 1} \frac{1}{k}z^k .  \qquad (17)
```
把第二个公式同式(7)结合，可以得到调和数的生成函数：
```math
\frac{1}{1-z}\ln \frac{1}{1-z} = z + \frac{3}{2}z^2 + \frac{11}{6}z^3 + \cdots = \sum_{k\geq 0} H_kz^k . \qquad (18) 
```


#### F. 已知的生成函数
每当能够确定一个函数的幂级数展开时，已经找到一个特定序列的生成函数。下面列举几个最重要的幂级数展开式：

(i) 二项式定理
```math
(1+z)^r = 1 + rz + \frac{r(r-1)}{2}z^2 + \cdots = \sum_{k\geq 0} \binom{r}{k}z^k . \qquad (19) 
```
当 r 为负整数时，得到一个反映在等式(5)(16)中的特例：
```math
\frac{1}{(1-z)^{n+1}} = \sum_{k\geq 0} \binom{-n-1}{k}(-z)^k = \sum_{k\geq 0} \binom{n+k}{n}z^k  . \qquad (20) 
```

如果 x 是 z 的连续函数，满足方程 $`x^{t+1}=x^t+z`$，其中当 z=0 时 x=1，那么
```math
x^r = 1 + rz + \frac{r(r-2t-1)}{2}z^2 + \cdots = \sum_{k\geq 0} \binom{r-kt}{k} \frac{r}{r-kt}z^k . \qquad (21) 
```

(ii) 指数级数
```math
exp z = e^z = 1 + z + \frac{1}{2!}z^2 + \cdots =  \sum_{k\geq 0}\frac{1}{k!}z^k . \qquad (22) 
```
一般的，有包含斯特林数的公式：
```math
(e^z-1)^n = z^n + \frac{1}{n+1}\begin{Bmatrix}n+1\\n\end{Bmatrix}z^{n+1} + \cdots 
=  n! \sum_k\begin{Bmatrix}k\\n\end{Bmatrix}\frac{z^k}{k!} . \qquad (23) 
```

(iii) 对数级数 (见式(17)和(18))
```math
\ln(1+z) = z - \frac{1}{2}z^2 + \frac{1}{3}z^3 - \cdots = \sum_{k\geq 1}\frac{(-1)^{k+1}}{k}z^k \qquad (24) 
```
```math
\frac{1}{(1-z)^{m+1}}\ln(1-z) = \sum_{k\geq 1}(H_{m+k}-H_m)\binom{m+k}{k}z^k \qquad (25) 
```
式(23)的斯特林给出了更一般的等式：
```math
(\ln\frac{1}{(1-z)})^n  = z^n + \frac{1}{n+1}\begin{bmatrix}n+1\\n\end{bmatrix}z^{n+1} + \cdots 
=  n! \sum_k\begin{bmatrix}k\\n\end{bmatrix}\frac{z^k}{k!} . \qquad (26) 
```

(iv) 其他
```math
z(z+1) \cdots z(z+n-1) = \sum_k\begin{bmatrix}n\\k\end{bmatrix}z^k \qquad (27) 
```
```math
\frac{z^n}{(1-z)(1-2z)\cdots(1-nz)} = \sum_k\begin{Bmatrix}n\\k\end{Bmatrix}z^k \qquad (28) 
```
```math
\frac{z}{e^z-1} = 1 - \frac{1}{2}z + \frac{1}{12}z^2 + \cdots = \sum_{k\geq 1}\frac{B_kz^k}{k!} \qquad (29) 
```
最后一个公式中的系数 $`B_k`$ 是伯努利数，后续将深入探讨。

等式(21)类似的另一个恒等式：如果 x 是 z 的连续函数，满足方程 $`x=e^{zx^t}`$，其中当 z=0 时 x=1，那么
```math
x^r = 1 + rz + \frac{r(r+2t)}{2}z^2 + \cdots = \sum_{k\geq 0} \frac{r(r+kt)^{k-1}}{k!}z^k . \qquad (30) 
```


#### G. 提取系数
对于 G(z) 中的 $`z_n`$ 项的系数，采用记号
```math
[z_n]G(z). \qquad (31) 
```
通常是很方便的。例如，如果 G(z) 是式(1) 中的生成函数，有 $`[z_n]G(z)=a_n`$ 和 $`[z_n]G(z)/(1-z)=\sum_{k=0}^n a_k`$。在复变函数中，一个极其基本的结果是柯西的一个公式，借助周线积分，可以利用此公式提取任何想要的系数：
```math
[z_n]G(z)=\frac{1}{2\pi i} \oint_{|z|=r} \frac{G(z)dz}{z^{n+1}} . \qquad (32) 
```
只要 G(z) 对于 $`z=z_0`$ 和  $`0 < r < |z_0|`$ 收敛。基本思想是，对于所有整数 $`m\neq -1`$，积分 $`\oint_{|z|=r} z^m dz`$ 为 0；而 m = -1 时为
```math
\int_{-\pi}^\pi (re^{i\theta})^{-1}d(re^{i\theta}) = i \int_{-\pi}^\pi d\theta = 2\pi i.
```
讨论一个系数的近似值时，等式(32)尤其重要。

最后，回过头讨论1.2.3节中仅获得部分解决的一个问题。由等式1.2.3-(13)和习题1.2.3-29，已经知道
```math
\sum_{1\leq i\leq j\leq n} x_ix_j = \frac{1}{2}(\sum_{k=1}^nx_k)^2 + \frac{1}{2}(\sum_{k=1}^nx_k^2) ,
```
```math
\sum_{1\leq i\leq j\leq k\leq n} x_ix_jx_k = \frac{1}{6}(\sum_{k=1}^nx_k)^3 + 
\frac{1}{2}(\sum_{k=1}^nx_k)(\sum_{k=1}^nx_k^2) + \frac{1}{3}(\sum_{k=1}^nx_k^3).
```
一般的，假定有 n 个数 $`x_1,\cdots, x_n`$，希望求和
```math
h_m = \sum_{1\leq j_1\leq\cdots\leq j_m\leq n} x_{j1}\cdots x_{jm}. \qquad (33)
```
如果可能，应当用 $`S_1,S_2,\cdots, S_m`$ 表示这个和，其中
```math
S_j = \sum_{k=1}^n x_k^j, \qquad (34)
```
即 j 次幂之和。利用这种更紧凑的记号，上面的公式变成：
```math
h_2 = \frac{1}{2}S_1^2 + \frac{1}{2}S_2, h_3 = \frac{1}{6}S_1^3 + \frac{1}{2}S_1S_2 + \frac{1}{3}S_3.
```
通过建立生成函数
```math
G(z) = 1 + h_1z + h_2z^2 + \cdots = \sum_{k\geq 0} h_kz^k. \qquad (35)
```
按照级数相乘的规则，求出：
```math
G(z) =(1 + x_1z + x_1^2z^2 + \cdots)(1 + x_2z + x_2^2z^2 + \cdots)\cdots(1 + x_nz + x_n^2z^2 + \cdots)
```
```math
=\frac{1}{(1-x_1z)(1-x_2z)\cdots(1-x_nz)}. \qquad (36)
```
所以 G(z) 是一个多项式的倒数。对乘积取对数常常有用，从式(17)中求出
```math
\ln G(z) =\ln\frac{1}{(1-x_1z)} + \cdots + \ln\frac{1}{(1-x_nz)}
```
```math
=(\sum_{k\geq 1}\frac{x_1^kz^k}{k}) + \cdots + (\sum_{k\geq 1}\frac{x_n^kz^k}{k}) = \sum_{k\geq 1}\frac{S_k^kz^k}{k}. \qquad (37)
```
至此，$`\ln G(z)`$ 已经由 S 表示。为了获得问题的答案，借助等式(22)(9)再次计算 G(z) 的幂级数展开：
```math
G(z) =e^{\ln G(z)} = exp(\sum_{k\geq 1}\frac{S_kz^k}{k}) = \prod_{k\geq 1} e^{s_kz^k/k}
```
```math
= (1+S_1z+\frac{S_1^2z^2}{2!}+\cdots)(1+\frac{S_2z^2}{2}+\frac{S_2^2z^4}{2^2\cdot 2!}+\cdots)\cdots
```
```math
= \sum_{k\geq 0}(\sum_{k_1,\cdots,k_m\geq 0,\\k_1+2k_2+\cdots+mk_m=m}\frac{S_1^{k_1}}{1^{k_1}k_1!}
\frac{S_2^{k_2}}{2^{k_2}k_2!}\cdots\frac{S_m^{k_m}}{m^{k_m}k_m!})z^m. \qquad (38)
```
括号中的量是 $`h_m`$，仔细考察便知，这个颇为壮观的和其实并不复杂。对特定的 m 值，项数就是 m 的分拆数 p(m)。例如 12 的分拆数是
```math
12 = 5 + 2 + 2 + 2 + 1.
```
分拆对应方程
```math
k_1 + 2k_2 + \cdots + 12k_{12} = 12
```
的解，其中 $`k_j`$ 是分拆中 j 的个数。在上面的例子中 $`k_1=1,k_2=3,k_5=1,`$，而其余 k 为 0；所以 $`h_{12}`$ 的表达式含有项
```math
\frac{S_1}{1^11!}\frac{S_2^3}{2^33!}\frac{S_5}{5^11!}=\frac{1}{240}S_1S_2^3S_5. 
```
对式(37)求导数，不难导出递归公式
```math
h_n = \frac{1}{n}(S_1h{n-1}+S_2h_{n-2}+\cdots+S_nh_0), n \geq 1. \qquad (39)
```
波利亚对生成函数的应用做了有趣的介绍，《具体数学》第7章沿用了他的方法。


### 1.2.10 典型算法分析
现在应用前几小节的讨论的一些方法，研究一个典型的算法

__算法 M__ 找出最大值
给定 n 个元素 X[1],X[2],...,X[n]，将求出 m 和 j，使得 m = X[j]= $`\max_{1\leq i\leq n} X[i]`$，其中 j 是满足这个关系式的最大下标。

M1.[初始化] 置 $`j\Leftarrow n,k\Leftarrow n-1,m\Leftarrow X[n],`$。算法执行期间有 m = X[j]= $`\max_{k\leq i\leq n} X[i]`$

M2.[是否检验完毕?] 如果 k = 0，算法终止

M3.[比较] 如果 $`X[k]\leq m`，转到 M5

M4.[改变m] 置 $`j\Leftarrow k,m\Leftarrow X[k],`$。这个 m 值是新的当前最大值

M5.[减小k] k 减 1，然后返回 M2

这个相当明显的算法看起来也许很平常，无须考虑仔细分析，但是，它其实唔唔充分展示可以用于更复杂的算法的研究途径。

在计算机程序设计中，算法分析是非常主要的，因为对于一种应用通常有若干可供使用的算法，希望知道哪个算法是最佳的。

算法 M 需要固定的存储空间，所以仅分析执行它所需的时间。为此计算每一步执行的次数

算法步号 | 执行次数
| :-: | :-: |
M1 | 1
M2 | n
M3 | n-1
M4 | A
M5 | n-1

只要知道每一步执行的次数，就可以确定它在特定计算机上的执行时间。

在上面的算法各步执行的次数表中，除量 A 之外，每个数都是已知的，而 A 是我们必须改变当前最大值的次数。为了完成分析，来讨论 A 这个有趣的量。

分析 A 时，通常要求 A 的最小值， A 的最大值， A 的平均值以及 A 的标准差。

A的最小值为 0，此时有
```math
X[n] = \max_{1\leq i\leq n} X[i]
```
最小值为 n-1，此时有
```math
X[1]  > X[2] > \cdots > X[n]
```
因此平均值介于 0 和 n-1 之间。平均值等于 $`\frac{1}{2}n`$ 吗？等于 $`\sqrt{n}`$ 吗？为了回答这个问题，需要定义平均值的含义。而为了正确的定义平均值，对于输入数据 $`X[1],X[2], \cdots,X[n]`$ 的性质必须做某些假定。假定 X[k] 两两取值不同，并且这些值的 n! 排列都是等可能的。

算法 M 的性能不依赖于 X[k] 的精确值，而只与它们的大小顺序有关。例如：

状态 | A值 | 状态 | A值 | 
| :-: | :-: | :-: | :-: |
X[1]< X[2] < X[3] | 0 | X[2]< X[3] < X[1] | 1
X[1]< X[3] < X[2] | 1 | X[3]< X[1] < X[2] | 1
X[2]< X[1] < X[3] | 0 | X[3]< X[2] < X[1] | 2

当 n = 3 时，A 的平均值为 5/6。

显而易见，可以取 $`X[1],X[2], \cdots,X[n]`$ 为  $`1,2, \cdots,n`$ 按某个顺序的排列，按假定，把这样的 n! 种排列视为等可能的。A 取 k 值的概率为
```math
p_{nk} = (满足 A = k 的 n 元排列数)/n!  \qquad (1)
```
例如，从上面的表可得 $`p_{30}=\frac{1}{3}, p_{31}=\frac{1}{2}, p_{32}=\frac{1}{6}`$

照例把 _平均值_ (“均值” 或 “期望值”) 定义为：
```math
A_n = \sum_k kp_{nk} \qquad (2)
```
把方差 $`V_n`$ 定义为 $`(A-A_n)^2`$ 的平均值，因此
```math
V_n = \sum_k (k-A_n)^2 p_{nk} = \sum_k k^2 p_{nk} - 2A_n\sum_k kp_{nk} + A_n^2\sum_k p_{nk}
```
```math
= \sum_k k^2p_{nk} -2A_nA_n + A_n^2 = \sum_k k^2p_{nk} - A_n^2. \qquad (3)
```
最后，把标准差 $`\sigma_n`$ 定义为 $`\sqrt{V_n}`$

标准差 $`\sigma_n`$ 的意义：
- 对于所有 $`r\geq 1`$，A 落在其平均值的 $`r\sigma_n`$ 邻域以外的概率小于 $`1/r^n`$
- 例如， $`|A-A_n|>2\sigma_n`$ 的概率小于 1/4
  证明：令 p 为所述概率。于是如果 p>0，那么 $`(A-A_n)^2`$ 的平均值大于 $`p\cdot(r\sigma_n)^2+(1-p)\cdot 0`$
  即，$`V_n\geq pr^2V_n`$. 证毕
  这一关系式通常成为切比雪夫不等式，虽然它其实是由边奈美发现的

可以通过确定概率 $`p_{nk}`$ 来测定 A 的特性。不难用归纳法进行计算：按照等式(1)，需要计算满足 A = k 的 n 元排列数。令此数为 $`P_{nk}=n!p_{nk}`$

考虑关于 {1,2,...,n} 的所有排列 $`x_1x_2\cdot x_n`$，见1.2.5节。如果 $`x_1=n`$，那么 A 的值比它对 $`x_2\cdot x_n`$ 得到的值大 1；如果 $`x_1\neq n`$，那么 A 值与它对 $`x_2\cdot x_n`$ 得到的值完全相同。因此求出 $`P_{nk}=P_{(n-1)(k-1)} + (n-1)P_{(n-1)k}`$，等价于：
```math
p_{nk} = \frac{1}{n}p_{(n-1)(k-1)} + \frac{n-1}{n}p_{(n-1)k}.   \qquad (4)
```
如果给出初始条件
```math
p_{1k} = \sigma_{0k}; p_{nk}=0 如果 k < 0.   \qquad (5)
```
则可由上式确定 $`p_{nk}`$.

利用生成函数，可以获得关于 $`p_{nk}`$ 的信息，令
```math
G_n(z) = p_{n0} + p_{n1}z + \cdots = \sum_kp_{nk}z^k.  \qquad (6)
```
知道 $`A\leq n-1`$，所以对很大的 k 值有 $`p_{nk}=0`$；因此 $`G_n(z)`$ 其实是一个多项式，只是为了方便把它写成无限和。

从等式(5)可得 $`G_1(z)=1`$ ，从式(4)可得
```math
G_n(z) = \frac{z}{n}G_{n-1}(z) + \frac{n-1}{n}G_{n-1}(z) = \frac{z+n-1}{n}G_{n-1}(z) .  \qquad (7)
```
现在可以看出：
```math
G_n(z) = \frac{z+n-1}{n}G_{n-1}(z) =  \frac{z+n-1}{n}\frac{z+n-2}{n-1}G_{n-2}(z) = \cdots
```
```math
= \frac{1}{n!}(z+n-1)(z+n-2) \cdots (z+1)
```
```math
= \frac{1}{z+n} \binom{z+n}{n}.  \qquad (8)
```
所以 $`G_n(z)`$ 实质上是一个二项式系数。

这个函数出现在上一小节的等式1.2.9-(27) 中，当时
```math
G_n(z) = \frac{1}{n!} \sum_k \begin{bmatrix}n\\k\end{bmatrix}z^{k-1},
```
所以 $`p_{nk}`$ 可以通过斯特林数表示
```math
p_{nk} = \begin{bmatrix}n\\k+1\end{bmatrix}/n!  \qquad (9)
```

现在只需要把 $`p_{nk}`$ 的值插入等式(2)和(3)，求出要求的平均值。事实上，很少能显式的确定概率 $`p_{nk}`$。在多数问题中，知道生成函数 $`G_n(z)`$，但是对与实际的概率知之甚少。重要的事实在于，_能够从生成函数本身轻而易举的确定均值和方差_。

为了看出这一点，假定有一个生成函数，它的系数表示概率：
```math
G(z) = p_0 + p_1z + p_2z^2 + \cdots,
```
其中 $`p_k`$ 是某个事件取 k 值的概率。希望计算均值和方差
```math
mean(G) = \sum_kkp_k, var(G)=\sum_kk^2-(mean(G))^2  \qquad (10)
```
利用微积分，不难发现如何求这两个值。注意到
```math
G(1)=1 \qquad (11)
```
因为 $`G(1)=p_0+p_1+p_2+\cdots`$ 是所有可能的概率值和。同样由 $`G'(z)=\sum_kkp_kz^{k-1},`$，有
```math
mean(G) = \sum_kkp_k = G'(1)  \qquad (12)
```
最后再次利用微积分，得到
```math
var(G)= G''(1) + G'(1) -G'(1)^2  \qquad (13)
```
等式(12)(13)通过生成函数给出所求的均值和方差的表达式

在例题中，希望计算 $`G'_n(1)=A_n`$。从等式(7)得到：
```math
G'_n(z) = \frac{1}{n}G_{n-1}(z) + \frac{z+n-1}{n}G'_{n-1}(z);
```
```math
G''_n(1) = \frac{1}{n} + G'_{n-1}(1);
```
再由初始条件 $`G'_1(1)=0`$ 求出
```math
A_n = G''_n(1) =  H_n-1 \qquad (14);
```
这是所求的执行 M4 步的平均次数。当 n 很大时，它近似等于 $`\ln n`$

> 注 A+1 的 r 阶矩，即 $`\sum_k(k+1)^rp_{nk}`$，等于 $`[z^n](1-z)^{-1}\sum_k {r\brace k}(\ln\frac{1}{1-z})^k`$，近似值为 $`(\ln n)^r`$。
A 的分布研究 皮特.罗斯 费里德里克.福斯特 艾伦斯.图尔

可以用同样的方式计算方差 $`V_n`$。首先，提出一个重要的简化结果。

__定理 A__
令 G 和 H 是满足 G(1)=H(1)=1 的两个生成函数。如果 mean(G) 和 var(G) 按照式 (12) 和 (13) 定义，有
```math
mean(GH) = mean(G) + mean(H); var(GH) = var(G) + var(H).  \qquad (15);
```
它说明生成函数之积的均值与方差可以化为均值之和与方差之和。

令 $`Q_n(z)=(z+n-1)/n`$，有 $`Q'_n(1)=1/n,Q''_n(1)=0`$。因此
```math
mean(Q_n) = \frac{1}{n}; var(Q_n) = \frac{1}{n} + \frac{1}{n^2}.
```
最后，由 $`G_n(z)=\prod_{k=2}^nQ_k(z)`$，推出
```math
mean(G_n) = \sum_{k=2}^n mean(Q_k) = \sum_{k=2}^n\frac{1}{k} = H_n - 1,
```
```math
var(G_n) = \sum_{k=2}^n var(Q_k) = \sum_{k=1}^n(\frac{1}{n}-\frac{1}{n^2}) = H_n - H_n^{(2)}.
```
综上所述，已经求出要求的与量 A 有关的统计值：
```math
A =(\min0, ave H_n-1, \max n-1, dev \sqrt{H_n-H_n^{(2)}}) .  \qquad (16)
```
本书将一直使用 中的记号描述其他概率量的统计特性。

考虑几道简单的概率问题。首先想到的是掷硬币问题：假定掷一枚硬币 n 次，每一次得到正面朝上的概率为 p，那么正面朝上的平均次数是多少？标准差是多少？

考虑硬币两面不均匀的情况，不做 $`p=\frac{1}{2}`$ 的假定。这样问题更有趣味，何况实际的硬币本来就都是不均匀的。

令 $p_{nk}`$ 为掷 n 次硬币出现 k 次正面的概率，并且令 $`G_n(z)`$ 为对应的生成函数，有
```math
p_{nk}=pp_{(n-1)(k-1)} + qp_{(n-1)k},  \qquad (17)
```
其中 q=1-p 是背面朝上的概率。同以前一样，从等式 出发，证明 $`G_n(z)=(q+pz)G_{n-1}(z)`$，进而从明显的初始条件 $`G_1(z)=q+pz`$ 得到
```math
G_n(z)=(q+pz)^n.  \qquad (18)
```
因此，有定理 A，
```math
mean(G_n)=n mean(G_1) = pn. var(G_n)=n var(G_1) = (p-p^2)n=nqn. 
```
所以，对于正面的次数，得到统计量
```math
(\min 0, ave pn, max n, dev \sqrt{pqn}).  \qquad (19)
```
当标准差同 $`\sqrt{n}`$ 成正比，而且最大值与最小值之差同 n 成正比时，可以认为状态关于平均值是 “稳定” 的

来处理一个更简单的问题。假定再某个过程中获得数值 $`1,2,\cdots,n`$ 的概率是相等的。这种情况的生成函数为
```math
G(z)= \frac{1}{n}z+\frac{1}{n}z^2+\cdots + \frac{1}{n}z^n=\frac{1}{n}\frac{z^{n+1}-z}{z-1}. \qquad (20)
```
经过某些比较困难的计算之后，求出
```math
G'(z)= \frac{nz^{n+1}-(n+1)z^n + 1}{n(z-1)^2}. 
```
```math
G''(z)= \frac{n(n-1)z^{n+1}-2(n+1)(n-1)z^n + n(n+1)z^{n-1}-2}{n(z-1)^3}. 
```
要想计算均值和方差，需要知道 $`G'(1)`$ 和 $`G''(1)`$；但是代入 z=1 时，得到的这两个等式变成 0/0 型不定式。因此，必须求当 z 趋近 1 时的极限，而这并不轻松。

幸好可以采用一种更简单得多的处理方法。有泰勒定理，有
```math
G(1+z)= G(1)+G'(1)z+\frac{G''(1)}{2!}z^2+\cdots, \qquad (21)
```
因此只需再生成函数 中用 z+1 替换 z，直接读出系数：
```math
G(1+z)= \frac{1}{n}\frac{(1+z)^{n+1}-1-z}{z}=1+\frac{n+1}{2}z+\frac{(n+1)(n-1)}{6}z^2+\cdots
```
由此推出 $`G'(1)=\frac{1}{2}(n+1), G''(1)=\frac{1}{3}(n+1)(n-1)`$。这个均匀分布的统计量为
```math
(min 1, ave \frac{n+1}{2}, max n, dev \sqrt{\frac{(n+1)(n-1)}{12}}) \qquad (22)
```
此时，偏差近似等于 0.289n，表示状态明显不稳定。

最后来证明定理 A。把结论与古典概率论联系起来。设 X 是一个仅取非负整数值的随机变量，X=k 的概率为 $`p_k`$。这种情况下，$`G(z)=p_0+p_1z+p_2z^2+\cdots`$ 称为 X 的 _概率生成函数_， $`G(e^{it})=p_0+p_1e^{it}+p_2e^{2it}+\cdots`$ 习惯上称为这个分布的 _特征函数_。由这样的两个生成函数之积给出的分布称为两个分布的卷积(convolution)，它代表分别具有相应分布的两个独立随机变量之和。

随机变量 X 的均值或平均值通常称为它的 期望值，记作 EX。于是，X 的方差是 $`EX^2-(EX)^2`$。使用这个记号，在 X 仅取非负整数值的情况下，X 的概率生成函数 $`G(z)=E z^X`$，也就是 $`z^X`$ 的期望值。

同样如果 X 是一个或者是真或者是假的命题，使用弗森记号 (式1.2.3-(16)) ，X 为真的概率是 $`Pr(X)=E[X]`$。

均值和方差只不过是索瓦尔德蒂勒于 1889 年发现的所谓 _半不变量_ 或者 _累积量_ 中的两个量。半不变量 $`\mathcal{k_1,k_2,k_3,\cdots}`$ 由规则
```math
\frac{k_1t}{1!}+\frac{k_2t^2}{2!}+\frac{k_3t^3}{3!}+\cdots=\ln G(e^t) \qquad (23)
```
定义，有
```math
k_n=\frac{d^n}{dt^n}\ln G(e^t)\Big|_{t=0},
```
特别地，因为 $`G(1)=\sum_k p_k=1`$，有
```math
k_1=\frac{e^tG'(e^t)}{G(e^t)}\Big|_{t=0} = G'(1),
```
以及
```math
k_2=\frac{e^{2t}G''(e^t)}{G(e^t)}+\frac{e^tG'(e^t)}{G(e^t)}-\frac{e^{2t}G'(e^t)^2}{G(e^t)^2}\Big|_{t=0} = G''(1)+G'(1)-2G'(1)^2.
```
由于半不变量是通过生成函数的对数定义的，定理 A 显然成立，而且实际上可以推广定理 A，使之适用于所有的半不变量。

正态分布的的半不变量除平均值和方差之外全部为 0。在生态分布中，可以大大加强切比雪夫不等式：正态分布的随机值同均值之差小于标准差的概率为：
```math
\frac{1}{\sqrt{2\pi}}\int_{-1}^{+1} e^{-t^2/2}dt.
```
所占比例约为 68.268949213709%。两者之差小于两倍标准差的概率大约为 95.449973610364%，小于三倍标准差的概率大约为 99.730020393674%。由等式 (8) 和 (18) 定义的分布当 n 很大时为近似正态分布

如果一个随机变量不大可能偏离其均值太多，则经常需要确切知道这样的信息。有两个极为简单然而很有效的公式可以方便估计这样的概率，这两个公式称为 _尾概率不等式_。如果 X 的概率生成函数是 G(z)，那么
```math
Pr(X\leq r)\leq x^{-r}G(x) if 0 < x \leq 1;\qquad (24)
```
```math
Pr(X\geq r)\leq x^{-r}G(x) if x \geq 1. \qquad (25)
```
这两个不等式很容易证明：如果 $`G(z)=p_0+p_1z+p_2z^2+\cdots`$，那么当 $`0 < x \leq 1`$ 时，有
```math
Pr(X\leq r)=p_0+p_1+\cdots+p_{\lfloor r\rfloor}\leq x^{-r}p_0+x^{1-r}p_1+\cdots+x^{\lfloor r\rfloor -r}p_{\lfloor r\rfloor}\leq x^{-r}G(x);
```
而当 $` x \geq 1`$ 时，有
```math
Pr(X\leq r)=p_{\lceil r\rceil}+p_{\lceil r\rceil +1} +\cdots\leq x^{\lceil r\rceil -r}p_{\lceil r\rceil}+x^{\lceil r\rceil+1-r}p_{\lceil r\rceil+1}+\cdots\leq x^{-r}G(x);
```
选择 x 的值使不等式 (24) 和 (25) 的右端达到或接近最小值，左端通常可以获得非常接近真实尾概率的上界。

习题21-23说明几种重要情形的尾概率不等式。这些不等式是一个一般原理的特例，该原理最早见于安德雷科尔莫哥洛夫的著作：如果 $`f(t) \geq s > 0`$ 对于所有 $`t \geq r`$ 成立， 对于所有在随机变量 X 定义域内的 t 成立，那么只要 Ef(x) 存在，就有 $`Pr(x\geq r)\1eq s^{-1}Ef(x)`$。当 $`f(t)=x^t`$ 且 $`s=x^r`$ 时，得到式(25)。
