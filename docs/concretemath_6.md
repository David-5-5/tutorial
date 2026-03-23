# 6 Special Numbers

在数学中有一些数列出现得非常频繁，以至于我们能立刻认出它们并赋予专门的名称。例如，每个学过算术的人都知道平方数序列 $\langle 1, 4, 9, 16, \dots \rangle$。在第 1 章我们遇到了三角形数 $\langle 1, 3, 6, 10, \dots \rangle$；在第 4 章我们研究了素数序列 $\langle 2, 3, 5, 7, \dots \rangle$；在第 5 章我们简要考察了卡特兰数 $\langle 1, 2, 5, 14, \dots \rangle$。

在本章中，我们将认识另外一些重要的数列。我们首先要讨论的是第一类斯特林数 $\genfrac{[}{]}{0pt}{}{n}{k}$、第二类斯特林数 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 以及欧拉数 $\left\langle\begin{smallmatrix}n\\k\end{smallmatrix}\right\rangle$；它们构成了与帕斯卡三角中的二项式系数 $\binom{n}{k}$ 类似的三角系数阵列。接下来我们会仔细研究调和数 $H_n$ 与伯努利数 $B_n$；它们与我们之前研究过的数列不同，因为它们是分数而非整数。最后，我们将介绍极具吸引力的斐波那契数 $F_n$ 及其一些重要的推广。


## 6.1 STIRLING NUMBERS 斯特林数
我们从二项式系数的一些近亲——斯特林数开始，它们以 James Stirling（1692–1770）命名。这类数有两种，习惯上被直接称为“第一类斯特林数”和“第二类斯特林数”。尽管它们历史悠久且应用广泛，但至今仍没有统一的标准记号。遵循 Jovan Karamata 的记法，我们用 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 表示第二类斯特林数，用 $\genfrac{[}{]}{0pt}{}{n}{k}$ 表示第一类斯特林数；事实证明这些符号比人们曾用过的许多其他记号更易用。

表 258 和表 259 给出了 $n$ 与 $k$ 较小时 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 与 $\genfrac{[}{]}{0pt}{}{n}{k}$ 的取值。一个涉及数列“1, 7, 6, 1”的问题很可能与 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 有关，而涉及“6, 11, 6, 1”的问题则很可能与 $\genfrac{[}{]}{0pt}{}{n}{k}$ 有关，就像我们会认为涉及“1, 4, 6, 4, 1”的问题与 $\binom{n}{k}$ 有关一样；这些都是 $n=4$ 时出现的标志性数列。

**表 258 子集对应的斯特林三角（第二类斯特林数 $\genfrac{\{}{\}}{0pt}{}{n}{k}$）**
|$n$|$\genfrac{\{}{\}}{0pt}{}{n}{0}$|$\genfrac{\{}{\}}{0pt}{}{n}{1}$|$\genfrac{\{}{\}}{0pt}{}{n}{2}$|$\genfrac{\{}{\}}{0pt}{}{n}{3}$|$\genfrac{\{}{\}}{0pt}{}{n}{4}$|$\genfrac{\{}{\}}{0pt}{}{n}{5}$|$\genfrac{\{}{\}}{0pt}{}{n}{6}$|$\genfrac{\{}{\}}{0pt}{}{n}{7}$|$\genfrac{\{}{\}}{0pt}{}{n}{8}$|$\genfrac{\{}{\}}{0pt}{}{n}{9}$|
|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|0|1|0|0|0|0|0|0|0|0|0|
|1|0|1|0|0|0|0|0|0|0|0|
|2|0|1|1|0|0|0|0|0|0|0|
|3|0|1|3|1|0|0|0|0|0|0|
|4|0|1|7|6|1|0|0|0|0|0|
|5|0|1|15|25|10|1|0|0|0|0|
|6|0|1|31|90|65|15|1|0|0|0|
|7|0|1|63|301|350|140|21|1|0|0|
|8|0|1|127|966|1701|1050|266|28|1|0|
|9|0|1|255|3025|7770|6951|2646|462|36|1|

第二类斯特林数比第一类更常用，所以我们先来看它。记号 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 表示将 $n$ 个元素的集合划分为 $k$ 个非空子集的方法数。例如，把一个含 $4$ 个元素的集合分成两部分共有 $7$ 种方法：
$$\{1, 2, 3\} \cup \{4\},\ \{1, 2, 4\} \cup \{3\},\ \{1, 3, 4\} \cup \{2\},\ \{2, 3, 4\} \cup \{1\},\\
\{1, 2\} \cup \{3, 4\},\ \{1, 3\} \cup \{2, 4\},\ \{1, 4\} \cup \{2, 3\};\quad (6.1)$$

因此 $\genfrac{\{}{\}}{0pt}{}{4}{2}=7$。注意花括号既用来表示集合，也用来表示数 $\genfrac{\{}{\}}{0pt}{}{n}{k}$。这种记号上的联系有助于我们记住 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 的含义，它可以读作“$n$ 子集 $k$”。

我们来看较小的 $k$。将 $n$ 个元素放入单个非空集合只有一种方法；因此对所有 $n>0$ 有 $\genfrac{\{}{\}}{0pt}{}{n}{1}=1$。另一方面 $\genfrac{\{}{\}}{0pt}{}{0}{1}=0$，因为空集不含任何元素。

$k=0$ 的情形稍微有点特殊。如果约定将空集划分为 $0$ 个非空部分恰好只有一种方法，那么一切都会最自然；因此 $\genfrac{\{}{\}}{0pt}{}{0}{0}=1$。但非空集合至少需要一个部分，所以对 $n>0$ 有 $\genfrac{\{}{\}}{0pt}{}{n}{0}=0$。

