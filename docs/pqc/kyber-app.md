<font size="8"><strong>Kyber</strong></font>
<font size="6.5"><strong>A Progammer's Perspective</strong></font>

[toc]

# 1. Kyber 概述

Kyber 是一种基于格的 **后量子密码学（PQC）** 公钥加密方案，作为 **CRYSTALS（Cryptographic Suite for Algebraic Lattices）** 套件的组成部分，其完整名称为 **CRYSTALS-Kyber**。该算法被 NIST 选为后量子密码标准化算法之一，其核心基于 Module Learning With Errors (MLWE) 问题，具有抗量子计算的特性。

## 1.1. 参数设定

Kyber 有不同的安全级别（如 Kyber-512、Kyber-768、Kyber-1024），主要参数包括：
- 多项式环：\( R_q = \mathbb{Z}_q[X]/(X^n + 1) \)（通常 \( n=256 \), \( q=3329 \)）。
- 向量维度：\( k \)（如 Kyber-512 中 \( k=2 \)）。
- 噪声分布：中心二项分布（用于生成小系数误差）。

## 1.2. 密钥生成（KeyGen）

- **私钥（sk）**：随机生成一个小的向量 \( \mathbf{s} \in R_q^k \)，系数从噪声分布中采样。
- **公钥（pk）**：
  1. 生成随机矩阵 \( \mathbf{A} \in R_q^{k \times k} \)（通常通过哈希函数从种子扩展）。
  2. 生成小的噪声向量 \( \mathbf{e} \in R_q^k \)。
  3. 计算 \( \mathbf{t} = \mathbf{A} \mathbf{s} + \mathbf{e} \in R_q^k \)。
- 输出：公钥 \( pk = (\mathbf{t}, \text{seed}_{\mathbf{A}}) \)，私钥 \( sk = \mathbf{s} \)。

## 1.3. 加密（Encrypt）

输入：公钥 \( pk \)、明文消息 \( m \)（编码为环元素）。  
步骤：
1. 将明文 \( m \) 编码为多项式 \( \hat{m} \in R_q \)（例如，通过二进制编码或冗余编码）。
2. 生成随机小的向量 \( \mathbf{r} \in R_q^k \)（系数从噪声分布采样）。
3. 从种子恢复矩阵 \( \mathbf{A} \)。
4. 计算密文的两个部分：
   - \( \mathbf{u} = \mathbf{A}^T \mathbf{r} + \mathbf{e}_1 \in R_q^k \)（线性部分）。
   - \( v = \mathbf{t}^T \mathbf{r} + e_2 + \hat{m} \cdot \lfloor q/2 \rfloor \in R_q \)（非线性部分，含明文）。
5. 输出密文 \( ct = (\mathbf{u}, v) \)。

## 1.4. 解密（Decrypt）

输入：私钥 \( sk = \mathbf{s} \)、密文 \( ct = (\mathbf{u}, v) \)。  
步骤：
1. 计算 \( w = v - \mathbf{s}^T \mathbf{u} \in R_q \)。
2. 解码 \( w \)：
   - 比较 \( w \) 的系数与 \( \lfloor q/2 \rfloor \) 的接近程度：
     - 若系数接近 \( 0 \)，解码为 \( 0 \)。
     - 若系数接近 \( \lfloor q/2 \rfloor \)，解码为 \( 1 \)。
3. 输出明文 \( m \)。


---

# 2. 用初等数学理解Kyber

## 2.1. mini-Kyber
我们可以用一个“玩具级”的迷你Kyber来直观理解这个加密算法。甚至可以拿纸笔手动完成整个加密解密过程：
- 将标准中庞大的 256 次多项式数学参数压缩到小学生也能计算 4 次多项式
- 将标准中复杂的噪声分布换成-1/0/1这样的简单数字
- 将标准中多项式中 3329 模数压缩到 17，即所有多项式的系数范围为 0 到 16

虽然这个玩具版一秒钟就能被破解，但它像X光片一样，能让你直接看到“格密码”的骨架结构——如何用矩阵乘法混合密钥和噪声，又如何通过巧妙的数学设计让合法用户能去除噪声还原信息，而攻击者只能面对一团乱麻。这种简化就像用透明机箱的示教模型，牺牲了安全性，但换来了对算法核心原理的“肉眼可见”的理解。

### 2.1.1 mini-Kyber 参数设置

