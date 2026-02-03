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