当 $k=2$ 时会怎样？显然 $\genfrac{\{}{\}}{0pt}{}{0}{2}=0$。如果将 $n>0$ 个对象的集合划分为两个非空部分，那么其中一部分包含最后一个对象，以及前 $n-1$ 个对象的某个子集。选取这个子集共有 $2^{n-1}$ 种方式，因为前 $n-1$ 个对象每个都可在其中或不在其中；但我们不能把所有这些对象都放进去，因为最终要得到两个非空部分。因此我们减去 1：
$$\genfrac{\{}{\}}{0pt}{}{n}{2}=2^{n-1}-1,\ \text{integer }n>0.\quad (6.2)$$

这与我们前面枚举的 $\genfrac{\{}{\}}{0pt}{}{4}{2}=7=2^3-1$ 种方法一致。

**表 259 轮换对应的斯特林三角（第一类斯特林数 $\genfrac{[}{]}{0pt}{}{n}{k}$）**

|$n$|$\genfrac{[}{]}{0pt}{}{n}{0}$|$\genfrac{[}{]}{0pt}{}{n}{1}$|$\genfrac{[}{]}{0pt}{}{n}{2}$|$\genfrac{[}{]}{0pt}{}{n}{3}$|$\genfrac{[}{]}{0pt}{}{n}{4}$|$\genfrac{[}{]}{0pt}{}{n}{5}$|$\genfrac{[}{]}{0pt}{}{n}{6}$|$\genfrac{[}{]}{0pt}{}{n}{7}$|$\genfrac{[}{]}{0pt}{}{n}{8}$|$\genfrac{[}{]}{0pt}{}{n}{9}$|
|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|0|1|0|0|0|0|0|0|0|0|0|
|1|0|1|0|0|0|0|0|0|0|0|
|2|0|1|1|0|0|0|0|0|0|0|
|3|0|2|3|1|0|0|0|0|0|0|
|4|0|6|11|6|1|0|0|0|0|0|
|5|0|24|50|35|10|1|0|0|0|0|
|6|0|120|274|225|85|15|1|0|0|0|
|7|0|720|1764|1624|735|175|21|1|0|0|
|8|0|5040|13068|13132|6769|1960|322|28|1|0|
|9|0|40320|109584|118124|67284|22449|4536|546|36|1|

对这个论证稍作修改，就能得到可对所有 $k$ 计算 $\genfrac{\{}{\}}{0pt}{}{n}{k}$ 的递推关系：将 $n>0$ 个对象划分为 $k$ 个非空部分时，要么把最后一个对象单独作为一类（有 $\genfrac{\{}{\}}{0pt}{}{n-1}{k-1}$ 种方法），要么把它与前 $n-1$ 个对象的某个非空子集放在一起。后一种情形有 $k\genfrac{\{}{\}}{0pt}{}{n-1}{k}$ 种可能，因为将前 $n-1$ 个对象划分为 $k$ 个非空部分的每 $\genfrac{\{}{\}}{0pt}{}{n-1}{k}$ 种分法，都对应 $k$ 个可加入第 $n$ 个对象的子集。因此
$$
\genfrac{\{}{\}}{0pt}{}{n}{k}= k\genfrac{\{}{\}}{0pt}{}{n-1}{k} + \genfrac{\{}{\}}{0pt}{}{n-1}{k-1},\quad \text{integer }n>0. \tag{6.3}
$$

这就是生成表 258 的递推法则；如果去掉系数 $k$，它就退化为生成帕斯卡三角的加法公式 (5.8)。

现在来看第一类斯特林数。它们与第二类有些相似，但 $\genfrac{[}{]}{0pt}{}{n}{k}$ 计数的是把 $n$ 个对象排成 $k$ 个轮换（循环）的方法数，而不是子集。我们把 $\genfrac{[}{]}{0pt}{}{n}{k}$ 读作“$n$ 轮换 $k$”。

轮换是环形排列，就像我们在第4章讨论过的项链。轮换可以更简洁地记作 `[A, B, C, D]`，并约定
$$[A, B, C, D] = [B, C, D, A] = [C, D, A, B] = [D, A, B, C];$$

轮换是“首尾相连”的，因为它的终点与起点相接。但另一方面，轮换 $[A, B, C, D]$ 与 $[A, B, D, C]$ 或 $[D, C, B, A]$ 并不相同。

将 4 个元素分成 2 个轮换，共有 11 种不同方法：
$$[1, 2, 3][4],\ [1, 2, 4][3],\ [1, 3, 4][2],\ [2, 3, 4][1],\\
[1, 3, 2][4],\ [1, 4, 2][3],\ [1, 4, 3][2],\ [2, 4, 3][1],\\
[1, 2][3, 4],\ [1, 3][2, 4],\ [1, 4][2, 3]; \tag{6.4}$$

因此 $\genfrac{[}{]}{0pt}{}{4}{2}=11$。

单点轮换（只含一个元素的轮换）本质上和单点集合（只含一个元素的集合）是一样的。类似地，2‑轮换就像 2‑元集合，因为我们有 $[A,B]=[B,A]$，就像 $\{A,B\}=\{B,A\}$。但是 3‑轮换有两种：$[A,B,C]$ 和 $[A,C,B]$。例如可以看到，式 (6.4) 里的 11 个轮换对，都可以从式 (6.1) 里的 7 个集合对中，把每个 3‑元集合拆成两个轮换得到。

一般来说，对任意 $n>0$，由 $n$ 个元素的集合可以构造出 $n!/n=(n-1)!$ 个不同的 $n$‑轮换。（共有 $n!$ 个排列，而每个 $n$‑轮换对应其中 $n$ 个排列，因为轮换中任意一个元素都可以写在开头。）因此我们有
$$
\genfrac{[}{]}{0pt}{}{n}{1} = (n-1)!,\quad \text{integer }n>0. \tag{6.5}
$$