| 参数 | 维度 | 模数 | 模块维度 | η | 私钥 | 公钥 | 乘法
|---|--:|--:|--:|:-:|--:|--:|---|
| **Mini Kyber** | 4 | 17 | 2 | {-1,0,1} |16B | 32B | 普通乘法
| **Kyber-512**  |256| 3329 | 2 | 中心二项分布 | 736B | 736B | NTT加速


### 2.1.2 密钥生成

#### 2.1.2.1 参数设置
- 多项式环：$R_{17} = \mathbb{Z}_{17}[x]/(x^4+1)$
- 明文空间：$\{0,1\}^4$ (如 [1, 0, 1, 0])
- 中心二项分布：系数从 $\{-1,0,1\}$ 随机选取
- 矩阵A系数在 $\{0,1,...,16\}$ 随机选取

#### 2.1.2.2. 生成私钥 s
$$
\mathbf{s} = \begin{bmatrix}
s_1 =& 0x^3 + x^2 - x + 1  &= [1,-1,1,0] \\
s_2 =& -x^3 + 0x^2 + x + 0 &= [0,1,0,-1]
\end{bmatrix}
$$
私钥 **s** 是符合**模块维度**为 2 的 $2\times 1$ 的二维矩阵，矩阵中的每个元素是一个多项式环。
- 私钥多项式环的系数符合 $\eta=1$ 的中心二项分布，因此系数的范围为 $\{-1,0,1\}$
- 多项环的次数 n = 4，模 $x^4 + 1$, 因此次数的范围为 [0, 3]

#### 2.1.2.3. 生成公钥矩阵 A
$$
\mathbf{A} = \begin{bmatrix}
A_{11} = 11x^3 + 6x^2 + 15x + 8 & A_{12} = 5x^3 + 13x^2 + 9x + 2 \\
A_{21} = 7x^3 + 4x^2 + 12x + 1 & A_{22} = 14x^3 + 3x^2 + 10x + 16 
\end{bmatrix}
$$
矩阵 **A** 是符合**模块维度**为 2 的 $2\times 2$ 的二维矩阵，矩阵中的每个元素是一个多项式环， 多项式环上的系数和次数要求同私钥 **s**。
- 公钥矩阵 A 的系数模 q = 17, 因此其系数的范围为 [0, 16]
- 多项环的次数 n = 4，模 $x^4 + 1$, 因此次数的范围为 [0, 3]

#### 2.1.2.4. 噪声向量 e
$$
\mathbf{e} = \begin{bmatrix} x^2 - x \\ 0 \end{bmatrix} = \begin{bmatrix} [0,1,-1,0] \\ [0,0,0,0] \end{bmatrix}
$$
- 噪声向量的系数符合 $\eta=1$ 的中心二项分布，因此系数的范围为 $\{-1,0,1\}$
- 多项环的次数 n = 4

#### 2.1.2.5. 计算 t = As + e

##### 2.1.2.5.1 计算 $\mathbf{t}_{\text{noiseless}} = \mathbf{As}$

首先计算第一分量 $t_1$
$$
\begin{aligned}
&(11x^3+6x^2+15x+8)(x^2 - x + 1) \\
&+ (5x^3+13x^2+9x+2)(-x^3 + x) \\
&= 11x^5 - 11x^4 + 11x^3 \\
&\quad + 6x^4 - 6x^3 + 6x^2 \\
&\quad + 15x^3 - 15x^2 + 15x \\
&\quad + 8x^2 - 8x + 8 \\
& -5x^6 + 5x^4 \\
&\quad -13x^5 + 13x^3 \\
&\quad -9x^4 + 9x^2 \\
&\quad -2x^3 + 2x \\
&\equiv \textcolor{magenta}{-5x^6} + \textcolor{magenta}{-2x^5} + \textcolor{magenta}{-9x^4} + 31x^3 + 8x^2 + 9x + 8\\
&\equiv \textcolor{green}{5x^2} + \textcolor{green}{2x} + \textcolor{green}{9} + 31x^3 + 8x^2 + 9x + 8\\
&\equiv 31x^3 + 13x^2 + 11x + 17\\
&\equiv 14x^3 + 13x^2 + 11x + 0 \quad (\text{mod } x^4+1, \text{mod }17)
\end{aligned}
$$

多项式环包含**两个模操作**：
- 系数模操作，例如 $31 \equiv 14 \bmod 17$
- 次数模操作，例如 $-5x^6 \equiv -5x^2(x^4+1) + 5x^2 \equiv 5x^2 (\bmod x^4+1)$

