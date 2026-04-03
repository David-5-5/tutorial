# 6 Special Numbers 特殊数

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

轮换是环形排列，就像我们在第4章讨论过的项链。轮换可以更简洁地记作 $[A, B, C, D]$，并约定
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
$$
\1\ 2\ 3\ 4\ 5\ 6\ 7\ 8\ 9 \\ 
3\ 8\ 4\ 7\ 2\ 9\ 1\ 5\ 6
$$

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

二阶欧拉数之所以重要，主要是因为它们与斯特林数存在关联[148]：对 $n$ 进行归纳可得
$$
\left\{ \begin{matrix} x \\ x-n \end{matrix} \right\}
= \sum_k \left\langle\!\!\left\langle n\atop k\right\rangle\!\!\right\rangle \binom{x+n-1}{2n-k},
\quad \text{integer } n\ge 0; \tag{6.43}
$$
$$
\left[ \begin{matrix} x \\ x-n \end{matrix} \right]
= \sum_k \left\langle\!\!\left\langle n\atop k\right\rangle\!\!\right\rangle \binom{x+k}{2n},
\quad \text{integer } n\ge 0. \tag{6.44}
$$

例如，
$$
\left\{ \begin{matrix} x \\ x-1 \end{matrix} \right\} = \binom{x}{2},\qquad
\left[ \begin{matrix} x \\ x-1 \end{matrix} \right] = \binom{x}{2};
$$
$$
\left\{ \begin{matrix} x \\ x-2 \end{matrix} \right\} = \binom{x+1}{4} + 2\binom{x}{4},\qquad
\left[ \begin{matrix} x \\ x-2 \end{matrix} \right] = \binom{x}{4} + 2\binom{x+1}{4};
$$
$$
\left\{ \begin{matrix} x \\ x-3 \end{matrix} \right\} = \binom{x+2}{6} + 8\binom{x+1}{6} + 6\binom{x}{6},\qquad
\left[ \begin{matrix} x \\ x-3 \end{matrix} \right] = \binom{x}{6} + 8\binom{x+1}{6} + 6\binom{x+2}{6}.
$$

（我们在式 (6.7) 中已经见过 $n=1$ 的情形。）这些恒等式对任意整数 $x$ 与非负整数 $n$ 都成立。由于右端是关于 $x$ 的多项式，我们可以用 (6.43) 和 (6.44) 把斯特林数 $\left\{\begin{matrix}x\\x-n\end{matrix}\right\}$ 与 $\left[\begin{matrix}x\\x-n\end{matrix}\right]$ 延拓定义到任意实数（或复数）$x$ 上。

若 $n>0$，则多项式 $\left\{\begin{matrix}x\\x-n\end{matrix}\right\}$ 与 $\left[\begin{matrix}x\\x-n\end{matrix}\right]$ 在 $x=0$，$x=1$，$\dots$，$x=n$ 时取值为 $0$，因此它们可被 $(x-0)$，$(x-1)$，$\dots$，$(x-n)$ 整除。将这些已知因子提出后剩下的部分很值得研究。我们按照如下规则定义斯特林多项式 $\sigma_n(x)$
$$
\sigma_n(x) = \left[ \begin{matrix} x \\ x-n \end{matrix} \right] \bigg/ \bigl(x(x-1)\cdots(x-n)\bigr). \tag{6.45}
$$

（$\sigma_n(x)$ 的次数为 $n-1$。）前几项为
$$
\begin{aligned}
\sigma_0(x) &= 1/x, \\
\sigma_1(x) &= 1/2, \\
\sigma_2(x) &= (3x-1)/24, \\
\sigma_3(x) &= (x^2-x)/48, \\
\sigma_4(x) &= (15x^3-30x^2+5x+2)/5760.
\end{aligned}
$$

它们可以通过二阶欧拉数来计算；例如，
$$
\sigma_3(x) = \frac{(x-4)(x-5) + 8(x-4)(x+1) + 6(x+2)(x+1)}{6!}.
$$

**表 272 斯特林卷积公式**
$$
r\sum_{k=0}^n \sigma_k(r+tk)\,\sigma_{n-k}(s+t(n-k)) = (r+s)\,\sigma_n(r+s+tn), \tag{6.46}
$$
$$
s\sum_{k=0}^n k\sigma_k(r+tk)\,\sigma_{n-k}(s+t(n-k)) = n\,\sigma_n(r+s+tn), \tag{6.47} 
$$
$$
\left\{\begin{matrix}n\\m\end{matrix}\right\} = (-1)^{n-m+1} \frac{n!}{(m-1)!}\,\sigma_{n-m}(-m), \tag{6.48} 
$$
$$
\left[\begin{matrix}n\\m\end{matrix}\right] = \frac{n!}{(m-1)!}\,\sigma_{n-m}(n). \tag{6.49}
$$

事实证明，这些多项式满足两个非常优美的恒等式：
$$
\left( \frac{z e^z}{e^z - 1} \right)^x = x \sum_{n\ge 0} \sigma_n(x) z^n; \tag{6.50}
$$
$$
\left( \frac{1}{z}\ln\frac{1}{1-z} \right)^x = x \sum_{n\ge 0} \sigma_n(x+n) z^n. \tag{6.51}
$$

并且一般地，如果 $S_t(z)$ 是满足下式的幂级数
$$\ln\left(1-zS_t(z)^{t-1}\right) = -zS_t(z)^t. \tag{6.52}$$
那么
$$S_t(z)^x = x \sum_{n\ge 0} \sigma_n(x+tn) z^n. \tag{6.53}$$

因此我们可以像在表 202 中对二项式系数那样，得到斯特林数的一般卷积公式，其结果列于表 272。当一个斯特林数的求和式不满足表 264 或 265 中的恒等式时，表 272 或许正是合适的工具。（本章稍后在式 (6.100) 后会给出一个例子。习题 7.19 讨论了基于形如 (6.50) 和 (6.53) 这类恒等式的卷积一般原理。）

## 6.3 HARMONIC NUMBERS 调和数
现在是时候更细致地考察调和数了，我们最早在第 2 章就已经接触过它：
$$
H_n = 1 + \frac12 + \frac13 + \cdots + \frac1n = \sum_{k=1}^n \frac1k,\quad \text{integer } n\ge 0. \tag{6.54}
$$

这些数在算法分析中出现得极为频繁，因此计算机科学家需要为它们专门设计一种记号。我们使用 $H_n$，其中字母 $H$ 代表“调和（harmonic）”，因为波长为 $1/n$ 的音调被称为波长为 $1$ 的音调的第 $n$ 次谐波。前几项的值如下所示：
| $n$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|-----|---|---|---|---|---|---|---|---|---|---|----|
| $H_n$ | 0 | $1$ | $\dfrac{3}{2}$ | $\dfrac{11}{6}$ | $\dfrac{25}{12}$ | $\dfrac{137}{60}$ | $\dfrac{49}{20}$ | $\dfrac{363}{140}$ | $\dfrac{761}{280}$ | $\dfrac{7129}{2520}$ | $\dfrac{7381}{2520}$ |

习题 21 表明：当 $n>1$ 时，$H_n$ 永远不是整数。

这里有一个纸牌魔术，其思路源自 R. T. Sharp [325]，可以说明调和数是如何在简单场景中自然出现的。给定 $n$ 张纸牌和一张桌子，我们要在重力规律的约束下，将纸牌堆叠在桌沿上方，以获得尽可能大的悬伸量。

为了更明确地定义这个问题，我们要求纸牌的边与桌沿保持平行；否则我们可以通过旋转纸牌，让角伸出更远来增大悬伸量。为了让结果更简洁，我们假设每张纸牌的长度为 $2$ 个单位。

对于单张纸牌，当其重心恰好位于桌沿正上方时，悬伸量最大。重心在纸牌正中，因此我们可以获得纸牌长度的一半，也就是 $1$ 个单位的悬伸量。

对于两张纸牌，不难发现最大悬伸出现在：顶层纸牌的重心恰好在第二张纸牌的边缘上方，且两张纸牌的合重心恰好在桌沿上方。两张纸牌的合重心位于它们重合部分的中点，因此我们可以额外获得半个单位的悬伸量。

这一规律提示了一种通用方法：我们摆放纸牌时，让最上方 $k$ 张牌的重心恰好位于第 $k+1$ 张牌（支撑上方 $k$ 张的牌）的边缘上方。桌子则扮演第 $n+1$ 张牌的角色。为用代数形式表示这一条件，设 $d_k$ 为从最上方纸牌的最外端到从上数第 $k$ 张牌对应边缘的距离。于是 $d_1 = 0$，并且我们希望 $d_{k+1}$ 等于前 $k$ 张牌的重心位置：
$$
d_{k+1} = \frac{(d_1+1)+(d_2+1)+\cdots+(d_k+1)}{k},\quad \text{for } 1\le k\le n. \tag{6.55}
$$

（$k$ 个物体的重心位置为 $(w_1p_1+\cdots+w_kp_1)/(w_1+\cdots+w_k)$，其中 $w_1,\dots,w_k$ 为各物体重量，$p_1,\dots,p_k$ 为对应重心位置。）我们可以把这个递推式改写成两种等价形式：
$$
k d_{k+1} = k + d_1 + \cdots + d_{k-1} + d_k,\quad k\ge 0; \\
(k-1) d_k = k-1 + d_1 + \cdots + d_{k-1},\quad k\ge 1.
$$

将两式相减可得
$$
k d_{k+1} - (k-1) d_k = 1 + d_k,\quad k\ge 1;
$$

因此 $d_{k+1} = d_k + 1/k$。第二张牌会比第三张多出半个单位的偏移，第三张比第四张多出 $1/3$ 个单位，依此类推。通过归纳法可得通项公式
$$
d_{k+1} = H_k \tag{6.56}
$$
令 $k=n$，则 $d_{n+1}=H_n$ 即为按上述方式堆叠 $n$ 张牌时的总悬伸量。

我们是否可以不把每张牌都推到极限位置，而是适当回缩、积攒“重力势能”以换取更大的最终悬伸量？答案是否定的。任何平衡的摆放方式都满足
$$
d_{k+1} \le \frac{(1+d_1)+(1+d_2)+\cdots+(1+d_k)}{k},\quad 1\le k\le n.
$$
又有 $d_1=0$，由归纳法即可推出 $d_{k+1}\le H_k$。

可以看到，不需要太多张牌，最上面的一张就能完全伸出桌沿之外。我们需要超过一倍牌长的悬伸量，也就是 $2$ 个单位。第一个超过 $2$ 的调和数是 $H_4 = \frac{25}{12}$，所以只需要 $4$ 张牌就够了。

而用 52 张牌时，悬伸量为 $H_{52}$ 个单位，折算成牌长约为 $H_{52}/2 \approx 2.27$ 倍牌长。（我们很快会学到一个公式，它能直接近似计算大 $n$ 时的 $H_n$，而不用把一大堆分数逐个相加。）

一个有趣的问题叫作“橡皮筋上的蠕虫”，它以另一种形式展现了调和数。一只缓慢但执着的蠕虫 W 从一米长的橡皮筋一端开始，以每分钟 1 厘米的速度向另一端爬行。每分钟结束时，同样执着的橡皮筋看守者 K（毕生唯一目标就是刁难 W）会把橡皮筋拉长 1 米。于是爬行 1 分钟后，W 距离起点 1 厘米、距终点 99 厘米；随后 K 拉长 1 米。在拉伸过程中，W 保持相对位置不变：距起点 1%、距终点 99%；因此 W 现在离起点 2 厘米、离终点 198 厘米。W 再爬 1 分钟后，已爬 3 厘米、还剩 197 厘米；但 K 又拉伸橡皮筋，距离变为 4.5 厘米和 295.5 厘米，依此类推。蠕虫最终能到达终点吗？它一直在前进，但终点似乎退得更快。（我们假设 K 和 W 长生不老，橡皮筋拥有无限弹性，且蠕虫体积无限小。）

