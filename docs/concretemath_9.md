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


## 9.2 O NOTATION
渐近分析中一套非常好用的符号体系，是 Paul Bachmann 在 1894 年引入的，并在随后由 Edmund Landau 等人推广普及。我们已经在如下公式中见过它：
$$
H_n = \ln n + \gamma + O(1/n), \tag{9.10}
$$
它表示第 n 个调和数等于 n 的自然对数加上欧拉常数，再加上一个“1/n 的大 O 项”。最后这一项并没有被精确给出；但这个符号的含义是：它的绝对值不超过某个常数乘以 1/n。

O 记号的美妙之处在于它忽略无关细节，让我们专注于主要特征：当 1/n 的常数倍可以忽略时，$O(1/n)$ 就是可以忽略的小量。

而且我们可以直接在公式中间使用 O。如果想用 9.1 节的符号表达 (9.10)，就必须把 $\ln n+\gamma$ 移到左边，然后写出一个较弱的式子，比如
$$
H_n - \ln n - \gamma \prec \frac{\log\log n}{n}
$$
或者一个较强的式子
$$
H_n - \ln n - \gamma \asymp \frac{1}{n}.
$$
大 O 记号让我们可以在原位表达恰到好处的精度，不必移项。

这种“不精确定义的量”的思想可以通过更多例子看得更清楚。我们有时会用符号 $\pm1$ 表示某个要么是 +1 要么是 -1 的量；我们不知道（或者不关心）具体是哪一个，但仍然可以在公式里对它进行运算。

N. G. de Bruijn 在他的《Asymptotic Methods in Analysis》[74] 一书开头，引入了一个**大 L 记号**来帮助理解大 O。如果用 $L(5)$ 表示一个绝对值小于 5 的数（具体是多少不指定），那么我们可以在不知道确切值的情况下做一些运算，例如：$1+L(5)=L(6),\quad L(2)+L(3)=L(5),\quad L(2)L(3)=L(6),\quad e^{L(5)}=L(e^5)$等等。但我们不能推出 $L(5)-L(3)=L(2)$，因为左边可能是 $4-0$。事实上，最精确的结论只能是 $L(5)-L(3)=L(8)$。

Bachmann 的 $O$ 记号与 $L$ 记号类似，但更粗略一些：$O(\alpha)$ 表示一个绝对值至多为某个常数乘以 $|\alpha|$ 的量。我们既不指明这个量具体是什么，也不指明常数是多少。当然，“常数”这个概念在没有变量时是没有意义的，所以我们只在至少有一个量（比如 $n$）在变化的场合使用 $O$ 记号。公式
$$
f(n)=O\bigl(g(n)\bigr),\quad \text{对所有 }n \tag{9.11}
$$
在这种语境下的意思是：存在常数 $C$，使得
$$
|f(n)|\le C\,|g(n)|,\quad \text{对所有 }n. \tag{9.12}
$$
当 $O\bigl(g(n)\bigr)$ 出现在公式中间时，它代表一个满足 (9.12) 的未知函数 $f(n)$。我们不知道 $f(n)$ 的确切值，但知道它不会太大。类似地，de Bruijn 的 $L(n)$ 代表一个满足 $|f(n)|<|n|$ 的未知函数。$L$ 与 $O$ 的主要区别在于：$O$ 记号包含一个**未指明的常数 $C$**；每次出现的 $O$ 可能对应不同的 $C$，但每个 $C$ 都与 $n$ 无关。

例如，我们知道前 $n$ 个平方和为
$$
\Box_n = \frac13n\bigl(n+\tfrac12\bigr)(n+1)= \frac13n^3 + \frac12n^2 + \frac16n.
$$
于是可以写
$$
\Box_n  = O(n^3),
$$
因为 $\Bigl|\frac13n^3+\frac12n^2+\frac16n\Bigr|\le \frac13|n|^3+\frac12|n|^2+\frac16|n|\le \frac13|n^3|+\frac12|n^3|+\frac16|n^3|= |n^3|$，对所有整数 $n$ 成立。类似地，我们有更精确的式子
$$
\Box_n  = \frac13n^3 + O(n^2),
$$
也可以粗略地丢掉信息，写成
$$
\Box_n  = O(n^{10}).
$$
$O$ 的定义并不要求我们给出最优的上界。

不过等一下：如果变量 $n$ 不是整数呢？比如有式子 $S(x) = \frac13x^3 + \frac12x^2 + \frac16x$，其中 $x$ 是实数。这时我们不能说 $S(x)=O(x^3)$，因为比值 $\frac{S(x)}{x^3} = \frac13 + \frac12x^{-1} + \frac16x^{-2}$ 在 $x\to0$ 时无界。我们也不能说 $S(x)=O(x)$，因为 $\frac{S(x)}{x} = \frac13x^2 + \frac12x + \frac16$ 在 $x\to\infty$ 时无界。这么看好像不能对 $S(x)$ 使用 $O$ 记号。

这个困境的答案是：与 $O$ 一起使用的变量通常带有附加条件。比如，若规定 $|x|\ge1$，或 $x\ge\epsilon$（$\epsilon>0$），或 $x$ 为整数，就可以写 $S(x)=O(x^3)$。若规定 $|x|\le1$ 或 $|x|\le c$，就可以写 $S(x)=O(x)$。$O$ 记号受其环境、受变量约束的支配。

这些约束常常通过一个极限关系给出。例如我们会说：
$$
f(n) = O\bigl(g(n)\bigr) \quad\text{as }n\to\infty. \tag{9.13}
$$

意思是 $O$ 条件只在 $n$“接近无穷”时成立；除非 $n$ 足够大，否则我们不关心。而且我们不必精确说明“接近”是什么意思：每个 $O$ 都隐含存在两个常数 $C,n_0$，使得
$$
|f(n)| \le C\bigl|g(n)\bigr| \quad\text{whenever }n\ge n_0. \tag{9.14}
$$

不同 $O$ 对应的 $C,n_0$ 可以不同，但都与 $n$ 无关。类似地，记号
$$
f(x) = O\bigl(g(x)\bigr) \quad\text{as }x\to0
$$

表示存在常数 $C,\epsilon$，使得
$$
|f(x)| \le C\bigl|g(x)\bigr| \quad\text{whenever }|x|\le\epsilon. \tag{9.15}
$$

极限不一定是 $\infty$ 或 $0$；我们可以写
$$
\ln z = z-1 + O\bigl((z-1)^2\bigr) \quad\text{as }z\to1,
$$
因为可以证明：当 $|z-1|\le\frac12$ 时，$|\ln z - z + 1|\le|z-1|^2$。

我们对 $O$ 的定义从看似直观的东西，慢慢变成了相当精细的概念：现在 $O$ 代表一个未明确的函数，以及一到两个未明确的常数，依环境而定。这对一个记号来说似乎已经足够复杂，但还不是全部：背后还有一个微妙点。也就是说，我们可以放心地写
$$
\frac13n^3 + \frac12n^2 + \frac16n = O(n^3),
$$
但绝不应该把等式两边反过来写。否则从 $n=O(n^2)$ 和 $n^2=O(n^2)$ 就能推出荒谬的 $n=n^2$。使用 $O$ 记号和其他含不精确量的公式时，我们面对的是单向等式。等式右边信息量不大于左边，通常更少；右边是左边的“粗糙化”。

从严格形式化角度看，记号 $O\bigl(g(n)\bigr)$ 并不代表单个函数 $f(n)$，而是代表所有满足 $|f(n)|\le C\bigl|g(n)\bigr|$ 的函数 $f(n)$ 构成的集合（对某个常数 $C$）。不含 $O$ 的普通式子 $g(n)$ 则代表只含一个函数 $f(n)=g(n)$ 的集合。

若 $S,T$ 是 $n$ 的函数集合，则 $S+T$ 表示所有形如 $f(n)+g(n)$ 的函数集合，其中 $f\in S,g\in T$；类似可定义 $S-T,ST,S/T,\sqrt S,e^S,\ln S$ 等。于是这类函数集合之间的“等式”严格来说其实是集合包含：符号 $=$ 实际上表示 $\subseteq$。这些形式化定义让所有 $O$ 运算建立在坚实的逻辑基础上。

例如，“等式”
$$
\frac13n^3 + O(n^2) = O(n^3)
$$
的含义是 $S_1 \subseteq S_2$，其中：
- $S_1$ 是所有形如 $\frac13n^3 + f_1(n)$ 的函数集合，满足存在常数 $C_1$ 使得 $|f_1(n)| \le C_1|n^2|$；
- $S_2$ 是所有函数 $f_2(n)$ 的集合，满足存在常数 $C_2$ 使得 $|f_2(n)| \le C_2|n^3|$。

我们可以形式化证明这个“等式”：任取左边一个元素，证明它属于右边。给定 $\frac13n^3 + f_1(n)$ 且 $|f_1(n)| \le C_1n^2$，只需取常数 $C_2 = \frac13 + C_1$，就有
$$
\Bigl|\frac13n^3 + f_1(n)\Bigr|
\le \frac13n^3 + C_1n^2
\le \Bigl(\frac13 + C_1\Bigr)n^3
= C_2n^3
$$
对所有整数 $n$ 成立。

既然“$=$”实际表示“$\subseteq$”，为什么我们不用 $\subseteq$ 而要滥用等号？有四个原因：
第一，传统。数论学家最早就把等号用在 $O$ 记号里，这一习惯沿用至今，已经根深蒂固，很难指望数学界改变。

第二，传统。计算机领域的人早已习惯等号的“滥用”——多年来 Fortran 和 BASIC 程序员一直在写 $N = N + 1$ 这样的赋值语句，再多一次滥用也无伤大雅。

