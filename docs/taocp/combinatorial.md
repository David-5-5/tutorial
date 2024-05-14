# Combinatorial Algorithms Part I

[toc]

组合学研究的是可以把离散对象排列成种种不同模式的方法。

研究组合问题是，一般有五类基本问题：
- 存在问题：是否存在遵循模式的排列 ~X~？
- 构造问题：如果存在，能否快速找到这样的 ~X~？
- 计数问题：存在多少不同排列的 ~X~？
- 生成问题：能否依序访问所有的排列 $X_1,X_2,\cdots$
- 优化问题：给出目标函数，何种排列使f(X)达到最大值或最小值？

__兰福德配对__
兰福德配对 2n 个数 {1,1,2,2,...,n,n}, 排列成一行，使得每个数 k 的两次出现之间恰好存在 k 个数。当 n=3 时，仅有这样一种排成兰福德配对的方法，即 231213。

兰福德配对的一些性质：
- 完全平衡
- 最小宽度(没弄明白)

___正交拉丁方__
取出一副纸牌中所有的A, K, Q, J，把他们排列成一个方阵，使得每行每列包含所有的四种面值和四种颜色。

1779年，圣彼得堡流传一个谜题，引起大数学家欧拉的注意，来自6个军团，6种不同军衔的36名军官，排成6*6的行军方阵，每行每列要求每个军团和每个军衔的军官各一名。

___图论-基本概念__

图 G 由顶点集合 V 和边集合 E 组成，其中边是不同顶点的配对。如果 u 和 v 是满足 $\{u,v\} \in E$, 记为 $u-v$，满足 $u-v$ 的顶点称为 __邻近__ 顶点或 __邻接__ 的。

- 子图
- 生成子图
- 诱导子图

一个包含 n 个顶点和 e 条边的图，我们说它有 n 阶和 e 大小。最简单和最重要的 n 阶图是完全图 $K_n$ 、路径 $P_n$ 和 图 $C_n$。假定顶点集为 $V=\{1,2,\cdots\}$，那么：
- 对于 $1 \leq u < v \leq n$ , $`K_n`$ 有 $\binom{n}{2}=\frac{1}{2}n(n-1)$ 条边 $u-v$ ；每个 n 顶点图是 $K_n$ 的生成子图
- 当 $n \geq 1$时，对于 $1 \leq v < n$ , $P_n$ 有 n-1 条边$`v-(v+1)`$; 它是一条长度为 n-1 的从 1 到 n 的 路径
- 当 $n \geq 1$时，对于 $1 \leq v \leq n$ , $C_n$ 有 n 条边$`v-(v \mod n +1)`$; 它是一条长度为 n-1 的从 1 到 n 的 路径

图顶点的度为指包含 __邻近__ 顶点的数量，如果一个图的所有顶点的具有相同的度，则称这个图是 __正则__ 的.

图的对称图形，也称为他的 _自同构_ ，是图的顶点保持邻接性的置换。当对有 k 个自同构的图执行算法， 经常能够利用对称图像避免不必要的计算，使算法执行几乎快 k 倍。


___路径与图__

一个图的生成路径 $P_n$ 被称为 _哈密顿路径_ ，生成圈 $C_n$ 被称为  _哈密顿圈_ 。因为威廉哈密顿在1856年创建一俄国谜题，其目标在十二面体的边上寻找这样的路径和圈。如果一个图有一个哈密顿圈则称为 _哈密顿图_。

图的 _围长_ 是它的最小圈的长度，如果图是无圈的，他的围长定义为无限大。

图中两个顶点 u 和 v 之间的距离 d(u, v) 是  u 和 v 之间的最短路径长度。d(v, v) = 0, d(u, v) = d(v, u), 还有三角不等式
```math
d(u, v) + d(v, w) \geq d(u, w)  \qquad \qquad   (18)
```

图的 _直径_ 是遍及其全部顶点 u 和 v 的距离 d(u, v) 的最大值。 如果图的直径是有限的，那么图是连通的。图的顶点总是可以划为成连通的分图。

__着色__
说一个图是 k 部的或 k 可着色的，是指能够把他的顶点划分成 k (或更少)部分，使得每条边的两个端点属于不同的部分。或者等价的，有一种方法把它的顶点涂成最多 k 种不同的颜色，使得两个邻接顶点不会涂上相同的颜色。

四色定理说明，每个平面图是 4 可着色的。 这个定理是 佛朗西斯.格思里在 1852年的猜测。

2 可着色图的情况在实践中特别重要，称为二部图，或简称偶图，它的每条边在每部分有一个端点。