我们来写出对应的公式。当 K 拉伸橡皮筋时，蠕虫已经爬过的长度占橡皮筋总长的比例保持不变。因此它第 1 分钟爬行了总长的 $1/100$，第 2 分钟爬行了总长的 $1/200$，第 3 分钟为 $1/300$，依此类推。$n$ 分钟后，它爬过的比例为
$$
\frac{1}{100}\left(1+\frac12+\frac13+\cdots+\frac1n\right)
=\frac{H_n}{100}. \tag{6.57}
$$
所以只要 $H_n$ 超过 $100$，蠕虫就能到达终点。

我们很快就会学习如何对大 $n$ 估算 $H_n$；现在先通过“超级蠕虫”在同一情境下的表现来检验我们的分析。超级蠕虫不同于普通蠕虫，每分钟能爬 50 厘米；按照刚才的推导，$n$ 分钟后它将爬过橡皮筋总长的 $H_n/2$。如果我们的推理正确，超级蠕虫应该在 $n$ 达到 4 之前就到达终点，因为 $H_4>2$。事实也确实如此，简单计算可知：3 分钟后它只剩 $33\frac13$ 厘米要爬。它会在 3 分 40 秒整到达终点。

调和数也出现在斯特林三角形中。我们来尝试求出 $\displaystyle\left[\begin{array}{c}n\\2\end{array}\right]$ 的闭式，它表示 $n$ 个元素恰好包含两个轮换的排列数。递推式 (6.8) 告诉我们
$$
\left[\begin{array}{c}n+1\\2\end{array}\right]
= n\left[\begin{array}{c}n\\2\end{array}\right] + \left[\begin{array}{c}n\\1\end{array}\right]
= n\left[\begin{array}{c}n\\2\end{array}\right] + (n-1)!,\quad n>0;
$$
这个递推式很适合用第 2 章的求和因子法：
$$
\frac1{n!}\left[\begin{array}{c}n+1\\2\end{array}\right]
= \frac1{(n-1)!}\left[\begin{array}{c}n\\2\end{array}\right] + \frac1n.
$$
展开这个递推式可得 $\displaystyle\frac1{n!}\left[\begin{array}{c}n+1\\2\end{array}\right] = H_n$，因此
$$
\left[\begin{array}{c}n+1\\2\end{array}\right] = n!\,H_n. \tag{6.58}
$$
我们在第 2 章已经证明调和级数 $\sum_k 1/k$ 是发散的，这意味着当 $n\to\infty$ 时 $H_n$ 可以任意大。不过我们当时的证明是间接的。

我们曾发现某个无穷级数 (2.58) 在重排后会得到不同结果，因此 $\sum_k 1/k$ 不可能有界。$H_n\to\infty$ 这一事实看起来有些反直觉，因为它意味着：足够多的纸牌堆叠起来可以伸出桌沿一英里甚至更远，而蠕虫 W 最终也能爬到橡皮筋的尽头。因此我们来更细致地考察大 $n$ 时 $H_n$ 的大小。

要看出 $H_n\to\infty$，最简单的方法或许是按 2 的幂次对项分组：第 1 组放 1 项，第 2 组放 2 项，第 3 组放 4 项，第 4 组放 8 项，依此类推：
$$
\underbrace{\frac11}_{\text{group 1}}
+\underbrace{\frac12+\frac13}_{\text{group 2}}
+\underbrace{\frac14+\frac15+\frac16+\frac17}_{\text{group 3}}
+\underbrace{\frac18+\frac19+\cdots+\frac1{15}}_{\text{group 4}}
+\cdots.
$$
第 2 组的两项都介于 $1/4$ 与 $1/2$ 之间，因此该组之和介于 $2\cdot1/4=1/2$ 与 $2\cdot1/2=1$ 之间。第 3 组的四项都介于 $1/8$ 与 $1/4$ 之间，因此它们的和也介于 $1/2$ 与 $1$ 之间。事实上，第 $k$ 组共有 $2^{k-1}$ 项，每一项都介于 $2^{-k}$ 与 $2^{1-k}$ 之间，因此每一组的和都介于 $1/2$ 与 $1$ 之间。

这种分组方法告诉我们：若 $n$ 落在第 $k$ 组，则必有 $H_n > k/2$ 且 $H_n \le k$（对 $k$ 归纳可证）。于是 $H_n\to\infty$，并且实际上
$$
\frac{\lfloor\lg n\rfloor+1}{2} < H_n \le \lfloor\lg n\rfloor+1. \tag{6.59}
$$
我们现在把 $H_n$ 的范围锁定在 2 倍因子之内。虽然调和数趋于无穷，但它只是对数增长——也就是说增长得相当缓慢。

只要再多做一点推导并借助一点微积分，就能得到更精确的界。我们在第 2 章已经知道，$H_n$ 是连续函数 $\ln n$ 的离散类比。自然对数定义为曲线下的面积，因此可以用几何方式进行比较： (图略)

曲线在 $1$ 到 $n$ 之间的面积为 $\int_1^n \frac{dx}{x} = \ln n$，它小于 $n$ 个矩形的面积之和 $\sum_{k=1}^n \frac1k = H_n$。于是 $\ln n < H_n$，这一比 (6.59) 更精细的结果。而把矩形换一种摆放方式，我们就能得到类似的上界：(图略)

这一次，$n$ 个矩形的总面积 $H_n$ 小于第一个矩形的面积加上曲线下的面积。我们就此证明了
$$
\ln n < H_n < \ln n + 1,\quad n>1. \tag{6.60}
$$
现在我们对 $H_n$ 的估值误差不超过 1。

**二阶调和数** $H_n^{(2)}$ 是对倒数的平方求和，而非单纯对倒数求和：
$$
H_n^{(2)} = 1 + \frac14 + \frac19 + \cdots + \frac1{n^2}
= \sum_{k=1}^n \frac1{k^2}.
$$
类似地，我们把 **$r$ 阶调和数** 定义为 $(-r)$ 次幂的和：
$$
H_n^{(r)} = \sum_{k=1}^n \frac1{k^r}. \tag{6.61}
$$
若 $r>1$，则当 $n\to\infty$ 时这些数会趋于一个极限；我们在习题 2.31 中提过，这个极限通常称为**黎曼 ζ 函数**：
$$
\zeta(r) = H_\infty^{(r)} = \sum_{k\ge1} \frac1{k^r}. \tag{6.62}
$$

欧拉 [103] 发现了一种巧妙方法，能用广义调和数逼近普通调和数 $H_n^{(1)}$。考察无穷级数
$$
\ln\!\left(\frac{k}{k-1}\right)
= \frac1k + \frac1{2k^2} + \frac1{3k^3} + \frac1{4k^4} + \cdots, \tag{6.63}
$$
它在 $k>1$ 时收敛。左边是 $\ln k - \ln(k-1)$，因此对 $2\le k\le n$ 两边求和后，左边会发生望远镜消去，得到
$$
\begin{aligned}
\ln n - \ln 1
&= \sum_{k=2}^n \left(
\frac1k + \frac1{2k^2} + \frac1{3k^3} + \frac1{4k^4} + \cdots
\right) \\
&= \bigl(H_n - 1\bigr) + \frac12\bigl(H_n^{(2)} - 1\bigr) + \frac13\bigl(H_n^{(3)} - 1\bigr) + \frac14\bigl(H_n^{(4)} - 1\bigr) + \cdots.
\end{aligned}
$$

整理后即可得到 $H_n$ 与 $\ln n$ 之差的表达式：
$$
H_n - \ln n
= 1 - \frac12\bigl(H_n^{(2)}-1\bigr) - \frac13\bigl(H_n^{(3)}-1\bigr) - \frac14\bigl(H_n^{(4)}-1\bigr) - \cdots.
$$

当 $n\to\infty$ 时，右边趋于极限值
$$
1 - \frac12\bigl(\zeta(2)-1\bigr) - \frac13\bigl(\zeta(3)-1\bigr) - \frac14\bigl(\zeta(4)-1\bigr) - \cdots,
$$
这个值如今被称为*欧拉常数*，通常用希腊字母 $\gamma$ 表示。事实上 $\zeta(r)-1$ 近似等于 $1/2^r$，因此这个无穷级数收敛得相当快，我们可以算出其小数值：

$$
\gamma = 0.5772156649\dots \tag{6.64}
$$

欧拉的推导确立了极限关系
$$
\lim_{n\to\infty}(H_n - \ln n) = \gamma. \tag{6.65}
$$
这说明 $H_n$ 大致落在式 (6.60) 上下界之间约 58% 的位置。我们正在逐步逼近它的精确值。

正如第 9 章将要介绍的，还可以做进一步精细化。我们将会证明：
$$
H_n = \ln n + \gamma + \frac1{2n} - \frac1{12n^2} + \frac{\varepsilon_n}{120n^4},\quad 0<\varepsilon_n<1. \tag{6.66}
$$
利用这个公式可以直接得出第一百万个调和数
$$
H_{1000000} \approx 14.3927267228657236313811275,
$$
而无需把一百万个分数相加。这也意味着，一百万张牌叠起来可以伸出桌沿超过七个牌长。

式 (6.66) 对橡皮筋上的蠕虫问题说明了什么？因为 $H_n$ 无界，蠕虫最终一定能到达终点，也就是当 $H_n$ 首次超过 100 时。根据 $H_n$ 的近似式，这会发生在 $n$ 约等于
$$
e^{100-\gamma} \approx e^{99.423}
$$
的时候。

事实上，习题 9.49 证明：临界的 $n$ 值要么是 $\lfloor e^{100-\gamma}\rfloor$，要么是 $\lceil e^{100-\gamma}\rceil$。我们可以想象蠕虫 W 在漫长爬行后终于冲过终点、取得胜利时的场景，这让看守者 K 极为懊恼——而这距离它开始爬行已经过去了大约 287 万亿亿亿个世纪。（此时橡皮筋已经被拉伸到超过 $10^{27}$ 光年长，上面的分子早已被拉得极度分散。）

## 6.4 HARMONIC SUMMATION 调和求和
现在我们来看一些包含调和数的求和公式，先回顾一下第2章学过的几个结论。我们在式(2.36)和(2.57)中已经证明：
$$
\sum_{k=1}^n H_k = (n+1)H_n - n; \tag{6.67}
$$
$$
\sum_{k=1}^n kH_k = \frac{n(n+1)}{2}H_n - \frac{n(n+1)}{4}. \tag{6.68}
$$

让我们大胆地求解一个更一般的求和式，它把上面两个式子都作为特例包含在内：当 $m$ 为非负整数时，求和
$$
\sum_{0\le k<n}\binom{k}{m} H_k
$$
的值是多少？

在第 2 章中对式 (6.67) 和 (6.68) 最有效的方法叫作*分部求和*。我们把被加项写成 $u(k)\Delta v(k)$ 的形式，并应用恒等式
$$
\sum_a^b u(x)\Delta v(x)\,\delta x
= u(x)v(x)\bigg|_a^b - \sum_a^b v(x+1)\Delta u(x)\,\delta x. \tag{6.69}
$$
还记得吗？我们现在要处理的这个和 $\sum_{0\le k<n}\binom{k}{m} H_k$ 非常适合用这个方法，因为可以令
$$
\begin{aligned}
u(k)&=H_k, & \Delta u(k)&=H_{k+1}-H_k=\frac1{k+1}; \\
v(k)&=\binom{k+1}{m+1}, & \Delta v(k)&=\binom{k+2}{m+1}-\binom{k+1}{m+1}=\binom{k+1}{m}.
\end{aligned}
$$

（换句话说，调和数的差分很简单，而二项式系数的逆差分很简单，因此方法可行。）代入 (6.69) 得到
$$
\begin{aligned}
\sum_{0\le k<n}\binom{k}{m} H_k = \sum_0^n \binom{x}{m} H_x\,\delta x &= \binom{x}{m+1} H_x\bigg|_0^n - \sum_0^n \binom{x+1}{m+1} \frac{\delta x}{x+1}\, \\
&= \binom{n}{m+1} H_n - \sum_{0\le k<n}\binom{k+1}{m+1}\frac1{k+1}.
\end{aligned}
$$
剩下的这个和很容易计算，因为可以用我们熟悉的式 (5.5) 把 $(k+1)^{-1}$ 吸收进去：
$$
\sum_{0\le k<n}\binom{k+1}{m+1}\frac1{k+1} = \sum_{0\le k<n}\binom{k}{m}\frac1{m+1} = \binom{n}{m+1}\frac1{m+1}.
$$

