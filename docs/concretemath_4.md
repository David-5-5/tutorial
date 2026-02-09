顺便说一下，有一个记忆技巧可以帮助你记住哪些情况用地板，哪些情况用天花板：半开区间如果包含左端点但不包含右端点（比如 $0\le\theta < 1$），比包含右端点但不包含左端点的区间稍微多一些；而地板比天花板稍微多一些。因此，根据墨菲定律，正确的规则与我们预期的恰恰相反——对于 $[\alpha\cdots \beta)$，用 $ceil$；而对于 $(\alpha\cdots \beta)$，用 $floor$。

类似分析表明，闭区间 $[\alpha\cdots \beta]$ 恰好包含 $\lfloor\beta\rfloor−\lceil\alpha\rceil+1$ 个整数，而开区间 $(\alpha\cdots \beta)$ 包含 $\lfloor\beta\rfloor−\lceil\alpha\rceil-1$；但我们对后者施加了额外的限制 $\alpha\ne\beta$，以避免该公式因声称空区间 $(\alpha\cdots \alpha)$ 总共包含 −1 个整数而令人尴尬。总而言之，我们推导出了以下事实：
```math
\begin{aligned}
区间 &\qquad 包含的整数 &\qquad 限制 \\
[\alpha\cdots \beta] &\qquad \lfloor\beta\rfloor−\lceil\alpha\rceil+1 &\qquad \alpha\le \beta, \\
[\alpha\cdots \beta) &\qquad \lfloor\beta\rfloor−\lceil\alpha\rceil &\qquad \alpha\le \beta, \\
(\alpha\cdots \beta] &\qquad \lfloor\beta\rfloor−\lceil\alpha\rceil &\qquad \alpha\le \beta \\
(\alpha\cdots \beta) &\qquad \lfloor\beta\rfloor−\lceil\alpha\rceil-1 &\qquad \alpha< \beta     \tag{3.12}
\end{aligned}
```

现在，我们遇到了一个无法拒绝的问题。具体数学俱乐部拥有一家赌场（仅限购买本书的读者开放），赌场里有一台轮盘，共有一千个槽位，编号从 $1$ 到 $1000$。如果某次旋转出现的数字 $n$ 能被其立方根的整数部分整除，也就是说，如果
```math
\lfloor\sqrt[3]{n}\rfloor \backslash n,
```

那么，这就算赢了，庄家付给我们 $5$ 美元；否则，就算输了，我们必须付 $1$ 美元。（符号 $a\backslash b$，读作“$a$ 整除 $b$”，表示 $b$ 是 $a$ 的整数倍；第4章将仔细研究这种关系。）如果我们玩这个游戏，能指望赚钱吗？

我们可以计算平均赢利，也就是每次游戏我们能赢（或输）的金额，首先统计一下赢家的数量 $W$ 和输家的数量 $L = 1000 − W$。如果在 $1000$ 次游戏中每个数字都出现一次，我们赢 $5W$ 美元，输 $L$ 美元，那么平均赢利将是
```math
\frac{5W - L}{1000} = \frac{5W - (1000 - W)}{1000} = \frac{6W - 1000}{1000}
```

如果有 $167$ 名或更多获胜者，我们占优势；否则，优势在庄家。

我们如何统计从 $1$ 到 $1000$ 之间的获胜者数量呢？不难发现其中的规律。从 $1$ 到 $2^3 − 1 = 7$ 的所有数字都是获胜者，因为对于每个数字，$\lfloor\sqrt[3]{n}\rfloor = 1$ 都成立。在 $2^3 = 8$ 到 $3^3 − 1 = 26$ 这些数字中，只有偶数才是获胜者。而在 $3^3 = 27$ 到 $4^3 − 1 = 63$ 之间，只有能被 $3$ 整除的数字才是获胜者。以此类推。

若运用第 2 章的求和技巧，并借助艾弗森约定（逻辑命题的取值为 0 或 1），我们便可对整套构造进行系统的分析：
```math
\begin{aligned}
W &= \sum_{n=1}^{1000} [n\ is\ a\ winner] \\
  &= \sum_{1\le n\le 1000} [\lfloor\sqrt[3]{n}\rfloor \backslash n] \\
  &= \sum_{k, m}[k=\lfloor\sqrt[3]{n}][k\backslash][1\le n\le 1000] \\
  &= 1 + \sum_{k, m}[k^3\le km<(k+1)^3][1\le k\le 10] \\
  &= 1 + \sum_{k, m}[m\in [k^2\cdots (k+1)^3/k]][1\le k\le 10] \\
  &= 1 + \sum_{1\le k\le 10}(\lceil k^2+3k+3+1/k\rceil - \lceil k^2\rceil) \\
  &= 1 + \sum_{1\le k\le 10}{3k+4} = 1 + \frac{7 + 31}{2}\cdot 9 = 172
\end{aligned}
```

这一推导值得仔细研究。请注意，第6行使用了我们公式（3.12）来计算半开区间中的整数个数。唯一“棘手”的步骤是第 3 行与第 4 行之间作出的决定：将 $n=1000$ 视作一种特殊情况。（当 $k=10$ 时，不等式 $k^3\le n＜(k+1)^3$ 与 $1\le n\le 1000$ 难以直接合并。）一般来说，边界条件往往是处理过程中最为关键的部分。

底线表明，$W=172$ ；因此，我们每局平均赢利的计算公式简化为：$(6.172-1000)/1000$ 美元，即 $3.2$ 美分。如果我们每局下注 $1$ 美元，共下 $100$ 局，那么预计可多赚约 $3.20$ 美元。（当然，庄家可能对某些数字进行了更均匀的设置。）