__定理 B.__  一个图是二部图当且仅当它不包含长度为奇数的圈。

完全二部图 $K_{m,n}$ 是最大的二部图，它分为两部分，分别有 m 和 n 个顶点。通过指明当 $` 1 \leq u \leq m < v \leq m + n`$ 时，就有 $u-v$，可以在顶点集 {1,2,...,m+n} 上定义完全二部图。

__有向图__

在形式上，大小为 m 的 n 阶有向图 D=(V, A) 是 n 顶点集合 V 加上 m 个序偶 (u,v) 组成的多重集 A。

多重图 (V,E) 就像普通的图，只不过它的边集 E 可以是顶点对 {u,v} 的任意多重集

__图和有向图的表示__ 
任何有向图完全是由它的邻接矩阵 $A=(a_{uv})$ 描述的。任何图或多重图也是如此。


__图代数__
通过对已有的图进行运算，可以获得新的图。

G = (V,E), G补图 $\overline{G} = (V,\overline{E})$。补图就是原先没有边的顶点之间出现了边。

看不懂了，o(╥﹏╥)o 以下略过


## 7.1 0 与 1
组合算法经常需要特别关注执行效率，则数据的恰当表示乃是获得必要速度的重要途径。
0 与 1 在信息编码、数据间的逻辑关系编码，乃至编写处理信息的算法中的惊人能力，极大的丰富了对二进制数字的研究。不仅利用按位运算加强组合算法，而且发现二进制逻辑的性质自然地引出一些本身就非常有趣的新的组合问题。

在研究二进制位量的高层概念和技术之前，我们最好能够透彻了解他们的基本性质。

## 7.1.1 布尔代数基础

存在16种可能的函数f(x,y)，它们把两个给定的二进制位 x 和 y 变换成第三个二进制位 z=f(x,y)，因为对每个f(0,0)，f(0,1)，f(1,0)，f(1,1)有两种选择。

__表1 两个变量的16种逻辑运算__
真值表 | 新记号与旧记号 | 运算符<br>符号	$\circ$ | 名称
|:-:|:-:|:-:|---|
0000 | 0 | $\bot$ | 永假式；假值；自相矛盾；常数0
0001 | $xy, x\wedge y $ | $\wedge$ | 和取；与
0010 | $x\wedge \overline y, x\not\supset y, [x>y], x y$ |  | 非蕴含；差；与非；但非
0110 | $x \oplus y$,x ^ y| $\oplus$ | 互斥析取；xor；异或
0111 | $x \vee y$| $\vee$ | 析取；或；与/或
1001 | | $\equiv$ | 等价
1111 | 1 | T | 永真式；肯定式；重言式；常数1

表1 中更加对称的记号 $x\wedge y$ 和 $x\vee y$，使得更容易记住这两个分配律：
```math
(x \vee y)\wedge z = (x\wedge z) \vee (y\wedge z), \qquad (1) \\
(x \wedge y)\vee z = (x\vee z) \wedge (y\vee z), \qquad (2)
```

$x\oplus y$ 和 $x\equiv y$，即等价和异或，它们之间的关系由下列恒等式表示：
```math
x\equiv y = \overline x\oplus y = x\oplus\overline y = 1\oplus x\oplus y \qquad (3) \\
x\oplus y = \overline x\equiv y = x\equiv\overline y = 1\equiv x\equiv y \qquad (4)
```
异或比等价更有用，主要原因在于：
```math
x\oplus y = (x+y)\mod 2 \qquad (5)
```


__基本恒等式__
考察一下运算符 $`\vee, \wedge, \oplus, \overline x`$ 的相互作用，因为其他运算符很容易通过这四种运算符表示。$`\vee, \wedge, \oplus`$ 的每一个都是可结合和可交换的。除了分配率(1)和(2)，还有以下分配率：
```math
(x\oplus y)\wedge z = (x\wedge z)\oplus(y\wedge z) \qquad (6)
```
以及吸收率：
```math
(x\wedge y)\vee x = (x\vee y)\wedge x \qquad (7)
```
注，编程语言使用&，|代替 $`\wedge, \vee`$


