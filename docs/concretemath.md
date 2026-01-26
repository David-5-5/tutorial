## 2.2 和以及递归

把形式类似：
```math
a_nT_n = b_nT_{n-1} + c_n \qquad (2.9)
```
的任何递归化为和的俄一般技巧的特殊情形，用求和因子 $s_n$ 乘两边：
```math
s_na_nT_n = s_nb_nT_{n-1} + s_nc_n 
```

巧妙的选择因子 $s_n$ 可使：
```math
s_nb_n = s_{n-1}a_{n-1}
```
记 $S_n = s_na_nT_n$，则得到一个和的递归：
```math
S_n = S_{n-1} + s_nc_n
```
因此
```math
S_n = s_0a_0T_0 + \sum_{k=1}^{n}s_kc_k = s_1b_1T_0 + \sum_{k=1}^{n}s_kc_k
```
原来递归 (2.9) 的解为：
```math
T_n = \frac{1}{s_na_n}(s_1b_1T_0 + \sum_{k=1}^{n}s_kc_k)  \qquad (2.10)
```
找到真正的 $s_n$，展开关系 $sn = s_{n-1}a_{n-1}/b_n$
```math
s_n = \frac{a_{n-1}a_{n-2}\cdots a_1}{b_nb_{n-1}\cdots b_2} \qquad (2.11)
```
---
快速分类所用的比较的平均次数满足递归：
```math
\begin{aligned}
C_0 &= 0 \\
C_n &= n + 1 + \frac{2}{n}\sum_{k=0}^{n-1}C_k \qquad (2.12)
\end{aligned}
```

首先把除法去掉，两边乘以 n，得到关系式：
```math
nC_n = n^2 + n + 2\sum_{k=0}^{n-1}C_k , (n > 0);
```

用 n-1 来代替 n，则
```math
(n-1)C_{n-1} = (n-1)^2 + (n-1) + 2\sum_{k=0}^{n-2}C_k , (n-1 > 0);
```
两式相减，$\sum$ 符号不再出现，得到：

```math
nC_n - (n-1)C_{n-1} = 2n + 2C_n , (n > 1);
```

原来的递归式简化为：
```math
\begin{aligned}
C_0 &= 0 \\
nC_n &= (n + 1)C_{n-1} + 2n, (n > 0);
\end{aligned}
```
此递归式具有式 (2.9) 的形式，其中 $a_n = n, b_n = n+1, c_n = 2n$，根据 (2.11) 式，得到：

```math
s_n = \frac{a_{n-1}a_{n-2}\cdots a_1}{b_nb_{n-1}\cdots b_2} = 
\frac{(n-1)\cdot(n-2)\cdots\cdot 1}{(n+1)\cdot n\cdots\cdot 3} = 
\frac{2}{(n+1)n}
```

依照式 (2.10) ，解就是：
```math
C_n = 2(n+1)\sum_{k=1}^n\frac{1}{k+1}
```
带入调和级数 $H_n$，当应用于 n 个随机次序的数据项时，快速分类所用的平均比较次数为
```math
C_n = 2(n+1)H_n - 2n \qquad (2.14)
```

## 2.3 和的操作

和操作的成功的关键是把一个 $\sum$ 改变成另一个较简单或更接近某个目标的能力。
设 K 是任何有限的整数集合，可用三哪个简单的规则来变化 K 的元素上的和：

- 分配律 distributive law
```math
\sum_{k\in K}ca_k = c\sum_{k\in K}a_k \qquad (2.15)
```

- 结合律 associative law
```math
\sum_{k\in K}(a_k + b_k) = \sum_{k\in K}a_k + \sum_{k\in K}b_k \qquad (2.16)
```

- 交换律 commutative law
```math
\sum_{k\in K}a_k = \sum_{p(k)\in K}a_{p(k)} \qquad (2.17)
```
重要的是牢记一般交换律中的函数 (2.17) 中的函数 p(k) 假设为所有整数中的一种排列。换句话说，对于每个整数 n，恰好有就有一个整数 k 使得 p(k) = n。否则交换律不成立。

