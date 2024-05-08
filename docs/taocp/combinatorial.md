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
考察一下运算符$\vee, \wedge, \oplus, \overline x$的相互作用，因为其他运算符很容易通过这四种运算符表示。$\vee, \wedge, \oplus$的每一个都是可结合和可交换的。除了分配率(1)和(2)，还有以下分配率：
```math
(x\oplus y)\wedge z = (x\wedge z)\oplus(y\wedge z) \qquad (6)
```
以及吸收率：
```math
(x\wedge y)\vee x = (x\vee y)\wedge x \qquad (7)
```
_注，编程语言使用&，|代替 $\wedge, \vee$_


一个最简单也最有用的恒等式
```math
x\oplus x = 0 \qquad (8)
```
因为它特别蕴含
```math
(x\oplus y)\oplus x = y, (x\oplus y)\oplus y = x  \qquad (9)
```
只要利用$x\oplus 0=x$这个明显的事实，既可以看出上式推导成立，同时也不要忽略简单的补定率：
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
3个布尔变量x,y,z的布尔函数f(x,y,z)可以用它的8位真值表f(0,0,0)f(0,0,1)...f(1,1,1)定义。一般来说，每个n元布尔函数$f(x_1,x_2,\cdots x_n)$对应于依次取值的f(0,0,...,0)f(0,0,...,1)...f(1,1,...,1)的$2^n$位真值表。当n>0时，总是可以写出
```math
f(x_1,x_2,\cdots x_n) = g(x_1,x_2,\cdots x_{n-1}) \oplus h(x_1,x_2,\cdots x_{n-1})\wedge x_n \qquad(16)
```
其中，相应的函数g和h定义如下：
```math
g(x_1,x_2,\cdots x_{n-1}) = h(x_1,x_2,\cdots x_{n-1},0)  \\
\\
h(x_1,x_2,\cdots x_{n-1}) = f(x_1,x_2,\cdots x_{n-1},0) \oplus f(x_1,x_2,\cdots x_{n-1},1) \qquad(17)
```
运算符$\wedge$优先于$\oplus$，所以等式(16)对于g和h递归地重复这个过程，直到降至0元函数，而且常数时常可以简化掉，因为有
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
等式(21)以代替式(17)，重复迭代布尔的过程，利用分配率(1)，并消除常数，留下一个0或小项的析取公式，其中每个小项是$x_1\wedge \overline x_2 \wedge \cdots \wedge x_n$这样的与(合取)，每个变量的或它的补都在小项中出现，一个小项恰好在一点为真的布尔函数。

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
其中每个$u_{jk}$是字面值，也就是变量$x_i$或它的补。同样，_和取范式_(conjunctive normal form,，简称CNF)是指析取的 _任意_ 和取：
```math
\wedge_{j=1}^{m} \vee_{k=1}^{s_j} u_{jk} = (u_{11} \vee \cdots \vee u_{1s_1}) \wedge \cdots \wedge (u_{m1} \vee \cdots \vee u_{ms_m})  \qquad(26)
```

通常把DNF中的项称为 _蕴含元_，因为析取的任何小项的真值蕴含整个公式的真值。例如在像：
```math
f(x,y,z) = (x \wedge \overline y \wedge z) \vee (y \wedge z) \vee (\overline x \wedge y \wedge \overline z)
```
这样的公式中，$x \wedge \overline y \wedge z$为真时f为真，就是说当(x,y,z)=(1,0,1)时f为真。在这个例子中$x \wedge z$也是f的蕴含元，所以，可以有更简单的公式
```math
f(x,y,z) = (x \wedge z) \vee (y \wedge z) \vee (\overline x \wedge y) \qquad(27)
```
对于一个蕴含元，如果通过消除它的字面值作进一步的分解时导致其弱化到不再时蕴含元，那么，称其为 _素蕴含元_。

如果简化记号，并采纳一种更具几何学的观点，把$`f(x_1,x_2,\cdots,x_n)`$直接写成f(x)，把 x 看成是向量，或者长度为 n 的二进制串。例如使式(22)的函数为真的二进制串 wxyz 是

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