一个最简单也最有用的恒等式
```math
x\oplus x = 0 \qquad (8)
```
因为它特别蕴含
```math
(x\oplus y)\oplus x = y, (x\oplus y)\oplus y = x  \qquad (9)
```
只要利用 $`x\oplus 0=x`$ 这个明显的事实，既可以看出上式推导成立，同时也不要忽略简单的补定率：
```math
\overline x = x\oplus 1 \qquad(10)
```
另外一对重要的恒等式称为 _德摩根定律_，它阐明了“一个聚合命题的反命题是其成员反命题的复合；一个复合命题的反命题是其成员反命题的聚合。因此(A,B)和AB具有对于反命题ab和(a,b).”。即
```math
\overline {x\wedge y } = \overline x \vee \overline y \qquad(11) \\
\overline {x\vee y } = \overline x \wedge \overline y \qquad(12)
```
德摩根定律以及其他几个恒等式可以用$\vee, \wedge, \oplus$互相表示：
```math
x\wedge y  = \overline {\overline x\vee \overline y } = x \oplus y \oplus (x\vee y) \qquad(13) \\
x\vee y  = \overline {\overline x\wedge \overline y } = x \oplus y \oplus (x\wedge y) \qquad(14) \\
x \oplus y = (x\vee y)\wedge \overline {x\wedge y } = (x\wedge \overline y)\vee(\overline x\wedge y) \qquad(15)
```


__n 变量函数__
3个布尔变量x,y,z的布尔函数f(x,y,z)可以用它的8位真值表f(0,0,0)f(0,0,1)...f(1,1,1)定义。一般来说，每个n元布尔函数 $`f(x_1,x_2,\cdots x_n)`$ 对应于依次取值的f(0,0,...,0)f(0,0,...,1)...f(1,1,...,1)的 $`2^n`$ 位真值表。当n>0时，总是可以写出
```math
f(x_1,x_2,\cdots x_n) = g(x_1,x_2,\cdots x_{n-1}) \oplus h(x_1,x_2,\cdots x_{n-1})\wedge x_n \qquad(16)
```
其中，相应的函数g和h定义如下：
```math
g(x_1,x_2,\cdots x_{n-1}) = h(x_1,x_2,\cdots x_{n-1},0)  \\
\\
h(x_1,x_2,\cdots x_{n-1}) = f(x_1,x_2,\cdots x_{n-1},0) \oplus f(x_1,x_2,\cdots x_{n-1},1) \qquad(17)
```
运算符 $`\wedge`$ 优先于 $`\oplus`$ ，所以等式(16)对于g和h递归地重复这个过程，直到降至0元函数，而且常数时常可以简化掉，因为有
```math
x \wedge 0 = 0 和 x \wedge 1 = x \oplus 0  =x \qquad(18)
```

乔治.布尔采用一种不同的方式分解布尔函数，对于实际中出现的各种函数，用这种方式通常更加简单，他不用等式(16)，而是把函数写成：
```math
f(x_1,x_2,\cdots x_n) = （g(x_1,x_2,\cdots x_{n-1}\wedge \overline x_n) \vee (h(x_1,x_2,\cdots x_{n-1})\wedge x_n) \qquad(20)
```
并把它称为 __展开定理__。现在有更为简单的：
```math
g(x_1,x_2,\cdots x_{n-1}) = h(x_1,x_2,\cdots x_{n-1},0)  \\
\\
h(x_1,x_2,\cdots x_{n-1}) = f(x_1,x_2,\cdots x_{n-1},1)\qquad(21)
```
等式(21)以代替式(17)，重复迭代布尔的过程，利用分配率(1)，并消除常数，留下一个0或小项的析取公式，其中每个小项是 $`x_1\wedge \overline x_2 \wedge \cdots \wedge x_n`$ 这样的与(合取)，每个变量的或它的补都在小项中出现，一个小项恰好在一点为真的布尔函数。

考虑或多或少随机的函数f(w,x,y,z)，它的真值表是 1100 1001 0000 1111  (22)，当重复应用布尔定律(20)展开这个函数时，我们获得8个小项的析取，真值表中的每个1都有一个对应的小项：
```math
f(w,x,y,z) = (\overline w \wedge \overline x \wedge \overline y \wedge \overline z) 
\vee (\overline w \wedge \overline x \wedge \overline y \wedge z) 
\vee (\overline w \wedge x \wedge \overline y \wedge \overline z) 
\vee (\overline w \wedge x \wedge y \wedge z) \\
\vee (w \wedge x \wedge \overline y \wedge \overline z) 
\vee (w \wedge x \wedge \overline y \wedge z) 
\vee (w \wedge x \wedge y \wedge \overline z) 
\vee (w \wedge x \wedge y \wedge z)  \qquad(23)
```
> [!CAUTION]
> 没看明白