利用交换律证明一个算术级数的一般形式：
```math
S = \sum_{0\le k\le n}(a + bk)
```
根据交换律，用 n-k 替代 k，得到
```math
S = \sum_{0\le n-k\le n}(a + b(n-k)) = \sum_{0\le k\le n}(a + bn - bk)
```
利用交换律可把这两个方程相加：
```math
\begin{aligned}
2S &= \sum_{0\le k\le n}((a + bk)+(a + bn - bk)) = \sum_{0\le k\le n}(2a + bn) \\
2S &= (2a+bn) \sum_{0\le k\le n} 1 = (2a + bn) (n+1)
\end{aligned}
```

两边各除以 2, 证明了：
```math
S = \sum_{k=0}^n(a + bk) = (a+\frac{1}{2}bn)(n+1)
```

---

艾弗森(Iverson)约定
```math
\sum_{k\in K}^na_k + \sum_{k\in K'}^na_k = \sum_{k\in K\cap K'}^na_k + \sum_{k\in K\cup K'}^na_k \qquad (2.20)
```
这是根据下列的一般公式
```math
\sum_{k\in K}^na_k = \sum_ka_k[k\in K] \qquad (2.21)
```
和
```math
[k\in K] + [k\in K] = [k\in K\cap K'] +  [k\in K\cup K'] \qquad (2.22)
```

得出的。典型的把规则 (2.20) 用到结合两个几乎不相交的指标集合，如同：
```math
\sum_{k=1}^ma_k + \sum_{k=m}^na_k = a_m + \sum_{k=1}^na_k, for 1\le m\le n;
```

或者从和中分出一项：
```math
\sum_{0\le k\le n}a_k = a_0 + \sum_{1\le k\le n}a_k, for n\ge 0; \qquad (2.23)
```

此分出一项的操作是摄动法的基础 (perturbation method)，它允许计算一个和为闭形式。想法从一个未知和 $S_n$ 开始，然后以两种方式重写 $S_{n+1}$，通过既分出它的第一项和最后一项：

```math
\begin{aligned}
S_n + a_{n+1} &= \sum_{0\le k\le n+1}a_k = a_0 + \sum_{1\le k\le n}a_k \\
              &= a_0 + \sum_{1\le k+1\le n}a_{k+1} \\
              &= a_0 + \sum_{0\le k\le n}a_{k+1} \qquad (2.24)
\end{aligned}
```

现在在此最后和上处理，且尝试由 $S_n$ 表达它。若成功，则可获得一个方程，它的解是我们所要找的和。例如，用此方法来求出一般几何级数的和，
```math
S_n = \sum_{0\le k\le n}ax^k .
```

式 (2.24) 中的一般摄动方法
```math
S_n + ax^{n+1} = ax^0 + \sum_{0\le k\le n}ax^{k+1} .
```

根据分配律，右边的和是 $x\sum_{0\le k\le n}ax^k = xS_n$，因此 $S_n + ax^{n+1} = a + xS_n$，这样解出 $S_n$ 得到
```math
\sum_{k=0}^nax^k = \frac{a-ax^{n+1}}{1-x}, 
 for\ x\ne 1 \qquad (2.25)
```

让我们在一个稍困难的和上试用摄动技巧
```math
S_n = \sum_{0\le k\le n}k2^k .
```

按照式 (2.24) 有
```math
S_n + (n+1)2^{n+1} = \sum_{0\le k\le n}(k+1)2^{k+1} .
```
右边的和借助结合律分为两个和
```math
\sum_{0\le k\le n}k2^{k+1} + \sum_{0\le k\le n}2^{k+1} 
```
第一个和是 $2S_n$。另一个和是几何级数，根据式 (2.25)，它等于 $(2-2^{n+2})/(1-2) = 2^{n+2} - 2$。所以我门得到 $S_n + (n+1)2^{n+1} = 2S_n + 2^{n+2} - 2$，而代数计算得到：
```math
\sum_{0\le k\le n}k2^k = (n-1)2^{n+1} + 2 .
```