第二分量 $t_2$ 同第一分量计算过程，得到 $t_2$：
$$
\begin{aligned}
&(7x^3+4x^2+12x+1)(x^2 - x + 1) \\
&+ (14x^3+3x^2+10x+16)(-x^3 + x) \\
&\equiv 2x^3 + 0x^2 + 6x + 0 \quad (\text{mod } x^4+1, \text{mod }17)
\end{aligned}
$$

得到无噪声结果结果 $\mathbf{t}_{\text{noiseless}}$
$$
\mathbf{t}_{\text{noiseless}} = \begin{bmatrix}
14x^3 + 13x^2 + 11x + 0  \\
2x^3 + 0x^2 + 6x + 0
\end{bmatrix}
$$

##### 2.1.2.5.2 计算 t = $\mathbf{t}_{\text{noiseless}}$ + e

通过下列的公式，计算
$$
\mathbf{t} = \mathbf{A} \cdot \mathbf{s} + \mathbf{e} = \mathbf{t}_{\text{noiseless}} + \begin{bmatrix} x^2 - x \\ 0 \end{bmatrix}
$$

得到最终的公钥 t
$$
\mathbf{t} = \begin{bmatrix}
14x^3 + 14x^2 + 10x + 0  \\
2x^3 + 0x^2 + 6x + 0
\end{bmatrix}
$$


### 2.1.3. 加密流程

#### 2.1.3.1. 参数定义

**明文**
$$
m = 1x^3 + 0x^2 + 1x + 1 = [1,1,0,1] \\
\text{放大：} \lfloor 17/2 \rceil \cdot m = 9x^3 + 9x + 9
$$

**随机向量 r**
$$
\mathbf{r} = (-x^3 + x^2, x^3 + x^2 - 1)
$$

**误差 e1**
$$
\mathbf{e_1} = (x^2 + x, x^2)
$$

**误差 e2**
$$
e_2 = -x^3 - x^2
$$

#### 2.1.3.2. 加密计算

加密计算包含两部分
$$
\mathbf{u} = \mathbf{A}^T\mathbf{r} + \mathbf{e_1} \\
v = \mathbf{t}^T\mathbf{r} + e_2 + m
$$

**计算 $\mathbf{u} = \mathbf{A}^T\mathbf{r} + \mathbf{e_1}$**
$$
\begin{aligned}
\mathbf{u_1} &= (11x^3+6x^2+15x+8)(-x^3+x^2) \\
&\quad + (7x^3+4x^2+12x+1)(x^3+x^2-1) + (x^2 + x) \\
&= -11x^6 - 6x^5 - 15x^4 - 8x^3 \\
&\quad + 11x^5 + 6x^4 + 15x^3 + 8x^2 \\
&\quad + 7x^6 + 4x^5 + 12x^4 + 1x^3 \\
&\quad + 7x^5 + 4x^4 + 12x^3 + 1x^2\\
&\quad - 7x^3 - 4x^2 - 12x - 1\\
&\quad + x^2 + x \\
&\equiv (-11+7)x^6 + (-6+11+4+7)x^5 + (-15+6+12+4)x^4\\
&\quad +(-8+15+1+12-7)x^3 + (8+1-4+1)x^2 +(-12+1)x -1\\
&\equiv -4x^6 + 16x^5 +7x^4 + 16x^3 + 6x^2 - 11x - 1 (\bmod(x^4+1)) \\
&\equiv 4x^2 - 16x - 7 + 13x^3 + 6x^2 - 11x - 1  \\  
&\equiv 13x^3 + 10x^2 - 27x - 8 (\bmod(17)) \\
&\equiv 13x^3 + 10x^2 + 7x + 9 \\
\end{aligned}
$$

$$
\begin{aligned}
\mathbf{u_2} &= (5x^3+13x^2+9x+2)(-x^3+x^2) \\
&\quad + (14x^3+3x^2+10x+16)(x^3+x^2-1) + (x^2) \\
&= -5x^6 - 13x^5 - 9x^4 - 2x^3 \\
&\quad + 5x^5 + 13x^4 + 9x^3 + 2x^2 \\
&\quad + 14x^6 + 3x^5 + 10x^4 + 16x^3 \\
&\quad + 14x^5 + 3x^4 + 10x^3 + 16x^2\\
&\quad - 14x^3 - 3x^2 - 10x - 16 + (x^2) \\
&\equiv (-5+14)x^6 + (-13+5+3+14)x^5 + (-9+10+3+14)x^4\\
&\quad +(-2+9+16+10-14)x^3 + (2+16-3 + 1)x^2 -10x -16\\
&\equiv 9x^6 + 9x^5 +18x^4 + 19x^3 + 16x^2 - 10x - 16 (\bmod(x^4+1)) \\
&\equiv -9x^2 - 9x - 18 + 19x^3 + 16x^2 - 10x - 16 \\  
&\equiv 19x^3 + 7x^2 - 19x - 16 (\bmod(17)) \\
&\equiv 2x^3 + 7x^2 + 15x + 1 \\
\end{aligned}
$$