小项的析取通常称为 _全析取范式_。每个布尔函数都可以用这种方式表示，而且结果是唯一的。我们一般说的 _析取范式_ (disjunctive normal form，简称DNF)是指和取的 _任意_ 析取
```math
\vee_{j=1}^{m} \wedge_{k=1}^{s_j} u_{jk} = (u_{11} \wedge \cdots \wedge u_{1s_1}) \vee \cdots \vee (u_{m1} \wedge \cdots \wedge u_{ms_m})  \qquad(25)
```
其中每个 $`u_{jk}`$ 是字面值，也就是变量 $`x_i`$ 或它的补。同样，_和取范式_(conjunctive normal form,，简称CNF)是指析取的 _任意_ 和取：
```math
\wedge_{j=1}^{m} \vee_{k=1}^{s_j} u_{jk} = (u_{11} \vee \cdots \vee u_{1s_1}) \wedge \cdots \wedge (u_{m1} \vee \cdots \vee u_{ms_m})  \qquad(26)
```

通常把DNF中的项称为 _蕴含元_，因为析取的任何小项的真值蕴含整个公式的真值。例如在像：
```math
f(x,y,z) = (x \wedge \overline y \wedge z) \vee (y \wedge z) \vee (\overline x \wedge y \wedge \overline z)
```
这样的公式中，$`x \wedge \overline y \wedge z`$ 为真时f为真，就是说当(x,y,z)=(1,0,1)时f为真。在这个例子中 $`x \wedge z`$ 也是f的蕴含元，所以，可以有更简单的公式
```math
f(x,y,z) = (x \wedge z) \vee (y \wedge z) \vee (\overline x \wedge y) \qquad(27)
```
对于一个蕴含元，如果通过消除它的字面值作进一步的分解时导致其弱化到不再时蕴含元，那么，称其为 _素蕴含元_。

如果简化记号，并采纳一种更具几何学的观点，把 $`f(x_1,x_2,\cdots,x_n)`$ 直接写成f(x)，把 x 看成是向量，或者长度为 n 的二进制串。例如使式(22)的函数为真的二进制串 wxyz 是

{0000,0001,0100,0111,1100,1101,1110,1111}   (28)

式(28)中的这8个点对应于全析取范式(23)中显式表示的小项蕴含元，但那些蕴含元中实际上没有一个是素蕴含元。如果像数据库查询时用星号表示通配符，那么式(28)的前两个点构成子立方 000\*，后四个点构成子立方 11\*\*。所以 $`\overline w \wedge \overline x \wedge \overline y`$ 是 f 的蕴含元，$`w \wedge x`$ 也是 f 的蕴含元。同样可以看出，式(28)中第一个点和第三个点构成子立方 0\*00，使 $`\overline w \wedge \overline y \wedge \overline z`$ 成为蕴含元。

一般说来，每个素蕴含元以这种方式对应一个最大子立方，这个子立方停留在使 f 为真的点集内。式(28)的8个点中，最大子立方是

000\*, 0\*00, \*100, \*111, 11\*\*,  (29)

所以式(23)中的函数 f(w,x,y,z) 的全部素蕴含元的析取是：
```math
(\overline w \wedge \overline x \wedge \overline y ) 
\vee (\overline w \wedge \overline y \wedge \overline z) 
\vee (x \wedge \overline y \wedge \overline z) 
\vee (x \wedge y \wedge z)
\vee (w \wedge x)  \qquad(30)
```
布尔函数的 _析取素式_ 是它的全部素蕴含元的析取。

可以用完全类似的方法定义 _素子句_:它是由 f 蕴涵的析取子句，其中不包含具有相同性质的子子句。f 的合取素式是它的全部素子句的合取。
析取素式时函数所能具有的析取范式中的最短可能范式。寻求最短析取范式的任务是一个 NP 难题。不过对于规模足够小的问题，已经建立了许多有用的简便方法。
有一个重要的析取范式特例，它的最短 DNF 得特征很容易表述。如果一个布尔函数在任何一个变量由 0 变成 1 时的函数值不会由 1 变成 0，那么就说它是 _单调函数_ 或 _正函数_。还句话说，f 是单调的充分必要条件是每当 $` x \subseteq y`$ 时有 $` f(x) \leq f(y) `$，其中，二进制位串 $` x = x_1\cdots x_n `$ 被视为包含于二进制串 $` y = y_1\cdots y_n `$ 或等于二进制串 y，当且仅当对于所有 j 有 $` x_j \leq y_j `$。一个等价的条件是，函数 f 为常数，或者可以完全通过 $`\wedge`$ 和 $` \vee `$ 不用补运算表示。