这远比子集型斯特林数的结果 $\genfrac{\{}{\}}{0pt}{}{n}{1}=1$ 大。事实上，很容易看出轮换型斯特林数必定至少和子集型斯特林数一样大。
$$
\genfrac{[}{]}{0pt}{}{n}{k} \ge \genfrac{\{}{\}}{0pt}{}{n}{k},\quad \text{integer }n,k\ge0. \tag{6.6}
$$

因为每个划分为非空子集的分拆，都至少对应一种轮换排列。

当所有轮换必然是单点或二元轮换时，式 (6.6) 取等号，因为在这种情况下轮换与子集等价。这在 \(k=n\) 与 \(k=n-1\) 时成立，因此
$$
\genfrac{[}{]}{0pt}{}{n}{n} = \genfrac{\{}{\}}{0pt}{}{n}{n},\qquad
\genfrac{[}{]}{0pt}{}{n}{n-1} = \genfrac{\{}{\}}{0pt}{}{n}{n-1}.
$$

事实上，不难看出
$$
\genfrac{[}{]}{0pt}{}{n}{n} = \genfrac{\{}{\}}{0pt}{}{n}{n} = 1; \qquad
\genfrac{[}{]}{0pt}{}{n}{n-1} = \genfrac{\{}{\}}{0pt}{}{n}{n-1} = \binom{n}{2}. \tag{6.7}
$$

(将 $n$ 个对象排成 $n-1$ 个轮换或子集的方法数，等于选出放在同一个轮换或子集里的两个对象的方法数。) 三角数 $\dbinom{n}{2}=1,3,6,10,\dots$ 在表 258 和表 259 中都清晰出现。

我们可以仿照第二类斯特林数的推导，给出第一类斯特林数的递推关系。将 $n$ 个对象排成 $k$ 个轮换的方案数，要么是把最后一个对象单独作为一个轮换（共 $\genfrac{[}{]}{0pt}{}{n-1}{k-1}$ 种），要么是把它插入前 $n-1$ 个对象排成的 $\genfrac{[}{]}{0pt}{}{n-1}{k}$ 种轮换方案中的某一个里。在后一种情况里，共有 $n-1$ 种不同的插入方式。（这需要稍微想一想，但不难验证：把一个新元素插入一个 $j$‑轮换以得到 $(j+1)$‑轮换，恰好有 $j$ 种方法。例如当 $j=3$ 时，轮换 $[A,B,C]$ 可以得到
$$[A, B, C, D],\ [A, B, D, C],\ \text{ or }\ [A, D, B, C]$$

将新元素 D 插入时，只有这三种可能。对所有 j 求和后，把第 n 个对象插入 n−1 个对象的轮换分拆中，总共有 n−1 种方式。）于是我们得到所求的递推式：
$$
\genfrac{[}{]}{0pt}{}{n}{k} = (n-1)\genfrac{[}{]}{0pt}{}{n-1}{k} + \genfrac{[}{]}{0pt}{}{n-1}{k-1},\quad \text{integer }n>0. \tag{6.8}
$$

这就是生成表 259 的对应加法公式。

对比式 (6.8) 与 (6.3) 可以发现：右边第一项在轮换型斯特林数中乘上标 $(n-1)$，而在子集型斯特林数中乘下标 $k$。因此在数学归纳法证明中，我们可以对形如 $n\genfrac{[}{]}{0pt}{}{n}{k}$ 和 $k\genfrac{\{}{\}}{0pt}{}{n}{k}$ 的项进行“吸收”操作。

每个置换都等价于一组轮换。例如，考虑将 123456789 映为 384729156 的置换，我们可以方便地用两行表示：
$$1 2 3 4 5 6 7 8 9 \\
3 8 4 7 2 9 1 5 6 ,$$

即 1 变成 3，2 变成 8，依此类推。轮换结构由此产生：1→3→4→7→1，这就是轮换 [1,3,4,7]。该置换中的另一个轮换是 [2,8,5]；还有一个是 [6,9]。因此置换 384729156 等价于轮换排列
$$[1, 3, 4, 7] [2, 8, 5] [6, 9] .$$

对于 $\{1,2,\dots,n\}$ 的任一置换 $\pi_1\pi_2\dots\pi_n$，每个元素都落在唯一的轮换中。因为若从 $m_0=m$ 出发，令 $m_1=\pi_{m_0}$，$m_2=\pi_{m_1}$，……，最终一定会回到 $m_k=m_0$。（数值迟早会重复，而第一个重复出现的数一定是 $m_0$，因为我们知道其他数 $m_1,m_2,\dots,m_{k-1}$ 都有唯一的前趋。）因此每个置换都唯一确定一个轮换分解；反过来，把构造过程逆过来，每个轮换分解也显然对应一个置换。这种一一对应说明：置换与轮换分解本质上是同一个对象。

因此 $\genfrac{[}{]}{0pt}{}{n}{k}$ 就是 $n$ 个对象恰有 $k$ 个轮换的置换数目。若对所有 $k$ 求和，就得到置换总数：
$$
\sum_{k=0}^n \genfrac{[}{]}{0pt}{}{n}{k} = n!,\quad \text{integer }n\ge 0. \tag{6.9}
$$
例如，$6 + 11 + 6 + 1 = 24 = 4!$。

斯特林数非常有用，因为递推关系 (6.3) 和 (6.8) 会在许多问题中出现。例如，如果我们想用下降幂 $x^{\underline{n}}$ 表示普通幂 $x^n$，前几项是：
$$
\begin{aligned}
x^0 &= x^{\underline{0}}; \\
x^1 &= x^{\underline{1}}; \\
x^2 &= x^{\underline{2}} + x^{\underline{1}}; \\
x^3 &= x^{\underline{3}} + 3x^{\underline{2}} + x^{\underline{1}}; \\
x^4 &= x^{\underline{4}} + 6x^{\underline{3}} + 7x^{\underline{2}} + x^{\underline{1}}.
\end{aligned}
$$