用 x 替换 2,相似推导给出方程
```math
S_n + (n+1)x^{n+1} = xS_n + (x - x^{n+2})/ (1 - x) .
```
因此我们能推出
```math
\sum_{0\le k\le n}kx^k = \frac{x- (n+1)x^{n+1} + nx^{n+2}}{(1-x) ^2} . \qquad (2.26)
```

我们能以完全不同的方法推导这个闭形式是有趣的，此方法运用了微分的基本技巧。从方程
```math
\sum_{k=0}^nx^k = \frac{1-x^{n+1}}{1-x} .
```
开始，且两边对 x 求导，得到
```math
\sum_{k=0}^nkx^{k-1} = \frac{(1-x)(-(n+1)x^n)+1-x^{n+1}}{(1-x)^2} = \frac{1-(n+1)x^n+nx^{n+1}}{(1-x)^2} .
```
因为和的求导是它各项求导的和。


## 2.4 多重和

一个和的项可能由两个或多个指标来指定，而不仅仅是一个指标指定。
```math
\begin{aligned}
\sum_{1\le j,k\le 3}a_jb_k &= a_1b_1 + a_1b_2 + a_1b_3\\
              &+ a_2b_1 + a_2b_2 + a_2b_3 \\
              &+ a_3b_1 + a_3b_2 + a_3b_3 
\end{aligned}
```

对于这样的和，用相同的表示法和方法，就像对一个指标和所做的那样。因此若 P(j,k) 是 j 和 k 的一个性质，则所有项 $a_{j, k}$ 的和使得 P(j,k) 是真能以两种方式写出，一种用艾弗森(Iverson)约定，且在所有整数对 j 和 k 上求和
```math
\sum_{P(j,k)}a_jb_k = \sum_{j,k}a_jb_k[P(j,k)].
```
虽然求和指标多于一个，仅需一个 $\sum$ 符合。

当讨论到几个和的总和，也有必要用两个 $\sum$，例如：
```math
\sum_j\sum_ka_jb_k[P(j,k)] = \sum_j(\sum_ka_jb_k[P(j,k)]) .
```

交换求和次序的基本定律，它推广了结合律 (2.16)
```math
\sum_j\sum_ka_jb_k[P(j,k)] = \sum_{P(j,k)}a_jb_k = \sum_k\sum_ja_jb_k[P(j,k)] \qquad (2.27) .
```
我们开始给 9 项和提供了一种处理二重和的好的说明。
```math
\begin{aligned}
\sum_{1\le j,k\le 3}a_jb_k &= \sum_{j,k}a_jb_k[1\le j,k\le 3] \\
    &= \sum_{j,k}a_jb_k[1\le j\le 3][1\le k\le 3] \\
    &= \sum_j\sum_ka_jb_k[1\le j\le 3][1\le k\le 3] \\
    &= \sum_ja_j[1\le j\le 3]\sum_kb_k[1\le k\le 3] \\
    &= \sum_ja_j[1\le j\le 3](\sum_kb_k[1\le k\le 3]) \\
    &= (\sum_ja_j[1\le j\le 3])(\sum_kb_k[1\le k\le 3]) \\
    &= (\sum_{j=1}^3a_j)(\sum_{k=1}^3b_k) 
\end{aligned}
```

此推导方法能用来证明一般的分配律
```math
\sum_{j\in J,k\in K}a_jb_k = (\sum_{j\in J}a_j)(\sum_{k\in K}b_k)  \qquad (2.28) .
```
对所有指标集 J 和 K 成立。

交换求和次序的基本定律式 (2.27) 有许多变形，当要限制的指标的范围而不是在所有的整数 j 和 k 上求和时它就出现。这些变形有两种形式，第一种形式：
```math
\sum_{j\in J}\sum_{k\in K}a_{j,k} = \sum_{j\in J, k\in K}a_jb_k = \sum_{k\in K}\sum_{j\in J}a_{j,k}  \qquad (2.29) .
```
以另一种形式写出的式 (2.27)，当 j 和 k 的范围彼此独立时应用此定律。

当内层和的范围依赖于外层和的指标变量时应用它：
```math
\sum_{j\in J}\sum_{k\in K(j)}a_{j,k} = \sum_{k\in K'}\sum_{j\in J'(k)}a_{j,k}.  \qquad (2.30) 
```

