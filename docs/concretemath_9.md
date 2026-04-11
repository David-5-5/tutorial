# 9. Asymptotics 渐进线

精确答案固然很好——完全掌握一个结果总会让人感到十分满足。但有些时候，我们也需要近似方法。如果遇到一个求和式或递推式，其解（在我们所知范围内）没有闭式表达，我们仍然希望对答案有所了解，不必坚持非全即无。
而且即便我们已经有了闭式，认知也可能并不完整，因为我们未必知道如何把它和其他闭式进行比较。

例如，和式
$$
S_n = \sum_{k=0}^n \binom{3n}{k}
$$
显然没有闭式。但我们可以知道：
$$
S_n \sim 2\binom{3n}{n},\quad n\to\infty,
$$
我们称这个和式“渐近等价于” $2\dbinom{3n}{n}$。如果能得到更精细的信息会更好，比如
$$
S_n = \binom{3n}{n}\left( 2 - \frac{4}{n} + O\!\left( \frac{1}{n^2} \right) \right), \tag{9.1}
$$
这给出了“阶为 $1/n^2$ 的相对误差”。但即便如此，仍不足以告诉我们 $S_n$ 与其他量相比究竟有多大。比如 $S_n$ 和斐波那契数 $F_{4n}$ 哪个更大？答案是：$n=2$ 时 $S_2=22>F_8=21$；但 $F_{4n}$ 最终会更大，因为
$$
F_{4n}\sim\phi^{4n}/\sqrt5,\quad \phi^4\approx6.8541,
$$
而
$$
S_n = \sqrt{\frac{3}{\pi n}}(6.75)^n \left( 1 - \frac{151}{72n} + O\!\left( \frac{1}{n^2} \right) \right). \tag{9.2}
$$

本章的目标，就是学会如何轻松地理解并推导出这类结果。

asymptotic 一词源自希腊语词根，意为“不会相合”。古希腊数学家研究圆锥曲线时，考察了形如 $y=\sqrt{1+x^2}$ 的双曲线，它以直线 $y=x$ 和 $y=-x$ 为“渐近线”。当 $x\to\infty$ 时，曲线不断逼近这些渐近线却永不相交。如今我们在更广泛的意义下使用“渐近”一词，指某个参数趋近极限值时，越来越接近真实值的近似。对我们而言，渐近性就是“几乎相合”。

有些渐近公式极难推导，远超本书范围。我们只对这一主题做入门介绍，希望打下合适的基础，以便后续学习更多方法。我们将重点理解 $\sim$，$O$ 等符号的定义，并学习处理渐近量的基本方法。

## 9.1 A HIERARCHY
实际应用中出现的关于 $n$ 的函数，通常具有不同的“渐近增长速率”：其中一个会比另一个更快趋于无穷。我们将其形式化定义为
$$
f(n) \prec g(n) \iff \lim_{n\to\infty} \frac{f(n)}{g(n)} = 0. \tag{9.3}
$$
该关系具有传递性：若 $f(n)\prec g(n)$ 且 $g(n)\prec h(n)$，则 $f(n)\prec h(n)$。
当 $f(n)\prec g(n)$ 时，我们也可写作 $g(n)\succ f(n)$。这个记号由 Paul du Bois-Reymond 在 1871 年引入。

例如，$n\prec n^2$；直观地说，$n$ 比 $n^2$ 增长更慢。事实上，对任意实数 $\alpha,\beta$ 有
$$
n^\alpha \prec n^\beta \iff \alpha < \beta. \tag{9.4}
$$

当然，除了幂函数，还有许多关于 $n$ 的函数。我们可以用 $\prec$ 关系把大量函数排成一个渐近优先级序列，形如：
$$
1 \prec \log\log n \prec \log n \prec n^\epsilon \prec n^c \prec n^{\log n} \prec c^n \prec n^n \prec c^{c^n}.
$$
（这里 $\epsilon$ 和 $c$ 是满足 $0<\epsilon<1<c$ 的任意常数。）

除了 1 以外，这里列出的所有函数当 $n\to\infty$ 时都趋于无穷。因此，把一个新函数放入这个层级时，我们关心的不是它是否趋于无穷，而是**以多快的速度**趋于无穷。

在做渐近分析时，保持开阔的视角很有帮助：想象变量趋于无穷时，要往“足够大”去想。例如，层级中说 $\log n\prec n^{0.0001}$；如果只看很小的数比如 $n=10^{100}$，这看起来似乎不对，因为此时 $\log n=100$，而 $n^{0.0001}=10^{0.01}\approx1.0233$。但如果取到古戈尔普勒克斯 $n=10^{10^{100}}$，则 $\log n=10^{100}$ 相比 $n^{0.0001}=10^{10^{96}}$ 就相形见绌了。

即便 $\epsilon$ 极小（比如小于 $1/10^{10^{100}}$），只要 $n$ 足够大，$\log n$ 仍会远小于 $n^\epsilon$。
令 $n=10^{10^{2k}}$，其中 $k$ 大到满足 $\epsilon\ge10^{-k}$，则 $\log n=10^{2k}$，而 $n^\epsilon\ge10^{10^k}$。于是比值 $(\log n)/n^\epsilon\to0$（当 $n\to\infty$）。

上面的层级针对的是趋于无穷的函数。但我们常常也关心趋于零的函数，因此为这类函数建立类似的层级会很有用。取倒数即可得到，因为当 $f(n),g(n)$ 恒不为零时，有
$$
f(n) \prec g(n) \iff \frac1{g(n)} \prec \frac1{f(n)}. \tag{9.5}
$$
于是，下面这些函数（除 1 外）都趋于零：
$$
\frac1{c^{c^n}} \prec \frac1{n^n} \prec \frac1{c^n} \prec \frac1{n^{\log n}}
\prec \frac1{n^c} \prec \frac1{n^\epsilon} \prec \frac1{\log n}
\prec \frac1{\log\log n} \prec 1.
$$