于是我们就得到了所求的答案：
$$
\sum_{0\le k<n}\binom{k}{m} H_k
= \binom{n+1}{m+1}\left( H_n - \frac1{m+1} \right). \tag{6.70}
$$
（当 $m=0$ 和 $m=1$ 时，该式与 (6.67)、(6.68) 吻合得很好。）

下一个求和例子用到除法而不是乘法：我们来计算
$$
S_n = \sum_{k=1}^n \frac{H_k}{k}.
$$
如果按定义展开 $H_k$，可以得到二重和：
$$
S_n = \sum_{1\le j\le k\le n}\frac1{j\cdot k}.
$$
这时第 2 章的另一个方法可以派上用场；式 (2.33) 告诉我们
$$
S_n = \frac12\left( \left( \sum_{k=1}^n \frac1k \right)^2 + \sum_{k=1}^n \frac1{k^2} \right)
= \frac12\bigl( H_n^2 + H_n^{(2)} \bigr). \tag{6.71}
$$
事实上，如果尝试用分部求和，我们也能用另一种途径得到这个结果（见习题 26）。

现在我们来挑战一个更难的问题 [354]，它无法用分部求和直接解决：
$$
U_n = \sum_{k\ge1}\binom{n}{k}\frac{(-1)^{k-1}}{k}(n-k)^n,\quad \text{integer }n\ge1.
$$
（这个求和式里也没有明显出现调和数，但谁也说不准它们什么时候会突然冒出来。）

我们将用两种方法解决这个问题：一种是硬算到底，另一种是巧妙（或者说运气好）的方法。首先是硬算派的思路。我们用二项式定理展开 $(n-k)^n$，让分母里麻烦的 $k$ 能和分子结合：
$$
U_n = \sum_{k\ge1}\binom{n}{k}\frac{(-1)^{k-1}}{k}
       \sum_j\binom{n}{j}(-k)^j n^{n-j} \\
     = \sum_j\binom{n}{j}(-1)^{j-1}n^{n-j}
       \sum_{k\ge1}\binom{n}{k}(-1)^k k^{j-1}.
$$

这看起来一团乱麻，其实不然：内层和里的 $k^{j-1}$ 是关于 $k$ 的多项式，而恒等式 (5.40) 告诉我们，这其实就是在对这个多项式取 **$n$ 阶差分**。差不多是这样；不过我们先要整理几点：
第一，如果 $j=0$，$k^{j-1}$ 就不是多项式了，所以要把这一项单独拆分处理。
第二，$n$ 阶差分公式里本来有 $k=0$ 这一项，我们这里漏掉了；而当 $j=1$ 时这一项不为零，所以最好把它补回来（再减掉）。
结果是：
$$
\begin{aligned}
U_n &= \sum_{j\ge1}\binom{n}{j}(-1)^{j-1}n^{n-j}
       \sum_{k\ge0}\binom{n}{k}(-1)^k k^{j-1} \\
    &\quad - \sum_{j\ge1}\binom{n}{j}(-1)^{j-1}n^{n-j}
       \binom{n}{0}0^{j-1}
     - \binom{n}{0}n^n
       \sum_{k\ge1}\binom{n}{k}\frac{(-1)^k}{k}.
\end{aligned}
$$
好了，现在第一行（唯一剩下的二重和）等于 **0**：它是次数小于 $n$ 的多项式的 $n$ 阶差分的线性组合，而这样的 $n$ 阶差分都是 0。
第二行只有在 $j=1$ 时不为 0，等于 $-n^n$。
所以只剩下第三行还有点麻烦。我们已经把原问题化简成一个简单得多的和：
$$
U_n = n^n (T_n - 1),
\quad\text{其中}\quad
T_n = \sum_{k\ge1}\binom{n}{k}\frac{(-1)^{k-1}}{k}. \tag{6.72}
$$
举个例子： $U_3 = \binom31\frac81 - \binom32\frac12 = \frac{45}2$；$T_3 = \binom31\frac11 - \binom32\frac12 + \binom33\frac13 = \frac{11}6$；于是 $U_3=27(T_3-1)$，和上面一致。

那怎么计算 $T_n$ 呢？一种方法是把 $\dbinom nk$ 拆成 $\dbinom{n-1}k+\dbinom{n-1}{k-1}$，得到 $T_n$ 关于 $T_{n-1}$ 的简单递推。
但还有一个更有启发性的方法：我们在 (5.41) 里见过一个很像的公式：
$$
\sum_k\binom{n}{k}\frac{(-1)^k}{x+k}
= \frac{n!}{x(x+1)\dots(x+n)}.
$$
把 $k=0$ 这一项去掉，再令 $x=0$，得到的就是 $-T_n$。于是：
$$
\begin{aligned}
T_n &= \left(\frac1x - \frac{n!}{x(x+1)\cdots(x+n)}\right)\bigg|_{x=0} \\
     &= \left(\frac{(x+1)\cdots(x+n)-n!}{x(x+1)\cdots(x+n)}\right)\bigg|_{x=0} \\
    &= \left(\frac{x\genfrac{[}{]}{0pt}{}{n+1}{n+1}+\cdots+x\genfrac{[}{]}{0pt}{}{n+1}{2}+\genfrac{[}{]}{0pt}{}{n+1}{1}-n!}{x(x+1)\cdots(x+n)}\right)\bigg|_{x=0}
     = \frac1{n!}\genfrac{[}{]}{0pt}{}{n+1}{2}.
\end{aligned}
$$

（我们用到了展开式 (6.11)：$(x+1)\cdots(x+n)=x^{\overline{n+1}}/x$；因为 $\displaystyle\left[\begin{array}{c}n+1\\1\end{array}\right]=n!$，所以可以把分子中的 $x$ 约去。）而由式 (6.58) 我们已知 $\displaystyle\left[\begin{array}{c}n+1\\2\end{array}\right]=n!H_n$，因此 $T_n=H_n$，于是得到答案：
$$
U_n=n^n(H_n-1).\tag{6.73}
$$

这是第一种方法。另一种方法是尝试计算一个更一般的和式：
$$
U_n(x,y)=\sum_{k\ge1}\binom{n}{k}\frac{(-1)^{k-1}}{k}(x+ky)^n,\quad 整数\ n\ge0;\tag{6.74}
$$
原问题中的 $U_n$ 就是其特殊情形 $U_n(n,-1)$。我们之所以尝试推广，是因为之前的推导“舍弃”了原题的大部分细节，这些细节想必无关紧要，因为 $n$ 阶差分已经将它们消去了。

我们可以对之前的推导稍作修改，求出 $U_n(x,y)$ 的值；也可以把 $(x+ky)^n$ 写成 $(x+ky)^{n-1}(x+ky)$，再将 $\binom{n}{k}$ 拆分为 $\binom{n-1}{k}+\binom{n-1}{k-1}$，从而得到递推关系：
$$
U_n(x,y)=xU_{n-1}(x,y)+\frac{x^n}{n}+yx^{n-1};\tag{6.75}
$$
这个递推式可以用求和因子轻松求解（见习题5）。

不过最简单的是使用第2章中帮过我们大忙的另一个技巧：求导。对 $y$ 求导后，$U_n(x,y)$ 会多出一个因子 $k$，正好与分母中的 $k$ 抵消，得到的和式非常简洁：
$$
\begin{aligned}
\frac{\partial}{\partial y}U_n(x,y)&=\sum_{k\ge1}\binom{n}{k}(-1)^{k-1}n(x+ky)^{n-1} \\
&=\binom{n}{0}nx^{n-1}-\sum_{k\ge0}\binom{n}{k}(-1)^kn(x+ky)^{n-1} =nx^{n-1}.
\end{aligned}
$$

（次数小于 $n$ 的多项式的 $n$ 阶差分再次消失了。）

我们已经证明，$U_n(x,y)$ 对 $y$ 的导数为 $nx^{n-1}$，与 $y$ 无关。一般地，若 $f'(y)=c$，则 $f(y)=f(0)+cy$；因此必有
$$
U_n(x,y)=U_n(x,0)+nx^{n-1}y.
$$

接下来只需确定 $U_n(x,0)$。而 $U_n(x,0)$ 正是 $x^n$ 乘以我们在 (6.72) 中已经求得的和 $T_n=H_n$。于是，一般和式 (6.74) 的闭式为：
$$
U_n(x,y)=x^n H_n+nx^{n-1}y.\tag{6.76}
$$

特别地，原问题的解即为 $U_n(n,-1)=n^n(H_n-1)$。

## 6.5 BERNOULLI NUMBERS 伯努利数
我们接下来要介绍的一类重要数列以雅各布·伯努利（Jakob Bernoulli，1654–1705）的名字命名。他在推导 $m$ 次幂和公式的过程中发现了一系列奇妙的关系式 [26]。我们记：
$$
S_m(n) = 0^m + 1^m + \cdots + (n-1)^m  = \sum_{k=0}^{n-1} k^m = \sum_0^n x^m \delta x. \tag{6.77}
$$

（因此，当 $m>0$ 时，在广义调和数的记号下有 $S_m(n)=H_{n-1}^{(-m)}$。）伯努利研究了下面这组公式，并从中发现了一个规律：

$$
\begin{aligned}
S_0(n) &= n \\
S_1(n) &= \frac12n^2 - \frac12n \\
S_2(n) &= \frac13n^3 - \frac12n^2 + \frac16n \\
S_3(n) &= \frac14n^4 - \frac12n^3 + \frac14n^2 \\
S_4(n) &= \frac15n^5 - \frac12n^4 + \frac13n^3 - \frac1{30}n \\
S_5(n) &= \frac16n^6 - \frac12n^5 + \frac5{12}n^4 - \frac1{12}n^2 \\
S_6(n) &= \frac17n^7 - \frac12n^6 + \frac12n^5 - \frac16n^3 + \frac1{42}n \\
S_7(n) &= \frac18n^8 - \frac12n^7 + \frac7{12}n^6 - \frac7{24}n^4 + \frac1{12}n^2 \\
S_8(n) &= \frac19n^9 - \frac12n^8 + \frac23n^7 - \frac7{15}n^5 + \frac29n^3 - \frac1{30}n \\
S_9(n) &= \frac1{10}n^{10} - \frac12n^9 + \frac34n^8 - \frac7{10}n^6 + \frac12n^4 - \frac3{20}n^2 \\
S_{10}(n) &= \frac1{11}n^{11} - \frac12n^{10} + \frac56n^9 - n^7 + n^5 - \frac12n^3 + \frac5{66}n
\end{aligned}
$$

你也能看出这个规律吗？$S_m(n)$ 中 $n^{m+1}$ 的系数永远是 $\frac{1}{m+1}$。 $n^m$ 的系数永远是 $-\dfrac12$。$n^{m-1}$ 的系数永远是……看一下……$\frac{m}{12}$。$n^{m-2}$ 的系数永远是 $0$。$n^{m-3}$ 的系数永远是……嗯……没错，是 $-\frac{m(m-1)(m-2)}{720}$。$n^{m-4}$ 的系数永远是 $0$。这个规律似乎会一直延续下去，$n^{m-k}$ 的系数总是某个常数乘以 $\binom{m}{k}$。

这就是伯努利的经验性发现（他并未给出证明）。用现代记号，我们将系数写成如下形式：
$$
\begin{aligned}
S_m(n) &= \frac1{m+1}\left(
            B_0 n^{m+1}
          + \binom{m+1}{1} B_1 n^m
          + \cdots
          + \binom{m+1}{m} B_m n
         \right) \\
       &= \frac1{m+1} \sum_{k=0}^m \binom{m+1}{k} B_k n^{m+1-k}.