这里一定要以这样一种方式把集合 J, K(j), K‘ 和 J‘(k) 联系起来，即
```math
[j \in J][k\in K(j)] = [k\in K'][j\in J'(k)]
```
像这样的因子分解原则上总是可能的。一种特别有用的因子分解：
```math
[1\le j\le n][j\le k\le n] = [1\le j\le k\le n] = [1\le k\le n][1\le j\le k]. \qquad (2.31) 
```

这个艾弗森(Iverson)方程允许写成：
```math
\sum_{j=1}^n\sum_{k=j}^na_{j,k} = \sum_{1\le j\le k\le n}a_{j,k}  = \sum_{k=1}^n\sum_{j=1}^ka_{j,k}. \qquad (2.32) 
```

把这些想法应用到一个有用的例子上去，考虑 $n^2$ 个 $a_ja_k$ 的数组
```math
\begin{bmatrix}
a_1a_1 & a_1a_2 & a_1a_3 & \cdots & a_1a_n \\
a_2a_1 & a_2a_2 & a_2a_3 & \cdots & a_2a_n \\
a_3a_1 & a_3a_2 & a_3a_3 & \cdots & a_3a_n \\
\vdots & \vdots & \vdots &  & \vdots \\
a_na_1 & a_na_2 & a_na_3 & \cdots & a_na_n \\
\end{bmatrix}
```
我们的目标是求出矩阵的主对角线或主对角线上的所有元素之和
```math
S_\triangle = \sum_{1\le j\le k\le n}a_{j,k} =  
    \sum_{1\le k\le j\le n}a_{k,j} +
    \sum_{1\le k\le j\le n}a_{j,k} = S_\triangledown, \ a_{j,k} = a_{k,j}
```


我们得到
```math
\begin{aligned}
2S_\triangle &= S_\triangle + S_\triangledown = 
    \sum_{1\le k, j\le n}a_{k,j} + 
    \sum_{1\le k=j\le n}a_{j,k} \\
    &= (\sum_{k=1}^na_k)^2 + \sum_{k=1}^na_k^2
\end{aligned}
```

因此得到
```math
S_\triangle = \frac{1}{2}((\sum_{k=1}^na_k)^2 + \sum_{k=1}^na_k^2)
```

另一个二重和，当交换 j 和 k 时，也有对称性:
```math
\begin{aligned}
S &= \sum_{1\le j< k\le n}(a_k-a_j)(b_k-b_j) \\
  &= \sum_{1\le k< j\le n}(a_j-a_k)(b_j-b_k) = \sum_{1\le k< j\le n}(a_k-a_j)(b_k-b_j)
\end{aligned}
```

利用等式
```math
[1\le j< k\le n] + [1\le k< j\le n] = [1\le j, k\le n] - [1\le j=k\le n]
```
得出：
```math
2S= \sum_{1\le j,k\le n}(a_k-a_j)(b_k-b_j) - \sum_{1\le j=k\le n}(a_k-a_j)(b_k-b_j)
```

上式中，第二项的和为 0；第一项可以分为四个和：
```math
\begin{aligned}
& \sum_{1\le j,k\le n}a_jb_j - \sum_{1\le j,k\le n}a_jb_k - \sum_{1\le j,k\le n}a_kb_j + \sum_{1\le j,k\le n}a_kb_k \\
&= 2\sum_{1\le j,k\le n}a_kb_k - 2\sum_{1\le j,k\le n}a_jb_k \\
&= 2n\sum_{1\le k\le n}a_kb_k - 2(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) \\
\end{aligned}
```