这些系数看起来很像表 258 中的数，只是左右镜像对称；因此我们可以相当确定，一般公式为
$$
x^n = \sum_{k} \genfrac\{\}{0pt}{}{n}{k} x^{\underline{k}},\quad \text{integer }n\ge 0. \tag{6.10}
$$

事实证明，一个简单的归纳法就能完成证明：我们有 $x\cdot x^{\underline{k}} = x^{\underline{k+1}} + k x^{\underline{k}}$，因为 $x^{\underline{k+1}} = x^{\underline{k}}(x - k)$；因此 $x\cdot x^{\underline{n-1}}$ 等于
$$
\begin{aligned}
x\sum_{k}\genfrac\{\}{0pt}{}{n-1}{k}x^{\underline{k}}
&= \sum_{k}\genfrac\{\}{0pt}{}{n-1}{k}x^{\underline{k+1}} + \sum_{k}\genfrac\{\}{0pt}{}{n-1}{k}k x^{\underline{k}} \\
&= \sum_{k}\genfrac\{\}{0pt}{}{n-1}{k-1}x^{\underline{k}}+ \sum_{k}\genfrac\{\}{0pt}{}{n-1}{k}k x^{\underline{k}} \\
&= \sum_{k}\left(
 k\genfrac\{\}{0pt}{}{n-1}{k}+ \genfrac\{\}{0pt}{}{n-1}{k-1}
\right)x^{\underline{k}} 
= \sum_{k}\genfrac\{\}{0pt}{}{n}{k}x^{\underline{k}}.
\end{aligned}
$$
换句话说，斯特林子集数是将阶乘幂展开为普通幂时所对应的系数。

我们也可以反过来，因为斯特林轮换数是将普通幂展开为阶乘幂时的系数：
$$
\begin{aligned}
x^{\overline{0}} &= x^0; \\
x^{\overline{1}} &= x^1; \\
x^{\overline{2}} &= x^2 - x^1; \\
x^{\overline{3}} &= x^3 - 3x^2 + 2x^1; \\
x^{\overline{4}} &= x^4 - 6x^3 + 11x^2 - 6x^1.
\end{aligned}
$$

我们有 $(x + n - 1) \cdot x^{\underline{k}} = x^{\underline{k+1}} + (n - 1) x^{\underline{k}}$，因此用与刚才类似的证明方法可以得出：
$$
(x + n - 1)x^{\underline{n-1}}
= (x + n - 1)\sum_{k}\genfrac{[}{]}{0pt}{}{n-1}{k}x^k
= \sum_{k}\genfrac{[}{]}{0pt}{}{n}{k}x^k.
$$

由此即可通过归纳法证明一般公式：
$$
x^{\underline{n}} = \sum_{k} \genfrac{[}{]}{0pt}{}{n}{k} x^k,\quad \text{integer }n\ge 0. \tag{6.11}
$$

（令 \(x=1\) 就再次得到式 (6.9)。）

不过你可能会问：这个等式用到的是上升阶乘幂\(x^{\overline{n}}\)，而式 (6.10) 用到的是下降阶乘幂\(x^{\underline{n}}\)。如果我们想把上升阶乘幂 \(x^{\overline{n}}\) 用普通幂表示，或者把下降阶乘幂 \(x^{\underline{n}}\) 用上升幂表示，该怎么办？很简单，只要添上一些正负号即可：
$$
x^{\overline{n}} = \sum_{k} \genfrac\{\}{0pt}{}{n}{k} (-1)^{n-k} x^k,\quad \text{integer }n\ge 0. \tag{6.12}
$$
$$
x^{\underline{n}} = \sum_{k} \genfrac{[}{]}{0pt}{}{n}{k} (-1)^{n-k} x^k,\quad \text{integer }n\ge 0. \tag{6.13}
$$

这是成立的，例如公式
$$
x^{\underline{4}} = x(x-1)(x-2)(x-3) = x^4 - 6x^3 + 11x^2 - 6x
$$
就跟公式
$$
x^{\overline{4}} = x(x+1)(x+2)(x+3) = x^4 + 6x^3 + 11x^2 + 6x
$$

只不过是符号交替变化而已。一般的恒等式
$$
x^{\underline{n}} = (-1)^n (-x)^{\overline{n}} \tag{6.14}
$$

这就是习题 2.17 中的恒等式，将 $x$ 取反后，它能把公式 (6.10) 转化为 (6.12)，把 (6.11) 转化为 (6.13)。

**表 264  基本斯特林数恒等式（整数 $n \ge 0$）。**
递推关系：
$$
\genfrac\{\}{0pt}{}{n}{k} = k\genfrac\{\}{0pt}{}{n-1}{k} + \genfrac\{\}{0pt}{}{n-1}{k-1}.
$$
$$
\genfrac{[}{]}{0pt}{}{n}{k} = (n-1)\genfrac{[}{]}{0pt}{}{n-1}{k} + \genfrac{[}{]}{0pt}{}{n-1}{k-1}.
$$

