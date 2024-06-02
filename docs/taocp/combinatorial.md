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

### 7.1.1 布尔代数基础

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


#### 基本恒等式
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


#### n 变量函数
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

#### 可满足性。
如果布尔函数不恒等于 0，即至少有一个蕴涵元，就说它是可满足的。如果布尔公式包含 30 个布尔变量，那么，进行 $` 2^30`$ 个事例的强行检验无疑会解决问题。所以，对于可满足性问题，找到确实有效的解法将是令人惊叹的成就。

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


#### 简单特例
有两类重要的布尔公式，它们的可满足性问题已被证明是很容易判定的。这些特例出现在被检验的合取范式完全由“霍恩子句” (Horn clause) 或者完全由“克罗姆子句” (Krom clause) 组成的时候。霍恩子句是包含一些字面值的 OR，其中全部字面值或者几乎全部字面值是带补的变量。克罗姆子句是恰好两个字面值的 OR。因此类如:
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

__定理 H.__ 布尔函数 $`f(x_1,x_2,\cdots,x_n)`$ 可以表示成若干霍恩子句的合取，当且仅当对于所有布尔值 $`x_j`$ 和 $`y_j`$ 有
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


__算法 C__ (计算确定霍恩子句的核心) 给定命题变元的集合 P 和子句的集合 C，每个子命题的形式为
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

__定理 K__ 每个子句带有两个字面值的合取范式是可满足的，当且仅当相关联的有向图的强分图不会同时包含一个变量和它的补。

证明：如果存在从 x 到 $`\overline x`$ 以及从 $`\overline x`$ 到 x 的路径，公式肯定是不可满足的。
反之，假定不存在这样的路径，任何有向图至少有一个强分图 S，它是不包含来自其他任何强分图顶点的引入弧的“源点”。 

> [!tip] 
> 略

罗伯特.塔杨建立了以线性时间寻找强分图的算法，从而由 定理k 立刻的出 2SAT 问题的一个有效解。

#### 中位数
还有一种重要的三元运算符 $`\langle xyz \rangle`$, 称为 $`x,y,z`$ 的中位数：
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

__定理 P__ 每个单调子对偶布尔函数 $`f(x_1,x_2,\cdots,x_n)`$ 完全可以用中位数运算 $`\langle xyz\rangle `$ 表示。
证明：首先注意到
```math
\langle x_1y\langle x_2y\cdots y\langle x_{s-1}yx_s\rangle \cdots\rangle \rangle \\
= ((x_1 \vee x_2 \vee \cdots \vee x_{s-1} \vee x_s) \wedge y) \vee (x_1 \wedge x_2 \wedge \cdots \wedge x_{s-1} \wedge x_s) \qquad(47)
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

通过构建中位数，定义函数 $`g_0,g_1,\cdots,g_m`$ 如下：
```math
g_0(x_1,\cdots,x_n) = x1, \\
g_j(x_1,\cdots,x_n) = h(x_{j1},\cdots,x_{js_j};g_{j-1}(x_1,\cdots,x_n)) \\
\qquad(48) 
```
其中 $`h(x_1,\cdots,x_s;y)`$ 是式(47)的第一行函数。根据对 j 的归纳法，从(47)(48)可以证明，每当 $`t_1 \vee \cdots \vee t_j = 1 有 g_m(x_1,\cdots,x_n) = 1`$，因此，当 k < j 时有 $`（x_{j1} \vee \cdots \vee x_{js_j} \wedge t_k = t_k`$。

最后，$`f(x_1,x_2,\cdots,x_n)`$ 必定等于 $`g_m(x_1,x_2,\cdots,x_n)`$，因为这两个函数都是单调子对偶函数，而且已经证明，对于 0 和 1 的所有组合有 $`f(x_1,x_2,\cdots,x_n) \leq g_m(x_1,x_2,\cdots,x_n)`$。这个不等式足以证明等式成立。因此子对偶函数在 $`2_n`$ 种可能的情形中恰好有半数等于 1。

定理P 的一个推论是，通过三元素中位数表示五元素中位数，因为任何奇数数量的布尔变量的中位数显然是单调子对偶的函数。我们把这样一个中位数记为<$`x_1,x_2,\cdots,x_{2k-1}`$>，于是 <$`vwxyz`$> 的析取素式是：
```math
(v \wedge w \wedge x) \vee (v \wedge w \wedge y) \vee (v \wedge w \wedge z) \vee \\
(v \wedge x \wedge y) \vee (v \wedge x \wedge z) \vee (v \wedge y \wedge z) \vee \\
(w \wedge x \wedge y) \vee (w \wedge y \wedge z) \vee (x \wedge y \wedge z);
```
所以，定理P 的证明中把 <$`vwxyz`$> 构造成一个包含 2046 个三元素中位数运算的很长的公式 $`g_10(v,w,x,y,z)`$。当然，这个表达式不是可能的公式中最短的一个。实际上有：

< vxwxyz > = < v< xyz< wx< wyz>>>>  $`\qquad(49) `$


#### *中位数代数与中位数图
如果把  $`\wedge 和 \vee`$ 分别表示 min 和 max 运算符，那么，当 x,y,z 属于实数集之类的任何有序集时，三元 < xyz > 是很有用的。_中位数代数_ 是指任意的集合 _M_，在其上定义了三元运算 < xyz >，把  _M_ 的元素变成 _M_ 的元素，并且遵守下面三条公理：
```math
\langle xxy\rangle = x 过半数定理； \qquad(50) 
```
```math
\langle xyz\rangle = \langle xzy\rangle = \langle yxz\rangle 
 = \langle yzx\rangle  = \langle zxy\rangle  = \langle zxy\rangle 交换律； \qquad(51) 