我们刚刚解决的赌场问题，其实是对一个更为平淡无奇的问题——在 $1\le n\le 1000$ 之间，有多少个整数满足关系 $\lfloor\sqrt[3]{n}\rceil\backslash n$？——的一种包装升级版。从数学角度来看，这两个问题本质上是相同的。但有时候，对问题进行适当包装反而是个好主意。这样一来，我们可以使用更多专业术语（比如“赢家”和“输家”），这有助于我们更深入地理解问题的本质。

让我们来探讨一下一般情况。假设我们将 $1000$ 改为 $1000000$，或者改为更大的数字 $N$。（我们假定赌场有关系，能够获得一个更大的转盘。）那么，现在有多少位赢家呢？

同样的论点同样适用，但我们需要更谨慎地处理k的最大值，为方便起见，我们可以将其称为 $K$：
```math
k = \lfloor\sqrt[3]{n}\rceil.
```

此前 K 为$10$。一般 $N$ 的获奖者总数为：
```math
\begin{aligned}
W &= \sum_{1\le k< K}(3k+4) + \sum_m[K^3\le Km\le N]  \\
  &= \frac{1}{2}(7+3K+1)(K-1) + \sum_m[m\in [k^2..N/K]] \\
  &= \frac{3}{2}k^2 + \frac{5}{2}K - 4 + \sum_m[m\in [k^2..N/K]].
\end{aligned}
```

我们知道，剩余的和为 $\lfloor N/K\rfloor - \lceil k^2\rceil + 1= \lfloor N/K\rfloor - k^2 + 1$，因此该公式成立。
```math
W = \lfloor N/K\rfloor + \frac{1}{2}K^2 + \frac{5}{2}K - 3, K=\lfloor \sqrt[3]{N}\rfloor \tag{3.13}
```

给出了尺寸为N的轮子的一般答案。

该公式前两项约为 $N^{2/3}+\frac{1}{2}N^{2/3} =\frac{3}{2}N^{2/3}$，而其他各项相比之下要小得多，尤其是在 $N$ 较大时。在第9章中，我们将学习如何推导出类似这样的表达式。
```math
W = \frac{3}{2}N^{2/3} + O(N^{1/3})
```

其中，$O(N^{1/3})$ 表示一个量，其值不超过常数与 $N^{1/3}$ 的乘积。无论这个常数是多少，我们都知道它与 $N$ 无关；因此，对于较大的 $N$ 而言，$O$ 项对 $W$ 的贡献将远小于 $N^{2/3}$。例如，下表展示了 $N^{2/3}$ 与 W 的接近程度：
| N | $\frac{3}{2}N^{2/3}$ | W | 误差 |
| --: | --: | --: | --: |
1,000 | 150 | 172 | 12.79
10,000 | 696.2 | 746 | 6.67
100,000 | 3231.7 | 3343 | 3.331
1,000,000 | 15000.0 | 15247 | 1.620
10,000,000 | 69623.9 | 90158 | 0.761
100,000,000 | 323165.2 | 344322 | 0.357
1,000,000,000 | 1500000 | 1502496 | 0.166

这是一个相当不错的近似值。

近似公式之所以实用，是因为它们比包含下取整、上取整的公式更简洁。然而，精确结果往往也很重要，尤其对于实际应用中经常出现的较小 $N$ 值而言。举个例子：赌场老板可能会错误地认为，当 $N = 1000$ 时，赢家只有 $\frac{3}{2}N^{2/3} = 150$ 人（这种情况下，庄家每注可赚取 $10$ 美分的优势）。

本节的最后一个应用，我们来看所谓的谱（spectrum）。我们将实数 x 的谱定义为整数构成的无限多重集，
```math
Spec(\alpha) = \{\lfloor\alpha\rfloor, \lfloor 2\alpha\rfloor, \lfloor 3\alpha\rfloor, \cdots \}
```

多重集与集合类似，但允许元素重复出现。例如，$1/2$​ 的谱的前几项为 $\{0,1,1,2,2,3,3,\cdots\}$。

不难证明没有两个不同的实数会拥有相同的谱—— 也就是说，$\alpha\ne\beta$ 当且仅当 $Spec(\alpha)\ne Spec(\beta)$。证明如下：不妨设 $\alpha<\beta$，则存在正整数 $m$ 使得 $m(\beta−\alpha)\ge 1$。（事实上，任意满足 $m\ge \lceil\beta−\alpha\rceil$ 的 $m$ 都可以；不过我们也不必时时刻刻都炫耀自己对上下取整函数的掌握。）于是有 $m\beta−m\alpha\ge 1$，进而 $\lfloor m\beta\rfloor>\lfloor m\alpha\rfloor$。因此， $Spec(\beta)$ 中 $\le \lfloor m\alpha\rfloor$ 的元素个数少于 $m$ 个，而 $Spec(\alpha)$ 中这样的元素至少有 $m$ 个。

谱 (Spectra) 具有许多优美的性质。例如，我们来考察如下两个多重集：
```math
Spec(\sqrt{2}) = \{1,2,4,5,7,8,9,11,12,14 \} \\
Spec(2 + \sqrt{2}) = \{3,6,10,13,17,20,23,27,30,34 \}
```