特殊取值：
$$
\genfrac\{\}{0pt}{}{n}{0} = \genfrac{[}{]}{0pt}{}{n}{0} = [n=0].
$$
$$
\genfrac\{\}{0pt}{}{n}{1} = [n>0];\quad
\genfrac{[}{]}{0pt}{}{n}{1} = (n-1)!\,[n>0].
$$
$$
\genfrac\{\}{0pt}{}{n}{2} = (2^{n-1}-1)[n>0];\quad
\genfrac{[}{]}{0pt}{}{n}{2} = (n-1)!\,H_{n-1}\,[n>0].
$$
$$
\genfrac\{\}{0pt}{}{n}{n-1} = \genfrac{[}{]}{0pt}{}{n}{n-1} = \binom{n}{2}.
$$
$$
\genfrac\{\}{0pt}{}{n}{n} = \genfrac{[}{]}{0pt}{}{n}{n} = \binom{n}{n} = 1.
$$
$$
\genfrac\{\}{0pt}{}{n}{k} = \genfrac{[}{]}{0pt}{}{n}{k} = \binom{n}{k} = 0,\quad \text{若 } k>n.
$$

幂之间的转换：
$$
x^n = \sum_k \genfrac\{\}{0pt}{}{n}{k} x^{\underline{k}}
     = \sum_k \genfrac\{\}{0pt}{}{n}{k} (-1)^{n-k} x^{\overline{k}}.
$$
$$
x^{\underline{n}} = \sum_k \genfrac{[}{]}{0pt}{}{n}{k} (-1)^{n-k} x^k;
\quad
x^{\overline{n}} = \sum_k \genfrac{[}{]}{0pt}{}{n}{k} x^k.
$$

反演公式：
$$
\sum_k \genfrac{[}{]}{0pt}{}{n}{k} \genfrac\{\}{0pt}{}{k}{m} (-1)^{n-k} = [m=n];
$$
$$
\sum_k \genfrac\{\}{0pt}{}{n}{k} \genfrac{[}{]}{0pt}{}{k}{m} (-1)^{n-k} = [m=n].
$$


**表 265  更多斯特林数恒等式（整数 $l,m,n \ge 0$）。**
$$
\genfrac\{\}{0pt}{}{n}{m+1} = \sum_{k} \binom{n}{k} \genfrac\{\}{0pt}{}{k}{m}. \tag{6.15}
$$
$$
\genfrac{[}{]}{0pt}{}{n}{m+1} = \sum_{k} \genfrac{[}{]}{0pt}{}{n}{k} \binom{k}{m}. \tag{6.16}
$$
$$
\genfrac\{\}{0pt}{}{n}{m} = \sum_{k} \binom{n}{k} \genfrac\{\}{0pt}{}{k}{m+1} (-1)^{n-k}. \tag{6.17}
$$
$$
\genfrac{[}{]}{0pt}{}{n}{m} = \sum_{k} \genfrac{[}{]}{0pt}{}{n+1}{k+1} \binom{k}{m} (-1)^{m-k}. \tag{6.18}
$$
$$
m!\genfrac\{\}{0pt}{}{n}{m} = \sum_{k}\binom{m}{k}k^n(-1)^{m-k}. \tag{6.19}
$$
$$
\genfrac\{\}{0pt}{}{n}{m+1} = \sum_{k=0}^{n}\genfrac\{\}{0pt}{}{k}{m}(m+1)^{n-k}. \tag{6.20}
$$
$$
\genfrac{[}{]}{0pt}{}{n}{m+1} = \sum_{k=0}^{n}\genfrac{[}{]}{0pt}{}{k}{m}n^{\underline{n-k}} = n!\sum_{k=0}^{n}\genfrac{[}{]}{0pt}{}{k}{m}\bigg/k!. \tag{6.21}
$$
$$
\genfrac\{\}{0pt}{}{m+n+1}{m} = \sum_{k=0}^{m}k\genfrac\{\}{0pt}{}{n+k}{k}. \tag{6.22}
$$
$$
\genfrac{[}{]}{0pt}{}{m+n+1}{m} = \sum_{k=0}^{m}(n+k)\genfrac{[}{]}{0pt}{}{n+k}{k}. \tag{6.23}
$$
$$
\binom{n}{m} = \sum_{k}\genfrac\{\}{0pt}{}{n+1}{k+1}\genfrac{[}{]}{0pt}{}{k}{m}(-1)^{m-k}. \tag{6.24}
$$
$$
n^{\underline{n-m}}[n\ge m] = \sum_{k}\genfrac{[}{]}{0pt}{}{n+1}{k+1}\genfrac\{\}{0pt}{}{k}{m}(-1)^{m-k}. \tag{6.25}
$$
$$
\genfrac\{\}{0pt}{}{n}{n-m} = \sum_{k} \binom{m-n}{m+k} \binom{m+n}{n+k} \genfrac{[}{]}{0pt}{}{m+k}{k}. \tag{6.26}
$$
$$
\genfrac{[}{]}{0pt}{}{n}{n-m} = \sum_{k} \binom{m-n}{m+k} \binom{m+n}{n+k} \genfrac\{\}{0pt}{}{m+k}{k}. \tag{6.27}
$$
$$
\genfrac\{\}{0pt}{}{l+n}{m} \binom{l+n}{l} = \sum_{k} \genfrac\{\}{0pt}{}{k}{l} \genfrac\{\}{0pt}{}{n-m}{k} \binom{n}{k}. \tag{6.28}
$$
$$
\genfrac{[}{]}{0pt}{}{l+n}{m} \binom{l+n}{l} = \sum_{k} \genfrac{[}{]}{0pt}{}{k}{l} \genfrac{[}{]}{0pt}{}{n-m}{k} \binom{n}{k}. \tag{6.29}
$$

我们可以记住像公式 (6.12) 中何时需要代入因子 $(-1)^{n-k}$，因为当 $x$ 很大时，幂次之间存在一种自然的大小次序：
$$
x^{\overline{n}} > x^n > x^{\underline{n}},\quad \forall x > n > 1. \tag{6.30}
$$
斯特林数 $\genfrac{[}{]}{0pt}{}{n}{k}$ 与 $\genfrac\{\}{0pt}{}{n}{k}$ 都是非负的，因此在用“大”幂次展开“小”幂次时，必须引入负号。