__定理Q. 单调布尔函数的最短析取范式是它的析取素式。__

__推论Q. 单调布尔函数的析取范式是它的析取素式，但且仅当当它没有带补的字面值，而且它的蕴涵元没有一个包含在另外一个中。__

__可满足性。__ 如果布尔函数不恒等于 0，即至少有一个蕴涵元，就说它是可满足的。如果布尔公式包含 30 个布尔变量，那么，进行 $` 2^30`$ 个事例的强行检验无疑会解决问题。所以，对于可满足性问题，找到确实有效的解法将是令人惊叹的成就。

可满足性检验通常是很棘手的。即使试图把布尔函数表示成“3CNF范式”，也就是表示成每个子句中仅有 3 个字面值的和取范式，以此来简化它:
```math
f(x_1,\cdots,x_n) = (t_1 \vee u_1 \vee v1) \wedge (t_2 \vee u_2 \vee v2) \wedge \cdots \wedge (t_m \vee u_m \vee v_m) \qquad(31)
```
在3CNF范式中最短的有趣公式至少有8个子句。根据在6.5-(13)中由罗纳德.李维斯特提出的结合区组设计，的确存在一个有趣的八子句公式:
```math
(x_1 \vee x_2 \vee \overline x3) \wedge (x_2 \vee x_3 \vee \overline x4) \wedge (x_3 \vee x_4 \vee  x1) \wedge (x_4 \vee \overline x_1 \vee  x2) \\
\wedge (\overline x_1 \vee \overline x_2 \vee  x3) \wedge (\overline x_2 \vee \overline x_3 \vee  x4) \wedge (\overline x_3 \vee \overline x_4 \vee \overline  x1) \wedge (\overline x_4 \vee x_1 \vee x2)\qquad(32)
```
这 8 个子句中的任何 7 个子句恰好以两种方式可满足，而且他们强行决定了 3 个变量的值。例如最后七子句意味着有 $` x_1x_2x_3 = 001 `$。但是八子句的完整集合不可能同时满足。


__简单特例。__ 有两类重要的布尔公式，它们的可满足性问题已被证明是很容易判定的。这些特例出现在被检验的合取范式完全由“霍恩子句” (Horn clause) 或者完全由“克罗姆子句” (Krom clause) 组成的时候。霍恩子句是包含一些字面值的 OR，其中全部字面值或者几乎全部字面值是带补的变量。克罗姆子句是恰好两个字面值的 OR。因此类如:
```math
\overline x \vee \overline y, w \vee \overline y \vee \overline z,\overline u \vee \overline v \vee \overline w \vee \overline x \vee \overline y \vee z, x
```
是霍恩子句的例子，而
```math
x \vee x,\overline x \vee \overline x,\overline x \vee \overline y,x \vee \overline y,\overline x \vee y,x \vee y
```
是克罗姆子句的例子，其中只有最后的子句不同时为霍恩子句。当局限于克罗姆子句时，其实是在考虑2SAT问题。在两种情形下都将看到，可以在线性时间内判定可满足性问题；也就是说，给定长度为N的公式能够在O(N)个简单步骤内求解。

首先考察霍恩子句子句。为什么它容易处理？主要原因，像 $` \overline u \vee \overline v \vee \overline w \vee \overline x \vee \overline y \vee z`$, 都可以转化为 $`\neg（u \wedge v \wedge w \wedge x \wedge y） \vee z`$ 的形式，这同
```math
u \wedge v \wedge w \wedge x \wedge y \Rightarrow  z
```
是一样的。还句话说，如果u，v，w，x，y全部为真，那么 z 也必为真。

__定理H.__ 布尔函数 $`f(x_1,x_2,\cdots,x_n)`$ 可以表示成若干霍恩子句的合取，当且仅当对于所有布尔值 $`x_j`$ 和 $`y_j`$ 有
```math
f(x_1,x_2,\cdots,x_n) = f(y_1,y_2,\cdots,y_n) = 1 蕴涵 f(x_1 \wedge y_1,x_2 \wedge y_2,\cdots,x_n \wedge y_n) = 1 \qquad(33)
```

证明 如果有
```math
x_0 \vee \overline x_1 \vee \cdots \vee \overline x_k = 1 和 \\
y_0 \vee \overline y_1 \vee \cdots \vee \overline y_k = 1 \\
```