用普通计算器就能轻松算出 $Spec(\sqrt{2}​)$，并且由式 (3.6) 可知，$Spec(2+\sqrt{2}​)$ 的第 $n$ 项恰好比 $Spec(\sqrt{2}​)$ 的第 $n$ 项大 $2n$。进一步观察会发现，这两个谱之间还存在一种更为惊人的关联：一个谱中缺失的数，总会出现在另一个谱中，且没有任何数会同时出现在两个谱里！这一结论是成立的：全体正整数恰好是 $Spec(\sqrt{2}​)$ 与 $Spec(2+\sqrt{2}​)$​) 的不相交并。我们称这样的一对谱构成了正整数集的一个*划分*。

为证明这一断言，我们来统计：$Spec(\sqrt{2}​)$ 中不大于 $n$ 的元素个数，以及 $Spec(2+\sqrt{2}​)$ 中不大于 $n$ 的元素个数。若对每个正整数 $n$，这两个数之和恰好等于 $n$，则这两个谱确实构成了正整数集的划分。

设正实数 $\alpha>0$，则 $Spec(\sqrt{\alpha}​)$ 中不大于 n 的元素个数为:
```math
\begin{aligned}
N(\alpha, n) &= \sum_{k>0}[\lfloor k\alpha\rfloor\le n]  \\
             &= \sum_{k>0}[\lfloor k\alpha\rfloor< n+1]  \\
             &= \sum_{k>0}[k\alpha< n+1]  \\
             &= \sum_k[0<k<(n+1)/\alpha]  \\
             &= \lceil(n+1)/\alpha\rceil - 1  \tag{3.14}
\end{aligned}
```

这个推导有两个特别值得关注的点。首先，它使用了该定律
```math
m\le n \iff m < n+1, integers\ m\ and\ n \tag{3.15}
```

将 $\le$ 改为 $<$,以便能够通过(3.7)去掉括号。另外，这一点更微妙，它对范围 $k > 0$ 求和，而不是对 $k\ge 1$ 求和，因为 $(n + 1)/\alpha$ 对于某些 $n$ 和 $\alpha$ 可能小于 $1$。如果我们试图应用(3.12)来确定 $[1..(n + 1)/\alpha]$ 中的整数个数，而不是 $(0..(n + 1)/\alpha)$ 中的整数个数，我们本会得到正确的答案；但我们的推导过程会有问题，因为适用条件并未满足。

我们有了一个公式 $N(\alpha, n)$。现在，我们可以通过检验 $N(\sqrt{2}, n)$ + $N(2+\sqrt{2}, n)$ 是否等于 $n$ 来判断 $Spec(\sqrt{2}​)$ 和 $Spec(2+\sqrt{2}​)$ 是否将正整数进行了划分，其中 $n$ 是所有大于 $0$ 的整数，使用 (3.14):
```math
\lceil\frac{n+1}{\sqrt{2}}\rceil -1 + \lceil\frac{n+1}{2+\sqrt{2}}\rceil -1 = n \\
\iff \lfloor\frac{n+1}{\sqrt{2}}\rfloor + \lfloor\frac{n+1}{2+\sqrt{2}}\rfloor = n, \qquad by (3.2)\\
\iff frac{n+1}{\sqrt{2}} - \{\frac{n+1}{\sqrt{2}}\}  + frac{n+1}{2+\sqrt{2}} - \{\frac{n+1}{2+\sqrt{2}}\} = n, \qquad by (3.8)
```

现在一切都变得简单了，因为有了这个简洁的标识。
```math
frac{1}{\sqrt{2}} + \frac{1}{2 + \sqrt{2}} = 1,
```

我们的条件归结为测试是否
```math
\{\frac{n+1}{\sqrt{2}}\}  +  \{\frac{n+1}{2+\sqrt{2}}\} = 1,
```

对于所有 $n> 0$，我们赢了，因为这两个非整数的分数部分相加等于整数 $n + 1$。这便是一个划分。

## 3.3 FLOOR/CEILING RECURRENCES
地板和天花板为研究增添了有趣的新维度关于递归关系。让我们首先看看递归
```math
\begin{aligned}
K_0 &= 1; \\
K_{n+1} &= 1 + min(2K_{\lfloor n/2\rfloor}, 3K_{\lfloor n/3\rfloor}), for\ n\ge 0. \tag{3.14}
\end{aligned}
```

因此，例如，$K_1$ 是 $1 + min(2K_0, 3K_0) = 3$；该序列以 $1, 3, 3, 4, 7, 7, 7, 9, 9, 10, 13,\cdots$ 开始。 。本书作者之一谦虚地决定将这些称为克努斯数。

习题 25 要求证明或证伪：对所有 $n\ge 0$，有 $K_n​\ge n$。上面列出的前几项 $K$ 确实满足该不等式，因此这个命题很有可能在一般情形下也成立。我们尝试用数学归纳法证明：归纳基础：$n=0$ 的情形可直接由定义递推式得出。归纳步骤：假设不等式对不超过某个固定非负整数 $n$ 的所有值都成立，我们来证明 $K_{n+1}​\ge {n+1}$。由递推式可知：$K_{n+1}= 1 + min(2K_{\lfloor n/2\rfloor}, 3K_{\lfloor n/3\rfloor})$。归纳假设告诉我们：$2K_{\lfloor n/2\rfloor}​\ge 2\lfloor n/2\rfloor,3K_{\lfloor n/3\rfloor}​\ge 3\lfloor n/3\rfloor$，然而，$2\lfloor n/2\rfloor$ 最小可以取到 $n−1$，$3\lfloor n/3\rfloor$ 最小可以取到 $n−2$。由归纳假设我们最多只能推出：$K_{n+1}\ge 1+(n−2)$ 这与需要证明的 $K_{n+1​}\ge n+1$ 相差甚远。

