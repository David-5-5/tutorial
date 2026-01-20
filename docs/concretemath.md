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
[k\in K] + [k\in K] = [k\in K\cap K'] +  [k\in K\cup K'] \qquad (2.20)
```
得出的。