\end{aligned} \tag{6.78}
$$

伯努利数由如下隐式递推关系定义：
$$
\sum_{j=0}^m \binom{m+1}{j} B_j = [m=0], \quad \text{对所有 } m \ge 0. \tag{6.79}
$$
例如，$\binom{2}{0}B_0 + \binom{2}{1}B_1 = 0$。
前几项的值为：

$$
\begin{array}{c|rrrrrrrrrrrrr}
n & 0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 10 & 11 & 12 \\
\hline
B_n & 1 & -\frac12 & \frac16 & 0 & -\frac1{30} & 0 & \frac1{42} & 0 & -\frac1{30} & 0 & \frac5{66} & 0 & -\frac{691}{2730}
\end{array}
$$

（奇怪的分数 $-\dfrac{691}{2730}$ 的出现，让所有关于 $B_n$ 存在简单闭式的猜想都破灭了。）

我们可以对 $m$ 归纳证明伯努利公式 (6.78)，使用扰动法（第 2 章中求 $S_2(n)$ 的方法之一）：
$$
\begin{aligned}
S_{m+1}(n) + n^{m+1}
&= \sum_{k=0}^{n-1} (k+1)^{m+1} \\
&= \sum_{k=0}^{n-1} \sum_{j=0}^{m+1} \binom{m+1}{j} k^j
 = \sum_{j=0}^{m+1} \binom{m+1}{j} S_j(n). \tag{6.80}
\end{aligned}
$$

设 $\hat{S}_m(n)$ 为式 (6.78) 的右端；我们想要证明 $S_m(n)=\hat{S}_m(n)$，并假设当 $0\le j<m$ 时已有 $S_j(n)=\hat{S}_j(n)$。仿照第 2 章对 $m=2$ 的做法，我们先从 (6.80) 两边同时减去 $S_{m+1}(n)$。然后用 (6.78) 展开每一个 $S_j(n)$，并重新整理，把右端 $n$ 的各次幂系数合并化简：
$$
\begin{aligned}
n^{m+1} &= \sum_{j=0}^m \binom{m+1}{j} S_j(n) \\
&= \sum_{j=0}^m \binom{m+1}{j} \hat{S}_j(n) + \binom{m+1}{m} \Delta \\
&= \sum_{j=0}^m \binom{m+1}{j} \frac{1}{j+1} \sum_{k=0}^j \binom{j+1}{k} B_k n^{j+1-k} + (m+1)\Delta \\
&= \sum_{0\le k\le j\le m}
   \binom{m+1}{j}\binom{j+1}{k}\frac{B_k}{j+1} n^{j+1-k} + (m+1)\Delta \\
&= \sum_{0\le k\le j\le m} \binom{m+1}{j}\binom{j+1}{j-k}\frac{B_{j-k}}{j+1} n^{k+1}+ (m+1)\Delta \\
&= \sum_{0\le k\le j\le m} \binom{m+1}{j}\binom{j+1}{k+1}\frac{B_{j-k}}{j+1} n^{k+1} + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \sum_{k\le j\le m} \binom{m+1}{j}\binom{j}{k} B_{j-k} + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \binom{m+1}{k+1} \sum_{k\le j\le m} \binom{m-k}{j-k} B_{j-k}  + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \binom{m+1}{k+1} \sum_{0\le j\le m-k} \binom{m-k}{j} B_j + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \binom{m+1}{k+1} [m-k=0] + (m+1)\Delta \\
&= \frac{n^{m+1}}{m+1} \binom{m+1}{m+1} + (m+1)\Delta \\
&= n^{m+1} + (m+1)\Delta, \quad\text{其中 }\Delta = S_m(n)-\hat{S}_m(n).
\end{aligned}
$$

（这一推导很好地复习了我们在第 5 章学过的标准运算技巧。）因此 $\Delta=0$，即 $S_m(n)=\hat{S}_m(n)$，证毕。

在第 7 章中，我们将利用生成函数给出式 (6.78) 一个简洁得多的证明。核心思路是证明伯努利数是幂级数的系数
$$
\frac{z}{e^z-1} = \sum_{n\ge0}\frac{B_n z^n}{n!} \tag{6.81}
$$

现在我们暂且假定式 (6.81) 成立，由此推导它的一些奇妙推论。如果在两边加上 $-\dfrac{z}{2}$，就可以消去右端的 $B_1 z/1! = -\dfrac{z}{2}$ 项，得到：
$$
\frac{z}{e^z-1} + \frac{z}{2}
= \frac{z}{2}\cdot\frac{e^z+1}{e^z-1}
= \frac{z}{2}\cdot\frac{e^{z/2}+e^{-z/2}}{e^{z/2}-e^{-z/2}}
= \frac{z}{2}\coth\frac{z}{2}. \tag{6.82}
$$
这里 $\coth$ 是**双曲余切**函数，微积分教材中也写作 $\cosh z/\sinh z$；我们有
$$
\sinh z = \frac{e^z-e^{-z}}{2},\quad \cosh z = \frac{e^z+e^{-z}}{2}. \tag{6.83}
$$

将 $z$ 换为 $-z$ 可得 $\dfrac{-z}{2}\coth\dfrac{-z}{2} = \dfrac{z}{2}\coth\dfrac{z}{2}$，因此 $\dfrac{z}{2}\coth\dfrac{z}{2}$ 中所有**奇次项系数均为 0**，从而
$$
B_3 = B_5 = B_7 = B_9 = B_{11} = B_{13} = \cdots = 0. \tag{6.84}
$$

此外，由 (6.82) 可直接得到 $\coth$ 展开式的闭式：
$$
z\coth z
= \frac{2z}{e^{2z}-1} + z
= \sum_{n\ge0} B_{2n}\frac{(2z)^{2n}}{(2n)!}
= \sum_{n\ge0} 4^n B_{2n}\frac{z^{2n}}{(2n)!}. \tag{6.85}
$$

不过双曲函数并不那么常用，人们更关心普通三角函数。利用关系式
$$
\sin z = -i\sinh iz,\quad \cos z = \cosh iz \tag{6.86}
$$
可以把三角函数用双曲函数表示。对应的幂级数为：
$$
\begin{aligned}
\sin z &= \frac{z^1}{1!} - \frac{z^3}{3!} + \frac{z^5}{5!} - \cdots,
& \sinh z &= \frac{z^1}{1!} + \frac{z^3}{3!} + \frac{z^5}{5!} + \cdots,\\
\cos z &= \frac{z^0}{0!} - \frac{z^2}{2!} + \frac{z^4}{4!} - \cdots,
& \cosh z &= \frac{z^0}{0!} + \frac{z^2}{2!} + \frac{z^4}{4!} + \cdots.
\end{aligned}
$$

因此 $\cot z = \cos z/\sin z = i\cosh iz/\sinh iz = i\coth iz$，于是有
$$
z\cot z = \sum_{n\ge0} B_{2n}\frac{(2iz)^{2n}}{(2n)!}
         = \sum_{n\ge0} (-4)^n B_{2n}\frac{z^{2n}}{(2n)!}. \tag{6.87}
$$

欧拉还发现了 $z\cot z$ 的另一个优美公式（见习题 73）：
$$
z\cot z = 1 - 2\sum_{k\ge1}\frac{z^2}{k^2\pi^2 - z^2}. \tag{6.88}
$$

将欧拉的公式按 $z^2$ 的幂次展开，可得
$$
\begin{aligned}
z\cot z
&= 1 - 2\sum_{k\ge1}\left( \frac{z^2}{k^2\pi^2} + \frac{z^4}{k^4\pi^4} + \frac{z^6}{k^6\pi^6} + \cdots \right) \\
&= 1 - 2\left(\frac{z^2}{\pi^2}H_\infty^{(2)} + \frac{z^4}{\pi^4}H_\infty^{(4)} + \frac{z^6}{\pi^6}H_\infty^{(6)} + \cdots \right).
\end{aligned}
$$

将上式与式 (6.87) 中 $z^{2n}$ 的系数对应相等，我们就得到了无穷级数求和的惊人闭式：
$$
\zeta(2n) = H_\infty^{(2n)}
         = (-1)^{n-1}\frac{2^{2n-1}\pi^{2n}B_{2n}}{(2n)!},
\quad \text{整数 } n>0. \tag{6.89}
$$

例如：
$$
\zeta(2) = H_\infty^{(2)} = 1+\frac14+\frac19+\cdots
         = \frac{\pi^2 B_2}{1} = \pi^2/6; \tag{6.90}
$$
$$
\zeta(4) = H_\infty^{(4)} = 1+\frac1{16}+\frac1{81}+\cdots
         = -\frac{\pi^4 B_4}{3} = \pi^4/90. \tag{6.91}
$$

公式 (6.89) 不仅给出了 $H_\infty^{(2n)}$ 的闭式，还揭示了 $B_{2n}$ 的大致量级——当 $n$ 很大时，$H_\infty^{(2n)}$ 非常接近 1。
同时它也说明：对所有 $n>0$，有 $(-1)^{n-1}B_{2n}>0$，即非零伯努利数的符号正负交替。

不仅如此，伯努利数同样出现在正切函数的系数中：
$$
\tan z=\frac{\sin z}{\cos z}
=\sum_{n\ge0} (-1)^{n-1}4^n(4^n-1)B_{2n}\frac{z^{2n-1}}{(2n)!},\tag{6.92}
$$
其余三角函数的展开式中也会出现伯努利数（见习题72）。由式 $(6.92)$ 可得到伯努利数的另一重要性质：
$$
T_{2n-1}=(-1)^{n-1}\frac{4^n(4^n-1)}{2n}B_{2n}
$$
为正整数。$(6.93)$

例如取值：

| $n$ | $1$ | $3$ | $5$ | $7$ | $9$ | $11$ | $13$ |
|-----|-----|-----|-----|-----|-----|------|------|
| $T_n$ | $1$ | $2$ | $16$ | $272$ | $7936$ | $353792$ | $22368256$ |

这些 $T_n$ 被称为**正切数**。

沿用 B. F. Logan 的思路，考察如下幂级数即可证明式 $(6.93)$：
$$
\begin{aligned}
\frac{\sin z+x\cos z}{\cos z-x\sin z}
&=x+(1+x^2)z+(2x^3+2x)\frac{z^2}{2}+(6x^4+8x^2+2)\frac{z^3}{6}+\cdots\\
&=\sum_{n\ge0}T_n(x)\frac{z^n}{n!}.\tag{6.94}
\end{aligned}
$$

其中 $T_n(x)$ 是关于 $x$ 的多项式；令 $x=0$ 可得 $T_n(0)=T_n$，即第 $n$ 个正切数。
对式 $(6.94)$ 关于 $x$ 求导：
$$
\frac{1}{(\cos z - x\sin z)^2}
=\sum_{n\ge0} T_n'(x)\frac{z^n}{n!};
$$
再对 $z$ 求导：
$$
\frac{1+x^2}{(\cos z - x\sin z)^2}
=\sum_{n\ge1} T_n(x)\frac{z^{n-1}}{(n-1)!}
=\sum_{n\ge0} T_{n+1}(x)\frac{z^n}{n!}.
$$
（自行验算即可发现化简抵消过程十分优美。）

由此得到递推关系：
$$
T_{n+1}(x)=(1+x^2)\,T_n'(x),\quad T_0(x)=x. \tag{6.95}
$$
这组简洁递推表明：$T_n(x)$ 的各项系数均为非负整数。同时易证 $T_n(x)$ 次数为 $n+1$，系数奇偶位置交替取零、取正值。因此 $T_{2n+1}(0)=T_{2n+1}$ 必为正整数，印证式 $(6.93)$ 的结论。

递推式 $(6.95)$ 提供了一种借助正切数计算伯努利数的简便途径，全程仅需整数基础运算；相比之下，定义递推 $(6.79)$ 需要处理复杂的分数算术。