现在我们有理由对 $K_n​\ge n$ 这一命题的正确性产生怀疑，因此不妨尝试证伪它。如果我们能找到某个正整数 $n$，使得 $2K_{\lfloor n/2\rfloor}​<n$ 或 $3K_{\lfloor n/3\rfloor}​<n$ 成立，换言之，只要找到满足
```math
K_{\lfloor n/2\rfloor}​<n/2\ or\ K_{\lfloor n/3\rfloor} < n/3,
```

那么就会有 $K_{n+1​}<n+1$。这是否真的可能发生？我们最好先不在这里揭晓答案，否则会破坏习题 25 的解题乐趣。

包含下取整与 / 或上取整的递推关系在计算机科学中十分常见，因为基于分治法（divide and conquer） 这一重要技术的算法，通常会把规模为 $n$ 的问题，归约为若干个规模是 $n$ 的分数倍、且规模为整数的同类子问题来求解。例如，当 $n>1$ 时，对 $n$ 条记录进行排序的一种方法是：将它们分成大小近似相等的两部分，一部分规模为 $\lfloor n/2\rfloor$，另一部分规模为 $\lceil n/2\rceil$。顺便提一句，请注意：
```math
n = \lfloor n/2\rfloor + \lceil n/2\rceil; \tag{3.17}
```

这个公式其实非常实用，还经常派上用场。当两部分各自完成排序后（采用相同的方法递归实现），我们只需再进行至多 $n−1$ 次比较，就能将这些记录合并为最终的有序序列。因此，整个排序过程执行的总比较次数至多为 $f(n)$，其中
```math
\begin{aligned}
f(0) &= 0; \\
f(n) &= f(\lfloor n/2\rfloor) + f(\lceil n/2\rceil), for\ n> 1. \tag{3.18}
\end{aligned}
```
该递推式的解法见习题 34

第 1 章的约瑟夫问题也存在一个相似的递推关系，该递推关系可表示为如下形式：
```math
\begin{aligned}
J(1) &= 1; \\
J(n) &= 2J(\lfloor n/2\rfloor) - (-1)^n, for\ n> 1.
\end{aligned}
```

如今我们掌握的解题工具，已经比第 1 章时丰富多了；因此我们来研究更贴合原题原型的约瑟夫问题 —— 此次是每第三个人被淘汰，而非原先的每第二个人。若我们将第 1 章中奏效的方法套用到这个更复杂的问题上，最终会得到形如这样的递推关系：
```math
J_3(n) = \lceil\frac{3}{2}J_3(\lfloor \frac{2}{3}n\rfloor)+a_n \rceil \mod n+1
```

其中 $mod$ 为我们即将展开研究的模函数；参数 $a$ 的取值为 $−2, +1$ 或 $1/2$，具体取决于 $n\mod 3$ 的结果是 0、1 还是 2。但这个递推式过于复杂，根本无从继续深究。

研究约瑟夫问题还有另一种方法，能构建出远更简洁的分析框架。每当有一个人被跳过时，我们就为其分配一个新编号：$1$ 号和 $2$ 号被重新编号为 $n+1$ 号和 $n+2$ 号，随后 $3$ 号被淘汰；$4$ 号和 $5$ 号被重新编号为 $n+3$ 号和 $n+4$ 号，随后 $6$ 号被淘汰；$\cdots 3k+1$ 号和 $3k+2$ 号被重新编号为 $n+2k+1$ 号和 $n+2k+2$ 号，随后 $3k+3$ 号被淘汰；$\cdots$ 最终 $3n$ 号要么被淘汰，要么留至最后存活。 例如，当 $n=10$ 时，各位置的编号对应关系如下：
1 | 2| 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10
| --: | --: | --: | --: | --: | --: | --: | --: | --: | --: |
11 | 12 |  | 13 | 14 |  | 15 | 16 |  | 17
18 | |  | 19 | 20 |  |  | 21 |  | 22
 | |  | 23 | 24 |  |  |  |  | 25
 | |  | 26 |  |  |  |  |  | 27
 | |  | 28 |  |  |  |  |  |
 | |  | 29 |  |  |  |  |  |
 | |  | 30 |  |  |  |  |  |
第 $k$ 个被淘汰的人，最终被分配的新编号为 $3k$。因此，只要我们能求出新编号为 $3n$ 的人对应的原始编号，就能确定最终的存活者。

若新编号 $N>n$，则新编号为 $N$ 的人必然对应一个原始编号，我们可按如下方法求出该原始编号：新编号满足 $N=n+2k+1$ 或 $N=n+2k+2$，因此 $k=\lfloor(N−n−1)/2\rfloor$；对应的原始编号则分别为 $3k+1$ 和 $3k+2$。换言之，原始编号可化简为 $3k+(N−n−2k)=k+N−n$。因此，我们可按如下方式计算每 3 人淘汰的约瑟夫问题中存活者的编号 $J_3​(n)$：
```math
N := 3n; \\
while\ N>n do\ N:=\lfloor\frac{N-n-1}{2}\rfloor + N - n; \\
J_3(n) := n.
```
这并非 $J_3​(n)$ 的闭式解，甚至都算不上一个递推式。但至少它告诉我们，当 $n$ 很大时，如何高效地计算出答案。