我们可以把 (6.11) 代入 (6.12)，从而得到一个二重和式：
$$
x^{\underline{n}} = \sum_{k} \genfrac\{\}{0pt}{}{n}{k} (-1)^{n-k} x^{\overline{k}}
= \sum_{k,m} \genfrac\{\}{0pt}{}{n}{k} \genfrac{[}{]}{0pt}{}{k}{m} (-1)^{n-k} x^m.
$$

该式对所有 $x$ 都成立，因此右侧 $x^0, x^1, \dots, x^{n-1}, x^{n+1}, x^{n+2}, \dots$ 的系数必须全为 0，由此可得恒等式
$$
\sum_{k} \genfrac\{\}{0pt}{}{n}{k} \genfrac{[}{]}{0pt}{}{k}{m} (-1)^{n-k} = [m = n], \quad \text{integer } m, n \ge 0. \tag{6.31}
$$

斯特林数与二项式系数一样，满足许多令人惊奇的恒等式。但这些恒等式不像我们在第5章中得到的那些那样用途广泛，因此它们的应用频率远没有那么高。所以对我们来说，最好只列出最简单的那些，以便将来在遇到棘手的斯特林数问题时查阅参考。表264和表265包含了最常用的公式，我们之前已经推导出来的主要恒等式也在其中重复列出。

在第5章研究二项式系数时，我们发现，为了让恒等式$\binom{n}{k} = \binom{n-1}{k} + \binom{n-1}{k-1}$不受限制地成立，将 $\dbinom{n}{k}$ 推广到负整数 $n$ 是很有益的。利用这个递推关系把 $\dbinom{n}{k}$ 扩展到超出组合意义的范围后，我们发现（见表164）：帕斯卡三角向上延伸时，本质上会以旋转形式重现自身。我们对斯特林三角也做同样尝试：如果规定基本递推关系

$$
\genfrac\{\}{0pt}{}{n}{k} = k\genfrac\{\}{0pt}{}{n-1}{k} + \genfrac\{\}{0pt}{}{n-1}{k-1},
$$
$$
\genfrac{[}{]}{0pt}{}{n}{k} = (n-1)\genfrac{[}{]}{0pt}{}{n-1}{k} + \genfrac{[}{]}{0pt}{}{n-1}{k-1}.
$$

对所有整数 $n$ 和 $k$ 都成立？如果我们再合理补充以下约定，解就会唯一：
$$
\genfrac\{\}{0pt}{}{0}{k} = \genfrac{[}{]}{0pt}{}{0}{k} = [k=0]
\text{ and }
\genfrac\{\}{0pt}{}{n}{0} = \genfrac{[}{]}{0pt}{}{n}{0} = [n=0]. \tag{6.32}
$$

**表 267  成对出现的斯特林三角**
|n|$\genfrac\{\}{0pt}{}{-n}{5}$|$\genfrac\{\}{0pt}{}{-n}{4}$|$\genfrac\{\}{0pt}{}{-n}{3}$|$\genfrac\{\}{0pt}{}{-n}{2}$|$\genfrac\{\}{0pt}{}{-n}{1}$|$\genfrac\{\}{0pt}{}{n}{0}$|$\genfrac\{\}{0pt}{}{n}{1}$|$\genfrac\{\}{0pt}{}{n}{2}$|$\genfrac\{\}{0pt}{}{n}{3}$|$\genfrac\{\}{0pt}{}{n}{4}$|$\genfrac\{\}{0pt}{}{n}{5}$|
|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|-5|1||||||||||
|-4|10|1|||||||||
|-3|35|6|1||||||||
|-2|50|11|3|1|||||||
|-1|24|6|2|1|1||||||
|0|0|0|0|0|0|1|||||
|1|0|0|0|0|0|0|1||||
|2|0|0|0|0|0|0|1|1|||
|3|0|0|0|0|0|0|1|3|1||
|4|0|0|0|0|0|0|1|7|6|1|
|5|0|0|0|0|0|0|1|15|25|10|1|

事实上，一个非常优美的规律浮现了出来：表示轮换的斯特林三角出现在表示子集的斯特林三角上方，反之亦然！这两类斯特林数由一个极其简洁的法则联系起来 [220, 221]：
$$
\genfrac{[}{]}{0pt}{}{n}{k} = \genfrac\{\}{0pt}{}{-k}{-n} ,\quad \text{integer }k,n. \tag{6.33}
$$

我们得到了一种**对偶性**，类似于最小值与最大值、向下取整 $\lfloor x\rfloor$ 与向上取整 $\lceil x\rceil$、上升幂 $x^{\overline{n}}$ 与下降幂 $x^{\underline{n}}$、最大公约数 gcd 与最小公倍数 lcm 之间的关系。在这种对应下，很容易验证递推式$\genfrac{[}{]}{0pt}{}{n}{k}=(n-1)\genfrac{[}{]}{0pt}{}{n-1}{k}+\genfrac{[}{]}{0pt}{}{n-1}{k-1}$ 和 $\genfrac\{\}{0pt}{}{n}{k} = k\genfrac\{\}{0pt}{}{n-1}{k} + \genfrac\{\}{0pt}{}{n-1}{k-1}$ 本质上是同一个式子。

## 6.2 EULERIAN NUMBERS 欧拉数


