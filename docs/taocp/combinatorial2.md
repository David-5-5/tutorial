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

事实上，如果倒过来分析，那么可以通过一次只处理一个真值表来查对计算，而不用记录全部三那个真值表。令 $`f_l(x_1,x_2,\cdots,x_n)`$ 表示经 $`l,l+1,\cdots,r`$ 步运算的函数，其中省略了前 l-1 步，这样在例子中， $`f_2(x_1,x_2,x_3)`$ 将是在三步运算中
```math
x_3 \Leftarrow x_3\wedge x_1,x_2\Leftarrow x_2\wedge\overline x_1,x_3 \Leftarrow x_3\vee x_2
```
之后 $`x_3`$ 中的结果。于是通过全部四步运算，寄存器 $`x_3`$ 中的计算函数是
```math
f_1(x_1,x_2,x_3) = f_2(x_1\oplus x_2,x_2,x_3).  \qquad(14)
```
同样，
```math
f_2(x_1,x_2,x_3) = f_3(x_1,x_2,x_3\wedge x_1), \\
f_3(x_1,x_2,x_3) = f_4(x_1,x_2\wedge\overline x_1,x_3), \\
f_4(x_1,x_2,x_3) = f_5(x_1,x_2,x_3\vee x_1), f_5(x_1,x_2,x_3)=x_3.
```
所以，通过一种适合的方式对个真值表进行操作，可以从 $`f_5`$ 回到 $`f_5`$ 回到 $`\cdots`$ 回到 $`f_1`$ 。

例如，假定 $`f(x_1,x_2,x_3)`$ 是真值表为 $`t=a_0a_1a_2a_3a_4a_5a_6a_7`$ 的函数；那么 $`g(x_1,x_2,x_3) = f(x_1\oplus x_2,x_2,x_3)`$ 的真值表为 $`u=a_0a_1a_6a_7a_4a_5a_2a_3`$，它是通过以 $`a_{x'}`$ 替代 $`a_{x}`$ 获得的，其中
```math
x=(x_1,x_2,x_3)_2 蕴涵 x‘ = ((x_1\oplus x_2)x_2x_3)_2.
```
同样，$`h(x_1,x_2,x_3) = f(x_1,x_2,x_3\wedge x_1)`$ 的真值表为
```math
t=a_0a_1a_2a_3a_4a_5a_6a_7
```
同时，可以用按位运算从 t 计算 u 和 (见7.1.3-83)
```math
u = t\oplus((t\oplus(t>>4)\oplus(t<<4))\&(00110011)_2).  \qquad(15)
```
```math
v = t\oplus((t\oplus(t>>1))\&(01010000)_2).  \qquad(16)
```
令 $`C_m(f)`$ 为对 f 的最短、最小存储计算的长度。反向计算原则表明，如果知道满足 $`C_m(f) < r`$ 的所有函数 f 的真值表，就可以很容易求出满足 的所有函数 $`C_m(f) = r`$ 的真值表。就是说可以像前面那样只考虑正规函数。于是，对于满足 $`C_m(g) = r-1`$ 的所有正规函数 g，可以构造对于
```math
g(x_1,\cdots,x_{j-1},x_j o x_k,x_{j+1},\cdots,x_n).  \qquad(17)
```
的 5n(n-1) 个真值表，并且如果他们以前未被标记，那么用代价 r 标记它们。

当 n=4 时，除了 13 个以外的全部 222 个基本函数类型都有 $`C_m(f)=C(f)`$ ，所以他们可以用最小存储求值而不增加代价。特别是，所有的对称函数具有这种性质，虽然这在图 9 中不是完全明显的。