所幸，若引入变量 $D=3n+1−N$ 替代 $N$，我们就能找到简化该算法的方法。（这一记法的变更，等价于将编号从 $3n$ 倒序分配至 $1$，而非原先的从 $1$ 正序分配至 $3n$；这有点类似倒计时的方式。）如此一来，原本针对 $N$ 的复杂赋值操作，就简化为：
```math
\begin{aligned}
D :&= 3n + 1 - (\lfloor\frac{(3n+1-D)-n-1}{2}\rfloor + (3n+1-D) - n) \\
   &= n + D - \lfloor\frac{2n-D}{2}\rfloor = D - \lfloor\frac{-D}{2}\rfloor = D + \lceil\frac{D}{2}\rceil = \lceil\frac{3}{2}D\rceil
\end{aligned}
```
由此，我们可将该算法重写如下：
```math
D := 1; \\
while\ D\le 2n do\ D:=\lfloor\frac{3}{2}D\rfloor; \\
J_3(n) := 3n + 1 - D.
```

这样的形式就简洁多了，因为 $n$ 在计算中的参与方式变得极为简洁。事实上，我们可通过完全相同的推导思路证明：当每第 $q$ 个人被淘汰时，存活者的编号 $J_q​(n)$ 可按如下方法计算：
```math
\begin{aligned}
&D := 1; \\
&while\ D\le (q-1)n do\ D:=\lfloor\frac{q}{q-1}D\rfloor; \\
&J_q(n) := qn + 1 - D. \tag{3.19}
\end{aligned} 
```

对于我们熟知的 $q=2$ 的情形，结合约瑟夫问题的经典形式 $n=2^m+l$，代入上述通用方法后可得 $D$ 最终取值为 $2^m+l$；因此推导得：$J_2​(n)=2(2^m+l)+1−(2^{m+l})=2l+1$。

式 (3.19) 中的计算法则可求出一个整数序列，该序列亦可由下述递推式定义：
极简批注版（书页标注）
```math
\begin{aligned}
&D_0^{(q)} = 1; \\
&D_n^{(q)} :=  \lceil\frac{q}{q-1}D_{n-1}^{(q)}\rceil for\ n > 0 \tag{3.20}
\end{aligned} 
```

除 $q=2$ 的情形外，这些数似乎无法以简洁的方式与任何常见函数建立关联；因此这类数大概率不存在简洁的闭式解。但倘若我们愿意将序列 $D_n^{(q)}$ 视作「已知序列」，那么广义约瑟夫问题的解就极易描述：存活者的编号 $J_q​(n)$ 满足 $J_q​(n)=qn+1−D_k^{(q)}$ ​其中 $k$ 为满足 $D_k^{(q)}​>(q−1)n$ 的最小正整数。


## 3.4 MOD: THE BINARY OPERATION
当 $m$ 和 $n$ 均为正整数时，$n$ 除以 $m$ 的商为下取整 $\lfloor n/m\rfloor$ 。为该除法的余数设定一套简洁的记号同样十分实用，我们将其记为 $n\mod m$（$n$ 对 $m$ 取余）。
```math
n = m
\begin{matrix}
\underbrace{\lfloor n/m\rfloor} \\
除数
\end{matrix}  + 
\begin{matrix}
\underbrace{n \mod m} \\
余数
\end{matrix} 
```

由此可知，我们可以将 $n\mod m$ 表示为：$n−m\lfloor n/m\rfloor$ 我们可以把这一定义推广到负整数，事实上，还能推广到任意实数。
```math
x \mod y = x - y\lfloor x/y\rfloor, for\ y\ne 0 \tag{3.21}
```

这就将 $mod$ 定义为一种二元运算，就像加法、减法同样是二元运算一样。数学家们早已非正式地以这种方式使用 $mod$，比如对各种量取模 $10$、模 $2\pi$ 等等；但直到近二十年，它才被正式地确立并广泛采用。古老的概念，崭新的记号。

当 $x, y$ 为正实数时，我们可以很直观地理解 $x\mod y$ 的含义：想象一个周长为 $y$ 的圆周，圆周上的点对应区间 $[0,y)$ 内的全体实数。若从 $0$ 出发，沿圆周行进长度为 $x$ 的距离，最终停留的位置就是 $x\mod y$。（而行进过程中经过 $0$ 点的次数，恰好是 $\lfloor x/y\rfloor$。）

当 $x$ 或 $y$ 为负数时，我们必须仔细审视其定义，才能确切理解它的含义。下面给出一些整数值的示例：
```math
\begin{aligned}
5 \mod 3 &= 5 - 3\lfloor 5/3\rfloor = 2; \\
5 \mod -3 &= 5 - (-3)\lfloor 5/(-3)\rfloor = -1; \\
-5 \mod 3 &= -5 - 3\lfloor -5/3\rfloor = 1; \\
-5 \mod -3 &= -5 - (-3)\lfloor -5/(-3)\rfloor = -2;
\end{aligned} 
```

$mod$ 后面的数称为模数；至于 $mod$ 前面的数该如何命名，目前尚无定论。在实际应用中，模数通常取正值，但即便模数为负，该定义依然完全成立。无论模数正负，$x\mod y$ 的结果始终介于 0 与模数之间：
```math
0\le x\mod y <y, for\ y>0; \\
0\ge x\mod t >y, for\ y<0;
```

那当 $y=0$ 时又该如何？为避免除零错误，定义 (3.21) 并未对这一情形给出定义；但为了体系完备，我们可以补充定义：
```math
x \mod 0 = x. \tag{3.22}
```

这一约定保留了核心性质：$x\mod y$ 与 $x$ 之间始终相差 $y$ 的某个整数倍。（表面上看，更自然的做法是让该函数在 $0$ 处连续，即通过定义 $x\mod 0= \lim_{y\to 0}​x \mod y=0$ 来实现。但我们将在第 4 章看到，这样的定义实用性会大打折扣。连续性并非取模运算的核心属性。）