**计算 $c = \mathbf{t}^T\mathbf{r} + e_2 + m$**

$$
\begin{aligned}
c &= (14x^3+14x^2+10x)(-x^3+x^2) \\
&\quad + (2x^3+6x)(x^3+x^2-1) + (-x^3-x^2) + (9x^3 + 9x + 9)\\
&= -14x^6 - 14x^5 - 10x^4\\
&\quad + 14x^5 + 14x^4 + 10x^3\\
&\quad + 2x^6 + 2x^5 - 2x^3\\
&\quad + 6x^4 + 6x^3 - 6x\\
&\quad + (-x^3-x^2) + (9x^3 + 9x + 9)\\
&\equiv (-14+2)x^6 + (-14+14+2)x^5 + (-10+14+6)x^4\\
&\quad +(12-2+6)x^3 -6x + (-x^3-x^2) + (9x^3 + 9x + 9)\\
&\equiv -12x^6 + 2x^5 + 10x^4 + 16x^3 - 6x + (-x^3-x^2) + (9x^3 + 9x + 9) (\bmod(x^4+1)) \\
&\equiv 12x^2 - 2x - 10 + 16x^3 -6x + (-x^3-x^2) + (9x^3 + 9x + 9) \\  
&\equiv 16x^3 + 12x^2 - 8x - 10 + (-x^3-x^2) + (9x^3 + 9x + 9) \\
&\equiv 24x^3 + 11x^2 + 1x - 1 (\bmod(17)) \\
&\equiv 7x^3 + 11x^2 + x + 16 \\
\end{aligned}
$$


**最终密文**
$$
\begin{cases}
\mathbf{u} = [13x^3 + 10x^2 + 7x + 9, \ 2x^3 + 7x^2 + 15x + 1] \\
c = 7x^3 + 11x^2 + x + 16
\end{cases}
$$

### 2.1.4. 解密流程

$$
m' = v - \mathbf{u}^T \mathbf{s}
$$

#### 2.1.4.1. 计算 $\mathbf{u}^T \mathbf{s}$
$$
\begin{aligned}
\mathbf{u}^T \mathbf{s} &= (13x^3 + 10x^2 + 7x + 9)(x^2 - x + 1) \\
&\quad + (2x^3 + 7x^2 + 15x + 5)(-x^3 + x) \\
&\equiv 13x^5 + 10x^4 + 7x^3 + 9x^2 \\
&\quad - 13x^4 - 10x^3 - 7x^2 - 9x \\
&\quad + 13x^3 + 10x^2 + 7x + 9 \\
&\quad - 2x^6 - 7x^5 - 15x^4 - x^3 \\
&\quad + 2x^4 + 7x^3 + 15x^2 + x \\
&\equiv (-2)x^6 + (13-7)x^5 + (10-13-15+2)x^4  \\
&\quad + (7-10+13-1+7)x^3 + (9-7+10+15)x^2 + (-9+7+1)x + 9\\
&\equiv -2x^6 + 6x^5 - 16x^4 + 16x^3 + 27x^2 - x + 9 (\bmod(x^4+1))  \\
&\equiv 2x^2 - 6x + 16 + 16x^3 + 27x^2 -x + 9 \\
&\equiv 16x^3 + 29x^2 - 7x + 25  (\bmod(17))\\
&\equiv 16x^3 + 12x^2 + 8x + 8  (\bmod(17))\\
\end{aligned}
$$

#### 2.1.4.2. 计算 $m' = v - \mathbf{u}^T \mathbf{s}$
$$
\begin{aligned}
m' &= 7x^3 + 11x^2 + x + 16 - (16x^3 + 12x^2 + 8x + 8) \\
&\equiv -9x^3 - 1x^2 -7x + 8  (\bmod(17))\\
&\equiv 6x^3 + 16^2 + 8x + 8
\end{aligned}
$$

#### 2.1.4.2. 解码
系数距离 $\lfloor q/2 \rceil$ 或 $0/q$ 更近，$q=17$ 的情况下，系数在 [5, 12]之间为 1， 其他区间为 0