若需要计算从 $a$ 到 $b-1$ 的 $m$ 次幂和（而非从 $0$ 到 $n-1$），根据第2章理论有：
$$
\sum_{k=a}^{b-1} k^m
=\sum_a^b x^m \delta x
=S_m(b)-S_m(a). \tag{6.96}
$$

考察负数项求和可得到有趣推论：当 $m>0$ 时
$$
\sum_{k=-n+1}^{-1} k^m
=(-1)^m \sum_{k=0}^{n-1} k^m,
$$
于是
$$
S_m(0)-S_m(-n+1)
=(-1)^m\big(S_m(n)-S_m(0)\big).
$$
又 $S_m(0)=0$，因此得到恒等式：
$$
S_m(1-n)=(-1)^{m+1}S_m(n),\quad m>0. \tag{6.97}
$$

因此 $S_m(1)=0$。若将多项式 $S_m(n)$ 写为因式形式，它必定含有因子 $n$ 与 $(n-1)$，因其在 $0$ 与 $1$ 处取零点。
一般而言，$S_m(n)$ 是次数为 $m+1$ 的多项式，首项为 $\dfrac{1}{m+1}n^{m+1}$。

此外，在式 $(6.97)$ 中令 $n=\dfrac12$，可推得
$$
S_m\left(\frac12\right)=(-1)^{m+1}S_m\left(\frac12\right);
$$
当 $m$ 为偶数时必有 $S_m\left(\frac12\right)=0$，于是 $\left(n-\dfrac12\right)$ 为额外因式。
这也解释了第 2 章中简洁因式分解
$$
S_2(n)=\frac13n\left(n-\frac12\right)(n-1)
$$
的由来；依靠上述分析即可直接判定结构，无需逐项计算。

进一步，记剩余因子构成多项式 $\widehat{S}_m(n)=S_m(n)\bigg/\left(n-\dfrac12\right)$，则对偶数 $m>0$ 恒满足
$$
\widehat{S}_m(1-n)=\widehat{S}_m(n).
$$

综上，$S_m(n)$ 总可写为如下标准因式形式：
$$
S_m(n)=
\begin{cases}
\displaystyle\frac{1}{m+1}\prod_{k=1}^{\lceil m/2\rceil}
\left(n-\tfrac12-\alpha_k\right)\left(n-\tfrac12+\alpha_k\right),& m\text{ odd};\\[6pt]
\displaystyle\frac{n-\tfrac12}{m+1}\prod_{k=1}^{m/2}
\left(n-\tfrac12-\alpha_k\right)\left(n-\tfrac12+\alpha_k\right),& m\text{ even}.
\end{cases}\tag{6.98}
$$

这里 $\alpha_1=\dfrac12$，而 $\alpha_2,\dots,\alpha_{\lceil m/2\rceil}$ 为依赖于 $m$ 的合适复数。例如：
$$
\begin{aligned}
S_3(n) &= \frac{n^2(n-1)^2}{4};  \\
S_4(n) &= \frac{1}{5}\,n\left(n-\frac12\right)(n-1)\left(n-\frac12+\sqrt{\frac{7}{12}}\right)\left(n-\frac12-\sqrt{\frac{7}{12}}\right); \\
S_5(n) &= \frac{1}{6}\,n^2(n-1)^2\left(n-\frac12+\sqrt{\frac{3}{4}}\right)\left(n-\frac12-\sqrt{\frac{3}{4}}\right); \\
S_6(n) &= n\left(n-\frac12\right)(n-1)\!\left(n-\frac12+\alpha\right)\!\left(n-\frac12-\alpha\right)\!\left(n-\frac12+\overline{\alpha}\right)\!\left (n-\frac12-\overline{\alpha}\right), \\
&\text{ where } \alpha = 2^{-5/2}\,3^{-1/2}\,3^{1/4}\!\left(\sqrt{\sqrt{31}+\sqrt{27}}+i\sqrt{\sqrt{31}-\sqrt{27}}\right).
\end{aligned}
$$

若 $m$ 为大于 $1$ 的奇数，则有 $B_m=0$；因此 $S_m(n)$ 能够被 $n^2$（以及 $(n-1)^2$）整除。除此之外，$S_m(n)$ 的根并无简洁通用规律可循。

最后我们结合斯特林数总结伯努利数的相关内容。求解 $S_m(n)$ 的一种思路是：将普通幂次转化为下降幂次——下降幂次具备简洁的求和公式，完成求和后再还原为普通幂次：

$$
\begin{aligned}
S_m(n)=\sum_{k=0}^{n-1} k^m &=\sum_{k=0}^{n-1}\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m}{j}k^{\underline{j}}
=\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m}{j}\sum_{k=0}^{n-1}k^{\underline{j}} \\
&=\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m}{j}\frac{n^{\underline{j+1}}}{j+1} \\
&=\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m}{j}\frac{1}{j+1}\sum_{k\ge 0}(-1)^{j+1-k}\genfrac[]{0pt}{}{j+1}{k}n^k.
\end{aligned}
$$

将上式与 (6.78) 的幂次系数比对，即可得到恒等式：
$$
\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m}{j}\genfrac[]{0pt}{}{j+1}{k}\frac{(-1)^{j+1-k}}{j+1}
=\frac{1}{m+1}\binom{m+1}{k}B_{m+1-k}. \tag{6.99}
$$

倘若能直接证明该关系式，就能以全新方式推导伯努利数。但对照书中第 264、265 页的恒等式，很难直接用数学归纳法证明：式 (6.99) 左侧求和是组合数 $\dbinom{m}{k-1}$ 的常数倍。当 $k=m+1$ 时，左侧仅有单项：$\genfrac\{\}{0pt}{}{m}{m}\genfrac[]{0pt}{}{m+1}{m+1}\frac{1}{m+1}=\frac{1}{m+1}$，该情形易于验证；当 $k=m$ 时，左侧化简结果为 $-\dfrac12$，同样简单直观。但若满足 $k<m$，左侧求和形式极其繁杂。倘若伯努利当初沿这条路径研究，大概率无法发现伯努利数体系。

我们可以做的一个替换是：将 $\genfrac\{\}{0pt}{}{m}{j}$ 替换为 $\genfrac\{\}{0pt}{}{m+1}{j+1} - (j+1)\genfrac\{\}{0pt}{}{m}{j+1}$。
$(j+1)$ 项可以很好地消去复杂的分母，于是左侧变为：

$$
\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m+1}{j+1}\genfrac[]{0pt}{}{j+1}{k}\frac{(-1)^{j+1-k}}{j+1}
-\sum_{j\ge 0}\genfrac\{\}{0pt}{}{m}{j+1}\genfrac[]{0pt}{}{j+1}{k}(-1)^{j+1-k}.
$$

当 $k<m$ 时，根据式 (6.31)，**第二个和式等于 0**。
于是只剩下第一个和式，它非常适合更换记号；我们重新命名所有变量，让求和指标为 $k$，另外两个参数为 $m$ 和 $n$。
这样，恒等式 (6.99) 就等价于：

$$
\sum_{k}\genfrac\{\}{0pt}{}{n}{k}\genfrac[]{0pt}{}{k}{m}\frac{(-1)^{k-m}}{k}
=\frac{1}{n}\binom{n}{m}B_{n-m}+[m=n-1]. \tag{6.100}
$$

很好，这个形式看起来更简洁了——尽管第 265 页的表格依然没有给出明显的下一步证明思路。

这时，第 272 页的卷积公式派上了用场。我们可以用 (6.49) 和 (6.48) 将求和项用斯特林多项式重新表示：

$$
\genfrac\{\}{0pt}{}{n}{k}\genfrac[]{0pt}{}{k}{m}
=(-1)^{n-k+1}\frac{n!}{(k-1)!}\sigma_{n-k}(-k)\cdot\frac{k!}{(m-1)!}\sigma_{k-m}(k);
$$
$$
\genfrac\{\}{0pt}{}{n}{k}\genfrac[]{0pt}{}{k}{m}\frac{(-1)^{k-m}}{k}
=(-1)^{n+1-m}\frac{n!}{(m-1)!}\sigma_{n-k}(-k)\sigma_{k-m}(k).
$$

情况变得明朗起来；在 (6.46) 中令 $t=1$，可得卷积公式：

$$
\begin{aligned}
\sum_{k=0}^{n}\sigma_{n-k}(-k)\sigma_{k-m}(k)
&=\sum_{k=0}^{n-m}\sigma_{n-m-k}\!\big(-n+(n-m-k)\big)\sigma_{k}(m+k) \\
&=\frac{m-n}{(m)(-n)}\sigma_{n-m}\!\big(m-n+(n-m)\big).
\end{aligned}
$$

至此，式 (6.100) 得到验证，并且我们发现伯努利数与斯特林多项式的常数项直接相关：

$$
\frac{B_m}{m!}=-m\sigma_m(0). \tag{6.101}
$$


## 6.6 FIBONACCI NUMBERS 斐波那契数
接下来我们介绍一组特殊数列，它或许是所有数列中最为优美的存在——斐波那契数列 $\langle F_n\rangle$：

$$
\begin{array}{c|ccccccccccccccc}
n & 0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 10 & 11 & 12 & 13 & 14 \\
\hline
F_n & 0 & 1 & 1 & 2 & 3 & 5 & 8 & 13 & 21 & 34 & 55 & 89 & 144 & 233 & 377
\end{array}
$$

调和数与伯努利数不同，斐波那契数都是简洁规整的整数。其定义满足递推关系：
$$
F_0 = 0,\quad F_1 = 1,\quad F_n = F_{n-1}+F_{n-2},\ n>1. \tag{6.102}
$$
该规则形式极简，是每项依赖前两项的基础递推结构，这也使得斐波那契数广泛出现在各类场景之中。

“蜜蜂谱系树”是斐波那契数自然出现的经典实例。我们考察雄蜂的血统谱系：每一只雄蜂（也称工蜂注：雄蜂为雄蜂 drone，蜂王 queen 为雌性）均由雌蜂无性繁殖产生；而每一只雌蜂则拥有双亲：一只雄蜂与一只雌蜂。下图展示了谱系树最初几代的结构：

雄蜂仅有一位祖父、一位祖母；它有一位曾祖父与两位曾祖母；它拥有两位高祖父、三位高祖母。一般地，通过数学归纳法易证：该雄蜂的第 $n$ 代远祖父数量为 $F_{n+1}$，第 $n$ 代远祖母数量为 $F_{n+2}$。

斐波那契数常常现身于自然界，其成因或许与蜜蜂族谱的规律同源。例如，典型向日葵的花盘上紧密排布着小花构成的螺旋纹路，一组螺旋通常有 $34$ 条，另一组则为 $55$ 条；较小的花盘会出现 $21$ 与 $34$、$13$ 与 $21$ 的组合；英格兰曾展出过一组螺旋数高达 $89$ 与 $144$ 的巨型向日葵。部分松果品类中也能观测到同类排布规律。

再来看另一类截然不同的实例[277]：现将两块玻璃板背对背贴合放置。光线改变传播方向 $n$ 次后，穿过玻璃板或发生反射的路径总共有多少种？前若干基础情形如下所示：

当 $n$ 为偶数时，光线经过偶数次折返并穿透玻璃板；
当 $n$ 为奇数时，光线被反射，从入射的同一侧射出。

序列 $a_n$ 恰好符合斐波那契数规律，观察光路结构即可理解成因：对 $n\ge 2$，偏转 $n$ 次的光路分为两类：首次在外侧界面反射，后续剩余路径有 $a_{n-1}$ 种；或首次在中间界面往返反射，后续剩余路径有 $a_{n-2}$ 种。由此得到斐波那契递推关系：$a_n = a_{n-1} + a_{n-2}$。初值仅有小幅偏移：$a_0=1=F_2$，$a_1=2=F_3$；整体序号平移两位，恒满足 $a_n = F_{n+2}$。

1202 年，莱昂纳多·斐波那契首次引入该数列，此后数学家陆续发掘出其诸多优美性质。第一章提及汉诺塔谜题的发明者爱德华·卢卡斯，在十九世纪下半叶对斐波那契数开展了大量深入研究，也是他正式推广了斐波那契数这一名称。卢卡斯取得的经典成果之一，便是依托斐波那契数的相关性质，证明了长达 $39$ 位的梅森数 $2^{127}-1$ 为素数。