我们已经见过一种伪装的模运算特殊情况，即当我们用整数部分和小数部分来表示 $x$ 时，$ x = \lfloor x\rfloor + \lceil x\rceil$。小数部分也可以写成 $x\mod 1$，因为我们有:
```math
x = \lfloor x\rfloor + x \mod 1.
```
请注意，此公式中不需要括号；我们采用取模运算符的优先级高于加法或减法。

$floor$ 函数已被用于定义模，而 $ceiling$ 函数却没有得到同等对待。我们或许可以使用 $ceiling$ 来定义一个类似于模的函数，比如
```math
x\ mumble\ y = y\lceil x/y\rceil -x.
```

在我们的圆圈类比中，这代表了旅行者在行进了一段距离 $x$ 后，需要继续前进的距离，才能回到起点 $0$。当然，我们需要一个比 $mumble$ 更好的名字。如果应用足够多，一个合适的名字很可能就会浮现出来。

分配律是模运算最重要的代数性质：我们有:
```math
c(x\mod y) = (cx) \mod (cy) \tag{3.23}
```

对于所有实数 $c, x$ 和 $y$。（喜欢模运算的绑定强度低于乘法运算的人，也可以从右侧去掉括号。）根据定义（3.21），很容易证明这一法则，因为
```math
c(x\mod y) = c(x-y\lfloor x/y\rfloor) = cx -cy\lfloor cx/cy\rfloor = cx\mod cy,
```

如果 $cy\ne 0$；而零模的情况则显而易见地成立。我们用 $\pm 5$ 和 $\pm 3$ 的四个例子两次说明了这一规律，其中 $c = −1$。像 (3.23) 这样的恒等式令人安心，因为它使我们有理由相信 $mod$ 的定义并未出现不当之处。

在本节的其余部分，我们将考虑一个应用，其中 $mod$ 虽然并不起核心作用，却派上了用场。这个问题经常出现在各种情境中：我们希望将 $n$ 个事物尽可能均匀地划分成 $m$组。

例如，假设我们有 $n$ 行短文本，希望将其排布在 $m$ 列中。出于美观考虑，我们要求各列按长度递减（严格来说是非递增）的顺序排列；同时各列长度应大致相等——任意两列的行数之差不得超过 $1$ 行。因此，若将 $37$ 行文本分为 $5$ 列，我们会更倾向于采用右侧的排布方式：

此外，我们希望按列分配文本行：先确定第一列的行数，再依次处理第二列、第三列，依此类推 —— 因为这符合人们的阅读习惯。若按行逐行分配，虽然每列的总行数是正确的，但文本行的先后顺序会被打乱。（我们会得到与右侧排布行数一致的结果，但第一列会是第 $1, 6, 11, \cdots, 36$ 行，而非我们期望的第 $1, 2, 3, \cdots, 8$ 行。）

逐行分配的方案虽不可行，却能帮我们确定每列应分配的行数。若 $n$ 不是 $m$ 的整数倍，通过逐行分配的思路可以清晰看出：较长的列每列应包含 $\lceil n/m\rceil$ 行，较短的列每列应包含 $\lfloor n/m\rfloor$ 行。其中长列的数量恰好为 $n\mod m$

我们来推广术语，用 $things$ 和 $groups$ 来代替 $lines$ 和 $columns$ 进行讨论。我们刚刚已经确定，第一组应当包含 $\lfloor n/m\rfloor$ 个 $things$；因此下面这种顺序分配方案应该是可行的：将 $n$ 个 $things$ 分配到 $m$ 个 $groups$ 中（$m>0$），先把 $\lceil n/m\rceil$ 个 $things$ 放入一个 $group$，然后用同样的方法递归地，把剩余的 $n'=n−\lfloor n/m\rfloor$ 个 $things$ 分配到 $m'=m−1$ 个额外的 $groups$ 中。

例如，当 n=314、m=6 时，分配过程如下所示：
| remaining things | remaining groups | $\lceil things/groups\rceil$
| --: | --: | --: |
314 | 6 | 53
261 | 5 | 53
208 | 6 | 52
156 | 6 | 52
104 | 6 | 52
52 | 6 | 52

该方法是有效的。即便除数在不断变化，我们得到的各组（groups）大小仍大致相等。

一般情形下，我们可设 $n=qm+r$，其中 $q=\lfloor n/m\rfloor$，$r=n\mod m$。若 $r=0$，过程十分简单：我们把 $\lfloor n/m\rfloor=q$ 个物品放入第一组，再用 $n'=n−q$ 代替原来的 $n$，此时剩余 $n'=qm'$ 个物品，可分配给剩下的 $m'=m−1$ 个组。若 $r>0$，我们把 $\lceil n/m\rceil=q+1$ 个物品放入第一组，并用 $n'=n−q−1$ 代替原来的 $n$，此时剩余 $n'=qm'+r−1$ 个物品供后续分组使用。新的余数为 $r'=r−1$，但 $q$ 保持不变。由此即可推出：最终会有 $r$ 个组各含 $q+1$ 个物品，紧接着是 $m−$r 个组各含 $q$ 个物品。

第 $k$ 个 $group$ 里有多少个 $things$？我们希望找到一个公式：当 $k\le n\mod m$ 时，结果为 $\lceil n/m\rceil$；其余情况则为 $\lfloor n/m\rfloor$。想要验证这一点并不困难。
```math
\lceil\frac{n-k+1}{m} \rceil
```