| 系数项 | 计算值 | $\lfloor \text{值}/9 \rfloor$ | 解码bit |
|--------|--------|-------------------------------|---------|
| $x^3$  | 6      | 1                             | 1       |
| $x^2$  | 16      | 0                             | 0       |
| $x$    | 8      | 1                             | 1       |
| 常数项 | 8      | 1                             | 1       |

**最终明文**：`1011` 解密成功



## 2.2. 噪声的作用：让"解方程"变得不可能

### 2.2.1 无噪声场景

攻击者视角知道公钥矩阵 A, t 可通过高斯消元法直接计算出私钥 s

#### 2.2.1.1 已知条件
给定公钥方程 $\mathbf{t} = \mathbf{A} \cdot \mathbf{s}$，其中：

$$
\mathbf{A} = \begin{bmatrix} 
11x^3 + 6x^2 + 15x + 8 & 5x^3 + 13x^2 + 9x + 2 \\
7x^3 + 4x^2 + 12x + 1 & 14x^3 + 3x^2 + 10x + 16 
\end{bmatrix}, \quad
\mathbf{t}_{\text{noiseless}} = \begin{bmatrix} 14x^3 + 13x^2 + 11x + 0  \\2x^3 + 0x^2 + 6x + 0 \end{bmatrix}
$$


设私钥 $\mathbf{s} = \begin{bmatrix} s_0 \\ s_1 \end{bmatrix} = \begin{bmatrix} a_3x^3 + a_2x^2 + a_1x + a_0 \\ b_3x^3 + b_2x^2 + b_1x + b_0 \end{bmatrix}$

####  2.2.1.1 消元法求私钥

1. **展开矩阵方程**

$$
\begin{cases}
(11x^3+6x^2+15x+8)s_0 + (5x^3+13x^2+9x+2)s_1 = 14x^3 + 13x^2 + 11x\quad (1) \\
(7x^3+4x^2+12x+1)s_0 + (14x^3+3x^2+10x+16)s_1 = 2x^3 + 6x \quad (2)
\end{cases}
$$

2. **构建系数矩阵**

将多项式方程转换为系数方程组（按$x^3,x^2,x,x^0$分列）：

方程(1)的系数关系
$$
\begin{aligned} 
x^3项: & \quad 11a_0 + 6a_1 + 15a_2 + 8a_3 + 5b_0 + 13b_1 + 9b_2 + 2b_3 &\equiv 14\\
x^2项: & \quad 6a_0 + 15a_1 + 8a_2 - 11a_3 + 13b_0 + 9b_1 + 2b_2 - 5b_3 &\equiv 13\\
x^1项: & \quad 15a_0 + 8a_1 - 11a_2 - 6a_3 + 9b_0 + 2b_1 - 5b_2 - 13b_3 &\equiv  11\\
x^0项: & \quad 8a_0 - 11a_1 - 6a_2 - 15a_3 + 2b_0 - 5b_1 - 13b_2 - 9b_3 &\equiv  0
\end{aligned}
$$

方程(2)的系数关系
$$
\begin{aligned} 
x^3项: & \quad 7a_0 + 4a_1 + 12a_2 + a_3 + 14b_0 + 3b_1 + 10b_2 + 16b_3 &\equiv 2\\
x^2项: & \quad 4a_0 + 12a_1 + a_2 - 7a_3 + 3b_0 + 10b_1 + 16b_2 - 14b_3 &\equiv 0\\
x^1项: & \quad 12a_0 + a_1 - 7a_2 - 4a_3 + 10b_0 + 16b_1 - 14b_2 - 3b_3 &\equiv  6\\
x^0项: & \quad a_0 - 7a_1 - 4a_2 - 12a_3 + 16b_0 - 14b_1 - 3b_2 - 10b_3 &\equiv  0
\end{aligned}
$$

3. **构建矩阵方程**
通过高斯消元法解这个8×8的线性方程组（模17），可以得到私钥的系数：

$$
\left[\begin{array}{cccc|cccc|c}
11 & 6 & 15 & 8 & 5 & 13 & 9 & 2 & 14 \\
6 & 15 & 8 & -11 & 13 & 9 & 2 & -5 & 13 \\
15 & 8 & -11 & -6 & 9 & 2 & -5 & -13 & 11 \\
8 & -11 & -6 & -15 & 2 & -5 & -13 & -9 & 0 \\ \hline
7 & 4 & 12 & 1 & 14 & 3 & 10 & 16 & 2 \\
4 & 12 & 1 & -7 & 3 & 10 & 16 & -14 & 0 \\
12 & 1 & -7 & -4 & 10 & 16 & -14 & -3 & 6 \\
1 & -7 & -4 & -12 & 16 & -14 & -3 & -10 & 0 \\
\end{array}\right]
$$