关于斐波那契数最早的经典定理之一，由法国天文学家让-多米尼克·卡西尼于 1680 年提出：
$$F_{n+1} F_{n-1} - F_n^2 = (-1)^n,\ n > 0. \tag{6.103}$$

例如取 $n=6$，代入卡西尼恒等式可得：$13\cdot 5 - 8^2 = 1$ 等式成立。

对于仅含小幅偏移下标 $F_{n\pm k}$ 的斐波那契多项式关系式，均可等价改写为只由 $F_n$ 与 $F_{n+1}$ 构成的形式：当下标 $m<n$，可用递推
$$F_m = F_{m+2} - F_{m+1} \tag{6.104}$$

将低下标项化为高下标项；当下标 $m>n+1$，可用基础定义
$$F_m = F_{m-2} + F_{m-1} \tag{6.105}$$
将高下标项降阶表示。

例如在式 $(6.103)$ 中代入 $F_{n-1}=F_{n+1}-F_n$，即可改写卡西尼恒等式为：
$$F_{n+1}^2 - F_{n+1}F_n - F_n^2 = (-1)^n \tag{6.106}$$

将原式下标 $n$ 替换为 $n+1$，卡西尼恒等式写作：
$$F_{n+2}F_n - F_{n+1}^2 = (-1)^{n+1}$$

结合递推 $F_{n+2}=F_{n+1}+F_n$ 展开化简，与式 $(6.106)$ 完全等价。由此可知：$\text{Cassini}(n)$ 成立当且仅当 $\text{Cassini}(n+1)$ 成立，借助数学归纳法可证 $(6.103)$ 对所有正整数 $n$ 恒成立。

卡西尼恒等式还是一则经典几何悖论的理论基础，这也是刘易斯·卡罗尔热衷的趣味谜题之一：将一块棋盘按图示分割为四部分，再重新拼接为一个矩形……

神奇之处在于：原本 $8 \times 8 = 64$ 的方格面积，重组后竟变为 $5 \times 13 = 65$。推广该构造：任意 $F_n \times F_n$ 的正方形，均可仿照图示，以 $F_{n+1},F_n,F_{n-1},F_{n-2}$ 为尺寸分割为四块，拼接得到尺寸为 $F_{n-1}\times F_{n+1}$ 的矩形。由式 $(6.103)$ 可知：依据 $n$ 的奇偶性不同，整体面积会凭空多出或缺失一个单位方格，这正是卡西尼恒等式对应的几何直观悖论。

严格来说，仅当 $m \ge 2$ 时才能使用化简式 $(6.105)$，因为我们尚未对负下标定义 $F_n$。若放宽这一边界条件，借助 $(6.104)$ 与 $(6.105)$ 定义负整数下标斐波那契数，大量推导将变得简便。

例如：$F_{-1}=F_1-F_0=1$，继而 $F_{-2}=F_0-F_{-1}=-1$。依此递推可得数值表：
$$
\begin{array}{c|cccccccccccc}
n & 0 & -1 & -2 & -3 & -4 & -5 & -6 & -7 & -8 & -9 & -10 & -11\\
\hline
F_n & 0 & 1 & -1 & 2 & -3 & 5 & -8 & 13 & -21 & 34 & -55 & 89
\end{array}
$$

通过数学归纳法易证：
$$
F_{-n}=(-1)^{n-1}F_n,\quad \forall n\in\mathbb Z. \tag{6.107}
$$

在该延拓定义下，卡西尼恒等式 $(6.103)$ 对全体整数 $n$ 成立，不再局限于 $n>0$。

利用式 $(6.105)$ 与 $(6.104)$ 将 $F_{n\pm k}$ 化为 $F_n$ 与 $F_{n+1}$ 的线性组合，可得到一组关系式：
$$F_{n+2} = F_{n+1}+F_n,\quad F_{n-1} = F_{n+1}-F_n,$$
$$F_{n+3} = 2F_{n+1}+F_n,\quad F_{n-2} = -F_{n+1}+2F_n,$$
$$F_{n+4} = 3F_{n+1}+2F_n,\quad F_{n-3} = 2F_{n+1}-3F_n,$$
$$F_{n+5} = 5F_{n+1}+3F_n,\quad F_{n-4} = -3F_{n+1}+5F_n.$$
从中可归纳出一般规律：
$$F_{n+k}=F_k F_{n+1}+F_{k-1}F_n \tag{6.108}$$
该恒等式可由数学归纳法证得，对全体整数 $k,n$（正数、负数、零）均成立。

在 $(6.108)$ 中取 $k=n$：
$$F_{2n}=F_n F_{n+1}+F_{n-1}F_n \tag{6.109}$$
可见 $F_{2n}$ 是 $F_n$ 的倍数。同理 $F_{3n}=F_{2n}F_{n+1}+F_{2n-1}F_n$，故 $F_{3n}$ 同样被 $F_n$ 整除。由归纳可得：
$$F_{kn}\text{ 恒为 }F_n\text{ 的倍数} \tag{6.110}$$
例如 $F_{15}=610$，同时是 $F_3=2$ 与 $F_5=5$ 的倍数。更进一步有最大公约数性质：
$$\gcd(F_m,F_n)=F_{\gcd(m,n)} \tag{6.111}$$
如 $\gcd(F_{12},F_{18})=\gcd(144,2584)=8=F_6$。

由此可证 $(6.110)$ 的逆命题：若 $n>2$ 且 $F_n\mid F_m$，则必有 $n\mid m$。
因 $F_n\mid F_m$ 蕴含 $F_n\mid \gcd(F_m,F_n)=F_{\gcd(m,n)}\le F_n$，仅当 $F_{\gcd(m,n)}=F_n$；结合 $n>2$ 即推得 $\gcd(m,n)=n$，亦即 $n\mid m$。

马蒂亚谢维奇基于斐波那契整除理论完成经典证明：不存在通用算法判定整系数多元多项式方程是否存在整数解。其引理指出：当 $n>2$ 时，$F_n^2\mid F_m$ 当且仅当 $nF_n\mid m$。
考察模 $F_n^2$ 序列 $\langle F_{kn}\rangle$：
初值 $F_n\not\equiv 0\pmod{F_n^2}$；由推导
$$F_{2n}\equiv 2F_n F_{n+1},\quad F_{3n}\equiv 3F_n F_{n+1}^2 \pmod{F_n^2},$$
归纳得
$$F_{kn}\equiv kF_n F_{n+1}^{k-1},\quad F_{kn+1}\equiv F_{n+1}^k \pmod{F_n^2}.$$
因 $\gcd(F_n,F_{n+1})=1$，故
$$F_{kn}\equiv 0\pmod{F_n^2}\iff kF_n\equiv 0\pmod{F_n^2}\iff k\equiv 0\pmod{F_n},$$
马蒂亚谢维奇引理得证。

斐波那契数另一核心性质为整数唯一表示。定义
$$j \gg k \iff j \ge k+2 \tag{6.112}$$
则任意正整数均可唯一写作：
$$n=F_{k_1}+F_{k_2}+\cdots+F_{k_r},\ k_1 \gg k_2 \gg\cdots\gg k_r \gg 0 \tag{6.113}$$
此即**泽肯多夫定理**。例如：
$$1000000=F_{30}+F_{26}+F_{24}+F_{12}+F_{10}.$$
构造采用贪心策略：每次选取不超过剩余数值的最大斐波那契数，并由间隔条件保证唯一性；连续间隔和满足估值约束
$$F_{k-2}+F_{k-4}+\cdots\le F_{k-1}-1\quad(k\ge 2) \tag{6.114}$$

该表示衍生斐波那契进制：
$$n=(b_mb_{m-1}\cdots b_2)_F \iff n=\sum_{k=2}^m b_k F_k \tag{6.115}$$
该进制类似二进制，但不存在相邻的两个 $1$。  
最后通过生成函数推导通项基础：设
$$F(z) = F_0 + F_1z + F_2z^2 + \cdots = \sum_{n\ge 0} F_n z^n \tag{6.116}$$
结合递推关系作差化简：
$$F(z) - zF(z) - z^2F(z) = z,$$
整理得到封闭形式：
$$F(z) = \frac{z}{1-z-z^2} \tag{6.117}$$

如今我们已将斐波那契数列的全部信息浓缩为简洁表达式
$$\frac{z}{1-z-z^2},$$
该形式虽直观性不强，但已是关键推进：对分母因式分解后拆分部分分式，即可展开为幂级数，其系数便是斐波那契数的闭式通项。

逆向理解该思路更为清晰：最简生成函数形如 $\displaystyle\frac{1}{1-\alpha z}$（$\alpha$ 为常数），其幂级数展开熟知：
$$\frac{1}{1-\alpha z}=1+\alpha z+\alpha^2 z^2+\alpha^3 z^3+\cdots.$$
同理，组合分式
$$\frac{A}{1-\alpha z}+\frac{B}{1-\beta z}$$
极易提取系数：
$$\frac{A}{1-\alpha z}+\frac{B}{1-\beta z}
=A\sum_{n\ge 0}(\alpha z)^n+B\sum_{n\ge 0}(\beta z)^n
=\sum_{n\ge 0}\big(A\alpha^n+B\beta^n\big)z^n. \tag{6.118}$$

因此只需确定常数 $A,B,\alpha,\beta$，满足
$$\frac{A}{1-\alpha z}+\frac{B}{1-\beta z}=\frac{z}{1-z-z^2},$$
即可得到 $z^n$ 系数 $F_n=A\alpha^n+B\beta^n$。
对左侧通分整理：
$$\frac{A}{1-\alpha z}+\frac{B}{1-\beta z}
=\frac{A-A\beta z+B-B\alpha z}{(1-\alpha z)(1-\beta z)},$$
对比分子分母结构，得到两组多项式约束：
$$(1-\alpha z)(1-\beta z)=1-z-z^2; \tag{6.119}$$
$$(A+B)-(A\beta+B\alpha)z=z. \tag{6.120}$$

我们将生成函数分母分解为 $(1-\alpha z)(1-\beta z)$，而非常规根形式 $c(z-\rho_1)(z-\rho_2)$，原因在于前者能直接适配简洁幂级数展开结构。

求解 $\alpha$ 与 $\beta$ 可采用巧妙技巧：引入变量 $w$，对
$$w^2 - wz - z^2 = (w-\alpha z)(w-\beta z)$$
因式分解，再令 $w=1$，即可得到 $1-z-z^2$ 的分解形式。
由二次求根公式求解方程 $w^2-wz-z^2=0$：
$$\frac{z\pm\sqrt{z^2+4z^2}}{2} = \frac{1\pm\sqrt{5}}{2}\,z$$
于是
$$w^2-wz-z^2 = \left(w-\frac{1+\sqrt5}{2}\,z\right)\!\left(w-\frac{1-\sqrt5}{2}\,z\right).$$

记黄金比例
$$\varphi = \frac{1+\sqrt5}{2}\approx 1.61803,$$
共轭根
$$\widehat\varphi = \frac{1-\sqrt5}{2}=-\frac1\varphi\approx -0.61803,$$
二者均满足特征方程
$$\varphi^2=\varphi+1,\quad \widehat\varphi^2=\widehat\varphi+1. \tag{6.121}$$

由此确定 $\alpha=\varphi,\ \beta=\widehat\varphi$；再求解式 $(6.120)$ 中的 $A,B$：
令 $z=0$ 得 $B=-A$，代入化简
$$-\widehat\varphi A+\varphi A = 1,$$
解得
$$A=\frac{1}{\varphi-\widehat\varphi}=\frac{1}{\sqrt5}.$$

最终得到生成函数的部分分式展开：
$$F(z)=\frac{1}{\sqrt5}\left(\frac{1}{1-\varphi z}-\frac{1}{1-\widehat\varphi z}\right). \tag{6.122}$$