5 类函数具有 $`C(f)=5`$，然而 $`C_m(f)=6`$；8类函数具有 $`C(f)=6`$，然而 $`C_m(f)=7`$。后面这种函数类型最令人感兴趣的例子或许是函数 $`(x_1\vee x_2)\oplus(x_3\vee x_4)\oplus(x_1\wedge x_2\wedge x_3\wedge x_4)`$，它的代价为 6,因为它有计算式
```math
x_1\oplus(x_3\vee x_4)oplus(x_2\wedge(\overline x_1\vee(x_3\wedge x_4))).  \qquad(18)
```
但是它么有长度小于 7 的最小存储链。


__*确定最小代价__
函数 f 的全部最优化布尔链 $`(x_{n+1},\cdots,x_{n+r})`$ 显然至少满足下面三那个条件之一，由此可以求出 $`C(f)`$ 的准确值：
1. $`x_{n+r}=x_j o x_k`$，其中 $`x_j`$ 和 $`x_k`$ 不使用共同的中间结果
2. $`x_{n+r}=x_j o x_k`$，其中在 $`x_{n+2},\cdots,x_{n+r}`$ 步或者不用 $`x_j`$ 或者不用 $`x_k`$；
3.  上面两个条件都不满足，即使对中间步骤重新编号。
在情况 1,有 f = g o h，其中 C(g)+C(h)=r-1，把这种结构称为 “自顶向下” 结构。
在情况 2,有 $`f(x_1,\cdots,x_n)=g(x_1,\cdots,x_{j-1},x_j o x_k,x_{j+1},\cdots,x_n)`$，其中 C(g)=r-1，我们把这种结构称为 “自底向上” 结构。

仅仅递归使用自顶向下结构的最佳链，对于最小公式长度 L(f)。仅仅递归使用自底向上结构的最佳链，对应于长度为 $`C_m(f)`$ 的最小存储计算。通过混合自顶向下结构和“自底向上” 结构，可以获得更好的结果；但是仍然无法知道是否已经求出 $`C(f)`$ ，因为属于情况 3 的一条特殊的布尔链可能是更短的。

幸好这种特殊链是罕见的，因为它们必须满足相当强的条件，而且当 n 和 r 不是过分大时可以用穷举方式列出它们。

通过在每一种特殊链中有条理的尝试 $`5^r`$ 种可能的方式，每一种方式为树的内部结点指定一个正规运算符，将在每个等价类种至少找到一个函数 f，对它而言，最小代价 C(f) 仅在情况 3 是可以达到的。

事实上，当 n=4 且 r=6 时，这 $`25\cdot 5^6=390 625`$ 种试验仅仅产生一类函数，此类函数不能通过任何自顶向下加自底向上的链用 6 步计算。这个以不完全对称函数 $`(\langle x_1x_2x_3\rangle\vee x_4)\oplus(x_1\wedge x_2\wedge x_3)`$ 为代表的缺少 $`C(f)`$ 的函数类，通过恰当的指定上面所属的前 5 种链种的任何一种链，可以用 6 步达到。例如，对应于第一种特别链的一个方式是
```math
x_5=x_1\wedge x_2, x_6=x_1\vee x_2, x_7=x_3\oplus x_5, \\
x_8=x_4\wedge\overline x_5, x_9=x_6\wedge x_7, x_10=x_8\vee x_9 \qquad(19)
```
由于所有其他函数有 $`L(f)\leq 7`$，因而这些试验计算确定了所有情况的真实最小代价。

_历史注记_: 对首次联合尝试以最优方式求值所有布尔函数 f(w,x,y,z) 的报道，霍华德艾肯的研究人员提出了他们所能构造的最佳开关电路的一些试探方法和大量的数据表。他们的代价量度 V(f) 不同于我们考虑的代价 C(f)。因为它是建立在真空管的 “控制栅极” 基础上的。他们有 4 种类型的门电路：NOT(f)、NAND(f,g)、$`OR(f_1,\cdots,f_k)`$ 和  $`AND(f_1,\cdots,f_k)`$，其代价分别为1,2, k 和 0. NOT、NAND、OR 的每个输入可能是一个变量，可能是一个变量的补，或者是前面的门的输出; AND 的每个输入必须或者是 NOT 尚未在别处使用的 NAND 的输出。