那么，
```math
(x_0 \wedge y_0) \vee \overline{x_1 \wedge y_1} \vee \cdots \overline{x_k \wedge y_k} \\
=(x_0 \vee \overline x_1 \vee \overline y_1 \vee \cdots \vee \overline x_k \vee \overline y_k) \wedge (y_0 \vee \overline x_1 \vee \overline y_1 \vee \cdots \vee \overline x_k \vee \overline y_k) \\
\geq (x_0 \vee \overline x_1 \vee \cdots \vee \overline x_k) \wedge (y_0 \vee \overline y_1 \vee \cdots \vee \overline y_k)
```

不妨说，霍恩函数是满足条件(33)的函数，而且，如果霍恩函数满足进一步的条件 f(1,...,1)=1，就称它为确定的。容易看出，若干霍恩子句的合取是确定的，当且仅当每子句恰好有一个不带横杠的字面值，因为如果哦所有的变量为真，那么仅有一个像 $`\overline x \vee \overline y`$ 这样完全由否定字面值构成的子句不为真。

处理确定的霍恩函数比处理一般的霍恩函数简单一些，因为他们显然总是可满足的。确定的霍恩函数的核心是在这个最小向量 x 中为真的所有变量 $`x_j`$ 的集合。

确定的霍恩函数出现在许多地方，例如在决策分析中。另一个有趣的例子来自编译器技术。对于程序设计中的代数表达式，考虑下面典型的语法：
```math
<表达式> \to <项> | <表达式> + <项> | <表达式> - <项> 
```
```math
<项> \to <因式> |-<因式>| <项>*<因式> | <项>/<因式>
```
```math
<因式> \to <变量> |<常数>| (表达式)
```
```math
<变量> \to <字母> |<变量><字母>| <变量><数字>
```
```math
<字母> \to a | b | c
```
```math
<常数> \to <数字> | <常数><数字>
```
```math
<数字> \to 1 | 0  \qquad(34)
```

例如，字符串 $`a/(-b0-10)+cc*cc`$ 符合 <表达式> 的语法，而且每条语法规则至少用到一次。

假定想知道什么字符配对可能彼此相续出现在这样的表达式中。确定的霍恩子句提供了答案，因为我们可以把问题表述如下：假设$`Xx，xY，xy`$ 表示布尔“命题”，其中 X 是符号 $`{E, T, F, V, L, C, D}`$ 之一，分别代表 <表达式> <项> <因式> <变量> <字母> <常数> <数字>，而 x 和 y 是集合 $`{+, -, *, /, (, ), a, b, c, 0, 1}`$ 中的符合。命题 Xx 表示 “X 可以以 x 结束”；同样，命题 xX 表示 “X 可以以 x 开始”；同时，xy 表示“子阿表达式中字符 x 之后可以直接跟着字符 y”。总共有 $`7 * 11 + 11 * 7 + 11 * 11 = 275`$ 个命题。于是可以写出

$$
\begin{array}{|rrrrrrrr|}
xT \Rightarrow xE & \Rightarrow -T & xC \Rightarrow xF & Vx \wedge yL \Rightarrow xy & \Rightarrow Lc \\
...\\
Fx \Rightarrow Tx & Vx \Rightarrow Fx & Lx \Rightarrow Vx & \Rightarrow cL & \Rightarrow D1 
\end{array}
 \qquad(35)
$$

> 待补充

如果喜欢布尔代数神秘记号而不用(35)中的惯用符合 $`\Rightarrow`$, 可以从形式上把它们写成
```math
(\overline {+T} \vee +E) \wedge (\overline {-T} \vee -E) \wedge \cdots  \wedge (\overline {V+} \vee \overline {OL} \vee +0) \wedge \cdots  \wedge (D1)
```

为什么要进行这种处理？因为所有这些子句的核心是这个特定语法中为真的全部命题的集合。例如，可以证实 -E 为真，因此在表达式中符号 $`(-`$ 可以彼此相续出现。但是 $`++`$ 和 $`*-`$ 这两对符合不能这样。

此外，对于一组任意给定的霍恩子句，找出它们的核心并不是难事。当 $`\Rightarrow`$ 的左端为空时，就从 $`\Rightarrow`$ 右侧单独出现的命题开始， 式(35)中出现了13个这种类型的子句。一旦确定了这些命题的真值，就可以会找到一个或多个左端已知为真的子句。因此，他们的右端也属于核心，而且可以用同样的方法继续进行。


__算法C__ (计算确定霍恩子句的核心) 给定命题变元的集合 P 和子句的集合 C，每个子命题的形式为
```math
u_1 \wedge \cdots \wedge u_k \Rightarrow v, 其中 k \geq 0 且 {u_1,\cdots,u_k, v} \subseteq P, \qquad(36)
```
算法求出每当全部子句为真时，必定为真的所有命题边缘的集合 $`Q \subseteq P`$。