另一类数值三角也时常出现，它由欧拉提出[104, 813; 110, 第485页]，我们用尖括号来表示它的元素：$\left\langle \begin{matrix}n\\k\end{matrix} \right\rangle$。这里的尖括号形象地表示“小于”和“大于”；$\left\langle \begin{matrix}n\\k\end{matrix} \right\rangle$ 是集合 $\{1,2,\dots,n\}$ 的排列 $\pi_1\pi_2\cdots\pi_n$ 中**恰好有 $k$ 个上升位**的排列个数。所谓上升位，是指满足 $\pi_i < \pi_{i+1}$ 的位置 $i$。（注意：这个记号不如斯特林数的记号通用，但我们会看到它是非常合理的。）

例如，集合 $\{1,2,3,4\}$ 的排列中，有 11 个排列恰好包含 2 个上升位：
$$
1324, 1423, 2314, 2413, 3412;        \\
1243, 1342, 2341; 2134, 3124, 4123.
$$

（第一行列出的是满足 $\pi_1 < \pi_2 > \pi_3 < \pi_4$ 的排列；第二行列出的是满足 $\pi_1 < \pi_2 < \pi_3 > \pi_4$ 与 $\pi_1 > \pi_2 < \pi_3 < \pi_4$ 的排列。）因此 $\left\langle \begin{matrix}4\\2\end{matrix} \right\rangle = 11$。

**表 268 欧拉三角**
|$n$|$\left\langle \begin{matrix}n\\0\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\1\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\2\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\3\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\4\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\5\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\6\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\7\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\8\end{matrix} \right\rangle$|$\left\langle \begin{matrix}n\\9\end{matrix} \right\rangle$|
|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|0|1||||||||||
|1|1|0|||||||||
|2|1|1|0||||||||
|3|1|4|1|0|||||||
|4|1|11|11|1|0||||||
|5|1|26|66|26|1|0|||||
|6|1|57|302|302|57|1|0||||
|7|1|120|1191|2416|1191|120|1|0|||
|8|1|247|4293|15619|15619|4293|247|1|0||
|9|1|502|14608|88234|156190|88234|14608|502|1|0|


表 268 列出了最小的一些欧拉数；可以看到这次标志性的序列是 1, 11, 11, 1。当 $n>0$ 时，上升位最多有 $n-1$ 个，因此在三角的对角线上我们有 $\left\langle \begin{matrix}n\\n\end{matrix} \right\rangle = [n=0]$。

欧拉三角与帕斯卡三角类似，左右是对称的。但在这种情形下，对称规律略有不同：
$$
\left\langle \begin{matrix}n\\k\end{matrix} \right\rangle = \left\langle \begin{matrix}n\\n-1-k\end{matrix} \right\rangle,\quad \text{整数 }n>0; \tag{6.34}
$$

排列 $\pi_1\pi_2\cdots\pi_n$ 有 $n-1-k$ 个上升位，当且仅当其翻转排列 $\pi_n\cdots\pi_2\pi_1$ 有 $k$ 个上升位。

我们来推导欧拉数 $\left\langle \begin{matrix}n\\k\end{matrix} \right\rangle$ 的递推关系。将元素 $n$ 插入 $\{1,\dots,n-1\}$ 的任意排列 $\rho = \rho_1 \dots \rho_{n-1}$ 中，可得到 $n$ 个 $\{1,2,\dots,n\}$ 的排列。假设把 $n$ 插入位置 $j$，得到排列 $\pi = \rho_1 \dots \rho_{j-1} n \rho_j \dots \rho_{n-1}$。若 $j=1$ 或 $\rho_{j-1} < \rho_j$，$\pi$ 的上升位数量与 $\rho$ 相同；若 $\rho_{j-1} > \rho_j$ 或 $j=n$，$\pi$ 的上升位数量比 $\rho$ 多 1。因此，从含 $k$ 个上升位的排列 $\rho$ 出发，有 $(k+1)\left\langle \begin{matrix}n-1\\k\end{matrix} \right\rangle$ 种方式得到含 $k$ 个上升位的 $\pi$；再加上从含 $k-1$ 个上升位的排列 $\rho$ 出发，有 $\left( (n-2)-(k-1)+1 \right)\left\langle \begin{matrix}n-1\\k-1\end{matrix} \right\rangle$ 种方式。最终递推关系为：
$$
\left\langle \begin{matrix}n\\k\end{matrix} \right\rangle = (k+1)\left\langle \begin{matrix}n-1\\k\end{matrix} \right\rangle + (n-k)\left\langle \begin{matrix}n-1\\k-1\end{matrix} \right\rangle , \text{integer n }> 0. \tag{6.35}
$$

我们再次通过设定初始条件来启动递推关系：
$$
\left\langle \begin{matrix} 0 \\ k \end{matrix} \right\rangle = [k=0],\quad \text{整数 }k. \tag{6.36}
$$

并且我们约定，当 $k < 0$ 时，$\left\langle \begin{matrix} n \\ k \end{matrix} \right\rangle = 0$。

欧拉数之所以重要，主要是因为它在普通幂与连续二项式系数之间建立了一种不寻常的联系：
$$
x^n = \sum_k \left\langle \begin{matrix} n \\ k \end{matrix} \right\rangle \binom{x+k}{n},\quad \text{integer }n \ge 0. \tag{6.37}
$$

（这被称为沃皮茨基恒等式[378]。）例如，我们有：
$$
\begin{aligned}
x^2 &= \binom{x}{2} + \binom{x+1}{2}, \\
x^3 &= \binom{x}{3} + 4\binom{x+1}{3} + \binom{x+2}{3}, \\
x^4 &= \binom{x}{4} + 11\binom{x+1}{4} + 11\binom{x+2}{4} + \binom{x+3}{4},
\end{aligned}
$$
依此类推。式 (6.37) 可以用数学归纳法轻松证明（见习题 14）。