回到讨论的地方，式子两边同除以 2:
```math
(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) = n\sum_{1\le k\le n}a_kb_k - \sum_{1\le j< k\le n}(a_k-a_j)(b_k-b_j) \qquad (2.34)
```
此等式产生了作为一种特殊情形的切比雪夫单调不等式(Chebyshev's monotonic inequalities):

```math
(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) \le n\sum_{1\le k\le n}a_kb_k, if\ a_1\le\cdots\le a_n\And b_1\le\cdots\le b_n;
```
```math
(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) \ge n\sum_{1\le k\le n}a_kb_k, if\ a_1\le\cdots\le a_n\And b_1\gt\cdots\gt b_n;
```

多重求和于单个和中改变求和的指标的一般操作有一种有趣的连续，如果 p(k) 是整数的任何排列，有交换律知道：
```math
\sum_{k\in K}a_k = \sum_{p(k)\in K}a_{p(k)},
```

若 p(k) 为整数的任意一个排列，那么当我们将 k 替换为 f(j), 其中 f 为任意函数:
```math
f: J\to K
```

取整数 $j\in J$ 映射为整数 $f(j)\in K$，那么此时的情况又将如何？指标替换的通用公式为:
```math
\sum_{j\in J}a_{f(j)} = \sum_{k\in K}a_k\#f^-(k), \qquad (2.35)
```

其中 #$f^-(k)$ 表明集合：
```math
f^-(k) = \{j|f(j) = k\}
```
中元素的个数，也就是使得 f(j) 等于 k 的 $j\in J$ 的值的个数。

由于 $\sum_{j\in J}[f(j)=k]=$#$f^-(k)$，通过交换求和的次序容易证明式 (2.35)
```math
\sum_{j\in J}a_{f(j)} = \sum_{j\in J, k\in K}a_k[f(j)=k] = \sum_{k\in K}a_k\sum_{j\in J}[f(j)=k]
```

在 f 是 J 和 K 之间的一个 1-1 对应的特殊情形中，对于所有 k 有 #$f^-(k)=1$，一般公式 (2.35) 化为：
```math
\sum_{j\in J}a_{f(j)} = \sum_{f(j)\in K}a_{f(j)} = \sum_{k\in K}a_k
```

---
看一看实际数的一个多重和：
```math
S_n = \sum_{1\le j < k \le n}\frac{1}{k-j}
```
例如  $S_1=0; S_2=1; S_3=\frac{1}{2-1}+\frac{1}{3-1}+\frac{1}{3-2} = \frac{5}{2} $

计算一个双重和的标准方法是先对 j 或先对 k 求和，所有讨论两种选取
```math
\begin{aligned}
S_n &=  \sum_{1\le k \le n}\sum_{1\le j < k}\frac{1}{k-j} &\qquad summing\ first\ on\ j \\
&=  \sum_{1\le k \le n}\sum_{1\le k-j < k}\frac{1}{j} &\qquad replace\ j\ by\ k - j \\
&=  \sum_{1\le k \le n}\sum_{0< j\le k-1}\frac{1}{j} &\qquad simplifying\ the\ bounds\ of\ j \\
&=  \sum_{1\le k \le n}H_{k-1} &\qquad by (2.13) \\
&=  \sum_{1\le k+1 \le n}H_k &\qquad replace\ k\ by\ k+1 \\
&=  \sum_{0\le k < n}H_k &\qquad simplifying\ the\ bounds\ of\ k
\end{aligned}
```

但是我们不知道如何得到调和数的和的闭形式。若尝试先对 k 求和，则得到：
```math
\begin{aligned}
S_n &=  \sum_{1\le j \le n}\sum_{j< k \le n}\frac{1}{k-j} &\qquad summing\ first\ on\ k \\
&=  \sum_{1\le j \le n}\sum_{j\le k+j \le n}\frac{1}{k} &\qquad replace\ k\ by\ k + j \\
&=  \sum_{1\le j \le n}\sum_{0< k\le n-j}\frac{1}{k} &\qquad simplifying\ the\ bounds\ of\ k \\
&=  \sum_{1\le j \le n}H_{n-j} &\qquad by (2.13) \\
&=  \sum_{1\le n-j \le n}H_j &\qquad replace\ j\ by\ n-j \\
&=  \sum_{0\le j < n}H_j &\qquad simplifying\ the\ bounds\ of\ j
\end{aligned}
```
又回到相同的绝境。

但是有另一种方法来处理，若在决定把 $S_n$ 化为和的和之前用 k+j 替换 k：
```math
\begin{aligned}
S_n &=  \sum_{1\le j < k \le n}\frac{1}{k-j} &\qquad recopying\ the\ given\ sum \\
&=  \sum_{1\le j < k+j \le n}\frac{1}{k} &\qquad replace\ k\ by\ k + j \\
&=  \sum_{1\le k \le n}\frac{n-k}{k} &\qquad the\ sum\ on\ j\ is\ trivial \\
&=  \sum_{1\le k \le n}\frac{n}{k} - \sum_{1\le k \le n}1 &\qquad associative\ law \\
&=  n\sum_{1\le k \le n}\frac{1}{k} - n &\qquad by\ gosh \\
&=  nH_n - n &\qquad by (2.13) 
\end{aligned}
```
我们找到了 $S_n$。把它和冒失的开端结合起来，作为一个额外的结果：
```math
\sum_{0\le k < n}H_k = nH_n - n. \qquad (2.36)
```



## 2.5 一般的方法
我们将尝试找前 n 个平方和的一个闭形式，称它为 $\Box_n$
```math
\Box_n = \sum_{0\le k\le n}k^2,\ for\ n \ge 0 \qquad (2.37)
```
将看到至少有 7 种不同的方法来解这个问题。

```math
\Box_n = \frac{n(n+1)(2n+1)}{6} ,\ for\ n \ge 0 \qquad (2.38)
```

- 方法1：猜测解答，用归纳法证明

等价的公式是：
```math
\Box_n = \frac{n(n+1)(n+\frac{1}{2})}{3} ,\ for\ n \ge 0 \qquad (2.39)
```

对于归纳法来说，假设 n > 0,且设当 n-1 替换 n 时，公式 (2.39) 成立，由于
```math
\Box_n = \Box_{n-1} + n^2 ,
```

得到：
```math
\begin{aligned}
3\Box_n &= n(n+1)(n+\frac{1}{2}) + 3n^2  \\
        &= (n^3 - \frac{3}{2}n^2 + \frac{1}{2}n) + 3n^2 \\
        &= (n^3 + \frac{3}{2}n^2 + \frac{1}{2}n) \\
        &= n(n+1)(n+\frac{1}{2})
\end{aligned}
```
所以无疑对所有 $n\ge 0$，公式(2.39) 确实成立。



- 方法2：摄动和
按照式 (2.24) 摄动方程：
```math
\begin{aligned}
\Box_n + (n+1)^2 &= \sum_{0\le k\le n}(k+1)^2  \\
    &= \sum_{0\le k\le n}(k^2+2k+1)\\
    &= \sum_{0\le k\le n}k^2 + 2\sum_{0\le k\le n}k \sum_{0\le k\le n}1 \\
    &= \Box_n + 2\sum_{0\le k\le n}k \sum_{0\le k\le n}1
\end{aligned}
```

$\Box_n$ 彼此消去了。偶尔摄动法产生像 $\Box_n = \Box_n$ 的结果，我们的工作白费了。另一方面，这个推导的结果并不是一点用没有，它展示了一种方法，把前 n 个整数相加为闭形式，
```math
2\sum_{0\le k\le n}k = (n+1)^2 - (n+1) ,
```

如果从整数立方的和开始，称它为 $\Box^3_n$，能否取的整数平方的一个表达式？让我们试试看。
```math
\begin{aligned}
\Box^3_n+ (n+1)^3 &= \sum_{0\le k\le n}(k+1)^3  \\
    &= \sum_{0\le k\le n}(k^3+3k^2+3k+1)\\
    &= \Box^3_n + 3\Box_n + 3\frac{(n+1)n}{2} + (n+1).
\end{aligned}
```
确实被消去，且有足够的资料来确定 $\Box_n$，而不依赖于归纳法：
```math
\begin{aligned}
3\Box_n  &= (n+1)^3 - 3\frac{(n+1)n}{2} - (n+1)  \\
    &= (n+1)(n^2 + 2n + 1 - \frac{3}{2}n - 1) \\
    &= (n+1)(n+\frac{1}{2})n.
\end{aligned}
```

- 方法3 建立所有组合部分
对于涉及 $n^2$ 的被加数，稍加推广递归式 (2.7) 也就够了。
```math
\begin{aligned}
R_0 &=  \alpha  \\
R_n &= R_{n-1} + \beta + \gamma n + \delta n^2, for\ n > 0, \qquad (2.40)
\end{aligned}
```

的解将是一般形式的解：
```math
R_n = A(n)\alpha + B(n)\beta + C(n)\gamma + D(n)\delta; \qquad (2.41)
```
且我们以及确定了 A(n) B(n) C(n)，因为当 $\delta=0$ 时，式 (2.41) 和 (2.7) 相同。若现在插入 $R_n = n^3$，发现当 $\alpha=0, \beta=1, \gamma=-3$ 时 $n^3$ 是解。因此
```math
3D(n) - 3C(n) + B(n) = n ^ 3
```
这样就确定了 D(n)。

我们对和 $\Box_n$ 感兴趣，它等于 $\Box_{n-1} + n^2$。于是，如果在式 (2.41) 中置 $\alpha=\beta=\gamma=0, \delta=1$，则取得 $\Box_n = R_n$，所以 $\Box_n = D(n)$。不需要从 B(n) 和 C(n) 计算 D(n) 的代数运算，因为已经知道了解答是什么，但是找到：
```math
3D(n) = n^3 + 3C(n) - B(n) = n^3 + 3\frac{(n+1)n}{2} - n = (n+1)(n+\frac{1}{2})n
```
将使怀疑者消除疑虑。


- 方法4 用积分替换和
在微积分中，积分可视为曲线下的面积，把接触曲线的长的小矩形加起来近似此面积。$\Box_n$ 是大小为 $1\times 1, 1\times 4, \cdots, 1\times n^2$ 的矩形面积之和，它近似等于 0 和 n 之间曲线 $f(x)=x^2$ 之下的面积。此曲线下的面积为 $\int_0^nx^2dx=n^3/3$，所有我们知道 $\Box_n$ 近似为 $n^3/3$。

用这个事实的一个方法是研究近似的误差 $E_n = \Box_n - n^3/3$。由于 $\Box_n$ 满足递归式 $\Box_n = \Box_{n-1} + n^2$ ，发现 $E_n$ 满足较简单的递归
```math
\begin{aligned}
E_n &=  \Box_n - n^3/3 =  \Box_{n-1} + n^2 - n^3/3\\
    &= E_{n-1} + (n-1)^3 + n^2 - n^3/3 \\
    &= E_{n-1} + n - 1/3
\end{aligned}
```

寻找积分近似的另一种方法是通过相加楔形误差项来找 $E_n$ 的公式。得到
```math
\begin{aligned}
\Box_n - \int_0^nx^2dx &=  \sum_{k=1}^n(k^2 - \int_{k-1}^kx^2dx)\\
    &= \sum_{k=1}^n(k^2 - \frac{k^3-(k-1)^3}{3}) = \sum_{k=1}^n(k-1/3)\\
\end{aligned}
```
不管用那一种方法，能找出 $E_n$，然后求得 $\Box_n$。


- 方法5 伸展和收缩
还有另外一种方式来找 $\Box_n$ 的闭形式，用看来较复杂的双重和来替换原来的和，如果适当的来回处理双重和，则实际上能简化它：
```math
\begin{aligned}
\Box_n &= \sum_{1\le k\le n}k^2 = \sum_{1\le j\le k\le n}k \\
    &= \sum_{1\le j\le n}\sum_{j\le k\le n}k \\
    &= \sum_{1\le j\le n} \frac{j+n}{2} (n-j+1) \\
    &= \frac{1}{2} sum_{1\le j\le n} (n(n+1) + j - j^2) \\
    &= \frac{1}{2}n^2(n+1) + \frac{1}{4}n(n+1) - \frac{1}{2}\Box_n \\
    &= \frac{1}{2}n(n+1)(n + \frac{1}{2})- \frac{1}{2}\Box_n \\
\end{aligned}
```
将单重求和转化为双重求和，乍看之下似乎是一种倒退，但实际上却是一种进步，因为它能产生更易于处理的求和形式。我们不能指望仅通过不断地化简、再化简来解决所有问题：毕竟，仅靠一味向上攀登是无法征服最高峰的。



- 方法6 用有限演算

- 方法7 用母函数