按幂级数展开提取系数，即得斐波那契数闭式通项：
$$F_n = \frac{1}{\sqrt5}\big(\varphi^n-\widehat\varphi^n\big). \tag{6.123}$$
该公式最早由莱昂纳多·欧拉于 1765 年发表[113]，后来被世人淡忘，直至1843年由雅克·比内重新发现[31]。

在惊叹推导结果之前，先验证公式准确性：当 $n=0$，代入得 $F_0=0$，结果正确；当 $n=1$，有 $F_1=(\phi-\widehat{\phi})/\sqrt{5}=1$，同样成立。由式 $(6.121)$ 可证，式 $(6.123)$ 定义的数列满足斐波那契递推关系，结合初值即可由数学归纳法确证其等价于斐波那契数列。虽可通过二项式展开 $\phi^n$ 与 $\widehat{\phi}^n$ 并化简 $\sqrt{5}$ 幂次核验，但过程繁琐；闭式核心价值不在于快速求值，而是揭示 $F_n$ 与其他数学常量的内在关联。

凭借直观猜想固然可以直接猜出式 $(6.123)$，再通过数学归纳法完成证明；但生成函数法是推导闭式的强力系统性手段。在第七章中将看到，该方法同样适用于求解复杂度更高的递推关系。顺带说明：推导 $(6.123)$ 的全过程并未验证无穷级数的收敛性。事实上，针对幂级数系数的绝大多数代数运算，无论级数本身是否收敛，均可严格成立[182]。即便读者对无穷求和的推演逻辑存疑，仍可放心：借助无穷级数得到的 $(6.123)$，总能依托严谨的数学归纳法完成核验。

式 $(6.123)$ 有一个优美推论：当 $n$ 充分大时，整数 $F_n$ 与无理数 $\phi^n/\sqrt{5}$ 极其接近。由于 $|\widehat\phi|<1$，$\widehat\phi^n$ 会随 $n$ 指数衰减，贡献几乎可以忽略。例如：$F_{10}=55,\ F_{11}=89$，而
$$\frac{\phi^{10}}{\sqrt{5}}\approx 55.00364,\quad \frac{\phi^{11}}{\sqrt{5}}\approx 88.99775.$$

据此可推另一闭式表达：
$$F_n = \left\lfloor \phi^n/\sqrt{5} + 1/2 \right\rfloor = \frac{\phi^n}{\sqrt{5}} \quad \text{ rounded to the nearest integer, } \tag{6.124}$$

这是由于对任意 $n\ge 0$，总有 $|\hat\phi^n/\sqrt{5}| < 1/2$。当 $n$ 为偶数时，$F_n$ 略小于 $ \phi^n/\sqrt{5} $；当 $n$ 为奇数时则略大。

将卡西尼恒等式 $(6.103)$ 改写为
$$\frac{F_{n+1}}{F_n} - \frac{F_n}{F_{n-1}} = \frac{(-1)^n}{F_{n-1}F_n}.$$

当 $n$ 很大时，$1/(F_{n-1}F_n)$ 趋近于 $0$，故比值 $F_{n+1}/F_n$ 与 $F_n/F_{n-1}$ 几乎相等；由 $(6.124)$ 可知该极限为 $\phi$。同时另有关系式：
$$F_{n+1} = \phi F_n + \hat\phi^n \tag{6.125}$$

当 $n=0$ 与 $n=1$ 时，该等式显然成立；$n>1$ 可由归纳证得，也可直接代入$( \phi^n - \hat\phi^n )/\sqrt{5}$ 核验。比值 $F_{n+1}/F_n$ 十分贴近 $ \phi $，且交替大于、小于该值。

巧合的是，$ \phi $ 与一英里对应的千米数高度接近（精确值为 $1.609344$，源于 $1\ \text{英寸}=2.54\ \text{厘米}$）。由此可得心算换算技巧：$F_{n+1}$ 千米的距离，在数值上近似等于 $F_n$ 英里。

若要对非斐波那契数值做千米转英里换算，以 $30$ 千米为例演示美式心算技巧：先用贪心法则将 $30$ 改写为斐波那契进制展开 $30 = 21 + 8 + 1$，再将每一项斐波那契数的下标整体下移一档，得到 $13 + 5 + 1$。下标下移等价于整体除以 ${\phi}$ 做近似缩放，求和估算结果为 $19$ 英里；真实精确值约为 $18.64$ 英里，估算误差很小。反向由英里换算为千米，只需将各项斐波那契数下标整体上移一档：对 $30$ 英里作分解并升档求和，得到近似 $34+13+2 = 49$ 千米；对应标准精确值约 $48.28$ 千米。

事实表明：对所有满足 $n \le 100$ 的数值，下标下移规则几乎总能给出千米转英里的正确舍入结果；仅在 $n=4,\,12,\,62,\,75,\,91,\,96$ 时存在偏差，且误差均小于 $2/3$ 英里。而下标上移规则对 $n \le 126$ 的英里转千米运算，要么得到精确舍入值，要么仅多出 $1$ 千米。其中最典型误差出现在 $n=4$：该数分解为斐波那契组合 $3+1$，两项各自舍入误差同向叠加，无法相互抵消，最终造成明显偏差。


## 6.7 CONTINUANTS 连续体
斐波那契数与第四章讨论的斯特恩—布罗科树存在深刻关联，同时可推广为一类多项式序列，欧拉曾对其展开系统性研究。这类多项式称为连分式多项式，是分析如下连分式结构的核心工具：
$$a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{a_3+\dfrac{1}{a_4+\dfrac{1}{a_5+\dfrac{1}{a_6+\dfrac{1}{a_7}}}}}}}\tag{6.126}$$

连多项式 $K_n(x_1,x_2,\dots,x_n)$ 含有 $n$ 个参数，递推定义如下：
$$
\begin{aligned}
K_0() &= 1; \\ K_1(x_1) &= x_1; \\
K_n(x_1,\dots,x_n) &= K_{n-1}(x_1,\dots,x_{n-1})x_n + K_{n-2}(x_1,\dots,x_{n-2}). \tag{6.127}
\end{aligned}
$$

示例展开：
$$
\begin{aligned}
K_2(x_1,x_2) &= x_1 x_2 + 1,    \\
K_3(x_1,x_2,x_3) &= x_1 x_2 x_3 + x_1 + x_3,    \\
K_4(x_1,x_2,x_3,x_4) &= x_1 x_2 x_3 x_4 + x_1 x_2 + x_1 x_4 + x_3 x_4 + 1.
\end{aligned}
$$

由数学归纳法易证，项数服从斐波那契数规律：
$$
K_n(1,1,\dots,1) = F_{n+1}. \tag{6.128}
$$

若参数个数可由上下文明确，则可简写 $K$ 替代 $K_n$，这与第五章超几何函数 $F$ 省略参数个数的写法一致。例如 $K(x_1,x_2)=K_2(x_1,x_2)=x_1 x_2+1$；但形如 $(6.128)$ 的式子仍必须保留下标 $n$。

欧拉指出：$K(x_1,x_2,\dots,x_n)$ 可先取乘积 $x_1 x_2 \cdots x_n$，再剔除所有相邻因子对 $x_k x_{k+1}$ 的全部组合得到。该规则可用「摩尔斯码」直观刻画：长为 $n$ 的点划序列，点占单位长度、划占两段长度；下面给出长度为 $4$ 的全体摩尔斯码构型。
$\cdot\cdot\cdot\cdot \quad \cdot\cdot- \quad \cdot-\cdot \quad -\cdot\cdot \quad -- $

这些点划模式一一对应 $K(x_1,x_2,x_3,x_4)$ 的各项：点代表保留单个变量，划代表删去一对相邻变量。例如序列 $\cdot-\cdot$ 对应 $x_1 x_4$。

长度为 $n$、含 $k$ 个划的摩尔斯序列，拥有 $n-2k$ 个点，总符号数量为 $n-k$。排布方式共计 $\binom{n-k}{k}$ 种；若将每个点替换为 $z$、每个划替换为 $1$，即可得到
$$
\begin{aligned}
K_n(z,z,\dots,z) = \sum_{k=0}^{}\binom{n-k}{k} z^{n-2k}. \tag{6.129}
\end{aligned}
$$

连多项式的总项数为斐波那契数，因而成立恒等式
$$
\begin{aligned}
F_{n+1} = \sum_{k=0}^{}\binom{n-k}{k}. \tag{6.130}
\end{aligned}
$$
式 $(6.129)$ 存在闭式表达，是斐波那契数欧拉—比内公式 $(6.123)$ 的推广，见 $(5.74)$。

结合摩尔斯码序列模型，可知连多项式具备镜像对称性：
$$
\begin{aligned}
K(x_n,\dots,x_2,x_1) = K(x_1,x_2,\dots,x_n). \tag{6.131}
\end{aligned}
$$
因此除定义 $(6.127)$ 右侧递推外，还满足左侧参数调整递推：
$$
\begin{aligned}
K_n(x_1,\dots,x_n) = x_1 K_{n-1}(x_2,\dots,x_n) + K_{n-2}(x_3,\dots,x_n). \tag{6.132}
\end{aligned}
$$

两组递推均可归入通用合成法则：
$$
\begin{aligned}
K_{m+n}(x_1,\dots,x_{m+n})
&= K_m(x_1,\dots,x_m)\,K_n(x_{m+1},\dots,x_{m+n}) \\
&\quad + K_{m-1}(x_1,\dots,x_{m-1})\,K_{n-1}(x_{m+2},\dots,x_{m+n}). \tag{6.133}
\end{aligned}
$$
借助摩尔斯码直观理解：第一项对应位置 $[m,m+1]$ 无划的构型，第二项对应该处存在一划的构型。若全体变量取 $1$，即得 $F_{m+n+1} = F_{m+1}F_{n+1}+F_m F_n$，可见 $(6.108)$ 是 $(6.133)$ 的特例。

欧拉发现连多项式还满足卡西尼恒等式的高阶推广：
$$
\begin{aligned}
&K_{m+n}(x_1,\dots,x_{m+n})\,K_k(x_{m+1},\dots,x_{m+k}) \\
=\;&K_{m+k}(x_1,\dots,x_{m+k})\,K_n(x_{m+1},\dots,x_{m+n}) \\
&\quad + (-1)^k K_{m-1}(x_1,\dots,x_{m-1})\,K_{n-k-1}(x_{m+k+2},\dots,x_{m+n}). \tag{6.134}
\end{aligned}
$$
只要下标非负，该式恒成立。取 $k=2,\,m=1,\,n=3$ 即可验证特例：
\[
K(x_1,x_2,x_3,x_4)\,K(x_2,x_3) = K(x_1,x_2,x_3)\,K(x_2,x_3,x_4)+1.
\]

连多项式与欧几里得算法深度关联。若 $\gcd(m,n)$ 经四步迭代完成计算：
\[
\begin{aligned}
\gcd(n_0,n_1)&=\gcd(n_1,n_2),\; n_0=m,\,n_1=n;\\
n_2 &= n_0-q_1 n_1,\quad n_3 = n_1-q_2 n_2,\\
n_4 &= n_2-q_3 n_3,\quad 0 = n_3-q_4 n_4,
\end{aligned}
\]
则有层级关系
\[
\begin{aligned}
n_4 &= K()\,n_4,\quad n_3 = K(q_4)\,n_4,\\
n_2 &= K(q_3,q_4)\,n_4,\quad n_1 = K(q_2,q_3,q_4)\,n_4,\\
n_0 &= K(q_1,q_2,q_3,q_4)\,n_4.
\end{aligned}
\]
一般地，欧几里得算法经 $k$ 步得到最大公约数 $d$、商序列为 $q_1,\dots,q_k$ 时，初始两数可写为 $K(q_1,q_2,\dots,q_k)\,d$ 与 $K(q_2,\dots,q_k)\,d$。十八世纪早期拉尼最早明确研究连多项式；相邻斐波那契数对应商取最小值时的连多项式取值，也是固定步数欧几里得算法所需的最小输入。

