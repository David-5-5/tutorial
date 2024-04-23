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
$$
\mu = \lceil \frac{n}{p} \rceil + \lceil \frac{n}{p^2} \rceil + \lceil \frac{n}{p^3} \rceil + ...  = \sum_{k>0}\lceil \frac{n}{p^k} \rceil
$$

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
$$
n! = \Gamma(n+1) = n\Gamma(n)
$$

后面太难了，略过........


### 1.2.6 二项式系数

从 n 个对象中选取 k 个进行排列，有 $n(n-1)\dots(n-k-1)$ 种方法，其中每个 k 元组合在这些排列中恰好出现 k！ 次。用$\binom{n}{k}$ 表示组合数。

$$
\binom{n}{k} = \frac{n(n-1)\cdots(n-k-1)}{k(k-1)\cdots1}
$$

分子 $n(n-1)\cdots(n-k-1)$ 表示从 n 个对象中选取 k 个进行排列的数量
分子 $k(k-1)\cdots1$ 表示每个 k 元组合在这些排列中恰好出现 k! 次

对于所有实数 r 和所有整数 k ，我们定义符号 $\binom{r}{k}$

$$
\binom{r}{k} = \frac{r(r-1)\cdots(r-k-1)}{k(k-1)\cdots1} = \frac{r^{\underline{k}}}{k!} = \prod_{j=1}^k \frac{r+1-j}{j}
$$



二项式系数历史悠久：
- 1653年，出现在帕斯卡的算术三角论中，称为帕斯卡三角
- 1303年，元代数学家朱世杰
- 1261年，杨辉把它归为贾宪的发现，称为杨辉三角
- 850年，印度数学家马哈维拉解释$\binom{n}{k}$的计算规则


#### A. 用阶乘表示二项式系数

$$
\binom{n}{k} = \frac{n!}{k!(n-k)!} ,  n \geq 0 , k \geq 0
$$

#### B. 对称性条件

$$
\binom{n}{k} = \binom{n}{n-k}
$$

#### C. 移进括号和移出括号

$$
\binom{r}{k} = \frac{r}{k}\binom{r-1}{k-1}, k \neq 0
$$

这个公式非常有用，可以用来把一个表达式中的二项式系数同其他部分结合起来，通过初等变换，得到规则：

$$
k\binom{r}{k} = r\binom{r-1}{k-1}, 
\frac{1}{r}\binom{r}{k} = \frac{1}{k}\binom{r-1}{k-1}
$$

第一条规则对于所有整数 k 成立，第二条规则当除数不为0时成立，还有一个类似的关系式：

$$
\binom{r}{k} = 
\frac{r}{r-k}\binom{r-1}{k} , r \neq k
$$