顺便一提，式 (6.37) 还给出了求前 $n$ 个平方数之和的另一种方法：
我们有 $k^2= \langle \begin{matrix} 2 \\ 0 \end{matrix} \rangle \binom{k}{2} + \langle \begin{matrix} 2 \\ 1 \end{matrix} \rangle \binom{k+1}{2} = \binom{k}{2} + \binom{k+1}{2},$ 因此
$$
\begin{aligned}
1^2 + 2^2 + \cdots + n^2
&= \left( \binom{1}{2} + \binom{2}{2} + \cdots + \binom{n}{2} \right) + \left( \binom{2}{2} + \binom{3}{2} + \cdots + \binom{n+1}{2} \right) \\
&= \binom{n+1}{3} + \binom{n+2}{3} = \frac16 (n+1)n\bigl((n-1)+(n+2)\bigr).
\end{aligned}
$$

欧拉数递推式 (6.35) 比斯特林数递推式 (6.3) 和 (6.8) 稍微复杂一些，因此我们并不指望 $\left\langle \begin{matrix} n \\ k \end{matrix} \right\rangle$ 满足同样多的简单恒等式。尽管如此，它们仍然满足一些恒等式：
$$
\left\langle \begin{matrix} n \\ m \end{matrix} \right\rangle
= \sum_{k=0}^m \binom{n+1}{k} (m+1-k)^n (-1)^k; \tag{6.38}
$$
$$
m! \left\{ \begin{matrix} n \\ m \end{matrix} \right\}
= \sum_k \left\langle \begin{matrix} n \\ k \end{matrix} \right\rangle \binom{k}{n-m}; \tag{6.39}
$$
$$
\left\langle \begin{matrix} n \\ m \end{matrix} \right\rangle
= \sum_k \left\{ \begin{matrix} n \\ k \end{matrix} \right\} \binom{n-m}{k} (-1)^{n-k-m} k!. \tag{6.40}
$$

如果将 (6.39) 式乘以 $z^{n-m}$ 并对 $m$ 求和，可得 $\sum_m \left\{ \begin{matrix} n \\ m \end{matrix} \right\} m! z^{n-m}= \sum_k \left\langle \begin{matrix} n \\ k \end{matrix} \right\rangle (z+1)^k.$。将 $z$ 替换为 $z-1$ 并比较 $z^k$ 的系数，即可得到 (6.40) 式。因此这后两个恒等式本质上是等价的。第一个恒等式 (6.38) 在 $m$ 取较小值时能给出特殊值：
$$
\left\langle \begin{matrix} n \\ 0 \end{matrix} \right\rangle = 1; \quad
\left\langle \begin{matrix} n \\ 1 \end{matrix} \right\rangle = 2^n - n - 1; \quad
\left\langle \begin{matrix} n \\ 2 \end{matrix} \right\rangle = 3^n - (n+1)2^n + \binom{n+1}{2}.
$$

**表 270 二阶欧拉数三角形**
|n|<<n,0>>|<<n,1>>|<<n,2>>|<<n,3>>|<<n,4>>|<<n,5>>|<<n,6>>|<<n,7>>|<<n,8>>|
|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|0|1|||||||||
|1|1|0||||||||
|2|1|2|0|||||||
|3|1|8|6|0||||||
|4|1|22|58|24|0|||||
|5|1|52|328|444|120|0||||
|6|1|114|1452|4400|3708|720|0|||
|7|1|240|5610|32120|58140|33984|5040|0||
|8|1|494|19950|195800|644020|785304|341136|40320|0|

这里我们不必再深入探讨欧拉数；通常只要知道它们存在，并且在需要时能查阅基本恒等式列表就足够了。不过，在结束这个话题之前，我们应当留意另一种系数的三角排列，如表 270 所示。我们把这些数称为**二阶欧拉数** $\left\langle\!\!\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle\!\!\right\rangle$，因为它们满足与式 (6.35) 相似的递推关系，只是在一处将 $n$ 替换成了 $2n-1$。
$$
\left\langle\!\!\left\langle n\atop k\right\rangle\!\!\right\rangle = (k+1)\left\langle\!\!\left\langle n-1\atop k\right\rangle\!\!\right\rangle + (2n-1-k)\left\langle\!\!\left\langle n-1\atop k-1\right\rangle\!\!\right\rangle. \tag{6.41}
$$

这些数有着奇妙的组合意义，最早由 Gessel 和 Stanley [147] 发现：如果我们构造多重集合 $\{1,1,2,2,\dots,n,n\}$ 的排列，且满足特殊性质：对每个 $1\le m\le n$，两个 $m$ 之间的所有数都大于 $m$，那么 $\left\langle\!\!\left\langle n\atop k\right\rangle\!\!\right\rangle$ 就是这类排列中**恰有 $k$ 个上升位**的数目。例如，$\{1,1,2,2,3,3\}$ 恰有 8 个满足条件且只有 1 个上升位的排列：
$$
113322, 133221, 221331, 221133, 223311, 233211, 331122, 331221.
$$

因此 $\left\langle\!\!\left\langle 3\atop 1\right\rangle\!\!\right\rangle = 8$。多重集合 $\{1,1,2,2,\dots,n,n\}$ 总共有
$$
\sum_k \left\langle\!\!\left\langle n\atop k\right\rangle\!\!\right\rangle
= (2n-1)(2n-3)\cdots(1)
= \frac{(2n)!}{2^n n!}.
\tag{6.42}
$$
个满足条件的排列，因为两个 $n$ 必须相邻，而且在 $n-1$ 对应的排列中共有 $2n-1$ 个位置可以插入它们。例如，当 $n=3$ 时，排列 $1221$ 有 5 个插入位置，分别得到 $331221$，$133221$，$123321$，$122331$ 和 $122133$。递推式 (6.41) 可以通过推广我们对普通欧拉数所用的论证方法来证明。