第三，传统。我们常把“$=$”读作“是”。比如我们会口头说 $H_n = O(\log n)$ 为：“$H_n$ 是 $\log n$ 的大 O”。

而在英语里，这种“是”是单向的。我们说“一只鸟是一种动物”，但不会说“一种动物是一只鸟”；“动物”是对“鸟”的一种粗略概括。

第四，对我们的用途来说很自然。如果我们只在公式**整个右边**用 $O$ 记号——比如调和数近似 $H_n=O(\log n)$，或是排序算法运行时间 $T(n)=O(n\log n)$——那用 `=` 还是别的符号都无所谓。但在渐近计算中，我们常常要把 $O$ 用在表达式**中间**，这时把等号当作普通等式、把 $O(1/n)$ 这类东西看成很小的量，直觉上会非常顺畅。

所以我们会继续用 `=`，并继续把 $O\bigl(g(n)\bigr)$ 看成一个“未完全指定的函数”，同时心里清楚：必要时随时可以回到集合论的严格定义。

不过在抠定义细节时，还有一个技术点要提：如果环境中有多个变量，$O$ 记号形式上表示**多元函数集合**，而不只是一元函数。每个函数的定义域包含当前所有“自由”变化的变量。

这个概念有点微妙，因为某个变量可能只在表达式的一部分中被定义，比如被 $\sum$ 约束。我们仔细看这个式子：
$$
\sum_{k=0}^n \bigl(k^2 + O(k)\bigr)
= \frac13n^3 + O(n^2),\quad \text{integer }n\ge0. \tag{9.16}
$$
左边的 $k^2+O(k)$ 表示所有形如 $k^2+f(k,n)$ 的二元函数集合，满足存在常数 $C$ 使得
$$|f(k,n)|\le C k,\quad 0\le k\le n.$$
对 $k=0\dots n$ 求和后，得到的函数 $g(n)$ 形如
$$
\sum_{k=0}^n\bigl(k^2+f(k,n)\bigr) = \frac13n^3+\frac12n^2+\frac16n + f(0,n)+\cdots+f(n,n).
$$
由于
$$
\Bigl|\frac12n^2+\frac16n+f(0,n)+\cdots+f(n,n)\Bigr|
\le \frac12n^2+\frac16n + C(0+1+\cdots+n)
< n^2 + C\frac{n^2+n}{2} < (C+1)n^2,
$$
所有这样的 $g(n)$ 都属于右边，因此 (9.16) 成立。

人们有时会滥用 $O$ 记号，把它当成精确增长阶，仿佛它同时给出了上界和下界。比如有人会说某个排序算法效率低，“因为运行时间是 $O(n^2)$”。但 $O(n^2)$ 并不排除它同时也是 $O(n)$。
对此有另一个表示下界的记号：大 Omega
$$
f(n)=\Omega\bigl(g(n)\bigr)
\iff |f(n)|\ge C|g(n)|,\quad \text{某个 }C>0. \tag{9.17}
$$
$f(n)=\Omega\bigl(g(n)\bigr)$ 当且仅当 $g(n)=O\bigl(f(n)\bigr)$。
运行时间为 $\Omega(n^2)$ 的排序算法，在 $n$ 足够大时，确实比 $O(n\log n)$ 的算法低效。

最后还有大 Theta，表示精确增长阶：
$$
f(n)=\Theta\bigl(g(n)\bigr)
\iff f(n)=O\bigl(g(n)\bigr)\text{ 且 }f(n)=\Omega\bigl(g(n)\bigr). \tag{9.18}
$$
$f(n)=\Theta\bigl(g(n)\bigr)$ 等价于之前式 (9.8) 的 $f(n)\asymp g(n)$。

Edmund Landau 还引入了小 oh 记号：
$$
f(n)=o\bigl(g(n)\bigr)
\iff
\begin{aligned}[t]
&|f(n)|\le\epsilon|g(n)|\\
&\text{对所有 }n\ge n_0(\epsilon)\\
&\text{以及所有常数 }\epsilon>0.
\end{aligned} \tag{9.19}
$$
这本质上就是 (9.3) 的 $f(n)\prec g(n)$。同时还有
$$
f(n)\sim g(n)
\iff f(n)=g(n)+o\bigl(g(n)\bigr). \tag{9.20}
$$

很多作者在渐近公式里用 $o$，但更明确的 $O$ 表达式几乎总是更好用。例如一种叫“冒泡排序”的算法平均运行时间与和式
$$
P(n)=\sum_{k=0}^n k^{n-k}k!/n!
$$
的渐近行为有关。基础渐近方法可以证明
$$
P(n)\sim\sqrt{\pi n/2},
$$
即比值趋于 1。但看表格会发现：

| $n$ | $P(n)/\sqrt{\pi n/2}$ | $P(n)-\sqrt{\pi n/2}$ |
|-----|-----------------------|-----------------------|
| 1   | 0.798                 | −0.253                |
| 10  | 0.878                 | −0.484                |
| 20  | 0.904                 | −0.538                |
| 30  | 0.918                 | −0.561                |
| 40  | 0.927                 | −0.575                |
| 50  | 0.934                 | −0.585                |

中间一列的比值说服力不强；但右边一列清楚显示 $P(n)$ 极接近 $\sqrt{\pi n/2}$。
所以如果能推出形如
$$
P(n)=\sqrt{\pi n/2}+O(1)
$$
甚至更精细的
$$
P(n)=\sqrt{\pi n/2}-\frac23+O(1/\sqrt n)
$$
就能好得多地刻画 $P(n)$ 的行为。

证明 $O$ 型结果需要更强的渐近分析方法，但为此多花的学习精力，会被更清晰的理解充分回报。

此外，许多排序算法的运行时间形如
$$
T(n)=A n\lg n+B n+O(\log n)
$$
只停留在 $T(n)\sim A n\lg n$ 的分析并不完整。事实证明，只根据系数 $A$ 选算法是糟糕的策略：$A$ 好看的算法往往 $B$ 很差。而 $n\lg n$ 只比 $n$ 稍快一点，渐近上更快的算法（$A$ 略小）可能只在现实中根本不会出现的超大 $n$ 才更快。因此，要做出正确选择，就必须用渐近方法算出首项之后的 $B$ 以及更精细的项。

在继续研究 $O$ 记号之前，我们再来谈一点数学书写风格上的小问题。本章中使用了三种不同的对数记号：$\lg$、$\ln$ 以及 $\log$。在与计算机相关的内容里，我们通常使用 $\lg$，因为在这种场景下二进制对数往往是相关的；而在纯数学计算中，我们常使用 $\ln$，因为自然对数的相关公式简洁优美。但是 $\log$ 呢？它不就是高中生所学的“常用”以 10 为底的对数吗——那种在数学与计算机科学中实际上非常不常用的“常用对数”？确实如此。而且许多数学家会混用这个记号，用 $\log$ 表示自然对数或二进制对数，这就把问题搞得更混乱了。在这一点上并没有统一的约定。

不过，当对数出现在 $O$ 记号内部时，我们通常可以放宽心，因为 $O$ 记号会忽略常数因子。当 $n\to\infty$ 时，$O(\lg n)$、$O(\ln n)$ 和 $O(\log n)$ 之间没有区别；类似地，$O(\lg\lg n)$、$O(\ln\ln n)$ 和 $O(\log\log n)$ 也没有区别。我们可以任选其一，而使用 $\log$ 的写法往往更友好，因为读起来更顺口。因此，在不引起歧义且能提升可读性的场合，我们通常统一使用 $\log$。

## 9.3 O MANIPULATION 操作
如同任何数学形式体系，$O$ 记号有一套运算规则，让我们不必纠缠于定义中的繁琐细节。一旦用定义证明了规则的正确性，我们就可以在更高层面上运算，不再需要逐一验证函数集合之间的包含关系。我们甚至不需要计算每个 $O$ 隐含的常数 $C$，只要遵守能保证这类常数存在的规则即可。