使用代价准则，一个函数可能不具有如其补一样的代价。例如，可以把 $`x\wedge y`$ 作为 $`AND(NOT(\overline x), NOT(\overline y))`$ 以代价 2 求值;但是，$`\overline x\vee(\overline y\wedge\overline z)=NAND(x, OR(y,z))`$ 的代价是 4，而它的补 $`x\wedge(y\vee z)=AND(\overline x, NAND(\overline y,\overline z))`$ 的代价仅为 3。所以，哈佛大学的研究人员需要考虑 402 种而不是 222 种实际上不同的 4 变量函数类。在那个年代，它们自然主要用手工计算。除了与 $`S_{0,1}(w,x,y,z)\vee (S_2(w,x,y)\wedge z)`$ 等价的 64 个函数，它们求出了在所有情况下 V(f) < 20，其时他们用 20 个控制栅极求值如下：
```math
g_1 = AND(NOT(\overline w), NOT(\overline x)), g_2 = NAND(\overline y, \overline z) \\
g_3 = AND(NOT(w), NOT(x));
f = AND(NAND(g_1,g_2),NAND(g_3,AND(NOT(\overline y),NOT(\overline z))), \\
NOT(AND(NOT(g_3),NOT(\overline y),NOT(Z))),\\
NOT(AND(NOT(g_1),NOT(g_2),NOT(g_3)))) \qquad(20)
```
求可严重的最优电路的第一个计算机程序由利奥赫勒曼编写，他对任何给定函数 f(x,y,z) 的求值确定了所需的最少 NOR 门。他要求每个门的每个输入或者是不带补的变量，或者是前一个门的输出；限制了扇入和扇出最多为 3。当两个电路就有同等数量的门时，他宁愿采用具有最小输入和的电路。例如，他计算出 $`\overline x=NOR(x)`$ 的代价是 1； $`x\vee y\vee z=NOR(NOR(x,y,z))`$ 的代价是 2； < xyz > = NOR(NOR(x,y),NOR(x,z),NOR(y,z)) 的代价是 4； $`S_1(x,y,z)=NOR(NOR(x,y,z),<xyz>)`$ 的代价是 6；等等。由于了限制了扇出为 3，因而他发现每个 3 变量的函数可以用 7 或者更小的代价求值，只有奇偶性函数 $`x\oplus y\oplus z=(x\equiv y)\equiv z`$，其中 $`x\equiv y`$ 的代价是4，因为它是 NOR(NOR(x,NOR(x,y)),NOR(y,NOR(x,y)))。

电气工程师们对于其他代价标准进行了不断的探索，但是，直到富兰克林梁在1977年建立表1种所示的 C(f) 值之前，4 变量函数看来没有取得进展。富兰克林梁没有发表的推导，建立在不能用自底向上结构简化的所有链的研究基础之上。


__n == 5的情况__
根据表 7.1.1-5，有 616126 类实质不同的函数 $`f(x_1, x_2, x_3,x_4, x_5)`$ 。如今计算机的速度已经快到足以使这个数字不再令人生畏，所以在我写这一节时，决定考察 5 个变量的全部布尔函数的 C(f)。幸亏运气好，获得了完整的结果，得出表 2 所示的统计数字。

对于这个计算，算法 L 及其变形不再是处理 $`2^{31}`$ 个正规真值表的集合，而是改为处理类的表示。给定一类函数中的任意一个函数，使用习题 7.2.1.2-20 的方法很容易产生那个类的全部函数，从而得到1000倍的加速。

自底向上的方法略有提高，例如，如果 C(f)=r-2，它可以推出 $`f(x_1\wedge x_2,x_1 \vee x_2, x_3,x_4, x_5)`$ 的代价小于等于 r。在求出代价为 10 的所有类之后，自顶向下和自底向上方法能求得除 7 个类函数以外的所有函数的长度小于等于 11 的链。然后开始费时的计算部分，其间大约产生 5300 万条 n=5 和 r=11 的特殊链；