对于子句 c 和命题 p，使用以下数据结构：
$`CONCLUSION(c)`$ 是子句 c 右端的命题；
$`COUNT(c)`$ 是尚未断定的 c 的假设数量；
$`TRUTH(p)`$ 当 p 已知为真时是1，否则是 0；
$`LAST(p)`$ 是其中 p 有待推断的最后一个子句；
$`PREV(c)`$ 是等待同 c 一样的假设的前一个子句；
$`START(c)`$ 指出 c 的假设出现在 MEM 的什么位置。(“假设”是在子句左端出现的命题。)
数组 MEM 保存所有子句的左端。如果 $`START(c) = l 且 COUNT(c) = k`$，子句 c 的尚未断定的假设是 $`MEM[l+1], \cdots, MEM[l+k]`$。还要维持一个栈 $`S_0,S_1,\cdots,S_{n-1}`$ 保存已知是真但尚未推断的所有命题。
- C1. [初始化]。对于每个命题 p，置 $`LAST(p) \leftarrow \Lambda, TRUTH(p) \leftarrow 0, l \leftarrow s \leftarrow 0`$，使得 MEM 和栈初始化为空，然后，对于具有形式(36)的每个子句 c，置 $`CONCLUSION(c)\leftarrow v`$。
  - 如果 k=0 且 TRUTH(v)=0，仅置 $`TRUTH(v) \leftarrow 1, S_s \leftarrow v, s \leftarrow s+1`$。
  - 如果 k>0，对于 $`1 \geq j \geq k`$ 置 $`MEM[l+j] \leftarrow u_j, COUNT(c) \leftarrow k, l \leftarrow l+k, PREV(c) \leftarrow LAST(u_k), LAST(u_k) \leftarrow c`$。

- C2. [准备循环]。如果 s = 0，算法终止。现在，所求的核心由那些 TRUTH 已经设置为 1 的所有命题组成。否则，置 $`s \leftarrow s-1, p \leftarrow S_s, c \leftarrow LAST(p)`$。

- C3. [循环结束?]。如果 $`c = \Lambda`$， 返回 C2。否则，置 $`k \leftarrow COUNT(c)-1, l \leftarrow START(c), c' \leftarrow PREV(c)`$。

- C4. [处理完c?]。如果 k=0，转到C5。否则，
  - 置 $`p \leftarrow MEM[l+k]`$
  - 如果 $`TRUTH(p)=1`$，置 $`k \leftarrow k-1`$，重复此步骤。否则，
  - 置 $`COUNT(c) \leftarrow k, PREV(c) \leftarrow LAST(p), LAST(p) \leftarrow c`$，转到 C6

- C4. [推断CONCLUSION(c)。] 置 $`p \leftarrow CONCLUSION(c)`$。如果 $`TRUTH(p)=0`$，置 $`TRUTH(p) \leftarrow 1, S_s \leftarrow p, s \leftarrow s+1`$

- C6. [对c循环。] 置 $`c \leftarrow c‘`$，返回 C3。

算法C 在许多方面同算法 2.2.3T (拓扑排序)相似，实际上，可以把算法 2.2.3T 看成是算法C的特例，其中每个命题恰好出现在一个子句的右端。

现在转到克罗姆函数和 2SAT 问题。又有一个线性时间的算法。首先考察一额简化而实际的应用，假定由七位喜剧演员，每个人都同意在三天节日期间的哦阿五家宾馆中的两家做一夜的独白诙谐表演：
- Tomlin 应于第 1 天和第 2 天在 Aladdin 和 Caesars 表演；
- Unwin 应于第 1 天和第 2 天在 Bellagio 和 Excalibur 表演；
- Vegas 应于第 2 天和第 3 天在 Desert 和 Excalibur 表演；
- Williams 应于第 1 天和第 3 天在 Aladdin 和 Desert 表演；
- Xie 应于第 1 天和第 3 天在 Caesars 和 Excalibur 表演；
- Yankovic 应于第 2 天和第 3 天在 Bellagio 和 Desert 表演；
- Zany 应于第 1 天和第 2 天在 Bellagio 和 Caesars 表演；

但是由于其他承诺，他们每个人在那三天中只有两天可以参演。有可能安排全部无冲突的表演日程吗？

__定理K__ 每个子句带有两个字面值的合取范式是可满足的，当且仅当相关联的有向图的强分图不会同时包含一个变量和它的补。

