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