每条这样的链都产生 $`5^{11} = 48 828 125`$ 个函数，其中某些函数可望归入剩余的 7 种神秘的类。但是，在那些类中仅有 6 类具有 11 步解。单独残存的类是唯一的 C(f)=12 的类，它的真值表的十六进制表示为 169ae443，而且它也有 L(f)=12。

图10(略) 显示了所产生的对称函数结构，其中某些函数出奇的精彩，某些函数简单的精彩，某些函数则简单的出奇。顺便指出，表 2 显示了所有深度小于等于 4 的 5 变量函数，但维试图使在图 10 中已经构成的深度达到最小。

最终，所有这些对称函数能够在不增加代价的情况下用最小存储求值。没有熟知的简单理由。

__表 2__ 具有给定复杂性的 5 变量函数的数目
C(f)| 类 | 函数 | L(f) | 类 | 函数 | D(f) | 类 | 函数
|--:|--:|--:|--:|--:|--:|--:|--:|--:|
0 | 2 | 12 | 0 | 2 | 12 | 0 | 2 | 12
1 | 2 | 100 | 1 | 2 | 100 | 1 | 2 | 100
2 | 5 | 1 140 | 2 | 5 | 1 140 | 2 | 17 | 5 350
3 | 20 | 11 570 | 3 | 20 | 11 570 | 3 | 1 789 | 6 702 242
4 | 93 | 109 826 | 4 | 93 | 109 826 | 4 | 614 316 | 4 288 259 592
5 | 389 | 995240 | 5 | 366 | 936 440 | 5 | 0 | 0
6 | 1 988 | 8 430 800 | 6 | 1 730 | 7 236 880 | 6 | 0 | 0
7 | 11 382 | 63 401 728 | 7 | 8 782 | 47 739 088 | 7 | 0 | 0
8 | 60 713 | 383 877 392 | 8 | 40 297 | 250 674 320 | 8 | 0 | 0
9 | 221 541 | 1 519 125 536 | 9 | 141 433 | 955 812 256 | 9 | 0 | 0
10 | 293 455 | 2 123 645 248 | 10 | 273 277 | 1 945 383 936 | 10 | 0 | 0
11 | 26 535 | 195 366 784 | 11 | 145 707 | 1 055 912 608 | 11 | 0 | 0
12 | 1 | 1 920 | 12 | 4 423 | 31 149 120 | 12 | 0 | 0


__多路输出__
我们时常需要对同样的输入值 $`x_1,\cdots,x_n`$ 求多个不同的布尔函数 $`f_1(x_1,\cdots,x_n)`$， $`f_m(x_1,\cdots,x_n)`$ 的值；还句话说，我们时常需要求一个多位函数 y=f(x) 的值，其中 $`y = f_1,\cdots,f_m$ 是长度为 m 的二进制向量，$`x = x_1,\cdots,x_n$ 是长度为 n 的二进制向量。所幸，计算分量值 $`f_j(x_1,\cdots,x_n)`$ 时涉及的大量工作同求其他分量值 $`f_k(x_1,\cdots,x_n`)$  所需的运算可能是共同的。

令 $`C(f)=C(f_1,\cdots,f_m`)$ 是计算所有非平凡函数 $`f_j`$ 的最短布尔链长度。更确切的说，布尔链 $`(x_{n+1},\cdots,x_{n+r})`$ 应具有这样的性质：对于 $`1 \leq j \leq m`$，以及对于满足 $`0 \leq l(j) \leq n+r`$ 的某些 l(j)，或者有 $`f_j(x_1,\cdots,x_n)=x_{l(j)}`$，或者有 $`f_j(x_1,\cdots,x_n)=\overline x_{l(j)}`$，其中 $`x_0=0`$。显然 $`C(f) \leq C(f_1) + \cdots + C(f_m)`$，但是我们可以做的更好。