$$
\mathbf{s} = \begin{bmatrix}
s_1 = 0x^3 + x^2 - x + 1 = [1,-1,1,0] \\
s_2 = -x^3 + 0x^2 + x + 0 = [0,1, 0, -1]
\end{bmatrix}
$$


### 2.2.2 有噪声场景

#### 2.2.2.1 攻击的时间复杂度
攻击者面临的新方程，攻击失败原因
- 噪声未知	方程数量 < 未知量数量（s+e）
- 噪声累积	错误在多项式乘法中扩散
- 模运算干扰	无法直接比较方程两边

实验验证
假设攻击者猜测e=0：
错误解：s' = [2x³+0x²+5x+1, 4x³+7x²+2x+3]  # 代入验证失败

实际需要尝试的噪声组合：
每个噪声可能值 = $\{-1,0,1\}^4 \to 3^4=81$ 种/多项式
mini-kyber中，在密钥生成阶段包含：
- 误差 $\mathbf{e}$ 包含$e_1, e_2$ 两个噪声多项式
- 私钥 $\mathbf{s}$ 包含 $s_1, s_2$ 两个噪声多项式

共 4 个噪声多项式，其组合数为 $81^4 \approx$ 4 百万种 *(实际情况下，考虑噪声符合CBD的分布，而非单纯组合数)*

而在标准的 kyber 多项式度数为 256，$\eta=2$，因此每个噪声可能值 = $\{-2, -1,0,1,2\}^{256} = 5^{256} \approx 10^{178}$


| 攻击方式       | 无噪声 | 有噪声 |
|----------------|--------|--------|
| 高斯消元法     | 0.1秒  | 不可能 |
| 暴力搜索       | 1秒    | >10年  |

核心结论
- 噪声作为保护层：将易解的线性方程变为难解的MLWE问题
- 可调安全性：通过增大噪声分布η，可提升安全等级
- Kyber的巧妙设计：
  - 足够大的噪声使攻击失效
  - 足够小的噪声保证解密正确


#### 2.2.2.2 噪声及解密正确性

复习一下上述出现的计算公式：
计算公钥 $\mathbf{t} = \mathbf{As} + \mathbf{e} (1)$

加密计算：
- $\mathbf{u} = \mathbf{A^Tr} + \mathbf{e_1}$
- $v = \mathbf{t^Tr} + e_2 + m$

解密计算 $m'  = v - \mathbf{s^Tu}$

正确性证明：将 $v$ 和 $\mathbf{u}$ 带入解密公式：
$$
\begin{aligned} 
m' &= \mathbf{t^Tr} + e_2 + m - \mathbf{s^T(A^Tr + e_1)} \\
  & = \mathbf{t^Tr} + e_2 + m - \mathbf{s^TA^Tr - s^Te_1}\\
  &= \mathbf{(As + e)^Tr} + e_2 + m - \mathbf{(As)^Tr - s^Te_1} \\
  &= \mathbf{(As)^Tr} + \mathbf{e^Tr} + e2 + m -\mathbf{(As)^Tr - s^Te_1} \\
  &= m + \underline{\mathbf{e^Tr} + e_2 - \mathbf{s^Te_1}}
\end{aligned} 
$$

上式中带下划线的部分称为“噪声”，kyber 通过中心二项分布的随机采样保证噪声在可控范围内不影响解密的正确性，保证噪声的系数小于 $\frac{q}{4}$, $q=17$ 的情况下噪声绝对值小于 4。

用上面的 $\mathbf{e, r, e_1}, e2$ 计算 $noise = \mathbf{e^Tr} + e_2 - \mathbf{s^Te_1}$

其中
$$
\begin{aligned} 
\mathbf{e^Tr} & = (x^2-x)(-x^3+x^2) + (0)(x^3+x^2+1) \\
 & = -x^5 + x^4 + x^4 - x^3 \\
 & = -x^5 + 2x^4 - x^3 \\
 & = x - 2 - x^3 = -x^3 + x - 2  
\end{aligned} 
$$

$$
\begin{aligned} 
\mathbf{s^Te_1} & = (x^2-x+1)(x^2+x) + (-x^3+x)x^2 \\
 & = x4 + x - x^5 + x^3 \\
 & = -1 + x + x + x^3 \\
 & = x^3 + 2x - 1  
