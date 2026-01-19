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