例如，我们可以一劳永逸地证明：
$$
n^m = O(n^{m'}), \quad \text{当 } m \le m'; \tag{9.21}
$$
$$
O\bigl(f(n)\bigr) + O\bigl(g(n)\bigr) = O\bigl(|f(n)|+|g(n)|\bigr). \tag{9.22}
$$

于是我们可以直接得出：$\frac13n^3+\frac12n^2+\frac16n = O(n^3)+O(n^3)+O(n^3) = O(n^3)$，而不必像上一节那样做繁琐计算。

下面是另一些从定义容易推出的规则：
$$
f(n) = O\bigl(f(n)\bigr); \tag{9.23}
$$
$$
c\cdot O\bigl(f(n)\bigr) = O\bigl(f(n)\bigr), \quad \text{ if c is constant}; \tag{9.24}
$$
$$
O\bigl(O\bigl(f(n)\bigr)\bigr) = O\bigl(f(n)\bigr); \tag{9.25}
$$
$$
O\bigl(f(n)\bigr)O\bigl(g(n)\bigr) = O\bigl(f(n)g(n)\bigr); \tag{9.26}
$$
$$
O\bigl(f(n)g(n)\bigr) = f(n)O\bigl(g(n)\bigr). \tag{9.27}
$$
习题 9 证明了 (9.22)，其余式子的证明类似。无论变量 $n$ 有什么附加条件，我们总可以把左边形式的式子替换成右边。

由 (9.27) 和 (9.23) 可以推出恒等式 $O\bigl(f(n)^2\bigr) = O\bigl(f(n)\bigr)^2$，这有时能省去括号，比如我们可以写
$$
O(\log n)^2 \text{ instead of } O\bigl((\log n)^2\bigr).
$$
两者都优于 $O(\log^2 n)$，因为后者有歧义：有些作者用它表示 $O(\log\log n)$。

我们能不能也把
$$
O\bigl((\log n)^{-1}\bigr) \text{ instead of } O(\log n)^{-1}?
$$
不行！这是对记号的滥用，因为集合 $1/O(\log n)$ 既不是 $O(1/\log n)$ 的子集也不是其超集。我们虽然可以合法地用 $\Omega(\log n)^{-1}$ 代替 $O\bigl((\log n)^{-1}\bigr)$，但那样很不自然。所以我们只把“指数写在 $O$ 外面”的写法限制在正整数常数指数上。

幂级数给我们提供了一些最实用的运算。如果级数
$$
S(z) = \sum_{n\ge0} a_n z^n
$$
在某个复数 $z=z_0$ 处绝对收敛，那么
$$
S(z) = O(1),\quad \text{ for all } |z| \le |z_0|.
$$
这是显然的，因为
$$
|S(z)| \le \sum_{n\ge0} |a_n|\,|z|^n
\le \sum_{n\ge0} |a_n|\,|z_0|^n = C < \infty.
$$
特别地，$S(z)=O(1)$ 当 $z\to0$，且 $S(1/n)=O(1)$ 当 $n\to\infty$，只要 $S(z)$ 至少在一个非零点处收敛。我们可以用这个原则在任意方便的位置截断幂级数，并用 $O$ 估计余项。例如，不仅有 $S(z)=O(1)$，还有
$$
S(z) = a_0 + O(z),\\
S(z) = a_0 + a_1 z + O(z^2),
$$
等等，因为
$$
S(z) = \sum_{0\le k<m} a_k z^k + z^m \sum_{n\ge m} a_n z^{n-m}
$$
而后一个和与 $S(z)$ 本身一样，在 $z=z_0$ 处绝对收敛，因此是 $O(1)$。
表 452 列出了一些最常用的渐近公式，其中一半正是基于这条规则对幂级数的截断。

形如 $\sum_{k\ge1} a_k/k^z$ 的**狄利克雷级数**也可以类似截断：如果一个狄利克雷级数在 $z=z_0$ 处绝对收敛，我们可以在任一项处截断，得到近似式
$$
\sum_{1\le k<m} a_k/k^z + O(m^{-z}),
$$
对 $\Re z\ge\Re z_0$ 成立。表 452 中伯努利数 $B_n$ 的渐近公式就体现了这一原则。

另一方面，表 452 中 $H_n$、$n!$ 与 $\pi(n)$ 的渐近公式并不是收敛级数的截断；如果无限延伸，它们对所有 $n$ 都会发散。这一点在 $\pi(n)$ 上尤其明显，因为我们在 7.3 节例 5 已经看到，幂级数 $\sum_{k\ge0} k!/(\ln n)^k$ 处处发散。然而，这些发散级数的截断式却成为非常有用的近似。

**表 452 渐近近似公式，当 $n\to\infty$ 且 $z\to 0$ 时成立**
$$
H_n = \ln n + \gamma + \frac1{2n} - \frac1{12n^2} + \frac1{120n^4} + O\!\left(\frac1{n^6}\right). \tag{9.28}
$$
$$
n! = \sqrt{2\pi n}\left(\frac{n}{e}\right)^{\!n} \left( 1 + \frac1{12n} + \frac1{288n^2} - \frac{139}{51840n^3} + O\!\left(\frac1{n^4}\right) \right). \tag{9.29}
$$
$$
B_n = 2\cdot[n\ even]\,(-1)^{n/2-1} \frac{n!}{(2\pi)^n} \bigl( 1 + 2^{-n} + 3^{-n} + O(4^{-n}) \bigr). \tag{9.30}
$$
$$
\pi(n) = \frac{n}{\ln n} + \frac{n}{(\ln n)^2} + \frac{2!\,n}{(\ln n)^3} + \frac{3!\,n}{(\ln n)^4} + O\!\left( \frac{n}{(\log n)^5} \right). \tag{9.31}
$$
$$
e^z = 1 + z + \frac{z^2}{2!} + \frac{z^3}{3!} + \frac{z^4}{4!} + O(z^5). \tag{9.32}
$$
$$
\ln(1+z) = z - \frac{z^2}{2} + \frac{z^3}{3} - \frac{z^4}{4} + O(z^5). \tag{9.33}
$$
$$
\frac1{1-z} = 1 + z + z^2 + z^3 + z^4 + O(z^5). \tag{9.34}
$$
$$
(1+z)^\alpha = 1 + \alpha z + \binom{\alpha}{2}z^2 + \binom{\alpha}{3}z^3 + \binom{\alpha}{4}z^4 + O(z^5). \tag{9.35}
$$

若一个渐近近似形如 $f(n)+O\bigl(g(n)\bigr)$（其中 $f(n)$ 不含 $O$），就称它的绝对误差为 $O\bigl(g(n)\bigr)$。若近似形如 $f(n)\bigl(1+O\bigl(g(n)\bigr)\bigr)$（$f(n)$ 不含 $O$），则称其相对误差为 $O\bigl(g(n)\bigr)$。例如，表 452 中 $H_n$ 的近似绝对误差为 $O(n^{-6})$；$n!$ 的近似相对误差为 $O(n^{-4})$。（式 (9.29) 右边并非严格写成 $f(n)\bigl(1+O(n^{-4})\bigr)$ 的形式，但我们可以改写为
$$
\sqrt{2\pi n}\left(\frac{n}{e}\right)^{\!n}
\left( 1+\frac1{12n}+\frac1{288n^2}-\frac{139}{51840n^3} \right)
\bigl(1+O(n^{-4})\bigr)
$$

习题 12 会涉及类似计算。）该近似的绝对误差为 $O(n^{n-3.5}e^{-n})$。忽略 $O$ 项时，绝对误差对应小数点后正确十进制位数；相对误差对应正确有效数字位数。

利用幂级数截断可以证明一般法则：
$$
\ln\bigl(1+O(f(n))\bigr)=O\bigl(f(n)\bigr),\quad \text{ if }f(n)\prec1; \tag{9.36}
$$
$$
e^{O(f(n))}=1+O\bigl(f(n)\bigr),\quad \text{ if }f(n)=O(1). \tag{9.37}
$$

（这里我们假设 $n\to\infty$；对于 $x\to0$ 时的 $\ln\bigl(1+O(f(x))\bigr)$ 和 $e^{O(f(x))}$，也有类似公式成立。）例如，设 $\ln\bigl(1+g(n)\bigr)$ 是属于 (9.36) 左边的任意一个函数，那么存在常数 $C,n_0$ 以及 $c$，使得
$$
|g(n)| \le C|f(n)| \le c < 1,\quad \text{for all }n\ge n_0.
$$
由此可知无穷级数
$$
\ln\bigl(1+g(n)\bigr)
= g(n)\cdot\Bigl(1-\frac12g(n)+\frac13g(n)^2-\cdots\Bigr)
$$
对所有 $n\ge n_0$ 收敛，并且括号内的级数被常数 $1+\frac12c+\frac13c^2+\cdots$ 所界。这就证明了 (9.36)，(9.37) 的证明类似。将 (9.36) 与 (9.37) 结合，可以得到有用的公式：
$$
\bigl(1+O(f(n))\bigr)^{O(g(n))}
= 1+O\bigl(f(n)g(n)\bigr),
\\ \text{if }f(n)\prec1\text{ and }f(n)g(n)=O(1).
\tag{9.38}
$$

---

### 问题 1：回到“幸运大转盘”
现在我们用渐近方法来解决几个问题。在第 3 章，我们推导出某个游戏中胜利位置个数的公式 (3.13)：
$$
W = \left\lfloor \frac{N}{K} \right\rfloor + \frac12K^2 + \frac52K - 3,\qquad K = \bigl\lfloor \sqrt[3]{N} \bigr\rfloor.
$$
当时我们承诺会在第 9 章给出 $W$ 的渐近形式。现在到了第 9 章，我们就来估计当 $N\to\infty$ 时的 $W$。

核心思路是去掉取整符号，把 $K$ 替换为 $N^{1/3}+O(1)$。进一步还可以写成：
$$
K = N^{1/3}\bigl(1+O(N^{-1/3})\bigr),
$$

这一步叫作*提取主部*（我们会经常用到这个技巧）。于是有
$$
K^2 = N^{2/3}\bigl(1+O(N^{-1/3})\bigr)^2
= N^{2/3}\bigl(1+O(N^{-1/3})\bigr)
= N^{2/3}+O(N^{1/3}),
$$
这里用到了 (9.38) 和 (9.26)。同理
$$
\begin{aligned}
\left\lfloor \frac{N}{K} \right\rfloor &= N^{1-1/3}\bigl(1+O(N^{-1/3})\bigr)^{-1}+O(1) \\
&= N^{2/3}\bigl(1+O(N^{-1/3})\bigr)+O(1)
= N^{2/3}+O(N^{1/3}).
\end{aligned}
$$
由此可得胜利位置个数为
$$
\begin{aligned}
W &= N^{2/3}+O(N^{1/3}) + \frac12\bigl(N^{2/3}+O(N^{1/3})\bigr) + O(N^{1/3})+O(1) \\
&= \frac32N^{2/3}+O(N^{1/3}).
\end{aligned}
\tag{9.39}
$$
注意 $O$ 项不断被吸收，最后只保留一项；这是典型现象，也体现了 $O$ 记号在公式中间使用的便利。

---

### 问题 2：斯特林公式的扰动
斯特林对 $n!$ 的近似无疑是最著名的渐近公式。我们会在本章稍后证明它；现在先熟悉它的性质。我们可以把近似写成如下形式（$n\to\infty$）：
$$
n! = \sqrt{2\pi n}\left(\frac{n}{e}\right)^{\!n}
\left( 1+\frac{a}{n}+\frac{b}{n^2}+O(n^{-3}) \right),
\tag{9.40}
$$
其中 $a,b$ 为常数。因为该式对所有充分大的 $n$ 成立，把 $n$ 换成 $n-1$ 也渐近成立：
$$
\begin{aligned}
(n-1)! &= \sqrt{2\pi(n-1)}
\left(\frac{n-1}{e}\right)^{\!n-1} \\
&\quad\times
\left( 1+\frac{a}{n-1}+\frac{b}{(n-1)^2}
+O\bigl((n-1)^{-3}\bigr) \right).
\end{aligned}
\tag{9.41}
$$
我们知道 $(n-1)! = n!/n$，因此上式右边必须能化简为 (9.40) 右边除以 $n$。

现在来化简 (9.41)。先对第一个因子提取主部：
$$
\sqrt{2\pi(n-1)}
= \sqrt{2\pi n}\,(1-n^{-1})^{1/2}
= \sqrt{2\pi n}\left( 1-\frac{1}{2n}-\frac{1}{8n^2}+O(n^{-3}) \right).
$$
这里用到了 (9.35)。

同理有
$$
\begin{aligned}
\frac{a}{n-1} &= \frac{a}{n}(1-n^{-1})^{-1}= \frac{a}{n}+\frac{a}{n^2}+O(n^{-3}); \\
\frac{b}{(n-1)^2} &= \frac{b}{n^2}(1-n^{-1})^{-2} = \frac{b}{n^2}+O(n^{-3});  \\
O\bigl((n-1)^{-3}\bigr) &= O\bigl(n^{-3}(1-n^{-1})^{-3}\bigr) = O(n^{-3}).
\end{aligned}
$$
(9.41) 中唯一稍显麻烦的是因子 $(n-1)^{n-1}$，它等于
$$
n^{n-1}(1-n^{-1})^{n-1}
= n^{n-1}(1-n^{-1})^n
\bigl(1+n^{-1}+n^{-2}+O(n^{-3})\bigr).
$$

（我们会把所有项展开到相对误差为 $O(n^{-3})$ 的精度，因为乘积的相对误差等于各因子相对误差之和，所有 $O(n^{-3})$ 项最后会合并在一起。）

为展开 $(1-n^{-1})^n$，我们先计算 $\ln(1-n^{-1})$，再取指数 $e^{n\ln(1-n^{-1})}$：
$$
\begin{aligned}
(1-n^{-1})^n
&= \exp\bigl(n\ln(1-n^{-1})\bigr) \\
&= \exp\Bigl(n\bigl(-n^{-1}-\tfrac12n^{-2}-\tfrac13n^{-3}+O(n^{-4})\bigr)\Bigr) \\
&= \exp\bigl(-1-\tfrac12n^{-1}-\tfrac13n^{-2}+O(n^{-3})\bigr) \\
&= e^{-1}\cdot\exp(-\tfrac12n^{-1})\cdot\exp(-\tfrac13n^{-2})\cdot\exp\bigl(O(n^{-3})\bigr) \\
&= e^{-1}\Bigl(1-\tfrac12n^{-1}+\tfrac18n^{-2}+O(n^{-3})\Bigr)
  \Bigl(1-\tfrac13n^{-2}+O(n^{-4})\Bigr)
  \bigl(1+O(n^{-3})\bigr) \\
&= e^{-1}\Bigl(1-\tfrac12n^{-1}-\tfrac{5}{24}n^{-2}+O(n^{-3})\Bigr).
\end{aligned}
$$

这里我们用 $\exp z$ 代替 $e^z$，方便把复杂指数写在主行上，而不是上角标。因为对数要乘以 $n$，所以必须把 $\ln(1-n^{-1})$ 展开到绝对误差 $O(n^{-4})$，才能保证最终相对误差达到 $O(n^{-3})$。

现在，式 (9.41) 的右边已经化简为：$\sqrt{2\pi n}$ 乘以 $n^{n-1}/e^n$，再乘以若干因子的乘积：
$$
\begin{aligned}
&\Bigl(1-\tfrac12n^{-1}-\tfrac18n^{-2}+O(n^{-3})\Bigr) \\
\cdot\;&\Bigl(1+n^{-1}+n^{-2}+O(n^{-3})\Bigr) \\
\cdot\;&\Bigl(1-\tfrac12n^{-1}-\tfrac{5}{24}n^{-2}+O(n^{-3})\Bigr) \\
\cdot\;&\Bigl(1+an^{-1}+(a+b)n^{-2}+O(n^{-3})\Bigr).
\end{aligned}
$$

将这些展开并把所有渐近项吸收为单个 $O(n^{-3})$，得到：
$$
1+an^{-1}+\Bigl(a+b-\frac{1}{12}\Bigr)n^{-2}+O(n^{-3}).
$$

嗯……我们原本希望得到 $1+an^{-1}+bn^{-2}+O(n^{-3})$，以便和 (9.40) 右边匹配。哪里出错了吗？并没有，一切正常，只要满足 $ a+b-\frac{1}{12}=b$。

这个扰动论证并不能证明斯特林公式本身成立，但它证明了一件事：公式 (9.40) 要成立，必须有 $a=\dfrac1{12}$。如果我们把 (9.40) 中的 $O(n^{-3})$ 换成 $cn^{-3}+O(n^{-4})$，并把计算精度推进到相对误差 $O(n^{-4})$，就可以推出 $b=\dfrac1{288}$，与表 452 一致。（这虽然不是求 $a,b$ 最简单的方法，但确实可行。）

### 问题 3：第 n 个素数
式 (9.31) 是不超过 n 的素数个数 π(n) 的渐近公式。如果把 n 换成第 n 个素数 p = Pₙ，就有 π(p) = n，因此当 n → ∞ 时：
$$
n = \frac{p}{\ln p} + O\!\left(\frac{p}{(\log p)^2}\right). \tag{9.42}
$$
我们尝试从这个方程“解出”p，就能得到第 n 个素数的近似大小。

第一步是简化 O 项。用 p/ln p 除两边，可知 n ln p / p → 1，因此 p/ln p = O(n)，并且
$$
O\!\left(\frac{p}{(\log p)^2}\right)
= O\!\left(\frac{n}{\log p}\right)
= O\!\left(\frac{n}{\log n}\right).
$$
（因为 p ≥ n，所以 (log p)⁻¹ ≤ (log n)⁻¹。）

第二步是交换 (9.42) 两边的主项（保留 O 项不动）。这是合法的，因为有一般规则：
$$
a_n = b_n + O\bigl(f(n)\bigr)
\iff
b_n = a_n + O\bigl(f(n)\bigr). \tag{9.43}
$$
因此
$$
\frac{p}{\ln p}
= n + O\!\left(\frac{n}{\log n}\right)
= n\Bigl(1+O(1/\log n)\Bigr),
$$
于是
$$
p = n\ln p\Bigl(1+O(1/\log n)\Bigr). \tag{9.44}
$$
这是 $p = P_n$ 关于自身的一个“近似递推式”。我们的目标是把它变成“近似闭式”，可以通过渐近展开递推实现。

对 (9.44) 两边取对数：
$$
\ln p = \ln n + \ln\ln p + O(1/\log n). \tag{9.45}
$$

我们可以把这个结果代回 (9.44) 中替换 $\ln p$，但更希望在代入前先消去右边所有的 $p$。无论如何，最终那个 $p$ 必须消失；而用普通递推的方法做不到这一点，因为 (9.44) 并没有给出小 $p$ 对应的初值条件。

一种可行的办法是先证明一个较弱的结论：$p = O(n^2)$。对 (9.44) 两边平方再除以 $pn^2$ 即可得到：
$$
\frac{p}{n^2}
= \frac{(\ln p)^2}{p}\Bigl(1+O(1/\log n)\Bigr),
$$
因为当 $n\to\infty$ 时右边趋于 0。这样我们就知道 $p = O(n^2)$，于是 $\log p = O(\log n)$，$\log\log p = O(\log\log n)$。

现在由 (9.45) 可以推出：
$$
\ln p = \ln n + O(\log\log n).
$$
进一步，利用这个新估计可得：
$$
\ln\ln p = \ln\ln n + O(\log\log n/\log n),
$$
再代入 (9.45) 就得到：
$$
\ln p = \ln n + \ln\ln n + O(\log\log n/\log n).
$$

把它代入 (9.44) 右边，最终得到：
$$
p = n\ln n + n\ln\ln n + O(n).
$$
这就是第 $n$ 个素数的近似大小。我们可以用更精确的 $\pi(n)$ 近似式代替 (9.42)，来改进这一估计。(9.31) 的下一项告诉我们：
$$
n = \frac{p}{\ln p} + \frac{p}{(\ln p)^2} + O\!\left(\frac{p}{(\log p)^3}\right). \tag{9.46}
$$

同理可得递推式：
$$
p = n\ln p\bigl(1+(\ln p)^{-1}\bigr)^{-1}
\Bigl(1+O(1/\log n)^2\Bigr), \tag{9.47}
$$

该式的相对误差为 $O((1/\log n)^2)$，而非 $O(1/\log n)$。取对数并保留恰当的精度（但不过度精细），可得
$$
\begin{aligned}
\ln p &= \ln n + \ln\ln p + O(1/\log n) \\
&= \ln n\left(1+\frac{\ln\ln p}{\ln n}
+O(1/\log n)^2\right),\\
\ln\ln p &= \ln\ln n + \frac{\ln\ln n}{\ln n}
+O\!\left(\frac{\log\log n}{\log n}\right)^{\!2}.
\end{aligned}
$$

最终代回 (9.47) 得到：
$$
P_n = n\ln n + n\ln\ln n - n + n\,\frac{\ln\ln n}{\ln n} + O\!\left(\frac{n}{\log n}\right). \tag{9.48}
$$

例如，当 $n = 10^6$ 时，这个估计式给出 $15631363.8 + O(n/\log n)$；而第一百万个素数的实际值是 $15485863$。习题 21 表明，如果用比 (9.46) 更精确的 $\pi(n)$ 近似式作为出发点，就可以得到 $P_n$ 更加精确的逼近。

**问题 4：一道旧期末考试题中的求和**
在 1970–1971 学年斯坦福大学第一次讲授《具体数学》时，学生被要求求出和式
$$
S_n = \frac{1}{n^2+1} + \frac{1}{n^2+2} + \cdots + \frac{1}{n^2+n} \tag{9.49}
$$
的渐近值，绝对误差要达到 $O(n^{-7})$。假设我们刚在期末（开卷）考试中遇到这道题，第一反应是什么？

不，我们不会慌。第一反应是**先做量级估计**。比如取 $n=10^{100}$，可以看到和式有 $n$ 项，每一项略小于 $1/n^2$，因此总和略小于 $1/n$。一般来说，处理渐近问题时，先对答案有一个大致估计，是很好的开局。

接下来我们对每一项提取主部，改进粗略估计：
$$
\frac{1}{n^2+k}
= \frac{1}{n^2\bigl(1+k/n^2\bigr)}
= \frac{1}{n^2}\left(
1-\frac{k}{n^2}+\frac{k^2}{n^4}-\frac{k^3}{n^6}
+O\!\left(\frac{k^4}{n^8}\right)
\right).
$$
很自然地，我们想把这些近似式逐项相加：
$$
\begin{aligned}
\frac1{n^2+1}
&= \frac1{n^2}-\frac1{n^4}+\frac{1^2}{n^6}-\frac{1^3}{n^8}
+O\!\left(\frac{1^4}{n^{10}}\right),\\
\frac1{n^2+2}
&= \frac1{n^2}-\frac2{n^4}+\frac{2^2}{n^6}-\frac{2^3}{n^8}
+O\!\left(\frac{2^4}{n^{10}}\right),\\
&\ \,\vdots\\
\frac1{n^2+n}
&= \frac1{n^2}-\frac n{n^4}+\frac{n^2}{n^6}-\frac{n^3}{n^8}
+O\!\left(\frac{n^4}{n^{10}}\right).
\end{aligned}
$$
相加后得到：
$$
S_n = \frac n{n^2} - \frac{n(n+1)}{2n^4} + \cdots.
$$
从前两列的和来看，似乎有 $S_n = n^{-1}-\frac12n^{-2}+O(n^{-3})$；但计算会变得非常繁琐。

如果硬着头皮算下去，最终也能得到结果，但我们不必继续加后面的列，原因有两个：第一，当 $n/2\le k\le n$ 时，最后一列会给出 $O(n^{-6})$ 的项，整体误差会是 $O(n^{-5})$，精度不够，还得再多展开一列。出题人会这么残忍吗？我们怀疑一定有更好的方法。第二，确实有一个好得多的办法，就摆在我们眼前。

也就是说，我们其实知道 $S_n$ 的闭式：它就是 $H_{n^2+n} - H_{n^2}$。
而我们有调和数很好的渐近近似，直接用两次即可：
$$
H_{n^2+n} = \ln(n^2+n) + \gamma + \frac1{2(n^2+n)} - \frac1{12(n^2+n)^2} + O\!\left(\frac1{n^8}\right); \\
H_{n^2} = \ln n^2 + \gamma + \frac1{2n^2} - \frac1{12n^4} + O\!\left(\frac1{n^8}\right).
$$

接下来像处理斯特林公式那样，提取主部并化简：

$$
\ln(n^2+n) = \ln n^2 + \ln\!\left(1+\frac1n\right)
= \ln n^2 + \frac1n - \frac1{2n^2} + \frac1{3n^3} - \cdots; \\
\frac1{n^2+n} = \frac1{n^2} - \frac1{n^3} + \frac1{n^4} - \cdots; \\
\frac1{(n^2+n)^2} = \frac1{n^4} - \frac2{n^5} + \frac3{n^6} - \cdots.
$$

于是大量项互相抵消，最后得到：

$$
\begin{aligned}
S_n &= n^{-1} - \tfrac12n^{-2} + \tfrac13n^{-3} - \tfrac14n^{-4} + \tfrac15n^{-5} - \tfrac16n^{-6} \\
&\quad - \tfrac12n^{-3} + \tfrac12n^{-4} - \tfrac12n^{-5} + \tfrac12n^{-6} \\
&\quad + \tfrac16n^{-5} - \tfrac14n^{-6} + O(n^{-7}).
\end{aligned}
$$

简单合并同类项就大功告成：
$$
S_n = n^{-1} - \tfrac12n^{-2} - \tfrac16n^{-3} + \tfrac14n^{-4} - \tfrac2{15}n^{-5} + \tfrac1{12}n^{-6} + O(n^{-7}). \tag{9.50}
$$

如果能像前面推导精确公式那样，用数值验证一下就好了。渐近公式不太好直接验证，因为 $O$ 里可能藏着任意大常数，任何数值测试都不能一锤定音。但在实际中，我们没理由怀疑有人故意刁难，所以可以认为未知的 $O$ 常数都不大。用计算器算一下：$S_4 = \frac1{17}+\frac1{18}+\frac1{19}+\frac1{20} = 0.2170107$；而渐近公式在 $n=4$ 时给出：

$$
\frac14\biggl(1+\frac14\Bigl(-\frac12+\frac14\bigl(-\frac16+\frac14\bigl(\frac14+\frac14(-\tfrac2{15}+\frac14\cdot\tfrac1{12})\bigr)\bigr)\Bigr)\biggr)
= 0.2170125.
$$

如果 $n^{-6}$ 项系数错了比如 $\frac1{12}$，误差会达到 $\frac1{12\cdot4096}$，会在小数点后第 5 位体现出来；
所以我们的渐近结果基本可以确定是对的。

### 问题 5：一个无穷级数
现在来看 Solomon Golomb [152] 提出的一个渐近问题：求和式
$$
S_n = \sum_{k\ge1}\frac1{k\,N_n(k)^2} \tag{9.51}
$$
的渐近值是多少？其中 $N_n(k)$ 是数 $k$ 在 $n$ 进制下的位数。

我们先做一个量级估计。位数 $N_n(k)$ 近似为 $\log_n k = \log k/\log n$，因此级数的项大致是 $(\log n)^2/k(\log k)^2$。对 $k$ 求和后近似为 $(\log n)^2\sum_{k\ge2}1/k(\log k)^2$，这个级数收敛到一个常数，因为可以和积分比较：
$$
\int_{2}^{\infty}\frac{dx}{x(\ln x)^2}
= -\frac1{\ln x}\bigg|_{2}^{\infty} = \frac1{\ln 2}.
$$
因此我们预期 $S_n$ 大约是 $C(\log n)^2$，其中 $C$ 是某个常数。

这类粗略分析有助于把握方向，但要真正解题还需要更精确的估计。一个思路是先把 $N_n(k)$ 写成精确表达式：
$$
N_n(k) = \lfloor\log_n k\rfloor + 1. \tag{9.52}
$$

例如，当 $n^2\le k<n^3$ 时，$k$ 在 $n$ 进制下有 3 位，对应 $\lfloor\log_n k\rfloor=2$。由此可知 $N_n(k)>\log_n k$，所以 $S_n = \sum_{k\ge1}\frac1{k\,N_n(k)^2} < 1 + (\log n)^2\sum_{k\ge2}\frac1{k(\log k)^2}$。

仿照问题 1 的做法，我们可以尝试写 $N_n(k)=\log_n k+O(1)$ 再代入 $S_n$。这里的 $O(1)$ 始终在 0 到 1 之间，平均值大约是 1/2，看起来性质不错。但即便如此，这个近似精度仍不足以求出 $S_n$：它在 $k$ 较小时有效数字完全为 0（即相对误差很大），而这些小 $k$ 项对级数贡献最大。我们需要换一种思路。

关键（如同问题 4）是在做渐近估计之前，先用代数技巧把和式改写成更易处理的形式。我们可以引入新求和变量 $m=N_n(k)$：
$$
\begin{aligned}
S_n &= \sum_{k,m\ge1}\frac{[m=N_n(k)]}{k\,m^2} \\
&= \sum_{k,m\ge1}\frac{[n^{m-1}\le k<n^m]}{k\,m^2} \\
&= \sum_{m\ge1}\frac1{m^2}\bigl(H_{n^m-1}-H_{n^{m-1}-1}\bigr).
\end{aligned}
$$

这个形式看起来可能比原来更复杂，但实际上是向前推进了一步，因为我们对调和数有非常好的渐近近似。

不过我们先不急着用渐近，再化简一步。利用分部求和，可以把每个需要近似的 $H_{n^m-1}$ 对应的项合并在一起：
$$
S_n = \sum_{k\ge1} H_{n^k-1}
\left( \frac1{k^2} - \frac1{(k+1)^2} \right).
$$
例如，$H_{n^2-1}$ 会被乘以 $1/2^2$，再乘以 $-1/3^2$。（这里用到了 $H_{n^0-1}=H_0=0$。）

现在可以展开调和数了。之前估计 $(n-1)!$ 的经验告诉我们，直接估计 $H_{n^k}$ 比 $H_{n^k-1}$ 更方便，因为 $n^k-1$ 会带来麻烦；于是我们写：
$$
\begin{aligned}
H_{n^k-1} = H_{n^k} - \frac1{n^k} 
&= \ln n^k + \gamma + \frac1{2n^k} + O\!\left(\frac1{n^{2k}}\right)- \frac1{n^k} \\
&= k\ln n + \gamma - \frac1{2n^k} + O\!\left(\frac1{n^{2k}}\right).
\end{aligned}
$$

代入后和式变为：
$$
\begin{aligned}
S_n
&= \sum_{k\ge1}
\left( k\ln n + \gamma - \frac1{2n^k} + O\!\left(\frac1{n^{2k}}\right) \right)
\left( \frac1{k^2} - \frac1{(k+1)^2} \right) \\
&= (\ln n)\,\Sigma_1 + \gamma\,\Sigma_2 - \frac12\,\Sigma_3(n) + O\bigl(\Sigma_3(n^2)\bigr).
\end{aligned}
\tag{9.53}
$$
现在只剩下四个简单部分：$\Sigma_1$、$\Sigma_2$、$\Sigma_3(n)$ 和 $\Sigma_3(n^2)$。

我们先算 $\Sigma_3$ 相关的和，因为 $\Sigma_3(n^2)$ 是误差项，先看误差量级。（如果其他计算最后都会被吞进 $O$ 里，精确计算就没有意义。）这个和其实就是一个幂级数：
$$
\Sigma_3(x) = \sum_{k\ge1}
\left( \frac1{k^2} - \frac1{(k+1)^2} \right) x^{-k},
$$

对 $x\ge1$ 收敛，因此可以在任意位置截断。如果只取 $\Sigma_3(n^2)$ 的 $k=1$ 项，就有 $\Sigma_3(n^2)=O(n^{-2})$，于是 (9.53) 的绝对误差为 $O(n^{-2})$。（想进一步减小误差可以用更精确的 $H_{n^k}$ 近似，但目前 $O(n^{-2})$ 已经够用。）如果把 $\Sigma_3(n)$ 截断到 $k=2$，可得：
$$
\Sigma_3(n) = \frac34 n^{-1} + O(n^{-2}),
$$
这已经满足我们需要的精度。

我们不妨现在就计算 $\Sigma_2$，因为它非常简单：
$$
\Sigma_2 = \sum_{k\ge1}\left(\frac1{k^2}-\frac1{(k+1)^2}\right).
$$
这是一个望远镜级数：$(1-\frac14)+(\frac14-\frac19)+(\frac19-\frac1{16})+\cdots=1$。

最后，$\Sigma_1$ 给出 $S_n$ 的主项，也就是 (9.53) 中 $\ln n$ 的系数：
$$
\Sigma_1 = \sum_{k\ge1}k\left(\frac1{k^2}-\frac1{(k+1)^2}\right).
$$

展开为$(1-\frac14)+(\frac24-\frac29)+(\frac39-\frac3{16})+\cdots=\frac11+\frac14+\frac19+\cdots=H_\infty^{(2)}=\pi^2/6$。（如果我们早先没有做分部求和，也能直接看出 $S_n\sim\sum_{k\ge1}(\ln n)/k^2$，因为$H_{n^k-1}-H_{n^{k-1}-1}\sim\ln n$；所以分部求和并没有帮助我们计算主项，但确实简化了其余部分的计算。）

现在我们已经求出了 (9.53) 中的每一个 $\Sigma$，把它们合在一起就得到了 Golomb 问题的答案：
$$
S_n = \frac{\pi^2}6\ln n + \gamma - \frac3{8n} + O\!\left(\frac1{n^2}\right). \tag{9.54}
$$

注意这个结果的增长速度比我们最初粗略估计的 $C(\log n)^2$ 要慢。有时候离散和并不服从连续直观给出的预期。

**问题 6：大和函数 $\Phi$**
在第 4 章末尾我们看到，法雷序列 $F_n$ 中的分数个数为 $1+\Phi(n)$，其中
$$
\Phi(n) = \phi(1)+\phi(2)+\cdots+\phi(n).
$$
并且在式 (4.62) 中证明了
$$
\Phi(n) = \frac12\sum_{k\ge1}\mu(k)\left\lfloor\frac nk\right\rfloor
\left\lfloor 1+\frac nk\right\rfloor. \tag{9.55}
$$
现在我们来估计大 $n$ 时的 $\Phi(n)$。（正是这类和式，最初促使 Bachmann 发明了 $O$ 记号。）

量级分析告诉我们，$\Phi(n)$ 大致与 $n^2$ 成正比。如果最后一个因子只是 $\lfloor n/k\rfloor$ 而不是 $\lfloor 1+n/k\rfloor$，就有 $|\Phi(n)| \le \frac12\sum_{k\ge1}\left\lfloor\frac nk\right\rfloor^2\le \frac12\sum_{k\ge1}\left(\frac nk\right)^2= \frac{\pi^2}{12}n^2$，因为莫比乌斯函数 $\mu(k)$ 只能是 $-1,0,+1$。最后那个“$1+$”额外增加了 $\sum_{k\ge1}\mu(k)\lfloor n/k\rfloor$；但当 $k>n$ 时它为 0，所以绝对值不超过 $nH_n=O(n\log n)$。

这一初步分析提示我们宜写成：
$$
\begin{aligned}
\Phi(n)&= \frac12\sum_{k=1}^n\mu(k)
\left( \left\lfloor\frac nk\right\rfloor + O(1) \right)^2 \\
&= \frac12\sum_{k=1}^n\mu(k) \left( \left\lfloor\frac nk\right\rfloor^2 + O\!\left(\frac nk\right) \right) \\
&= \frac12\sum_{k=1}^n\mu(k)\left(\frac nk\right)^2+ \sum_{k=1}^n O\!\left(\frac nk\right) \\
&= \frac12\sum_{k=1}^n\frac{\mu(k)n^2}{k^2} + O(n\log n).
\end{aligned}
$$

这样就去掉了取整符号。剩下的问题是把无取整的和 $\frac12\sum_{k=1}^n\mu(k)n^2/k^2$ 精确到 $O(n\log n)$；换句话说，要把 $\sum_{k=1}^n\mu(k)/k^2$ 精确到 $O(n^{-1}\log n)$。这很容易：直接把和延拓到 $k=\infty$ 即可，因为新增项满足
$$
\sum_{k>n}\frac{\mu(k)}{k^2}
= O\!\left(\sum_{k>n}\frac1{k^2}\right)
= O\!\left(\sum_{k>n}\frac1{k(k-1)}\right)
= O\!\left(\frac1n\right).
$$

在式 (7.89) 中我们已经证明 $\sum_{k\ge1}\mu(k)/k^z = 1/\zeta(z)$，因此 $\sum_{k\ge1}\frac{\mu(k)}{k^2} = \frac1{\zeta(2)} = \frac6{\pi^2}.$于是得到最终结果：
$$
\Phi(n) = \frac3{\pi^2}n^2 + O(n\log n). \tag{9.56}
$$

## 9.4 TWO ASYMPTOTIC TRICKS 两种渐进技巧
现在我们已经对 $O$ 记号的运算有了一定掌握，不妨从更高的视角回顾一下前面的做法。这样一来，在应对更困难的渐近问题时，我们就能掌握几件重要的武器。

**技巧 1：逐步逼近（Bootstrapping）**
在 9.3 节的问题 3 估计第 $n$ 个素数 $P_n$ 时，我们求解了形如
$$
P_n = n\ln P_n\bigl(1+O(1/\log n)\bigr)
$$
的渐近递推关系。我们先用递推得到较弱的结果 $O(n^2)$，再由此推出 $P_n = n\ln n + O(n)$。这是一种通用方法的特例，称为**逐步逼近法**：先从一个粗糙估计出发，把它代回递推式，反复迭代，通常就能得到越来越好的近似，就像“提着鞋带把自己拉起来”一样。

下面再用一个问题很好地演示逐步逼近：
生成函数
$$
G(z) = \exp\!\left(\sum_{k\ge1}\frac{z^k}{k^2}\right) \tag{9.57}
$$

的系数 $g_n = [z^n]G(z)$ 在 $n\to\infty$ 时的渐近值是多少？对 $z$ 求导：
$$
G'(z) = \sum_{n\ge0}n g_n z^{n-1} = \left(\sum_{k\ge1}\frac{z^{k-1}}{k}\right)G(z).
$$
比较两边 $z^{n-1}$ 的系数，得到递推式：
$$
n g_n = \sum_{0\le k<n}\frac{g_k}{n-k}. \tag{9.58}
$$

我们的问题等价于：在初值 $g_0=1$ 下，求递推式 (9.58) 解的渐近公式。
前几项的值为：

| n | 0 | 1 |  2  |   3    |    4     |     5      |      6       |
|---|---|---|-----|--------|----------|------------|--------------|
| $g_n$ | 1 | 1 | 3/4 | 19/36 | 107/288 | 641/2400 | 51103/259200 |

看不出明显规律，整数序列 $\langle n!^2 g_n\rangle$ 也没有出现在 Sloane 手册 [330] 中。因此 $g_n$ 几乎不可能有闭式，我们能指望的最好结果就是渐近公式。

第一个突破口是观察到：对所有 $n\ge0$ 有 $0<g_n\le1$，用归纳法很容易证明。于是我们有了起点：
$$
g_n = O(1).
$$

这个估计可以用来给逐步逼近“启动泵”：把它代入 (9.58) 右边，得到
$$
n g_n
= \sum_{0\le k<n}\frac{O(1)}{n-k}
= H_n\,O(1) = O(\log n);
$$
因此对 $n>1$ 有
$$
g_n = O\!\left(\frac{\log n}{n}\right).
$$

我们可以继续逐步逼近：
$$
\begin{aligned}
n g_n
&= \frac1n + \sum_{0<k<n}\frac{O\bigl((1+\log k)/k\bigr)}{n-k} \\
&= \frac1n+ \sum_{0<k<n}\frac{O(\log n/k)}{n-k} \\
&= \frac1n + \sum_{0<k<n}\left(\frac1k+\frac1{n-k}\right) \frac{O(\log n)}n \\
&= \frac1n + \frac2n H_{n-1}\,O(\log n) = \frac1n O(\log n)^2,
\end{aligned}
$$

于是得到
$$
g_n = O\!\left(\left(\frac{\log n}{n}\right)^{\!2}\right). \tag{9.59}
$$

这个过程会一直持续下去吗？也许我们会得到对所有 $m$ 都成立的 $g_n = O(n^{-1}(\log n)^m)$。

其实并不会，我们已经到了收益递减的阶段。下一次逐步逼近会涉及和式
$$
\sum_{0<k<n}\frac1{k^2(n-k)}
= \sum_{0<k<n}\left(\frac1{n k^2}+\frac1{n^2 k}+\frac1{n^2(n-k)}\right) \\
= \frac1n H_{n-1}^{(2)}+\frac2{n^2}H_{n-1},
$$

它是 $\Omega(n^{-1})$ 的；因此我们不可能得到低于 $\Omega(n^{-2})$ 的 $g_n$ 估计。

事实上，现在我们对 $g_n$ 已经有足够了解，可以使用老技巧——**提取主部**：
$$
\begin{aligned}
n g_n
&= \sum_{0\le k<n}\frac{g_k}n + \sum_{0\le k<n}g_k\left(\frac1{n-k}-\frac1n\right) \\
&= \frac1n\sum_{k\ge0}g_k - \frac1n\sum_{k\ge n}g_k + \frac1n\sum_{0\le k<n}\frac{k g_k}{n-k}.
\end{aligned}
\tag{9.60}
$$

这里第一个和就是 $G(1) = \exp\!\left(1+\frac14+\frac19+\cdots\right) = e^{\pi^2/6}$， 因为 $G(z)$ 在 $|z|\le1$ 上处处收敛。第二个和是第一个的尾部；利用 (9.59) 可以给出上界：
$$
\sum_{k\ge n}g_k
= O\!\left(\sum_{k\ge n}\frac{(\log k)^2}{k^2}\right)
= O\!\left(\frac{(\log n)^2}{n}\right).
$$

这个最后的估计成立，是因为例如：
$$
\sum_{k>n}\frac{(\log k)^2}{k^2}
< \sum_{m\ge1}\sum_{n^m<k\le n^{m+1}}
\frac{(\log n^{m+1})^2}{k(k-1)}
< \sum_{m\ge1}\frac{(m+1)^2(\log n)^2}{n^m}.
$$
（习题 54 会讨论估计这类尾部和的更一般方法。）

(9.60) 中的第三个和为
$$
O\!\left(\sum_{0\le k<n}\frac{(\log n)^2}{k(n-k)}\right)
= O\!\left(\frac{(\log n)^3}{n}\right),
$$
用我们已经熟悉的方法即可证明。于是 (9.60) 给出：
$$
g_n = \frac{e^{\pi^2/6}}{n^2}+ O\!\left(\frac{(\log n)^3}{n}\right). \tag{9.61}
$$

最后，把这个式子代回递推式再做一次逐步逼近，可得：
$$
g_n = \frac{e^{\pi^2/6}}{n^2}+ O\!\left(\frac{\log n}{n^3}\right). \tag{9.62}
$$
（习题 23 会进一步探究剩余 $O$ 项内部的结构。）

**技巧 2：尾部交换（Trading tails）**
我们推导式 (9.62) 的思路，与推导 $\Phi(n)$ 的渐近式 (9.56) 颇为相似：两者都是从有限和出发，最终通过考虑**无穷和**得到渐近结果。我们不能简单地在通项里直接加 $O$ 就把和延到无穷；必须小心处理：对小的 $k$ 用一种近似，对大的 $k$ 用另一种。

这些推导都是一个重要三步渐近求和法的特例，下面我们更一般地介绍它。每当我们要估计 $\sum_k a_k(n)$ 时，都可以尝试如下思路：

1. 先把求和拆成两个不相交的范围：$D_n$（主部）和 $T_n$（尾部）。对充分大的 $n$，$D_n$ 上的和应是“主导部分”，包含足够多决定和式有效数字的项；另一部分 $T_n$ 只是“尾部”，对总和贡献很小。

2. 对 $k\in D_n$，找到渐近展开 $a_k(n) = b_k(n) + O\bigl(c_k(n)\bigr)$ 这个 $O$ 估计只需要在 $D_n$ 内成立，不必在 $T_n$ 内成立。

3. 接着证明下面三个和都足够小：
$$\Sigma_a(n) = \sum_{k\in T_n}a_k(n),\quad
\Sigma_b(n) = \sum_{k\in T_n}b_k(n),\quad   \\
\Sigma_c(n) = \sum_{k\in D_n}\bigl|c_k(n)\bigr|. \tag{9.63}$$

如果这三步都能顺利完成，我们就得到了很好的估计：
$$\sum_{k\in D_n\cup T_n}a_k(n) = \sum_{k\in D_n\cup T_n}b_k(n) + O\bigl(\Sigma_a(n)\bigr) + O\bigl(\Sigma_b(n)\bigr) + O\bigl(\Sigma_c(n)\bigr).$$

原理如下：我们可以“切掉”原和的尾部，在需要精确估计的主部 $D_n$ 上做近似：
$$\sum_{k\in D_n}a_k(n)
= \sum_{k\in D_n}\bigl(b_k(n)+O(c_k(n))\bigr)
= \sum_{k\in D_n}b_k(n) + O\bigl(\Sigma_c(n)\bigr).$$

而尾部可以直接换成另一个尾部，哪怕新尾部对旧尾部近似很差也没关系，因为尾部本身不重要：
$$
\begin{aligned}
\sum_{k\in T_n}a_k(n) &= \sum_{k\in T_n}\bigl(b_k(n)-b_k(n)+a_k(n)\bigr) \\
&= \sum_{k\in T_n}b_k(n) + O\bigl(\Sigma_b(n)\bigr) + O\bigl(\Sigma_a(n)\bigr).
\end{aligned}
$$

比如在估计式 (9.60) 中的和时，我们取
$$
\begin{aligned}
a_k(n) &= [0\le k<n]g_k/(n-k),\\
b_k(n) &= g_k/n,\\
c_k(n) &= k g_k/n(n-k);
\end{aligned}
$$
求和范围是
$$D_n = \{0,1,\dots,n-1\},\quad T_n = \{n,n+1,\dots\};$$

并得到
$$\Sigma_a(n)=0,\quad
\Sigma_b(n)=O\bigl((\log n)^2/n^2\bigr),\quad
\Sigma_c(n)=O\bigl((\log n)^3/n^2\bigr),$$
由此推出了 (9.61)。

类似地，在估计 (9.55) 中的 $\Phi(n)$ 时，我们取
$$
a_k(n) = \mu(k)\lfloor n/k\rfloor\lfloor 1+n/k\rfloor,\quad
b_k(n) = \mu(k)n^2/k^2,\quad
c_k(n) = n/k; \\
D_n = \{1,2,\dots,n\},\quad T_n = \{n+1,n+2,\dots\}.
$$
并由 $\Sigma_a(n)=0$，$\Sigma_b(n)=O(n)$，$\Sigma_c(n)=O(n\log n)$ 推出了 (9.56)。

再来看一个尾部交换特别有效的例子。（与之前不同，这个例子完整展示了一般情形，其中 $\Sigma_a(n)=0$。）我们求渐近值：
$$
L_n = \sum_{k\ge0}\frac{\ln(n+2^k)}{k!}
$$

因为分母是 $k!$，所以主要贡献来自 $k$ 较小的部分。在这个范围内：
$$
\ln(n+2^k) = \ln n + \frac{2^k}{n} - \frac{2^{2k}}{2n^2} + O\!\left(\frac{2^{3k}}{n^3}\right). \tag{9.64}
$$

可以证明这个估计在 $0\le k<\lfloor\lg n\rfloor$ 时成立，因为被 $O$ 吸收的截断项满足
$$
\sum_{m\ge3}\frac{2^{km}}{m n^m}
\le \frac{2^{3k}}{n^3}\sum_{m\ge3}\frac{2^{k(m-3)}}{n^{m-3}}
\le \frac{2^{3k}}{n^3}\left(1+\frac12+\frac14+\cdots\right)
= \frac{2^{3k}}{n^3}\cdot2.
$$
（在此范围内 $2^k/n\le 2^{\lfloor\lg n\rfloor-1}/n\le\frac12$。）

于是可以用上面的三步法，取
$$
\begin{aligned}
a_k(n) &= \ln(n+2^k)/k!,\\
b_k(n) &= \bigl(\ln n + 2^k/n - 4^k/(2n^2)\bigr)/k!,\\
c_k(n) &= 8^k/(n^3 k!), \\
D_n &= \{0,1,\dots,\lfloor\lg n\rfloor-1\}, \\
T_n &= \{\lfloor\lg n\rfloor,\lfloor\lg n\rfloor+1,\dots\}.
\end{aligned}
$$
只需对 (9.63) 中的三个 $\Sigma$ 给出好的界，就能得到$\sum_{k\ge0}a_k(n)\approx\sum_{k\ge0}b_k(n)$。

主部中的误差 $\Sigma_c(n) = \sum_{k\in D_n}\frac{8^k}{n^3 k!} < \sum_{k\ge0}\frac{8^k}{n^3 k!} = e^8/n^3$ 可记为 $O(n^{-3})$。新尾部的误差
$$
\begin{aligned}
|\Sigma_b(n)| &= \left|\sum_{k\ge\lfloor\lg n\rfloor}b_k(n)\right| \\
&< \sum_{k\ge\lfloor\lg n\rfloor}\frac{\ln n+2^k+4^k}{k!}    \\
&< \frac{\ln n+2^{\lfloor\lg n\rfloor}+4^{\lfloor\lg n\rfloor}}{\lfloor\lg n\rfloor!}\sum_{k\ge0}\frac{4^k}{k!} = O\!\left(\frac{n^2}{\lfloor\lg n\rfloor!}\right).
\end{aligned}
$$

因为 $\lfloor\lg n\rfloor!$ 增长比任何 $n$ 的幂次都快，这个极小的误差完全被 $\Sigma_c(n)=O(n^{-3})$ 覆盖。来自原尾部的误差
$$
\Sigma_a(n) = \sum_{k\ge\lfloor\lg n\rfloor}a_k(n) < \sum_{k\ge\lfloor\lg n\rfloor}\frac{\ln n + 2^k}{k!}
$$
更小。

最后，$\sum_{k\ge0}b_k(n)$ 很容易求出闭式，于是得到想要的渐近公式：
$$
\sum_{k\ge0}\frac{\ln(n+2^k)}{k!} = e\ln n + \frac{e^2}{n} - \frac{e^4}{2n^2} + O\!\left(\frac1{n^3}\right). \tag{9.65}
$$

我们所用的方法可以清楚地推广到一般情形：
$$
\sum_{k\ge0}\frac{\ln(n+2^k)}{k!} = e\ln n + \sum_{k=1}^{m-1}\frac{(-1)^{k+1}e^{2^k}}{k n^k} + O\!\left(\frac1{n^m}\right), \tag{9.66}
$$
对任意固定的 $m>0$ 成立。（这是一个级数的截断，若令 $m\to\infty$ 则对所有固定 $n$ 发散。）

我们的解法里只有一点小遗憾：太过谨慎了。之前是在 $k<\lfloor\lg n\rfloor$ 的假设下推出 (9.64)，但习题 53 可以证明，这个估计其实对**所有** $k$ 都成立。如果早知道这个更强的结论，就不必使用尾部交换技巧，可以直接得到最终公式！但在后面遇到的问题里，尾部交换会是唯一靠谱的方法。

## 9.5 EULER’S SUMMATION FORMULA 欧拉求和公式
接下来我们介绍下一个技巧——事实上也是本书将要讨论的最后一种重要方法——转向一种用于逼近和式的通用方法，该方法由莱昂哈德·欧拉于 1732 年首次发表 [101]。（这个思想有时也与科林·麦克劳林的名字联系在一起，他是爱丁堡的数学教授，不久后独立发现了这一方法 [263, 第 305 页]。）

公式如下：
$$
\sum_{a\le k<b} f(k) = \int_a^b f(x)\,dx + \sum_{k=1}^m \frac{B_k}{k!}\,f^{(k-1)}(x)\bigg|_a^b + R_m, \tag{9.67}
$$
其中
$$
R_m = (-1)^{m+1}\int_a^b \frac{B_m\bigl(\{x\}\bigr)}{m!}\,f^{(m)}(x)\,dx,   \begin{array}{c} \text{integers } a\le b； \\ \text{integers} m\ge 1.\end{array} \tag{9.68}
$$

左边是我们通常想要计算的一类和式，右边则是该和式包含积分与导数的另一种表达式。如果 $f(x)$ 是足够“光滑”的函数，它具有 $m$ 阶导数 $f'(x),\dots,f^{(m)}(x)$，那么这个公式就是一个恒等式。右边通常是左边和式的极佳近似，因为余项 $R_m$ 往往很小。例如我们将会看到，斯特林的 $n!$ 近似公式是欧拉求和公式的推论；调和数 $H_n$ 的渐近近似也是如此。

式 (9.67) 中的 $B_k$ 是我们在第 6 章遇到的伯努利数；式 (9.68) 中的 $B_m(\{x\})$ 是第 7 章见过的伯努利多项式。记号 $\{x\}$ 表示小数部分 $x-\lfloor x\rfloor$，与第 3 章一致。欧拉求和公式可以说把所有内容都整合在了一起。

我们回顾一下较小的伯努利数，把它们放在欧拉公式附近总是很方便：
$$
\begin{aligned}
B_0 &=1,\; B_1=-\frac12,\; B_2=\frac16,\; B_4=-\frac1{30},\; B_6=\frac1{42},\; B_8=-\frac1{30}; \\
B_3 &=B_5=B_7=B_9=B_{11}=\cdots=0.
\end{aligned}
$$

雅各布·伯努利在研究整数幂和时发现了这些数，而欧拉公式解释了其缘由：若令 $f(x)=x^{m-1}$，则 $f^{(m)}(x)=0$，于是 $R_m=0$，式 (9.67) 简化为
$$
\begin{aligned}
\sum_{a\le k<b} k^{m-1} &= \left.\frac{x^m}{m}\right|_a^b + \sum_{k=1}^m \frac{B_k}{k!}\,(m-1)^{\underline{k-1}}\,x^{m-k}\bigg|_a^b \\
&= \frac1m\sum_{k=0}^m \binom{m}{k}B_k\bigl(b^{m-k}-a^{m-k}\bigr).
\end{aligned}
$$

例如取 $m=3$，就得到我们最熟悉的求和式：
$$
\sum_{0\le k<n} k^2 = \frac13\left( \binom30B_0n^3 +\binom31B_1n^2 +\binom32B_2n \right) = \frac{n^3}{3}-\frac{n^2}{2}+\frac{n}{6}.
$$

（这是本书最后一次推导这个著名公式。）
在证明欧拉公式之前，我们先从较高层面理解（源自拉格朗日 [234]）：为什么应该存在这样的公式。第 2 章定义了差分算子 $\Delta$，并说明 $\sum$ 是 $\Delta$ 的逆，正如 $\int$ 是求导算子 $D$ 的逆。我们可以用泰勒公式把 $\Delta$ 用 $D$ 表示如下：
$$
f(x+\varepsilon)=f(x)+\frac{f'(x)}{1!}\varepsilon+\frac{f''(x)}{2!}\varepsilon^2+\cdots.
$$

令 $\varepsilon=1$ 可得
$$
\begin{aligned}
\Delta f(x)&=f(x+1)-f(x)  \\
&= f'(x)/1!+f''(x)/2!+f'''(x)/3!+\cdots \\
&= (D/1!+D^2/2!+D^3/3!+\cdots)f(x)=(e^D-1)f(x). \tag{9.69}
\end{aligned}
$$

这里 $e^D$ 表示微分算子 $1+D/1!+D^2/2!+D^3/3!+\cdots$。因为 $\Delta=e^D-1$，所以逆算子 $\sum=1/\Delta$ 应为 $1/(e^D-1)$；而由表 351 可知 $z/(e^z-1)=\sum_{k\ge0}B_k z^k/k!$ 是包含伯努利数的幂级数。因此
$$
\sum
= \frac{B_0}{D}+\frac{B_1}{1!}+\frac{B_2}{2!}D+\frac{B_3}{3!}D^2+\cdots
= \int+\sum_{k\ge1}\frac{B_k}{k!}D^{k-1}. \tag{9.70}
$$
将该算子等式作用于 $f(x)$ 并加上上下限，得到
$$
\sum_a^b f(x)\delta x
= \int_a^b f(x)dx+\sum_{k\ge1}\frac{B_k}{k!}f^{(k-1)}(x)\bigg|_a^b, \tag{9.71}
$$

这正是不带余项的欧拉求和公式 (9.67)。（事实上欧拉并未考虑余项，直到 1823 年 S. D. Poisson [295] 发表关于近似求和的重要论文前，都无人考虑余项。余项非常重要，因为无穷级数 $\sum_{k\ge1}(B_k/k!)f^{(k-1)}(x)\big|_a^b$ 往往发散。我们对 (9.71) 的推导是纯形式的，未考虑收敛性。）

现在证明带余项的 (9.67)。只需证明 $a=0,b=1$ 的情形：
$$
f(0)=\int_0^1 f(x)dx+\sum_{k=1}^m\frac{B_k}{k!}f^{(k-1)}(x)\bigg|_0^1
-(-1)^m\int_0^1\frac{B_m(x)}{m!}f^{(m)}(x)dx,
$$
因为对任意整数 $l$，将 $f(x)$ 换成 $f(x+l)$ 可得
$$
f(l)=\int_l^{l+1}f(x)dx+\sum_{k=1}^m\frac{B_k}{k!}f^{(k-1)}(x)\bigg|_l^{l+1}
-(-1)^m\int_l^{l+1}\frac{B_m(\{x\})}{m!}f^{(m)}(x)dx.
$$
一般公式 (9.67) 只是该等式在 $a\le l<b$ 上的求和，因为中间项会完美地望远镜抵消。

$a=0,b=1$ 的情形对 $m$ 归纳证明，从 $m=1$ 开始：
$$
f(0)=\int_0^1 f(x)dx-\frac12\bigl(f(1)-f(0)\bigr)
+\int_0^1\Bigl(x-\frac12\Bigr)f'(x)dx.
$$