该式具备我们想要的性质，因为若按照上一段的写法令 $n=qm+r$（其中 $q=\lfloor n/m\rfloor$），原式可化简为：$q+\lceil (r−k+1​)/m\rceil$。 当 $1\le k\le m$ 且 $0\le r<m$ 时，有 $\lceil (r−k+1​)/m\rceil=[k\le r]$。由此我们可写出一个恒等式，它将 $n$ 划分为 $m$ 个尽可能相等、且按非递增顺序排列的部分:
```math
n = \lceil\frac{n}{m}\rceil + \lceil\frac{n-1}{m}\rceil + \cdots + \lceil\frac{n-m+1}{m}\rceil. \tag{3.24}
```
该恒等式对所有正整数 $m$ 以及任意整数 $n$（无论正、负或零）均成立。我们在式 (3.17) 中已经见过 $m=2$ 的情形，尽管当时的写法略有不同：$n=\lfloor 2n\rfloor + \lceil 2n\rceil​⌉$

如果我们希望各部分按非递减顺序排列，让较小的 $groups$ 出现在较大的 $groups$ 之前，只需沿用同样的推导方式，只是在第一组中放入 $\lfloor n/m\rfloor$ 个 $%$ 即可。这样我们便能推导出对应的恒等式：
```math
n = \lfloor\frac{n}{m}\rfloor + \lfloor\frac{n-1}{m}\rfloor + \cdots + \lfloor\frac{n-m+1}{m}\rfloor. \tag{3.25}
```

利用式 (3.4) 或习题 12 中的恒等式，即可在式 (3.25) 与式 (3.24) 之间相互转换。

现在，如果我们将 (3.25) 中的 $n$ 替换为 $\lfloor mx\rfloor$，并运用规则 (3.11) 消去嵌套在内层的 $floor$ 符号，就能得到一个对所有实数 $x$ 都成立的恒等式：
```math
\lfloor mx\rfloor = \lfloor x\rfloor + \lfloor x+\frac{1}{m}\rfloor + \cdots + \lfloor x+\frac{m-1}{m}\rfloor. \tag{3.26}
```

这一结论相当令人惊叹，因为下取整函数只是对实数的整数近似，但左侧这单次近似，竟然与右侧一长串近似值的总和完全相等。如果我们假设平均来看 $\lfloor x\rfloor \approx x-\frac{1}{2}$​，那么左侧大致等于 $mx-\frac{1}{2}$​；而右侧则近似为 $(x-\frac{1}{2}) + (x-\frac{1}{2}+\frac{1}{m})+ \cdots + (x-\frac{1}{2}+\frac{m-1}{m}) = x-\frac{1}{2}$；​这些粗略近似值的总和，最终竟然是精确等式！


## 3.5 FLOOR/CEILING SUMS
式 (3.26) 表明，至少对于一类包含"floor" $\lfloor\rfloor$ 的求和式，我们是可以求出闭式的。这样的求和式还有其他吗？当然有。处理这类问题的常用技巧是：通过引入一个新变量，消去 "floor" 或 "ceil" 符号。

例如，我们来看看能否求出这个和式的闭式：
```math
\sum_{0\le k<n} \lfloor\sqrt{k}\rfloor
```

求出其闭式。一种思路是引入变量 $m=\lfloor k\rfloor$；我们可以像处理轮盘赌问题时那样，“mechanically”（机械地）按部就班地操作：
```math
\begin{aligned}
\sum_{0\le k<n} \lfloor\sqrt{k}\rfloor &= \sum_{k,m\ge 0} m[k<n] [m=\lfloor\sqrt{k}\rfloor]                 \\
&= \sum_{k,m\ge 0} m[k<n][m\le \sqrt{k}<m+1] \\
&= \sum_{k,m\ge 0} m[k<n][m^2\le k<(m+1)^2] \\
&= \sum_{k,m\ge 0} m[m^2\le k<(m+1)^2\le n] \\
&+ \sum_{k,m\ge 0} m[m^2\le k<n<(m+1)^2] 
\end{aligned} 
```

边界条件依旧需要小心处理。我们先假设 $n=a^2$ 是一个完全平方数，此时第二个和式为 $0$，而第一个和式可以通过我们惯用的常规方法计算：
```math
\begin{aligned} 
\sum_{k,m\ge 0} & m[m^2\le k<(m+1)^2\le a^2] \\
& = \sum_{m\ge 0} m((m+1)^2-m^2) [(m+1)\le a] \\
& = \sum_{m\ge 0} m(2m+1) [m<a] \\
& = \sum_{m\ge 0} (2m^{\underline{2}}+3m^{\underline{1}})[m<a] \\
& = \sum_0^a (2m^{\underline{2}}+3m^{\underline{1}})\delta m\\
& = \frac{2}{3}a(a-1)(a-2) + \frac{3}{2}a(a-1) = \frac{1}{6}(4a+1)a(a-1).
\end{aligned} 
```

对于一般情形，我们可令 $a=\lfloor\sqrt{n}\rfloor$；此时只需补上满足 $a^2\le k< n$ 的项，这些项的值均为 $a$，因此它们的和为 $(n-a^2)a$。由此便得到了所求的closed form（闭式）：
```math
\sum_{0\le k<n} \lfloor\sqrt{k}\rfloor=na -\frac{1}{3}a^3 -\frac{1}{2}a^2-\frac{1}{6}a, a=\lfloor\sqrt{n}\rfloor \tag{3.27}
```