```
```math
\langle xw\langle ywz\rangle \rangle = \langle \langle xwy\rangle wz \rangle 结合律； \qquad(52) 
```
在布尔代数的情形，例如结合律(52)对于 w=0 和 w=1 成立， 因为 $`\wedge 和 \vee`$ 是结合的。这三条公理还蕴涵中位数的分配律，它具有短形式
```math
\langle xyz\langle uv\rangle \rangle = \langle x\langle yuw\rangle \langle zuv\rangle \rangle \qquad(53) 
```
和更对称的长形式
```math
\langle xyz\langle uv\rangle \rangle = \langle \langle xuv\rangle\langle yuw\rangle \langle zuv\rangle \rangle \qquad(54) 
```
这个事实没有已知的简单证明，但至少可以证实(53)(54)当 y=u 且 z=v 时的特例，有
```math
\langle xyz\langle yz\rangle \rangle = \langle xyz\rangle \qquad(54) 
```
因为两端都等于 < xy < zyz >>。事实上，结合律(52)恰好是 (53) y=u 时的特例。同时还可以用 (55)(52)证实 x=u 时的特例：
```math
\langle \langle uyz \rangle uv\rangle = \langle vu\langle yuz\rangle\rangle = 
\langle\langle vuy\rangle uz\rangle = \langle \langle yuz\rangle uz\rangle = \\
\langle \langle \langle yuz\rangle uv\rangle uz \rangle = 
\langle \langle yuv\rangle u \langle vuz\rangle \rangle = \langle u \langle yuv \rangle\langle zuv\rangle \rangle
```
中位数代数 M 的理想时结合 $`C \subseteq M`$，满足
```math
\langle xyz \rangle \in C, 当 x \in C, y \in C, z \in M. \qquad(56) 
```
如果 u 和 v 是 M 的任意元素，则区间 [u..v] 定义为
```math
[u..v] = \{\langle xyz \rangle | x \in M\} \qquad(57) 
```
说 “x 在 u 和 v 之间” 当且仅当 $`x \in [u..v]`$。按照这些定义，u 和 v 总是属于区间[u..v]。

__引理 M__ 每个区间 [u..v] 都是一个理想，而且 $`x \in [u..v] \Leftrightarrow x = \langle xyz \rangle `$。

证明 另 < xuv > 和 < yuv > 是 [u..v] 的任意元素。那么，根据 (51)和(53)，对于所有 $`z \in M`$，有
```math
\langle\langle xuv\rangle \langle yuv\rangle z\rangle = \langle \langle xyz\rangle uv\rangle \in [u..v]
```
所以 [u..v] 是一个理想。此外，根据(51)和(55)，每个元素 $`\langle xuv \rangle \in [u..v]`$ 满足 $`\langle xuv \rangle = \langle u \langle xuv\rangle v \rangle`$

根据中位数定律，区间 [u..v] 具备良好的性质：
```math
x \in [u..v] \Rightarrow u = v;  \qquad(58)  \\
x \in [u..v] 且 y \in [u..x] \Rightarrow y \in [u..v];  \qquad(59)  \\
x \in [u..v] 且 y \in [u..z] 且 y \in [v..x] \Rightarrow y \in [x..z];  \qquad(60)
```
这些性质相当于： [u..u] = {u}；如果 $`x \in [u..v] 那么 [u..x] \subseteq [u..v]`$；对于所有的 z，$`x \in [u..v]`$ 蕴涵 $`[u..z]\cap[v..z] \subseteq [x..z]`$ 

现在，在顶点集 M 山定义一个具有下述边的图：
```math
u - v \Leftrightarrow u \neq v 且对于所有 x \in M 有 \langle xuv \rangle \in [u..v] \qquad(61)
```
换句话说，顶点 u 和 v 是邻接的，当且仅当区间 [u..v] 恰好仅由 u 和 v 这两个点组成。

__定理 G.__ 如果 M 是任意有限的中位数代数，那么由(61)定义的图是连通的。此外，顶点 x 属于区间 [u..v]，当且仅当 x 位于从 u 到 v 的最短路径上。
证明. 如果 M 不是连通的，那么选择 u 和 v，使得不存在从 u 到 v 的路径，且区间 [u..v] 具有尽可能少的元素。

令 $`x \in [u..v]`$ 是不同于 u 和 v 的元素。那么 $`\langle xuv \rangle = x \neq v`$，所以 $`v \notin [u..x]`$；同理，$`u \notin [x..v]`$。

但是由(59)可知，[u..x] 和 [x..v] 是包含在 [u..v] 内的区间，所以他们是更小的区间，因此必定有一条从 u 到 x 以及 从 x 到 v 的路径。导致矛盾。

目前，从中位数代数开始，利用它定义带有的某些性质的图。如果 u 和 v 是任意图的顶点，那么，把区间 [u..v] 定义为 u 和 v 之间的那些最短路径的所有点的集合。

如果一个有限图只有工艺额顶点位于连接任何三个给定顶点 x,y,z 的三个区间交集 $`[x..y]\cap[x..z]\cap[y..z]`$ 上，那么，这个有限图称为 _中位数图_。

按照这个定义，很多重要的图是中位数图。例如，任何自由树都是中位数图。


#### *中位数标记
如果 u 和 v 是中位数代数的任意元素，取 $`x \to \langle xuv \rangle`$ 的映射 f(x) 是一个 _同态_。根据长分配率(54)，它满足
```math
f(\langle xyz \rangle) = \langle f(x)f(y)f(z) \rangle  \qquad(62)
```
根据(57)，这个函数 $`\langle xuv \rangle`$ 把任何给定的点 x “投影”到区间 [u..v] 上。

当 u-v 是相应图的一条边时，它特别有趣，因为此时 f(x) 时二值函数，实质上是一个布尔映射。

> 有图，不变记录，后续需要加强学习
> 自由树，待学习，算法导论中有相关章节

如果当 $`u \in C 且 v \in C`$ 时，有 $`[u..v] \subseteq C`$，则图中的顶点结合 C 称为凸集。即当一条最短路径的两个端点属于 C 时，这条路径上的所有顶点必定也出现在 C 中。

因此凸集同前面所说的“理想”是相同的。现在，使用几何语言而不是代数语言。

我们把 $`\{v_1,\cdots,v_m\}`$ 的凸包定义为包含每一个顶点  $`v_1,\cdots,v_m`$ 的最小凸集。前述理论结果已经证明，每个区间 [u..v] 都是凸集。因此，[u..v] 是两点集合 {u,v} 的凸包。


__定理 C__ 中位数图中 $`\{v_1,v_2,\cdots,v_m\}`$ 的凸包是所有点的集合
```math
C = \{\langle v_1xv_2x\cdots xv_m\rangle | x \in M\}  \qquad(66)
```
此外，$`x \in C`$ 当且仅当 x = $`\langle v_1xv_2x\cdots xv_m \rangle`$

证明 对于 $`1 \leq j \leq m`$ 有 $`x_j \in C`$。因为点 x‘ = $`\langle v_2x\cdots xv_m \rangle`$ 在凸包中，而且 $`\langle v_1xv_2x\cdots xv_m \rangle \in [v_1..x']`$，所以 C 的每个点必定属于凸包。 0-1 原则证明
```math
\langle x \langle v_1yv_2y\cdots yv_m \rangle\langle v_1zv_2z\cdots zv_m \rangle\rangle 
= \langle v_1\langle xyz\rangle v_2\langle xyz\rangle \cdots \langle xyz\rangle v_m \rangle \qquad(67)
```
因此 C 是凸集。在这个公式中设 y=x，证明 $`\langle v_1xv_2x\cdots xv_m \rangle`$ 是 C 中离 x 最近的点，而且对于所有 $`z \in C`$ 有 $`\langle v_1xv_2x\cdots xv_m \rangle \in [x..z]`$


__推论 C__
对于 <$`1\leq j\leq m`$>，令 $`v_j`$ 的标记是 $`v_{j1},\cdots,v_{jt}`$。那么，$`\{v_1,\cdots,v_m\} `$ 的凸包是所有这样的 $`x \in M`$ 的集合，当  $`v_{1j} = v_{2j} = \cdots = v_{mj} = c_j`$ 时 x 的标记 $`x_1,\cdots,x_t`$ 满足 $`x_j=c_j`$。


__算法 H__
> 略，太难了，等看第二遍


#### *中位数集合
_中位数集合_ 是具有下特征的二进制向量的集合 X：每当 $`x \in X, y \in X, z \in X`$ 时有 $`\langle xyz\rangle`$，其中中位数是处理中位数标记那样按分量计算的。

托马斯舍费在 1978 年注意到，对于定理 H中的霍恩函数的表征，_中位数集合_ 提供了富有吸引力的对照。


__定理 S.__
布尔函数 $`f(x_1,\cdots,x_n)`$ 可以表示成克罗姆子句的合取，当且仅当对于所有的布尔值有 $`x_j, y_j, z_j`$ 有
```math
f(x_1,\cdots,x_n) = f(y_1,\cdots,y_n) = f(z_1,\cdots,z_n) 蕴涵
f(\langle x_1y_1z_1\rangle,\cdots,\langle x_ny_nz_n\rangle) = 1
\qquad(68)
```
证明 如果 $`x_1\vee x_2=y_1\vee y_2=z_1\vee z_2=1`$，同时 $`x_1\leq y_1\leq z_1`$，那么
```math
\langle x_1y_1z_1\rangle\vee\langle x_2y_2z_2\rangle=y_1\vee\langle x_2y_2z_2\rangle=1
```
因为 $`y_1=0`$ 蕴涵 $`x_2=y_2=1`$。因此(68)是必要条件

反之，如果(68)成立，假定 $`u_1\vee\cdots\vee u_k`$ 是 f 的素子句，其中每个 $`u_j=0`$ 都是字面值。
那么对于  $`1\leq j\leq k`$，子句  $`u_1\vee\cdots\vee u_{j-1}\vee u_{j+1}\vee\cdots\vee u_k`$ 不是 f 的子句。

所以，存在一个向量 $`x^{(j)}`$ 满足 $`f(x^{(j)})=1`$，但对于所有 $`i \neq j`$ 时，$`u_i^{(j)}=0`$ 。

如果 $`k\geq 3`$，则中位数 $`\langle x^{(1)}x^{(2)}x^{(3)}\rangle`$ 对于 $`1\leq i\leq k`$ 有  $`u_i=0`$。但这是不可能的，因此已假定 $`u_1\vee\cdots\vee u_k`$ 是子句。因此 $`k\geq 2`$
证毕。

这样中位数集合与 “2SAT范例” 相同，是满足用 2CNF 表示的某个公式 f 的点的集合。

如果中位数集合的向量 $`x=x_1\cdots,x_t`$ 不包含冗余分量，也就是说，它是缩减的。


__定理 F__
> 略，太难了，等看第二遍


__推论 F__
> 略，太难了，等看第二遍


#### 门限函数
一类特别有吸引力的重要布尔函数 $`f(x_1,x_2,\cdots,x_n)`$ 出现在 f 可以用公式
```math
f(x_1,x_2,\cdots,x_n) = [w_1x_1+w_2x_2+\cdots+w_nx_n+\geq t] \qquad(75)
```
定义的时候，其中常数 $`w_1,w_2,\cdots,w_n`$ 是整数“权值”，t 是整数 “门限”。甚至当所有权值都是 1 时，门限函数也很重要，有：
```math
x_1\wedge x_2\wedge\cdots\wedge x_n = [x_1+x_2+\cdots+x_n+\geq n] \qquad(76)
```
```math
x_1\vee x_2\vee\cdots\vee x_n = [x_1+x_2+\cdots+x_n+\geq 1] \qquad(77)
```
```math
\langle x_1x_2\cdots x_{2t-1}\rangle = [x_1+x_2+\cdots+x_{2t-1}+\geq t] \qquad(78)
```
其中 $`\langle x_1x_2\cdots x_{2t-1}\rangle`$ 代表由任意奇数布尔值 {$`x_1,x_2,\cdots,x_{2t-1}`$} 组成的多重集的中位数值。特别是，基本映射 $`x\wedge y,x \vee y, \langle xyz\rangle`$ 全都是门限函数，所以
```math
\overline x = [-x\geq 0] \qquad(79)
```
也是门限函数。

使用更一般的权值，得到许多其他有趣的函数，如
```math
[2^{n-1}x_1+2^{n-2}x_2+\cdots+x^n \geq (t_1t_2\cdots t_n)_2] \qquad(80)
```
这个门限函数为真，当且仅当二进制串 $`x_1x_2\cdots x_n`$ 按照字典序大于等于给定的二进制串 $`t_1t_2\cdots t_n`$。

给定大小分别为 $`w_1w_2\cdots w_n`$ 的那个对象的集合，这些对象的一个子集能够装进大小为 t-1 的背包，当且仅当  $`f(x_1,x_2,\cdots,x_n) = 0`$，其中 $`x_j=1`$ 表示对象 j 出现在子集中。

通过置 $`x_j \Leftarrow\overline x_j,w_j \Leftarrow -w_j,t \Leftarrow t+|w_j|`$ ，我们可以消除任何负权值  $`w_j`$，这样，一般的门限函数可以约化为正门限函数，其中所有权值都是非负的。此外可以把任何正门限函数(75)表示成奇数个变量的中位数/过半数的函数，因为有
```math
\langle 0^a1^bx_1^{w_1}x_2^{w_2}\cdots x_n^{w_n}\rangle =
[b + w_1x_1 + w_2x_2 + \cdots + w_nx_n \geq b+t], \qquad(81)
```
其中 $`x^m`$ 代表 x 的 m 个副本，而 a 和 b 是由规则
```math
a=\max(0,2t-1-w), b=\max(0,w+1-2t), w=w_1+w_2+\cdots+w_n  \qquad(82)
```
定义的。例如当所有权值都是 1 时，有
```math
\langle 0^{n-1}x_1x_2\cdots x_n\rangle = x_1\wedge x_2\wedge\cdots\wedge x_n 和
\langle 1^{n-1}x_1x_2\cdots x_n\rangle = x_1\vee x_2\vee\cdots\vee x_n , \qquad(83)
```
当 n=2 时，已经在式(45)中建国这两个公式。一般情况下，不是 a 为 0 就是 b 为 0，式(81)的左端代表 2T - 1个元素的中位数，其中
```math
T = b + t = \max(t, w_1 + w_2 + \cdots + w_n + 1 - t). \qquad(84)
```
令 a 和 b 都大于 0 毫无意义，因为过半数函数显然满足消去律
```math
\langle 01x_1x_2\cdots x_{2t-1}\rangle = \langle x_1x_2\cdots x_{2t-1}\rangle \qquad(85)
```
式(81)有一个重要推论：通过置 $`x_0=0`$ 或 $`x_0=1`$，每一个正门限函数来源于纯过半数函数
```math
g(x_0,x_1,x_2,\cdots,x_n) = \langle x_0^{a+b}x_1^{w_1}x_2^{w_2}\cdots x_n^{w_n}\rangle \qquad(86)
```
换句话，知道 n 个变量的所有门限函数，当且仅当知道 n+1 个或者更少变量的所有不同的奇数个变量的中位数函数。每个纯多半数函数都是单调自对偶函数。

通过置 $`w=0`$ 或 $`w=1`$，获得 3 个变量的所有正门限函数 f(x,y,z):
```math
\langle 0\rangle,\langle 1\rangle,\langle 00xyz\rangle,\langle 11xyz\rangle,
\langle 0yz\rangle,\langle 1yz\rangle,\langle 0xyzz\rangle,\langle 1xyzz\rangle,
\langle xyz\rangle,\langle z\rangle,
```
```math
\langle 0xyyz\rangle,\langle 0xyyz\rangle,\langle y\rangle,\langle 0xz\rangle,
\langle 1xz\rangle,\langle 0xxyz\rangle,\langle 1xxyz\rangle,
\langle x\rangle,\langle 0xy\rangle,\langle 1xy\rangle. \qquad(87)
```

存在权值 $`w_1,w_2,\cdots,w_n`$ 的无限数量的序列，但是，对于任意给定的 n 值，仅有为数有限的门限函数。所以，许多不同的权值序列显然是等价的。例如，考虑纯过半数函数
```math
\langle x_1^2x_2^3x_3^5x_4^7x_5^{11}x_6^{13}\rangle,
```
其中用素数作为权值。暴力检验 $`2^6`$ 种情形，可以证明
```math
\langle x_1^2x_2^3x_3^5x_4^7x_5^{11}x_6^{13}\rangle = \langle x_1x_2^2x_3^2x_4^3x_5^3x_6^5 \rangle.  \qquad(88)
```
因此，可以用数量少得多的权值表示同一个函数。同样作为式(80)的特例，门限函数
```math
[(x_1x_2\cdots x_{20})_2 \geq (01100100100001111110)_2] = 
\langle 1^{225028}x_1^{524288}x_2^{262144}\cdots x_{20}\rangle 
```
可以简化为
```math
\langle 1^{323}x_1^{764}x_2^{323}x_3^{323}x_4^{118}x_5^{118}x_6^{87}x_7^{31}x_8^{31}x_9^{25}
x_{10}^6x_{11}^6x_{12}^6x_{13}^6x_{13}x_{14}x_{15}x_{16}x_{17}x_{18}x_{19}\rangle  \qquad(89)
```

周绍康发现标识门限函数的好方案，可以把唯一的标识符赋予任何一个门限函数。给定任意布尔函数 $`f(x_1,x_2,\cdots,x_n)`$，令 N(f) 是使 f(x)=1 的向量 $`x = (x_1,x_2,\cdots,x_n)`$ 的数量，$`\sum (f)`$ 是所有这些向量的和。例如，如果 $`f(x_1,x_2)=x_1 \vee x_2`$，有 N(f)=3 以及 $`\sum f(x)=(0,1)+(1,0)+(1,1)=(2,2)`$。

__定理 T.__
令 $`f(x_1,x_2,\cdots x_n)`$ 和 $`g(x_1,x_2,\cdots x_n)`$ 是满足条件 N(f)=N(g) 和 $`\sum (f)= \sum (g)`$ 的布尔函数，其中 f 为门限函数。那么 f = g.
证明： 假定恰有 k 个向量 $`x^{(1)},\cdots,x^{(k)}`$ 使得 $`f(x^{(j)})=1`$ 且 $`g(x^{(j)})=0`$。

由于 N(f)=N(g)， 必定恰有 k 个向量 $`y^{(1)},\cdots,y^{(k)}`$ 使得 $`f(y^{(j)})=0`$ 且 $`g(x^{(j)})=1`$。

同时由于 $`\sum (f)= \sum (g)`$，必定还有 $`x^{(1)}+\cdots+x^{(n)} = y^{(1)}+\cdots+y^{(k)}`$。

现在假定 f 是门限函数(75)。那么，对于 $`1\leq j \leq k`$，使得有 $`w\cdot x^{(j)}\geq t`$ 且 $`w\cdot y^{(j)} < t`$。但是，如果 $`f \neq g`$，有 k>0，而且
```math
w\dot(x^{(1)}+\cdots+x^{(k)}) \geq > w\cdot (y^{(1)}+\cdots+y^{(k)})
```
出现矛盾，证毕。


#### 对称布尔函数
如果对于 {1,...,n} 的所有排列 p(1),...p(n)，函数 $`f(x_1,x_2,\cdots x_n)`$ 等于 $`f(x_{p(1)},x_{p(2)},\cdots x_{p(n)})`$，就称函数 $`f(x_1,x_2,\cdots x_n)`$ 是对称的。

当所有的 为 0 或 1 时，这个条件意味着 f 仅依赖于自变量中出现的 1 的数量，也就是 “位叠加和”：
```math
vx = v(x_1,\cdots,x_n) = x_1 + \cdots + x_n.
```
记号 $`S_{k_1,k_2,\cdots,k_r}(x_1,x_2,\cdots x_n)`$ 常用于表示这样的布尔函数：它为真，当且仅当 vx 或者是 $`k_1`$，或者是 $`k_2,\cdots`$，或者是 $`k_r`$。例如：
```math
S_{1,3,5}(v,w,x,y,z) = v\oplus w\oplus x\oplus y\oplus z,
S_{3,4,5}(v,w,x,y,z) = \langle vwxuz\rangle, S_{4,5}(v,w,x,y,z) = \langle 00vwxuz\rangle
```
对称性的许多应用同仅当 vx=k 时为真的基本函数S_k(x1,\cdots,x_n)有关。

例如，$`S_3(x_1,x_2,x_3,x_4,x_5,x_6)`$ 为真。当且仅当变量 {$`x_1,\cdots,x_6`$} 恰有一半为真，一半为假。显然有
```math
S_k(x_1,x_2,\cdots x_n) = S_{\geq k}(x_1,x_2,\cdots x_n)\wedge \overline{S_{\geq k+1}(x_1,x_2,\cdots x_n)}.  \qquad(90)
```
其中 $`S_{\geq k}(x_1,x_2,\cdots x_n)`$ 是 $`S_{k,k-1,\cdots,n}(x_1,x_2,\cdots x_n)`$ 的缩写。当然函数 $`S_{\geq k}(x_1,x_2,\cdots x_n)`$ 是探讨过的门限函数 $`[x_1+x_2+\cdots+x_n+\geq k]`$ 

更复杂的情形可以作为的门限函数的门限函数处理。例如有
```math
S_{2,3,6,8,9}(x_1,x_2,\cdots x_{12}) = [vx\geq 2 + 4[vx\geq 4] + 2[vx\geq 7] + 5[vx\geq 10]] \\
= \langle 00x_1\cdots x_{12}\langle 0^5\overline x_1\cdots \overline x_{12}\rangle^4
\langle 1\overline x_1\cdots \overline x_{12}\rangle^2
\langle 1^7\overline x_1\cdots \overline x_{12}\rangle^5\rangle, \qquad(91)
```
因为当 $`x_1+x_2+\cdots x_{12}=(0,1,\cdots,12)`$ 时，在最外层的 25 的过半数中，二进制位 1 的数量分别为 (11,12，13,14,11,12,13,12,13,14,10,11,12)。一种类似的两层结构在一般情形是适用的。多三层或更多层逻辑，可以进一步减少门限运算的数量。

业已发现的各种巧妙方法用于计算对称布尔函数。例如，室贺三郎把下面著名的算式序列归功于佐佐木不可止
```math
x_0\oplus x_1\oplus\cdots\oplus x_{2m} = \langle \overline x_0s_1s_2\cdots s_{2m}\rangle,\\
where s_j=\langle x_0x_jx_{j+1}\cdots x_{j+m-1}\overline x_{j+m}\overline x_{j+m+1}\cdots\overline x_{j+2m-1}\rangle, \qquad(92)
```
条件是 m > 0，而且，当 $`k\geq 1`$ 时把 $`x_{2m+k}`$ 和 $`x_k`$ 看成是相同的。特别的，当 m=1 和 m=2 时，有恒等式
```math
x_0\oplus x_1\oplus x_2 = \langle\overline x_0 \langle x_0x_1\overline x_2\rangle
\langle x_0x_2\overline x_1\rangle\rangle \qquad(93)
```
```math
x_0\oplus\cdots\oplus x_4 = \langle\overline x_0
\langle x_0x_1x_2\overline x_3\overline x_4\rangle
\langle x_0x_2x_3\overline x_4\overline x_1\rangle
\langle x_0x_3x_4\overline x_1\overline x_2\rangle
\langle x_0x_4x_1\overline x_2\overline x_3\rangle\rangle   \qquad(94)
```
两式右端完全时对称的。


#### 定向函数
如果通过检查布尔函数 $`f(x_1,x_2,\cdots x_n)`$ 的至多一个变量就能推断出它的值，就称为 _定向函数_ 或者 “强制函数“。更确切的说，如果 n = 0，或者存在一个下标 j，使得 f(x) 要么当置 $`x_j=0`$ 时取常数值，要么当置 $`x_j=1`$ 时取常数值，那么 f 是 _定向函数_。

例如，$`f(x,y,z)=(x\oplus)\vee\overline y`$ 是定向函数，因为当 y = 0 时它横等于 1。

斯图亚特考夫曼引入这类函数，在许多应用(特别时化学和生物学)中已被证实是很重要的。


#### 数量考虑因素
已探讨过许多不同类型的布尔函数，于是自然要问：每种类型的 n 变量函数实际有多少个？表3、表5和表5给出了对于小的 n 值的答案。

表3 对所有函数计数。对于每个 n 有 $`22_n`$ 种可能性，因为存在 $`22_n`$ 个可能的真值表。在这些函数中，有些是子对偶函数；有些是单调函数；有些既是子对偶函数又是单调函数，如定理 P所示；有些是霍恩函数，如定理 H 所示；有些是克罗姆函数，如定理 S 所示；诸如此类。

__表3 n 变量布尔函数__
| | n=0 | n=1  | n=2 | n=3 | n=4 | n=5 | n=6 
|:--|--:|--:|--:|--:|--:|--:|--:|
任意函数 | 2 | 4 | 16 | 256 | 65,536 | 4,294,967,296 | 18,446,744,073,709,551,616
自对偶函数 | 0 | 2 | 4 | 16 | 256 | 65,536 | 4,294,967,296
单调函数 | 2 | 3 | 6 | 20 | 168 | 7,581 | 7,828,354
单调自对偶函数 | 0 | 1 | 2 | 4 | 12 | 81 | 2,646
霍恩函数 | 2 | 4 | 14 | 122 | 4,960 | 2,771,104 | 151,947,502,948
克罗姆函数 | 2 | 4 | 16 | 166 | 4,170 | 224,716 | 24,445,368
门限函数 | 2 | 4 | 14 | 104 | 1,882 | 94,572 | 15,028,134
对称函数 | 2 | 4 | 8 | 16 | 32 | 64 | 128
定向函数 | 2 | 4 | 14 | 120 | 3,514 | 1,292,276 | 103,071,426,294


在表4 中，如果两个函数的差别仅仅在于变量名称有所改变，那么他们被视为相同的。因此当 n = 2 时只有 12 种不同的情形，因为 例如 $`x\vee\overline y`$  $`\overline x\vee y`$ 实际上是相同的。

__表4 变量置换下不同的布尔函数__
| | n=0 | n=1  | n=2 | n=3 | n=4 | n=5 | n=6 
|:--|--:|--:|--:|--:|--:|--:|--:|
任意函数 | 2 | 4 | 12 | 80 | 3,984 | 37,333,248 | 25,626,412,338,274,304
自对偶函数 | 0 | 2 | 2 | 8 | 32 | 1,088 | 6,385,408
单调函数 | 2 | 3 | 5 | 10 | 30 | 210 | 16,353
单调自对偶函数 | 0 | 1 | 1 | 2 | 3 | 7 | 30
霍恩函数 | 2 | 4 | 10 | 38 | 368 | 29,328 | 216,591,692
克罗姆函数 | 2 | 4 | 12 | 48 | 308 | 3,028 | 49,490
门限函数 | 2 | 4 | 10 | 34 | 178 | 1,720 | 590,440
定向函数 | 2 | 4 | 10 | 38 | 294 | 15,774 | 149,325,022


表5 更进一步，它允许对单独的变量取补，甚至对整个函数取补，这实际上没有改变它。

__表5 变量取补或置换下不同的布尔函数__
| | n=0 | n=1  | n=2 | n=3 | n=4 | n=5 | n=6 
|:--|--:|--:|--:|--:|--:|--:|--:|
任意函数 | 1 | 2 | 4 | 14 | 222 | 616,126 | 200,253,952,527,184
自对偶函数 | 0 | 1 | 1 | 3 | 7 | 83 | 109,950
门限函数 | 1 | 2 | 3 | 6 | 15 | 63 | 567
自对偶门限函数 | 0 | 1 | 1 | 2 | 3 | 7 | 21
定向函数 | 1 | 2 | 3 | 6 | 22 | 402 | 1,228,158


按照这种观点，(x,y,z) 的 256 个布尔函数仅分成 14 个不同的等价类：
| 表示式 | 类大小 | 表示式  | 类大小 
|:--|--:|:--|--:|
0 | 2 | $`x\wedge(y\oplus z)`$ | 24
x | 6 | $`x\oplus(y\wedge z)`$ | 24
$`x\wedge y`$ | 24 | $`(x\wedge y)\vee(\overline x\wedge z)`$ | 24
$`x\oplus y`$ |6 | $`(x\vee y)\wedge(x\oplus z)`$ | 48
$`x\wedge y\wedge z`$ | 16 | $`(x\oplus y)\vee(x\oplus z)`$ | 8
$`x\oplus y\oplus z`$ | 2 | $`\langle xyz \rangle`$ | 8
$`x\wedge(y\vee z)`$ | 48 | $`S_1(x,y,z)`$ | 16 
(95)


### 7.1.2 布尔函数求值

布尔函数求值同在4.6.4节讨论的多项式求职方法非常相似。研究这一主题的的一种自然途径是考虑函数的基本运算链，这种链类似于前面讨论的多项式链。

对于 n 变量函数 $`(x_1,\cdots,x_n)`$， _布尔链_ 就是每一步组合了先前两步的序列 $`(x_{n+1},\cdots,x_(n+r))`$:
```math
x_i = x_{j(i)} o_i x_{k(i)}, n+1\leq i \leq n+r   \qquad(1)
```
其中 $`1\leq j(i) < i,1\leq k(i) < i, o_i`$ 是表7.1.1-1 中 16种二元运算符之一。例如，当 n=3 时，两条链
```math
x_4 = x_1\wedge x_2 \qquad x_4 = x_2\oplus x_3  \\
x_5 = \overline x_1\wedge x_5 \qquad x_5 = x_1\wedge x_4 \\
x_6 = x_4\vee x_5 \qquad x_6 = x_3\oplus x_5  \qquad(2)
```
都是计算 “多路复用器” 函数或 “若-则-否则” 函数 $`x_6=(x_1?x_2:x_3)`$，它的取 $`x_2`$ 或 $`x_3`$ 的值取决于 $`x_1`$ 是 1 (真) 或 $`x_1`$ 是 0 (假)。

布尔链自然的对应于电子线路，链中的每一步对应于有两个输入和一个输出的 “门” 电路。

此外也可以把布尔链画成二叉树，当布尔链的中间步骤被多次使用时，这种二叉树会有交叠的子树。每个内部节点用二元运算符标记，外部节点用代表变量的 $`x_k`$ 整数 k 标记。

给定一个 n 变量的函数 f，经常需要求一条使得 $`x_{n+r} = f(x_1,\cdots,x_n)`$ 的布尔链，其中 r 尽可能的小。

函数 f 的 _组合复杂性_ C(f) 是计算它的最短布尔链的长度。将 C(f) 简称为 “f 的代价”

在 7.1.1 节讨论的 f 的 DNF 和 CNF 表示，没有提供多少关于 C(f) 的信息，因为通常可能存在更有效的计算方案。例如在 7.1.1-(30) 后面的讨论种，发现近乎随机的 4 变量函数(它的正值表是 1100 1001 0000 1111) 没有比
```math
(\overline x_1\wedge\overline x_2\wedge\overline x_3)\vee 
(\overline x_1\wedge\overline x_3\wedge\overline x_4)\vee
(x_2\wedge x_3\wedge x_4)\vee(x_1\wedge x_2) \qquad(5)
```
更短的 DNF 表达式。这个公式对应于一条 10 步的布尔链。但是那个函数也可以更巧妙的表示成
```math
(((x_2\wedge\overline x_4)\oplus\overline  x_3)\wedge\overline x_1\oplus x_2) \qquad(6)
```
所以它的复杂性最多是 4。

如何能够发现式(6)那样并非显而易见的公式呢?将会看到，对于 4 个变量的函数，计算机无需大量的计算就可以求出最佳链。不仅如此，即使对布尔函数已经很有经验的人，其结果也可能令其非常吃惊。

考虑函数  $`S_2(x_1,x_2,x_3,x_4)`$，有
函数 | 真值表
|:--|--:|
$`x_1`$ | 0000 0000 1111 1111
$`x_2`$ | 0000 1111 0000 1111
$`x_3`$ | 0011 0011 0011 0011
$`x_4`$ | 0101 0101 0101 0101
$`x_5=x_1\oplus x_3`$ | 0011 0011 1100 1100
$`x_6=x_1\oplus x_2`$ | 0000 1111 1111 0000
$`x_7=x_3\oplus x_4`$ | 0110 0110 0110 0110
$`x_8=x_5\vee x_6`$ | 0011 1111 1111 1100
$`x_9=x_6\oplus x_7`$ | 0110 1001 1001 0110
$`x_{10}=x_8\wedge\overline x_9`$ | 0001 0110 0110 1000

这里的真值表很容易证实计算的每一步。$`x_8`$ 步产生一个当 $`x_1\neq x_2`$ 或 $`x_1\neq x_3`$ 时为真的函数；同时， $`x_9 = x_1\oplus x_2\oplus x_3\oplus x_4`$ 是奇偶性函数 $`(x_1+x_2+x_3+x_4)\mod 2`$。所以，最后的结果 $`x_{10}`$ 恰好当 {$`x_1,x_2,x_3,x_4`$} 的两个是 1 时为真；这就是满足 $`x_s`$ 并且具有偶检验的两种情况

一般说来，如果 $`f(x_1,\cdots,x_n)`$ 是任意布尔函数，说它的长度 L(f) 是 f 的最短公式种二元函数的数目。显而易见 $`L(f)\geq C(f)`$。当 n=4 时 $`L(S_2)=7`$ 超过 $`C(S_2)=6`$，而且当 n 很大时， L(f) 几乎总是大大超过 C(f)。

布尔函数的深度 f 的深度 D(f) 是其固有复杂性的另一个重要度量：一条布尔链的深度是它的树形图中最长下行路径的长度。

__对于 n = 4 的最优链__
对于 4 变量函数，穷举计算是可行的，因为这样的函数只有 $`2^{16}=65536`$ 个真值表。事实上只需考虑真值表的一半，因为任何函数 f 的补 $`\overline f`$ 具有同 f 本身一样的代价，长度和深度。

如果 f(0,...,0) = 0，不妨说 $`f(x_1,\cdots,x_n)`$ 是 _正规的_，而且一般说来，
```math
f(x_1,\cdots,x_ n)\oplus f(0,\cdots,0) \qquad(10)
```
是 f 的“正规化”。任何布尔链的正规化，可以通过对它的每一步做正规化并对运算符做相应改变来实现；因为如果 $`(\hat x_1,\cdots,\hat x_{i-1})`$  是 $`(x_1,\cdots,x_{i-1})`$ 的正规化，且像式(1)那样 $`x_i = x_{j(i)} o_j x_{k(i)}`$ 那么 $`\hat x_i`$ 显然是 $`\hat x_{j(i)}`$ 和 $`\hat x_{k(i)}`$ 的二进制函数。 因此不失一般性，可以只考虑正规布尔链，其中每一步 $`x_i`$ 都是正规的。

一条布尔链是正规的，当且仅当它的每一个二元运算符 $`o_i`$ 都是正规的。同时只有 8 个正规二元运算符，其中 3 个运算符是平凡的。 因此可以认为所有值得注意的布尔链是由 5 个运算符构成的。此外，可以假定在每一步中 $`j(i) < k(i)`$。

4 变量的正规布尔函数共有 $`2^{15}=32768`$ 个，依次列举长度为 0,1,2,... 的所有函数，可以荣誉计算出他们的长度。

实际上，L(f) = r 蕴涵对于某个 g 和 h 有 f = g o h，其中 L(g) + L(h) = r - 1, o 是 5 个非平凡正规运算符之一。所有计算如下：

__算法 L__ 求正规函数的长度

对于 $`r\geq 0`$，通过建立长度为 r 的所有非零正规函数的列表，这个算法确定对于所有正规真值表 $`0\geq f < 2^{2^n-1}`$ 的 L(f)。

L1. [初始化] 置 $`L(0)\Leftarrow 0, L(f)\Leftarrow \infty(1\leq f < 2^{2^n-1})`$。然后，对于 $`1\leq k\leq n`$ 置 $`L(x_k)\Leftarrow 0`$ 并把 $`x_k`$ 放进表 0，其中
```math
x_k = (2^{2^n} -1)/(2^{2^{n-k}}+1) \qquad(10)
```
是 $`x_k`$ 的真值表。最后，置 $`c\Leftarrow 2^{2^n-1}-n-1`$，c 是 $`L(f)=\infty`$ 的位置的数目。

L2. [对r循环] 对于 r=1,2,... 执行 L3；当 c 变成 0时，算法终止。

L3. [对j和k循环] 当 $`j\leq k`$ 时，对于 j=1,2,... 和 k=r-1-j 执行 L4 。

L4. [对g和h循环] 对于表 j 中的所有 g 和表 k 中的所有 h 执行 L5。 

L5. [对f循环] 对于 $`f=g\&h, f=\overline g\&h, f=g\&\overline h, f=g | h, f=g\oplus h`$ 执行 L6。

L6. [f是新项吗?] 如果 $`L(f)=\infty`$，置 $`L(f)\Leftarrow r,c\Leftarrow c-1`$，并且把 f 放进表 r 中，如果 c=0，算法终止。

事实上，再加上少量工作，可以通过计算一个称为 f 的 ”足迹“ 的试探二进制位置向量 $`\phi(f)`$ 来修改算法L，用它求 C(f) 的更好的上界。

一条正规布尔链能够仅以 $`5\binom{n}{2}`$ 种不同的方式开始，因为第一步 $`x_{n+1}`$ 必须或是 $`x_1\wedge x_2`$，或是 $`\overline x_1\wedge x_2`$ 或是 $`x_1\wedge \overline x_2`$ 或是 $`x_1\vee x_2`$ 或是 $`x_1\oplus x_2`$ 或是 $`x_1\wedge x_3`$ 或是 $`\cdots`$ 或是 $`x_{n-1}\oplus x_n`$。假定 $`\phi(f)`$ 是长度为 $`5\binom{n}{2}`$ 的二进制位向量，U(f) 是 C(f) 的上界，他们具有下述性质： $`\phi(f)`$ 中的每个二进制位 1 对应于以 U(f) 步计算 f 的某条布尔链的第一步。

这样的上界-足迹对 $`(U(f),\phi(f))`$ 可以通过扩充算法 L 的基本策略计算。

最初，置 $`U(f)\Leftarrow 1`$，并且对于代价为 1 的所有函数 f 置 $`\phi(f)`$ 为相应的向量 0...010...0  。

然后，对于 r =2,3,...，像以前那样继续求函数 f = g o h，其中 U(g)+U(h)=r-1 ，但是有两点改变：
- 如果 g 和 h 的足迹至少有一个公共元素，即若 $`\phi(g)\& \phi(h)\neq 0`$，那么可知 $`C(f)\leq r-1`$，所以若它大于等于 r ，则可以降低 U(f)
- 如果 g o h 的代价等于当前 U(f) 的上界，那么若 U(f)=r 置 $`\phi(f)\Leftarrow \phi(f)|(\phi(g)|\phi(h))`$；若 U(f)=r-1 置 $`\phi(f)\Leftarrow \phi(f)|(\phi(g)\&\phi(h))`$。

结果表明，当 n=4 时，这种足迹试探强到足以对所有函数 f 求最优代价 U(f)=C(f) 的布尔链。此外，在后面可以看到，足迹也有助于求解更为复杂的求值问题。

根据表 7.1.1-5，如果忽略由于变量置换 以及/或者 布尔量取补引起的次要差别，4 变量的 $`2^{16}=65536`$ 个函数仅属于 222 个不同的类。算法 L 及其变形产生了表 1 所示的全部统计。

__表 1 具有给定复杂性的 4 变量函数的数目__
C(f) | 类 | 函数 | L(f) | 类 | 函数 | D(f) | 类 | 函数
|:--|--:|--:|:--|--:|--:|:--|--:|--:|
0 | 2 | 10 | 0 | 2 | 10 | 0 | 2 | 10 
1 | 2 | 60 | 1 | 2 | 60 | 1 | 2 | 60
2 | 5 | 456 | 2 | 5 | 456  | 2 | 17 | 1 458
3 | 20 | 2 474 | 3 | 20 | 2 474  | 3 | 179 | 56 456
4 | 34 | 10 624 | 4 | 34 | 10 624  | 4 | 22 | 7 552
5 | 75 | 24 184 | 5 | 75 | 24 184  | 5 | 0 | 0
6 | 72 | 25 008 | 6 | 68 | 24 640  | 6 | 0 | 0
7 | 12 | 2 720 | 7 | 16 | 3 088  | 7 | 0 | 0

__*用最小存储求值__
假定布尔值 $`x_1,\cdots, x_n`$ 出现在 n 个寄存器中，希望通过执行形如
```math
x_{j(i)} \Leftarrow x_{j(i)} o_i x_{k(i)} \qquad(12)
```
的一系列运算来求函数的值，其中 $`1\leq j(i)\leq n, 1\leq k(i)\leq n`$，且 $`o_i`$ 是二元运算符。在计算结束时，所求的函数值应出现在寄存器中。例如 当 n=3 时，4 步运算序列
```math
(x_1=00001111, x_2=00110011, x_3=01010101)
```
```math
x_1 \Leftarrow x_1\oplus x_2
```
```math
(x_1=00111100, x_2=00110011, x_3=01010101)
```
```math
x_3 \Leftarrow x_3\wedge x_1
```
```math
(x_1=00111100, x_2=00110011, x_3=00010100)
```
```math
x_2 \Leftarrow x_2\wedge\overline x_1
```
```math
(x_1=00111100, x_2=00000011, x_3=00010100)
```
```math
x_3 \Leftarrow x_3\vee x_2
```
```math
(x_1=00111100, x_2=00000011, x_3=00010111) \qquad(13)
```
计算中位数<$`x_1x_2x_3`$>，并把它存放到 $`x_3`$ 的原有位置。在执行每步运算的前后，寄存器内容的全部8种可能性作为真值表显示如上。