\end{aligned} 
$$

$$
\begin{aligned} 
noise & = \mathbf{e^Tr} + e_2 - \mathbf{s^Te_1}\\
 & = (-x^3 + x - 2) + (-x^3 - x^2) - ( x^3 + 2x - 1 ) \\
 & = -3x^3 - x^2 - x - 1
\end{aligned} 
$$
得到最终的噪声 $-3x^3 - x^2 - x - 1$，其系数的绝对值小于 $\frac{q}{4}$，不影响解密的正确性。

回顾一下 m = {1,0,1,1} 转换为多项式为
$$
\begin{aligned} 
m \cdot \lfloor\frac{q}{2}\rceil & = (x^3 + 0x^2 + x^1 + 1) \cdot 9 \\
 & = 9x^3 + 9^x + 9
\end{aligned} 
$$

$$
\begin{aligned} 
m + noise & = (9x^3 + 9^x + 9) + (-3x^3 - x^2 - x - 1) \\
  & = 6^x - x^2 + 8x + 8 \\
  & = 6^x + 16x^2 + 8x + 8 
\end{aligned} 
$$
恰好为 2.1.4节 解密结果


# 3. Kyber工作流程全景解析

## 3.1 算法黑箱工作流

### 密钥生成阶段
1. **矩阵构造**  
   - 通过种子ρ扩展生成伪随机矩阵A∈R<sub>q</sub><sup>k×k</sup>  
   - 关键创新：避免存储大矩阵（即时计算）

2. **噪声注入**  
   - 采用三级噪声体系：
     - 私钥噪声s←CBD<sub>η</sub>
     - 公钥噪声e←CBD<sub>η</sub>
     - 临时噪声e<sub>1</sub>,e<sub>2</sub>←CBD<sub>η</sub>

3. **密钥格式化**  
   - 公钥pk=(ρ, A·s+e)  
   - 私钥sk=(s, 抗CCA2哈希种子)

### 加密封装流程
1. **双通道保护机制**  
   \[
   \begin{cases}
   u = A^T·r + e_1 & \text{(LWE保护层)} \\ 
   v = t^T·r + e_2 + encode(K) & \text{(密钥传输层)}
   \end{cases}
   \]

2. **密文优化特征**  
   - 密文膨胀率：比RSA高3-5倍  
   - 量子安全增益：指数级提升

### 解密解封装
1. **误差补偿技术**  
   - 核心运算：v - s<sup>T</sup>·u ≈ K + noise  
   - 动态解码阈值：q/4边界判定

2. **安全验证层**  
   - CCA2防护：密文一致性验证  
   - 错误处理：伪随机回退机制

## 3.2 性能特征分析

### 计算效率对比
| 操作        | 时钟周期(Intel Xeon) | 加速比 vs RSA |
|-------------|---------------------|--------------|
| 密钥生成     | 15,000              | 24x          |
| 加密        | 20,000              | 11x          |
| 解密        | 25,000              | 3.3x         |

### 关键性能突破
1. **代数结构优化**  
   - 采用NTT-friendly环：Z<sub>3329</sub>[X]/(X<sup>256</sup>+1)  
   - 模数选择：3329 = 2<sup>8</sup>+2<sup>6</sup>+2<sup>4</sup>+1（加速约减）

2. **内存层级优化**  
   - 矩阵A的按需生成  
   - 错误采样缓存复用策略

3. **指令级并行**  
   - AVX2处理8个系数并行  
   - ARM NEON优化模运算

## 3.3 安全参数设计

### 多维防御体系
1. **噪声调配艺术**  
   | 安全级别 | 噪声参数η | 解密失败率 |
   |----------|----------|------------|
   | Kyber512 | 3        | 2<sup>-144</sup> |
   | Kyber768 | 2        | 2<sup>-138</sup> |

2. **双重保护机制**  
   - 数学基础：MLWE问题困难性  
   - 工程实现：恒定时间编码

### 参数选择权衡
```mermaid
graph LR
A[安全性] -->|增加维度k| B(更高的计算开销)
A -->|增大模数q| C(更大的密文)
D[效率] -->|降低噪声| E(更高的失败率)
```

# 4. 必须掌握的优化技巧

## 4.1 Montgomery 模乘

Montgomery模乘算法是一种高效的大数模乘计算方法，由Peter L. Montgomery在1985年提出。它通过将数字转换到 Montgomery 域中，避免了模运算中耗时的除法操作，特别适合硬件实现和密码学应用。