处理这类和式的另一种方法，是将形如 $\lfloor x\rfloor$ 的表达式替换为 $\sum_j​[1\le j\le x]$；当 $x\ge 0$ 时，这种替换是合法的。为方便起见，不妨设 $n=a^2$，下面演示该方法如何用于 square roots 下取整的求和：
```math
\begin{aligned} 
\sum_{0\le k<n} \lfloor\sqrt{k}\rfloor &=\sum_{j, k}[1\le j\le sqrt{k}][0\le k\le a^2] \\
&=\sum_{1\le j<a}\sum_k[j^2\le k< a^2] \\
&=\sum_{1\le j<a}(a^2-j^2) = a^3-\frac{1}{3}a(a+\frac{1}{2})(a+1)
\end{aligned}
```

这里再举一个变量替换导出变换和式的例子。1909 年前后，三位数学家 ——Bohl [34]、Sierpiński [326]、Weyl [368]—— 各自独立发现了一条著名定理：若 $\alpha$ 是无理数，则当 $n\to\infty$ 时，分数部分 $\{n\alpha\}$ 在区间 $(0,1)$ 上会呈高度均匀分布。该定理的一种表述方式是：
```math
\lim_{n\to\infty}\frac{1}{n} \sum_{0\le k<n}f(\{k\alpha\}) = \int_0^1f(x)dx \tag{3.28}
```

对所有无理数 $\alpha$，以及所有几乎处处连续的函数 $f$，该式均成立。例如，取 $f(x)=x$，即可求出 ${n\alpha}$ 的平均值；我们会得到 $\frac{1}{2}$​.（这正是我们直观预期的结果；但无论 $\alpha$ 是怎样的无理数，这个结论都能被严格证明成立，这一点依然十分美妙。）

Bohl、Sierpiński 和 Weyl 的这条定理，是通过用 *step functions* （阶梯函数）对 $f(x)$ 进行上下逼近来证明的；而阶梯函数是若干简单函数的线性组合。
```math
f_v(x) = [0\le x<v]
```

其中 $0\le v\le 1$。我们这里的目的并非证明这条定理，那是微积分教材的内容。但我们不妨通过考察特殊情形 $f(x)=f_v​(x)$ 下的表现，来探究它成立的核心原因。换句话说，我们来看看这个和式
需要我帮你把这个特殊情形下的和式完整写出来，并配上直观解释吗？
```math
\sum_{0\le k<n} [\{k\alpha\}<v]
```

当 $n$ 充分大、且 $x$ 为无理数时，我们来看看这个和式与 *理想* $nv$ 的逼近程度究竟如何。为此，我们定义差异 $D(\alpha, n)$ 为所有 $0\le v\le 1$ 中，总和的最大绝对值
```math
s(\alpha, n, v) = \sum_{0\le k<n} ([\{k\alpha\}<v] - v) \tag{3.29}
```

我们的目标是证明，与 $n$ 相比， $D(\alpha, n)$ 不会太大，方法是证明当 $\alpha$ 为无理数时， $|s(\alpha, n, v)|$ 总是相当小。

首先，我们可以将 $s(\alpha, n, v)$ 重写为更简单的形式，然后引入一个新的索引变量 $j$:
```math
\begin{aligned} 
\sum_{0\le k<n} ([\{k\alpha\}<v] - v) &= \sum_{0\le k<n}(\lfloor k\alpha\rfloor-\lfloor k\alpha-v\rfloor-v) \\
&= -nv + \sum_{0\le k<n}\sum_j[k\alpha-v<j\le k\alpha] \\
&= -nv + \sum_{0\le j<\lceil n\alpha\rceil}\sum_{k<n}[j\alpha^{-1}\le k<(j+v)\alpha^{-1}] 
\end{aligned}
```

如果运气好的话，我们可以在 $k$ 上进行求和。但我们应该引入一些新的变量，这样公式就不会那么乱了。不失一般性，我们可以假设 $0<\alpha < 1$；让我们写
```math
\begin{aligned} 
a &= \lfloor \alpha^{-1}\rfloor, & \alpha^{-1} = a + \alpha' \\
b &= \lceil v\alpha^{-1}\rceil, & v\alpha^{-1} = b - v' 
\end{aligned}
```

因此 $\alpha' = \{\alpha^{-1}\}$ 是 $\\alpha^{-1}$ 的小数部分，而 $v'$ 是 $v\alpha^{-1}$ 的模糊小数部分。

再次强调，边界条件是我们唯一的烦恼来源。目前，让我们先忽略限制条件 $k < n$，不带它来计算求和：
```math
\begin{aligned} 
\sum_k[k\in [j\alpha^{-1}..(j+v)\alpha^{-1}]] &= \lceil(j+v)(a+\alpha')\rceil - \lceil j(a+\alpha')\rceil \\
&= b + \lceil j\alpha'-v'\rceil - \lceil j\alpha'\rceil.
\end{aligned}
```

好的，这很简单；我们把它插上，然后开始使用：
```math
s(\alpha, n, v) = -nv + \lceil n\alpha\rceil b + \sum_{0\le j<\lceil n\alpha\rceil}(\lceil j\alpha'-v'\rceil - \lceil j\alpha'\rceil) - S   \tag{3.30}
```

其中 S 是对那些我们未能排除的 $k\ge n$ 情况所作的修正。量 $j\alpha'$ 永远不会是整数，因为 $\alpha$（从而 $\alpha'$）是无理数；而且 $j\alpha'-v'$  至多只有一个 $j$ 的值会是整数。因此我们可以把上取整项换成下取整项：
```math
s(\alpha, n, v) = -nv + \lceil n\alpha\rceil b + \sum_{0\le j<\lceil n\alpha\rceil}(\lceil j\alpha'\rceil - \lceil j\alpha'-v'\rceil) - S + \{0\ or\ 1\}.
```