证明：如果存在从 x 到 $`\overline x`$ 以及从 $`\overline x`$ 到 x 的路径，公式肯定是不可满足的。
反之，假定不存在这样的路径，任何有向图至少有一个强分图 S，它是不包含来自其他任何强分图顶点的引入弧的“源点”。 

> [!tip] 
> 略

罗伯特.塔杨建立了以线性时间寻找强分图的算法，从而由 定理k 立刻的出 2SAT 问题的一个有效解。

__中位数__ 还有一种重要的三元运算符 $`\langle xyz \rangle`$, 称为 $`x,y,z`$ 的中位数：
```math
\langle xyz\rangle  = (x\wedge y) \vee (y\wedge z) \vee (z\wedge x) = (x\vee y) \wedge (y\vee z) \wedge (z\vee x)  \qquad(43)
```
事实上，$`\langle xyz\rangle `$ 或许是这整个领域中最重要的三元运算，因为它存在正在不断发展和重现发现的惊人性质。

首先，关于 $`\langle xyz\rangle `$ 这个公式描述了任何三个布尔量 $`x,y,z`$ 的 _过半数_： $`\langle 000\rangle =\langle 001\rangle =0, \langle 011\rangle =\langle 111\rangle =1`$，称 $`\langle xyz\rangle `$ 为 “中位数” 而不说 “过半数”，原因在于，如果 $`x,y,z`$ 为任意实数，而且式(43)中的运算 $`\wedge 和 \vee`$ 分别表示 min 和 max，那么：
```math
\langle xyz\rangle  = y \qquad(44)
```
其次，基本二元运算 $`\wedge 和 \vee`$ 是中位数的特例 
```math
x \wedge y = \langle x0y\rangle , x \vee y = \langle x1y\rangle  \qquad(45)
```
因此，任何单调布尔函数函数可以用三元中位数运算符以及常数 0 和 1 表示。

如果布尔函数 $`f(x_1,x_2,\cdots,x_n)`$ 满足
```math
\overline{f(x_1,x_2,\cdots,x_n)} = f(\overline x_1,\overline x_2,\cdots,\overline x_n) \qquad(46)
```
那么称它为 __自对偶__ 的。布尔函数是单调的，当且仅当它可以用 $`\wedge 和 \vee`$ 表示。根据德摩根定律(11)和(12)，单调公式是子对偶的，当且仅当可以交换符号 $`\wedge 和 \vee`$ 而不改变公式的值。因此式(43)定义的中位数运算不仅是单调的而且是子对偶的。实际上，它是该类型的最简单的非平凡函数，因为除了投射运算 外，在表1中没有其他二元运算既是单调的又是子对偶的。

此外，完全用中位数运算符构成并且不带常数的任何表达式，不仅是单调的，而且是子对偶的。例如函数 $`\langle w\langle xyz\rangle \langle w\langle uvw\rangle x\rangle \rangle `$

__定理P__ 每个单调子对偶布尔函数 $`f(x_1,x_2,\cdots,x_n)`$ 完全可以用中位数运算 $`\langle xyz\rangle `$ 表示。
证明：首先注意到
```math
\langle x_1y\langle x_2y\cdots y\langle x_{s-1}yx_s\rangle \cdots\rangle \rangle \\
= ((x_1 \vee x_2 \vee \cdots \vee x_{s-1} \vee x_s) \wedge y) \vee (x_1 \wedge x_2 \wedge \cdots \wedge x_{s-1} \wedge x_s) \qquad(46)
```
通过对 s 的归纳法，容易证实这个重复取中位数的公式。

现在假定 $`f(x_1,x_2,\cdots,x_n)`$ 是单调子对偶函数，并且具有析取素式
```math
f(x_1,x_2,\cdots,x_n) = t_1 \vee \cdots \vee t_m, t_j = x_{j1} \wedge \cdots \wedge x_{js_j}
```
其中没有任何素蕴涵元 $`t_j`$ 包含在另一个素蕴涵元中。任何两个素蕴涵元必定至少有一个公共变量。
因为，如果有 $`t_1 = x \wedge y 和 t_2 = u \wedge v \wedge w`$，
那么，当 $`x = y = 1 且 u = v = w = 0`$ 时
或者
当 $`x = y = 0 且 u = v = w = 1`$ 时
f 的值将是 1，同函数的子对偶性矛盾。
因此，如果任何 $`t_j`$ 包含单个变量 x，它必定时唯一的素蕴涵元，此时 f 是平凡函数 $`f(x_1,x_2,\cdots,x_n) = x = \langle xxx\rangle `$