连多项式之名源自与连分数的紧密联系，例如
$$
\begin{aligned}
a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{a_3}}}
=\dfrac{K(a_0,a_1,a_2,a_3)}{K(a_1,a_2,a_3)}. \tag{6.135}
\end{aligned}
$$
任意深度连分数均服从该结构，可用归纳结合基础恒等式证明：
$$
\begin{aligned}
K_n(x_1,\dots,x_{n-1},x_n+y)
= K_n(x_1,\dots,x_{n-1},x_n)+K_{n-1}(x_1,\dots,x_{n-1})\,y. \tag{6.136}
\end{aligned}
$$

此外，连多项式与第四章介绍的斯特恩–布罗科树联系紧密。树上每个结点均可由一串左右行走序列表示：
$$
R^{a_0}L^{a_1}R^{a_2}L^{a_3}\cdots R^{a_{n-2}}L^{a_{n-1}} \tag{6.137}
$$
其中 $a_0\ge 0,\,a_1,a_2,\dots,a_{n-2}\ge 1,\,a_{n-1}\ge 0$，且 $n$ 为偶数。

借助式 $(4.33)$ 的二阶矩阵 $\boldsymbol L$ 与 $\boldsymbol R$，由数学归纳法可证，序列 $(6.137)$ 对应的等价矩阵为
$$
\begin{aligned}
\begin{pmatrix}
K_{n-2}(a_1,\dots,a_{n-2}) & K_{n-1}(a_1,\dots,a_{n-2},a_{n-1})\\
K_{n-1}(a_0,a_1,\dots,a_{n-2}) & K_{n}(a_0,a_1,\dots,a_{n-2},a_{n-1})
\end{pmatrix} \tag{6.138}
\end{aligned}
$$

例如特例：
$$
R^a L^b R^c L^d
$$
可对应展开为含连多项式组合的二阶矩阵形式。

结合式 $(4.34)$，即可给出斯特恩–布罗科树中路径 $(6.137)$ 对应分数的闭式，此即**哈尔芬定理**：
$$
\begin{aligned}
f(R^{a_0}\cdots L^{a_{n-1}})
=\frac{K_{n+1}(a_0,a_1,\dots,a_{n-1},1)}{K_{n}(a_1,\dots,a_{n-1},1)} \tag{6.139}
\end{aligned}
$$

以路径 $\mathit{LRRL}$ 举例：取 $a_0=0,\,a_1=1,\,a_2=2,\,a_3=1,\,n=4$，代入计算
$$
\frac{K(0,1,2,1,1)}{K(1,2,1,1)}
=\frac{K(2,1,1)}{K(1,2,1,1)}
=\frac{K(2,2)}{K(3,2)}
=\frac{5}{7}.
$$
推导用到规则：在 $(6.136)$ 中取 $y=1$，即可合并首尾参数里的常数 $1$。

对比 $(6.135)$ 与 $(6.139)$ 可知：树中一般结点对应的分数等价连分式展开为
$$
\begin{aligned}
f(R^{a_0}\cdots L^{a_{n-1}})
=a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{\cdots+\dfrac{1}{a_{n-1}+1/1}}}} \tag{6.140}
\end{aligned}
$$

于是我们能够直观完成连分式与斯特恩—布罗科树结点的相互转换，例如：
$$
\begin{aligned}
f(\mathit{LRRL}) = 0+\frac{1}{1+\frac{1}{2+\frac{1}{1+1/1}}}
\end{aligned}
$$

第四章曾指出：无理数对应斯特恩—布罗科树中的无穷路径，可表示为无穷 $\mathit{L},\mathit{R}$ 序列。若 $\alpha$ 的无穷序列形如 $R^{a_0}L^{a_1}R^{a_2}L^{a_3}\cdots$，则对应无穷连分式
$$
\begin{aligned}
\alpha = a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{a_3+\dfrac{1}{a_4+\dfrac{1}{a_5+\cdots}}}}} \tag{6.141}
\end{aligned}
$$

该无穷连分式亦可递推直接构造：置 $\alpha_0=\alpha$，对 $k\ge 0$ 定义
$$
\begin{aligned}
a_k = \lfloor \alpha_k\rfloor,\quad \alpha_k = a_k + 1/\alpha_{k+1} \tag{6.142}
\end{aligned}
$$
序列 $a_k$ 称作 $\alpha$ 的**部分商**。若 $\alpha$ 为有理数 $m/n$，该迭代过程等价遍历欧几里得算法的全部商后终止，最终满足 $\alpha_{k+1}=\infty$。

欧拉常数 $\gamma$ 究竟为有理数还是无理数，至今仍是未解难题。借助斯特恩–布罗科树可对该经典猜想给出部分结论：若 $\gamma$ 为有理数，则必能在树中精准定位；若为无理数，则可由此获取其全体最优有理逼近。

欧拉常数 $\gamma$ 的连分式前若干项部分商如下：
$$
\begin{array}{c|ccccccccc}
k & 0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 \\
a_k & 0 & 1 & 1 & 2 & 1 & 2 & 1 & 4 & 3
\end{array}
$$

对应斯特恩–布罗科路径起始串为 $\mathit{LRLLRLLRLLLLRRRL}\cdots$，序列无明显周期规律。理查德·布伦特的计算结果表明：倘若 $\gamma$ 确为有理数，其分母的十进制位数必超过 $10000$ 位。

因此学界普遍猜测 $\gamma$ 为无理数，但至今尚无严格证明。

本章最后证明一则精妙恒等式，串联前述诸多概念。回顾第三章的谱概念：常数 $\alpha$ 的谱是全体 $\lfloor n\alpha \rfloor$ 构成的多重集。无穷级数
$$\sum_{n\ge 1} z^{\lfloor n\phi \rfloor} = z + z^3 + z^4 + z^6 + z^8 + z^9 + \cdots$$
即为黄金比例 $\phi=(1+\sqrt{5})/2$ 的谱对应的生成函数。1976 年戴维森发现如下无穷连分式恒等式，将该生成函数与斐波那契序列关联：
$$
\begin{aligned}
\dfrac{z^{F_1}}{1+\dfrac{z^{F_2}}{1+\dfrac{z^{F_3}}{1+\dfrac{z^{F_4}}{\;\cdots\;}}}}
=(1-z)\sum_{n\ge 1} z^{\lfloor n\phi \rfloor}. \tag{6.143}
\end{aligned}
$$

先分析 $\lfloor n\phi \rfloor$：设 $n$ 的斐波那契展开为 $F_{k_1}+\cdots+F_{k_r}$，由下标左移近似可知 $n\phi$ 逼近 $F_{k_1+1}+\cdots+F_{k_r+1}$。结合式 $(6.125)$ 有
$$n\phi = F_{k_1+1}+\cdots+F_{k_r+1}-\big(\hat\phi^{k_1}+\cdots+\hat\phi^{k_r}\big).$$
由于 $\hat\phi=-1/\phi$、指标满足严格递减 $k_1\gg\cdots\gg k_r\gg 0$，估计
$$
\begin{aligned}
\big|\hat\phi^{k_1}+\cdots+\hat\phi^{k_r}\big|
&< \phi^{-k_r}+\phi^{-k_r-2}+\phi^{-k_r-4}+\cdots \\
&= \phi^{-k_r}/(1-\phi^{-2})
= \phi^{1-k_r} \le \phi^{-1} < 1;
\end{aligned}
$$
且该求和符号与 $(-1)^{k_r}$ 一致，于是
$$
\lfloor n\phi \rfloor
= F_{k_1+1}+\cdots+F_{k_r+1}-\big[k_r(n)\text{ is even}\big]. \tag{6.144}
$$

若数 $n$ 的最低有效斐波那契位为 $1$，即满足 $k_r(n)=2$，则称 $n$ 为**斐波那契奇数**（简称F奇数）；反之称为**斐波那契偶数**（F偶数）。最小一批F奇数依次为：$1,4,6,9,12,14,17,19$。

由 $(6.114)$：当 $k_r(n)$ 为偶数时，$n-1$ 是F偶数；当 $k_r(n)$ 为奇数时，$n-1$ 是F奇数。于是等价关系成立：
$$k_r(n)\text{ is even} \iff n-1\text{ is F-even}.$$

结合式 $(6.144)$：若 $k_r(n)$ 偶，则 $k_r(\lfloor n\phi\rfloor)=2$；若 $k_r(n)$ 奇，则 $k_r(\lfloor n\phi\rfloor)=k_r(n)+1$。故 $k_r(\lfloor n\phi\rfloor)$ 恒为偶数，由此证得：$\lfloor n\phi\rfloor - 1$ 恒为 F 偶数。

反之，任取一个 F 偶数 $m$，均可反向构造整数 $n$ 使得 $m+1=\lfloor n\phi\rfloor$。先对斐波那契表示做加 $1$ 操作：若无进位，则 $n$ 为 $m+2$ 下标右移；若有进位，则 $n$ 为 $m+1$ 下标右移。因此 $(6.143)$ 右侧求和可改写为
$$
\sum_{n\ge 1} z^{\lfloor n\phi\rfloor}
= z\sum_{m\ge 0} z^{m}\,[m\text{ is F-even}]. \tag{6.145}
$$

再处理左侧连分式，将 $(6.143)$ 标准化为分子全为 $1$ 的经典连分式形制 $(6.141)$：
$$
\begin{aligned}
\frac{1}{z^{-F_0}+\dfrac{1}{z^{-F_1}+\dfrac{1}{z^{-F_2}+\cdots}}}
=\frac{1-z}{z}\sum_{n\ge 1} z^{\lfloor n\phi\rfloor}. \tag{6.146}
\end{aligned}
$$
该变换需将原式每层含 $z^{F_n}$ 的分式同除 $z^{F_{n-1}}$。

若截断至项 $1/z^{-F_n}$，其值可表为连多项式比值，与 $(6.135)$ 结构一致：
$$
\frac{K_{n+2}(0,z^{-F_0},z^{-F_1},\dots,z^{-F_n})}{K_{n+1}(z^{-F_0},z^{-F_1},\dots,z^{-F_n})}
=\frac{K_n(z^{-F_1},\dots,z^{-F_n})}{K_{n+1}(z^{-F_0},z^{-F_1},\dots,z^{-F_n})}.
$$

记分母序列 $Q_n=K_{n+1}(z^{-F_0},\dots,z^{-F_n})$，枚举初项：$Q_0=1,\ Q_1=1+z^{-1},\ Q_2=1+z^{-1}+z^{-2},\ Q_3=1+z^{-1}+z^{-2}+z^{-3}+z^{-4}$，一般规律贴合几何级数结构：
$$Q_n = 1 + z^{-1} + z^{-2} + \dots + z^{-(F_{n+2}-1)}.$$

对应分子记为 $P_n = K_n(z^{-F_1},\dots,z^{-F_n})$，其结构与 $Q_n$ 相似但项数更少。
例如：
$$P_5 = z^{-1}+z^{-2}+z^{-4}+z^{-5}+z^{-7}+z^{-9}+z^{-10}+z^{-12}$$，
而 $Q_5 = 1+z^{-1}+\dots+z^{-12}$。整理可清晰看出规律：
$$
P_5
=\frac{1+z^2+z^3+z^5+z^7+z^8+z^{10}+z^{11}}{z^{12}}
=z^{-12}\sum_{m=0}^{12} z^m\,[m\text{ 为 F-even}]
$$

由数学归纳法可证一般形式：
$$
P_n = z^{\,1-F_{n+2}}\sum_{m=0}^{F_{n+2}-1} z^m\,[m\text{ 为 F-even}]$$。

于是分式比值为
$$
\begin{aligned}
\frac{P_n}{Q_n}
=\frac{\displaystyle\sum_{m=0}^{F_{n+2}-1} z^m\,[m\text{ 为 F-even}]}
{\displaystyle\sum_{m=0}^{F_{n+2}-1} z^m}.
\end{aligned}
$$

令 $n\to\infty$，结合恒等式 $(6.145)$ 取极限，即可证得 $(6.146)$ 成立。