我们再看几个函数，判断它们的位置。不超过 $n$ 的素数个数 $\pi(n)$ 已知近似为 $n/\ln n$。
由于 $1/n^\epsilon \prec 1/\ln n \prec 1$，两边同乘 $n$ 可得
$$
n^{1-\epsilon} \prec \pi(n) \prec n.
$$

事实上，我们可以推广式 (9.4)，例如：
$$
n^{\alpha_1}(\log n)^{\alpha_2}(\log\log n)^{\alpha_3}
\prec
n^{\beta_1}(\log n)^{\beta_2}(\log\log n)^{\beta_3} \\
\iff (\alpha_1,\alpha_2,\alpha_3) < (\beta_1,\beta_2,\beta_3). \tag{9.6}
$$

这里 $(\alpha_1,\alpha_2,\alpha_3) < (\beta_1,\beta_2,\beta_3)$ 指字典序：即 $\alpha_1<\beta_1$，或 $\alpha_1=\beta_1$ 且 $\alpha_2<\beta_2$，或 $\alpha_1=\beta_1$、$\alpha_2=\beta_2$ 且 $\alpha_3<\beta_3$。

那函数 $e^{\sqrt{\log n}}$ 在层级中处于什么位置？我们可以用下面的法则回答这类问题：
$$
e^{f(n)} \prec e^{g(n)} \iff \lim_{n\to\infty}\bigl(f(n)-g(n)\bigr) = -\infty, \tag{9.7}
$$
这可以由定义 (9.3) 取对数后两步推出。从而有
$$
1 \prec f(n) \prec g(n) \implies e^{|f(n)|} \prec e^{|g(n)|}.
$$
又因为 $1 \prec \log\log n \prec \sqrt{\log n} \prec \epsilon\log n$，所以
$$
\log n \prec e^{\sqrt{\log n}} \prec n^\epsilon.
$$

当两个函数 $f(n)$ 与 $g(n)$ 增长速率相同时，我们记作 $f(n) \asymp g(n)$。严格定义为：
$$
f(n) \asymp g(n) \iff
\bigl|f(n)\bigr| \le C\bigl|g(n)\bigr| \text{ 且 }
\bigl|g(n)\bigr| \le C\bigl|f(n)\bigr|
$$
对某个常数 $C$ 以及所有充分大的 $n$ 成立。
\tag{9.8}

例如，当 $f(n)$ 为常数、$g(n)=\cos n+\arctan n$ 时就满足这一关系。我们很快会证明：只要 $f(n)$ 与 $g(n)$ 是同次多项式，就有 $f(n)\asymp g(n)$。还有一个更强的关系，定义为
$$
f(n) \sim g(n) \iff \lim_{n\to\infty}\frac{f(n)}{g(n)} = 1. \tag{9.9}
$$
此时我们称“$f(n)$ 渐近于 $g(n)$”。

G. H. Hardy 引入了一个重要而有趣的概念，称为**对数-指数函数类**，递归定义为满足以下性质的最小函数族 $\mathcal L$：
- 常函数 $f(n)=\alpha$ 属于 $\mathcal L$，对所有实数 $\alpha$；
- 恒等函数 $f(n)=n$ 属于 $\mathcal L$；
- 若 $f(n),g(n)\in\mathcal L$，则 $f(n)-g(n)\in\mathcal L$；
- 若 $f(n)\in\mathcal L$，则 $e^{f(n)}\in\mathcal L$；
- 若 $f(n)\in\mathcal L$ 且“最终为正”，则 $\ln f(n)\in\mathcal L$。

函数 $f(n)$ 称为“最终为正”，如果存在整数 $n_0$，使得对所有 $n\ge n_0$ 都有 $f(n)>0$。

利用这些规则可以证明：若 $f(n),g(n)\in\mathcal L$，则 $f(n)+g(n)\in\mathcal L$，因为 $f(n)+g(n)=f(n)-\bigl(0-g(n)\bigr)$。若 $f(n),g(n)$ 是 $\mathcal L$ 中最终为正的函数，则它们的乘积
$$
f(n)g(n)=e^{\ln f(n)+\ln g(n)}
$$
与商
$$
f(n)/g(n)=e^{\ln f(n)-\ln g(n)}
$$
都属于 $\mathcal L$；类似地，$\sqrt{f(n)}=e^{\frac12\ln f(n)}$ 等也属于 $\mathcal L$。Hardy 证明了：每个对数-指数函数要么最终为正，要么最终为负，要么恒为零。因此任意两个 $\mathcal L$ 函数的乘积与商仍属于 $\mathcal L$，只是不能除以恒为零的函数。

Hardy 关于对数-指数函数的核心定理是：它们构成一个**渐近全序层级**：如果 $f(n)$ 和 $g(n)$ 都属于 $\mathcal L$，那么必有下列三种关系之一成立：
$$f(n) \prec g(n),\quad f(n) \succ g(n),\quad\text{或}\quad f(n) \asymp g(n).$$
而且在第三种情形下，实际上一定存在常数 $\alpha$，使得
$$f(n) \sim \alpha\,g(n).$$

Hardy 定理的证明超出了本书范围，但知道这个定理存在是很有用的，因为我们实际需要处理的几乎所有函数都属于 $\mathcal L$。在实践中，我们通常可以不费力地把一个给定函数放进已知的渐近层级中。