### 4.1.1 Montgomery 模乘介绍
现代CPU下，加减法及位操作的时钟周期需要1～3时钟周期，乘法需要3～10个时钟周期，而除法需要30+时钟周期。传统的模运算需要进行除法运算，获取余数。
```c++
// 常规模乘计算
int naive_modmul(int a, int b, int q) {
    return (a * b) % q  // 需要昂贵的除法
}
```

Montgomery模乘可以分为 3 个步骤：
1. 转换输入到Montgomery域
2. 计算 Montgomery 约减
3. 转换回常规域（可选）

因此，首先定义Montgomery域，相对于模数 q，选择 $R=2^n > q, R \bot q $，则对于常规域 $x \in \Z_q$，其对应的 Montgomery 域下的数 $\tilde{x}$
$$
\tilde{x} = xR \bmod q
$$

Montgomery域与普通域关键操作对比
| 操作类型 | 普通域运算  | Montgomery域运算 | 说明 |
|---|---|---|---|
| 加法 | $(a + b) \bmod q$ | $(\tilde{a}  + \tilde{b} ) \bmod q$  | 完全一致，直接模加|
| 减法 | $(a - b) \bmod q$ | $(\tilde{a}  + \tilde{b}) \bmod q$  | 完全一致，直接模减 |
| 标量乘 | $(ka) \bmod q$ | $(k\tilde{a}) \bmod q$  | 完全一致，直接模减 |
| 乘法 | $(a × b) \bmod q$ | $montmul(\tilde{a}, \tilde{b}) = (\tilde{a}×\tilde{b}×R^{-1}) \bmod q$  | Montgomery核心优化：<br>1. 用乘法和移位代替除法<br>2. 需预计算$q'=-q^{-1} \bmod R$ |
| 转换 | - | $\tilde{a} = montmul(a, R^2)$| 进入Montgomery域的代价                                              |
| 逆转换 | - | $a = montmul(\tilde{a}, 1)$ | 退出Montgomery域的代价                                              |

说明：
- Montgomery域上的加法，减法以及标量乘法后，操作的结果仍在 Montgomery 域中，因此直接进行操作即可。由于加法、减法或标量乘操作可能超出模 q 的范围，其处理有如下三种方式：
  1. 暂时溢出，待执行Montgomery域乘法时进行约简，这种方法称为 *惰性约简*
  2. 进行加法操作后，可以执行以下语句：
     ```c
     if (result>=q) result -= q;
     ```
  3. 必须严格模N的情况，采用[4.2Barrett约减]()等无除法算法

- 由于 $\tilde{a}\times \tilde{b} = abR^2$, 因此结果已经不在Montgomery 域中，因此需要乘以 $R^{-1}modq$，将结果重新映射到 Montgomery 域中。因此方法 $montmul$ 执行Montgomery域上乘法，又称为[4.1.2Montgomery约简]()，是Montgomery模乘的核心。


### 4.1.2 Montgomery约减


### 4.1.3 Kyber中的Montgomery模乘

kyber中的Montgomery模乘是上面模乘的一个实例化。以下分段列出涉及到的代码

ref/reduce.h 文件中，定义 Montgomery 域相关的预处理值。
```c
#define MONT -1044 // 2^16 mod q
#define QINV -3327 // q^-1 mod 2^16
```

ref/reduce.c 文件中，定义了montgomery约简方法 montgomery_reduce，其：
- 输入是两个 montgomery 域上数的乘积，已不在 montgomery 域上。
- 输出是一个montgomery 域上乘积转换。
```c
int16_t montgomery_reduce(int32_t a)
{
  int16_t t;

  t = (int16_t)a*QINV;
  t = (a - (int32_t)t*KYBER_Q) >> 16;
  return t;
}
```

ref/poly.c 文件中，将多项式上的系数从常规域转换到 montgomery 域。
```c
void poly_tomont(poly *r)
{
  unsigned int i;
  const int16_t f = (1ULL << 32) % KYBER_Q;
  for(i=0;i<KYBER_N;i++)
    r->coeffs[i] = montgomery_reduce((int32_t)r->coeffs[i]*f);
}
```
其中 $f$ 即是上节介绍的 $R^2$

ref/ntt.c 文件中，定义了montgomery 模乘方法，其关键调用了 montgomery_reduce
```c
static int16_t fqmul(int16_t a, int16_t b) {
  return montgomery_reduce((int32_t)a*b);
}
```


## 4.2 Montgomery 模乘


