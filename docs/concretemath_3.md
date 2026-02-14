# 3. Integer Functions 整数函数

整数构成了离散数学的基石，我们经常需要将分数或任意实数转换为整数。本章的目标是熟悉并熟练掌握此类转换，并了解它们的一些显著性质。


## 3.1 FLOORS AND CEILINGS

我们首先介绍下取整（最大整数）和上取整（最小整数）整数函数，其定义域为所有实数 $x$ ，如下所示：
```math
\lfloor x\rfloor = 小于或等于x的最大整数 \\
\lceil x\rceil = 大于或等于x的最小整数         \tag{3.1}
```

Kenneth E. Iverson 在20世纪60年代初引入了这种记法，以及 $floor$ 和 $ceiling$ 这两个名称[191，第12页]。他发现排版人员可以通过削减 [ 和 ] 的顶部和底部来处理这些符号。他的记法已变得足够流行，以至于在技术论文中现在可以直接使用 $floor$ 和 $ceiling$ 括号，而无需解释其含义。直到最近，人们大多习惯用 [x] 来表示不大于 x 的最大整数，却很少有针对最小整数函数的良好等价表示。一些作者甚至尝试使用 ']x[' ，但收效甚微。

除了表示法上的差异，函数本身也存在差异。例如，一些袖珍计算器具有 $INT$ 函数，其定义为：当 $x$ 为正时，$\lfloor x\rfloor$；当 $x$ 为负时， $\lceil x\rceil$。这些计算器的设计者可能希望他们的 $INT$ 函数满足恒等式 $INT(−x) = −INT(x)$。不过，我们还是坚持使用我们的 $floor$ 和 $ceiling$ 函数，因为它们比这个恒等式具有更优的性质。

通过凝视这张插图，我们可以观察到关于 $floors$ 和 $ceilings$ 的几个事实。首先，由于 $floor$ 函数位于或低于对角线 $f(x) = x$ 之下，我们有 $\lfloor x\rfloor\le x$；同样地， $\lceil x\rceil\ge x$。（当然，这一点从定义中就已十分明显。）这两个函数在整数点上完全相等：
```math
\lfloor x\rfloor=x\iff x\ is\ an\ integer\iff\lceil x\rceil=x 
```

我们使用符号 $\iff$ 表示“当且仅当”。此外，当它们不同时，$ceilings$ 恰好比 $floors$ 高 1：
```math
\lfloor x\rfloor-\lceil x\rceil= [x\ is\ not\ an\ integer] \tag{3.2}
```

如果我们把对角线向下平移一个单位，它将完全位于 $floors$ 函数下方，因此 $x − 1 < \lfloor x\rfloor$；同样 $x + 1 > \lceil x\rceil$。综合这些观察结果，我们得到:
```math
x-1 < \lfloor x\rfloor\le\lceil x\rceil<x+1. \tag{3.3}
```

最后，这些函数互为关于两个轴的反射：
```math
\lfloor -x\rfloor=-\lceil x\rceil; \lceil -x\rceil=-\lfloor x\rfloor. \tag{3.4}
```

因此，二者之间可以轻松地相互表达。这一事实有助于解释为什么上取整函数曾经没有自己的符号。但我们经常遇到上取整的情况，足以证明有必要为它们赋予特殊的符号，正如我们已经为上升幂和下降幂采用了特殊符号一样。数学家们长期以来一直使用正弦和余弦、正切和余切、正割和余割、最大值和最小值；现在，我们也有了下取整和上取整。

为了真正证明关于 $floor$ 和 $ceil$ 函数的性质，而不仅仅是通过图形观察这些事实，以下四条规则尤其有用：
```math
\lfloor x\rfloor = n \iff n\le x< n+1, (a)\\
\lfloor x\rfloor = n \iff x-1 <n\le x, (b)\\
\lceil x\rceil = n \iff n-1< x\le n, (c)\\
\lceil x\rceil = n \iff x\le n<x+1, (d) \tag{3.5}
```

我们假设在所有四种情况下， $n$ 都是整数，且 $x$ 是实数。规则 (a) 和 (c) 是定义 (3.1) 的直接推论；规则 (b) 和 (d) 与此相同，只是不等式重新排列，使 $n$ 处于中间位置。

可以将整数项移入或移出下限（或上限）：
```math
\lfloor x+n\rfloor= \lfloor x\rfloor + n, integer\ n \tag{3.6}
```

因为规则 (3.5(a)) 说明，该断言等价于不等式 $\lfloor x\rfloor + n\le x+n< \lfloor x\rfloor+n+1$。但类似这样的操作，比如提取常数因子，并不能普遍适用。例如，我们有 $\lfloor nx\rfloor\ne n\lfloor x\rfloor$，当 $n = 2$ 且 $x = 1/2$ 时。这意味着 $floor$ 和 $ceil$ 括号相对来说不够灵活。通常情况下，如果我们能去掉它们，或者至少能在它们存在时证明一些东西，我们就已经很满足了。

事实证明，在许多情况下，$floor$ 和 $ceil$ 括号都是多余的，因此我们可以随意插入或删除它们。例如，实数与整数之间的任何不等式都等价于整数之间的下取整或上取整不等式：
```math
x<n \iff \lfloor x\rfloor<n, (a)\\
n<x \iff n<\lceil x\rceil, (b)\\
x\le n \iff \lceil x\rceil\le n, (c)\\
n\le x \iff n\le\lfloor x\rfloor. (d) \tag{3.7}
```

这些规则很容易证明。例如，如果 $x < n$，那么显然 $\lfloor x\rfloor<n$，因为 $\lfloor x\rfloor\le x$。反之，如果 $\lfloor x\rfloor<n$，那么我们必然有 $x < n$，因为 $x < \lfloor x\rfloor+ 1\ and\ \lfloor x\rfloor+ 1\le n$.

如果(3.7)中的四条规则像它们的证明一样容易记住，那就太好了。每个不带向下取整或向上取整的不等式都对应于带有下界或上界的相同不等式；但在决定二者哪个合适之前，我们需要三思。

$x$ 与 $\lfloor x\rfloor$ 之间的差值称为 $x$ 的小数部分，它在应用中出现的频率足够高，值得拥有自己的符号：
```math
\{x\} = x-\lfloor x\rfloor. \tag{3.8}
```

我们有时称 $\lfloor x\rfloor$ 为 $x$ 的整数部分，因为 $x=\lfloor x\rfloor+\{x\}$。如果一个实数 $x$ 可以写成 $x=n+\theta$ 的形式，其中 $n$ 是整数且  $0\le \theta < 1$，那么根据(3.5(a))，我们可以得出 $n=\lfloor x\rfloor$ 且 $\theta=\{x\}$.


恒等式(3.6)在 $n$ 为任意实数时并不成立。但我们可以推断，一般情况下， $\lfloor x+y\rfloor$ 只有两种可能：如果我们写 $x=\lfloor x\rfloor+\{x\}$ 且 $y=\lfloor y\rfloor+\{y\}$，则有 $\lfloor x+y\rfloor=\lfloor x\rfloor + \lfloor y\rfloor + \lfloor\{x+y\}\rfloor$。又因为 $0\le \{x\}+\{y\} < 2$，我们发现，有时 $\lfloor x+y\rfloor$ 等于 $\lfloor x\rfloor + \lfloor y\rfloor$，否则它等于 $\lfloor x\rfloor + \lfloor y\rfloor+1$。


## 3.2 FLOOR/CEILING APPLICATIONS
我们现在已经了解了处理 $floor$ 和 $ceil$ 的基本工具。让我们开始用它们解决一个简单的问题：$\lceil \lg 35\rceil$ 是多少？（根据爱德华·M·莱因戈尔德的建议，我们用 $\lg$ 表示以2为底的对数。）嗯，由于 $2^5<35\le 2^6$，我们可以取对数得到 $5<\lg 35\le 6$；因此，关系式(3.5(c))告诉我们 $\lceil \lg 35\rceil = 6$.

请注意，数字 $35$ 用基数 $2$ 表示时是 $6$ 位长：$35 = (100011)_2$。那么，是否总是成立 $\lceil \lg n\rceil = 6$ 是 $n$ 用二进制表示时的位数呢？并不完全正确。我们还需要六位来表示 $32 = (100000)_2$。因此，$\lceil \lg n\rceil = 6$ 并不是这个问题的正确答案。（它仅在 $n$ 是 $2$ 的幂时出错，但这种情况有无穷多。）我们可以通过认识到每个数 $n$ 需要 $m$ 位来写，使得 $2^{m−1}\le n < 2^m$；从而（3.5(a)）告诉我们 $m-1 = \lfloor \lg n\rfloor$，所以 $m = \lfloor \lg n\rfloor +1$。也就是说，对于所有 $n > 0$，我们需要 $\lfloor\lg n\rfloor +1$ 位来用二进制表示 $n$。或者，类似的推导也可以得到答案 $\lceil\lg(n+1)\rceil$；如果愿意承认写 $n = 0$ 用二进制表示需要零位，那么这个公式对 n = 0 也成立。

接下来我们来看一下包含多个向上取整或向下取整的表达式。$\lceil\lfloor x\rfloor\rceil$ 是什么？很简单 | 因为 $\lfloor x\rfloor$ 是一个整数， $\lceil\lfloor x\rfloor\rceil$ 就等于 $\lfloor x\rfloor$。因此，任何最内层是 $\lfloor x\rfloor$，并被任意数量的向上取整或向下取整包围的表达式也是如此。

这里有一道难度更高的问题：证明或证伪该断言：
```math
\lfloor\sqrt{\lfloor x\rfloor}\rfloor = \lfloor\sqrt{x}\rfloor, real\ x\ge 0 \tag{3.9}
```

当 $x$ 是整数时，显然等式成立，因为 $x=\lfloor x\rfloor$。在特殊情况下也存在等式： $\pi=3.14159\cdots$， $e=2.71828\cdots$，以及 ($\phi= (1 + \sqrt{5})/2 = 1.61803\cdots$)，因为我们得到 $1 = 1$。我们未能找到反例，这表明等式一般情况下成立，那么让我们试着证明它吧。

顺便说一下，当我们面对“证明或反驳”时，通常最好先尝试用反例来反驳，原因有两点：首先，反驳可能更容易（我们只需要一个反例）；其次，吹毛求疵能激发我们的创造力。即使给定的命题是正确的，我们在寻找反例的过程中往往也会自然而然地找到证明，一旦我们意识到为什么反例不可能存在。此外，保持怀疑态度也是有益健康的。

如果我们试图借助微积分证明 $\lfloor\sqrt{\lfloor x\rfloor}\rfloor = \lfloor\sqrt{x}\rfloor$，我们可能会先将 x分解成整数部分和小数部分： $\lfloor x\rfloor+\{x\}=n+\theta$ ，然后利用二项式定理展开平方根： $(n+\theta)^{1/2} = n^{1/2} + n^{−1/2}\theta/2 − n^{−3/2}\theta^2/8 +\cdots$。但这种方法会变得相当复杂。

使用我们开发的工具要容易得多。这里有一个可能的策略：某种方式下，先去掉外层的 $floor$ 函数和平方根 $\lfloor\sqrt{\lfloor x\rfloor}\rfloor$，再移除内层的 $floor$ 函数，然后把外层的值加回去，得到 $\lfloor\sqrt{x}\rfloor$。好的。我们令 $m=\lfloor\sqrt{\lfloor x\rfloor}\rfloor$，并调用(3.5(a))，得到 $m\le \sqrt{\lfloor x\rfloor}<m+1$。这样就去掉了外层的 $floor$ 括号，且没有丢失任何信息。由于这三个表达式都是非负的，我们对两边同时平方，得到 $m^2\le\sqrt{x}<(m + 1)^2$。这一步消除了平方根。接下来，我们利用(3.7(d))处理左边不等式，用(3.7(a))处理右边不等式，从而去掉 $floor$ 函数： $m^2\le x<(m + 1)^2$。现在，只需简单地反向推导，取平方根即可得到 $m\le \sqrt{x}<m+1$，再调用(3.5(a))，得到 $m=\lfloor\sqrt{x}\rfloor$。因此，$\lfloor\sqrt{\lfloor x\rfloor}\rfloor = m = \lfloor\sqrt{x}\rfloor$；该断言成立。类似地，我们也可以证明
```math
\lceil\sqrt{\lceil x\rceil}\rceil = \lceil\sqrt{x}\rceil, real\ x\ge 0
```

我们刚刚找到的证明并不严重依赖于平方根的性质。仔细观察会发现，我们可以推广这些思路并证明更多内容：设 $f(x)$ 是任意一个连续、单调递增的函数，且具有以下性质
```math
f(x) = integer \implies x = integer.
```

符号 $\implies$ 表示 $implies$。那么我们有
```math
\lfloor f(x)\rfloor = \lfloor f(\lfloor x\rfloor)\rfloor, \lceil f(x)\rceil = \lceil f(\lceil x\rceil)\rceil \tag{3.10}
```

无论何时，当 $f(x), f(\lfloor x\rfloor) , f(\lceil x\rceil)$ 都有定义时，我们来证明这一关于向上取整的一般性质。由于我们之前已经讨论过向下取整，而且向下取整的证明几乎相同，因此我们先证明这一性质。如果 $x = \lceil x\rceil$，则无需证明。否则， $x < \lceil x\rceil$，并且由于 $f$ 是递增的，所以 $f(x) < f(\lceil x\rceil)$。因此， $\lceil f(x)\rceil\le \lceil f(\lceil x\rceil)\rceil$，因为 $\lceil\rceil$ 是非递减的。如果 $\lceil f(x)\rceil< \lceil f(\lceil x\rceil)\rceil$，则必然存在一个数 $y$，使得 $x \le y < \lceil x\rceil$ 且 $f(y) = \lceil f(x)\rceil$，这是因为 $f$ 是连续的。根据 $f$ 的特殊性质，这个 $y$ 必然是整数。然而，$x$ 和 $\lceil x\rceil$ 之间不可能存在严格介于二者之间的整数。这种矛盾表明，我们必须有 $\lceil f(x)\rceil = \lceil f(\lceil x\rceil)\rceil$。

该定理的一个重要特例值得明确指出：
```math
\lfloor\frac{x+m}{n}\rfloor = \lfloor\frac{\lfloor x\rfloor+m}{n}\rfloor, \lceil\frac{x+m}{n}\rceil = \lceil\frac{\lceil x\rceil+m}{n}\rceil \tag{3.11}
```

如果 $m$ 和 $n$ 是整数，且分母 $n$ 为正数。例如，令 $m=0$；我们有 $\lfloor\lfloor\lfloor x/10 \rfloor/10 \rfloor/10 \rfloor = \lfloor x/1000\rfloor$。连续三次除以 $10$ 并舍弃小数部分，等同于除以 $1000$ 并丢弃余数。

我们现在来尝试证明或证伪另一个命题：
```math
\lceil\sqrt{\lfloor x\rfloor}\rceil \stackrel{?}{=} \lceil\sqrt{x}\rceil， real\ x\ge 0.
```

当 $x = \pi$ 且 $x = e$ 时，此方法有效；但当 $x = \phi$ 时，它会失效；因此我们知道，这在一般情况下并不成立。

在继续之前，让我们稍作离题，讨论一下数学书籍中可能出现的不同层次的问题：
**Level 1**. 给定一个明确的对象 $x$ 和一个明确的属性 $P(x)$，证明 $P(x)$ 为真。例如，“证明 $\lfloor\pi \rfloor = 3$。” 在这里，问题涉及寻找某个所谓事实的证明。

**Level 2**. 给定一个明确的集合 $X$ 和一个明确的性质 $P(x)$，证明对于所有 $x\in X$，$P(x)$ 都为真。例如，“证明对于所有实数 $x, \lfloor x\rfloor\le x$。” 再次，这个问题涉及寻找一个证明，但这次的证明必须是通用的。我们是在做代数，而不仅仅是算术。

**Level 3**. 给定一个显式集合 $X$ 和一个显式性质 $P(x)$，证明 或者反证，使得 $P(x)$ 对所有 $x\in X$ 成立。例如，“证明或反证：对于所有实数 $x\ge 0, \lceil\sqrt{\lfloor x\rfloor}\rceil=\lceil\sqrt{x}\rceil$。”这里存在额外一层不确定性；结果可能朝任何方向发展。这更贴近数学家日常面对的真实情况：那些被写进书里的断言往往是正确的，但新出现的命题则必须以怀疑的眼光看待。如果该陈述是错误的，我们的任务就是找到一个反例；如果该陈述是正确的，我们就必须像第二级那样找到一个证明。


**Level 4**. 给定一个明确的集合 $X$ 和一个明确的性质 $P(x)$，求一个 必要且充分条件 $Q(x)$，使得 $P(x)$ 为真。例如，“找出一个必要且充分的条件，使得 $\lfloor x\rfloor\le \lceil x\rceil$。”这个问题就是要找到 $Q$，使得 $P(x)\iff Q(x)$。当然，总有一个平凡的答案；我们可以取 $Q(x) = P(x)$。但隐含的要求是找到一个尽可能简单的条件。要发现一个简单的、可行的条件，需要一定的创造性。（例如，在本例中，“$\lfloor x\rfloor\le \lceil x\rceil\iff x $ 是整数。”）寻找 $Q(x)$ 所需的额外发现环节使这类问题更加困难，但也更贴近数学家在“现实世界”中所必须面对的情形。最后，当然，必须给出证明，说明 $P(x)$ 为真当且仅当 $Q(x)$ 为真。

**Level 5**. 给定一个明确的集合 $X$，找出其元素的一个有趣性质 $P(x)$。现在我们进入了纯粹研究的可怕领域，学生们可能会认为这里一片混乱。这可是真正的数学。教科书作者很少敢出第5级的问题。

闲话到此结束。但让我们把刚才讨论的最后一个问题从第3级转换到第4级：什么条件是必要且充分的，使得 $\lceil\sqrt{\lfloor x\rfloor}\rceil=\lceil\sqrt{x}\rceil$？我们已经观察到，当 $x = 3.142$时等式成立，但当 $x = 1.618$ 时则不成立；进一步实验表明，当 $x$ 介于 9 和 10 之间时，等式同样不成立。哦哈。没错。我们发现，只要 $m^2 < x < m^{2+1}$，就会出现反例，因为此时左边得到 $m$，而右边则是 $m+1$。在所有其他情况下，即当 $sqrt{x}$ 有定义时——也就是当 $x=0\ or\ m^2+1\le x\le (m+1)^2$ 时，等式都能成立。因此，以下陈述便是等式的必要且充分条件：要么 $x$ 是整数，要么 $sqrt{\lfloor x\rfloor}$ 不是实数。

对于我们的下一个问题，让我们来考虑一种由C. A. R. Hoare和Lyle Ramshaw提出的、用于表示实数轴上区间的新颖便捷的记法： $[\alpha\cdots \beta]$ 表示实数集合 $x$，使得 $\alpha\le x \le\beta$。这个集合被称为*闭区间*，因为它包含了两个端点 $\alpha$ 和 $\beta$。不包含任何端点的区间，用 $(\alpha\cdots \beta)$ 表示，由所有满足 $\alpha< x< \beta$ 的 $x$ 组成；这被称为*开区间*。而区间 $[\alpha\cdots \beta)$ 和 $(\alpha\cdots \beta)$，它们只包含一个端点，定义方式类似，并被称为*半开区间*。

这样的区间里包含多少个整数？半开区间更容易处理，所以我们从它开始。事实上，半开区间几乎总是比开区间或闭区间更 “好用”。例如，它们具有可加性—— 我们可以把半开区间 $[\alpha\cdots \beta)$ 和 $[\beta\cdots \gamma)$ 合并成 $[\alpha\cdots \gamma)$。如果是开区间就行不通，因为点 $\beta$ 会被排除掉；而闭区间也会出问题，因为 $\beta$ 会被算进去两次。

回到我们的问题。如果 $\alpha$ 和 $\beta$ 是整数，那么答案就很简单：此时 $[\alpha . . \beta)$ 包含 $\beta − \alpha$ 个整数 $\alpha, \alpha + 1, . . ., \beta − 1$，前提是 $\alpha\le \beta$。同样地， $(\alpha . . \beta]$ 在这种情况下也包含 $\beta − \alpha$ 个整数。但我们的问题更难，因为 $\alpha$ 和 $\beta$ 是任意实数。不过，我们可以将其转化为更容易解决的问题，因为
```math
\begin{aligned}
\alpha\le n< \beta &\iff \lceil\alpha\rceil\le n < \lceil\beta\rceil, \\
\alpha< n\le \beta &\iff \lfloor\alpha\rfloor<n\le \lfloor\beta\rfloor, 
\end{aligned}
```

当 $n$ 是一个整数时，根据（3.7）。右侧的区间具有整数端点，并且包含与左侧区间相同数量的整数，而左侧区间的端点是实数。因此，区间 $[\alpha\cdots \beta)$ 恰好包含 $\lceil\beta\rceil −\lfloor \alpha\rfloor$ 个整数，而 $(\alpha . . \beta]$  包含 $\lfloor\beta\rfloor -\lceil\alpha\rceil$ 个整数。这种情况正是我们实际上希望引入下取整或上取整符号的时候，而不是将其去除。

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
$floor$ 和 $ceiling$ 为研究增添了有趣的新维度关于递归关系。让我们首先看看递归
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
while\ N>n\ do\ N:=\lfloor\frac{N-n-1}{2}\rfloor + N - n; \\
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
s(\alpha, n, v) = -nv + \lfloor n\alpha\rfloor b + \sum_{0\le j<\lfloor n\alpha\rfloor}(\lfloor j\alpha'\rfloor - \lfloor j\alpha'-v'\rfloor) - S + \{0\ or\ 1\}.
```

挺有意思的。我们并没有得到闭式，反而得到了一个和式，它看上去和 $s(\alpha, n, v)$ 十分相似，只是参数不同：用 $\alpha'$ 代替了 $\alpha$，用 $\lfloor n\alpha\rfloor$ 代替了 $n$，用 $v'$ 代替了 $v$。这样一来，我们就能得到关于 $s(\alpha, n, v)$ 的一个递推关系，而这（有望）进一步导出偏差 $D(\alpha,n)$ 的递推关系。这就意味着，我们也要亲自上阵
```math
s(\alpha', \lceil n\alpha\rceil, v') = \sum_{0\le j<\lceil n\alpha\rceil}(\lfloor j\alpha'\rfloor-\lfloor j\alpha'-v'\rfloor-v').
```

推导一番了
```math
s(\alpha, n, v) =  -nv + \lceil n\alpha\rceil b -\lceil n\alpha\rceil v' - s(\alpha', \lceil n\alpha\rceil, v')- S + \{0\ or\ 1\}.
```

回想一下 $b−v'=v\alpha^{−1}$，我们会发现，如果把 $\lceil n\alpha\rceil(b−v')$ 替换成 $n\alpha(b−v')=nv$，所有式子都会变得极其简洁：
```math
s(\alpha, n, v) =  -s(\alpha', \lceil n\alpha\rceil, v') -S + \epsilon + \{0\ or\ 1\}.
```

这里 $\epsilon$ 是一个不超过 $v\alpha^{−1}$ 的正误差。习题 18 同样证明了，$S$ 也介于 $0$ 和 $\lceil v\alpha^{−1}\rceil$ 之间。我们还可以从和式中去掉 $j=\lceil n\alpha^{−1}\rceil−1=\lfloor j\alpha'\rfloor$ 对应的项，因为它的贡献要么是 $v'$，要么是 $v'−1$。
因此，如果对所有 $v$ 取绝对值的最大值，我们就得到：
```math
D(\alpha, n)\le D(\alpha',\lfloor \alpha n\rfloor) + \alpha^{-1} + 2. \tag{3.31}
```

在后续章节中我们将学到的方法，可以让我们从这个递推式得出结论：当 $n$ 足够大时，$D(\alpha, n)$ 始终远小于 $n$。因此，定理 (3.28) 不仅成立，还可以加强：它收敛到极限的速度非常快。

这可真是一场对和式、下取整与上取整的花式操作演练。那些不习惯于 **证明误差很小** 的读者，可能很难相信，面对如此怪异的和式，居然有人有勇气一路推导下去。但仔细再看就会发现，整个计算过程中其实贯穿着一条简单清晰的主线。核心思想是：某个包含 $n$ 项的和 $s(\alpha, n, v)$，可以被化简为一个至多只有 $\lfloor \alpha n\rfloor$ 项的同类和式。除了在边界附近会留下一点点微小的余项之外，其他所有项都会相互抵消。

现在让我们深呼吸，再来算一个和式。它并不简单，但相比我们刚才做的那些，它有一个巨大的优点：最终能得到闭式，这样我们就能轻松检验结果对不对。我们现在的目标，是把式 (3.26) 中的和式推广，求出下面这个表达式：
```math
\sum_{0\le <m} \bigg\lfloor\frac{nk+x}{m}\bigg\rfloor, integer\ m>0, integer\ n.
```

求出这个和式的闭式，比我们到目前为止做过的所有题目都更难（也许只比刚才那个偏差问题简单一点）。但它非常有启发性，所以本章剩下的内容，我们就专心把它啃下来。

跟往常一样，尤其是面对难题时，我们先从简单情形入手观察。$n=1$ 的特例就是公式 (3.26)，只是把 x$ 换成了 $x/m$：
```math
 \lfloor\frac{x}{m}\rfloor + \lfloor\frac{1+x}{m}\rfloor + \cdots + \lfloor\frac{m-1+x}{m}\rfloor = \lfloor x\rfloor.
```

就像在第 1 章里那样，我们发现往更简单的方向推广到 $n=0$ 来获取更多数据是很有用的：
```math
 \lfloor\frac{x}{m}\rfloor + \lfloor\frac{x}{m}\rfloor + \cdots + \lfloor\frac{x}{m}\rfloor = m\lfloor\frac{x}{m}\rfloor.
```

我们的问题里有两个参数：$m$ 和 $n$。先来看 $m$ 取小值的情况。当 $m=1$ 时，和式里只有一项，值为 $\lfloor x\rfloor$。当 m=2 时，和式是 $\lfloor x/2\rfloor + \lfloor (x+n)/2\rfloor$。我们可以把 $n$ 从下取整符号里挪出来，以此消除 $x$ 和 $n$ 之间的耦合，但要这么做，必须分偶数和奇数两种情况讨论。如果 $n$ 是偶数，$n/2$ 是整数，于是可以把它从下取整里提出来：
```math
\lfloor\frac{x}{2}\rfloor + (\lfloor\frac{x}{2}\rfloor + \frac{n}{2}) = 2\lfloor\frac{x}{2}\rfloor + \frac{n}{2}.
```

如果 $n$ 是奇数，那么 $(n−1)/2$ 是整数，于是我们得到：
```math
\lfloor\frac{x}{2}\rfloor + (\lfloor\frac{x+1}{2}\rfloor + \frac{n-1}{2}) = \lfloor\ x\rfloor + \frac{n-1}{2}.
```
最后一步是由公式 (3.26) 取 $m=2$ 得到的。

这些针对偶数和奇数 $n$ 的公式，与 $n=0, 1$ 的情形略有相似，但目前还没有呈现出清晰的规律。所以我们最好继续探索更多小例子。当 $m=3$ 时，和式为：
```math
\lfloor\frac{x}{3}\rfloor + \lfloor\frac{x+n}{3}\rfloor + \lfloor\frac{x+ 2n}{3}\rfloor,
```

我们对 $n$ 分三种情况讨论：它要么是 $3$ 的倍数，要么是 $3$ 的倍数加 $1$，要么是 $3$ 的倍数加 $2$。也就是说，$n\mod 3=0,1,2$。如果 $n\mod 3=0$，那么 $n/3$ 和 $2n/3$ 都是整数，于是这个和为：
```math
\lfloor\frac{x}{3}\rfloor + (\lfloor\frac{x}{3}\rfloor+\frac{n}{3}) + (\lfloor\frac{x}{3}\rfloor+\frac{2n}{3})=3\lfloor\frac{x}{3}\rfloor + n.
```

如果 $n\mod 3=1$，那么 $(n−1)/3$ 和 $(2n−2)/3$ 都是整数，于是我们得到：
```math
\lfloor\frac{x}{3}\rfloor + (\lfloor\frac{x+1}{3}\rfloor+\frac{n-1}{3}) + (\lfloor\frac{x+2}{3}\rfloor+\frac{2n-2}{3})=\lfloor x\rfloor + n-1.
```

最后这一步同样由公式 (3.26) 得出，$m=3$。最后如果 $n\mod 3=2$，那么：
```math
\lfloor\frac{x}{3}\rfloor + (\lfloor\frac{x+2}{3}\rfloor+\frac{n-2}{3}) + (\lfloor\frac{x+1}{3}\rfloor+\frac{2n-1}{3})=\lfloor x\rfloor + n-1.
```

我们大脑的左脑已经搞定了 $m=3$ 的情况，但右脑还是没看出规律，于是我们继续看 $m=4$：
```math
\lfloor\frac{x}{4}\rfloor + \lfloor\frac{x+n}{4}\rfloor + \lfloor\frac{x+ 2n}{4}\rfloor + \lfloor\frac{x+ 3n}{4}\rfloor.
```

至少现在我们已经很清楚，要根据 $n\mod m$ 来分情况讨论。如果 $n\mod 4 = 0$，那么：
```math
\lfloor\frac{x}{4}\rfloor + (\lfloor\frac{x}{4}\rfloor+\frac{n}{4}) + (\lfloor\frac{x}{4}\rfloor+\frac{2n}{4}) + (\lfloor\frac{x}{4}\rfloor+\frac{3n}{4})=4\lfloor\frac{x}{4}\rfloor + \frac{3n}{2}.
```

如果 $n\mod 4 = 1$：
```math
\lfloor\frac{x}{4}\rfloor + (\lfloor\frac{x+1}{4}\rfloor+\frac{n-1}{4}) + (\lfloor\frac{x+2}{4}\rfloor+\frac{2n-2}{4}) + (\lfloor\frac{x+3}{4}\rfloor+\frac{3n-3}{4})=\lfloor x\rfloor + \frac{3n}{2}-\frac{3}{2}.
```

结果发现，$n\mod 4=3$ 的情况也给出相同的结果。最后，在 $n\mod 4=2$ 的情况下，我们得到了一个略有不同的式子，而这恰恰成为了理解整体规律的一条重要线索：
```math
\lfloor\frac{x}{4}\rfloor + (\lfloor\frac{x+2}{4}\rfloor+\frac{n-2}{4}) + (\lfloor\frac{x}{4}\rfloor+\frac{2n}{4}) + (\lfloor\frac{x+2}{4}\rfloor+\frac{3n-2}{4}) \\
=2(\lfloor\frac{x}{4}\rfloor + \lfloor\frac{x+2}{4}\rfloor) + \frac{3n}{2} -1 = 2\lfloor\frac{x}{2}\rfloor+ \frac{3n}{2} -1.
```

最后这一步化简的是形如 $\lfloor y/2\rfloor + \lfloor (y+1)/2\rfloor$ 的式子，这同样是公式 (3.26) 的一个特例。

总结一下，下面是我们对较小的 $m$ 算出的和式的值：
| $m$ | $n\mod m = 0$ | $n\mod m = 1$ | $n\mod m = 2$ | $n\mod n = 3$ |
| :-- | :-- | :-- | :-- | :-- |
| 1 | $\lfloor x\rfloor$ |  |  |  |
| 2 | 2$\lfloor\frac{x}{2}\rfloor + \frac{n}{2}$ | $\lfloor x\rfloor + \frac{n}{2} - \frac{1}{2}$|  |  |
| 3 | 3$\lfloor\frac{x}{3}\rfloor + n$ | $\lfloor x\rfloor + n -1$ | $\lfloor x\rfloor + n -1$ |  |
| 4 | 4$\lfloor\frac{x}{4}\rfloor + \frac{3n}{2}n$ | $\lfloor x\rfloor + \frac{3n}{2} - \frac{3}{2}$ | 2$\lfloor\frac{x}{2}\rfloor + \frac{3n}{2} -1$ | $\lfloor x\rfloor + \frac{3n}{2} - \frac{3}{2}$ | 

看起来我们得到的结果好像都具有某种形式：
```math
a\lfloor\frac{x}{a}\rfloor + bn + c,
```

其中 $a, b, c$ 以某种方式依赖于 $m$ 和 $n$。就算是眼力不太好的人也能看出，$b$ 很可能就是 $(m−1)/2$​。要找出 $a$ 的表达式则更难一些，但 $n\mod 4=2$ 这个例子给了我们一个提示：$a$ 很可能是 $\gcd(m,n)$，也就是 $m$ 和 $n$ 的最大公约数。这是合理的，因为 $\gcd(m,n)$ 正是我们把分数 $n/m$​ 约分成最简形式时，从 $m$ 和 $n$ 中约去的那个因子，而我们的和式里正好出现了 $n/m$​。（我们会在第 4 章仔细研究最大公约数运算。）$c$ 的值看起来就更神秘了，不过也许等我们证明完 $a$ 和 $b$ 之后，$c$ 自然就清楚了。

在对较小的 $m$ 计算这个和式时，我们实际上已经把和式中的每一项重新写成了：
```math
\lfloor\frac{x+kn}{m}\rfloor = \lfloor\frac{x+kn\mod n}{m}\rfloor + \frac{kn}{m} - \frac{kn\mod m}{m},
```

因为 $(kn−(kn\mod m))/m$ 是一个整数，可以从下取整括号里提出来。于是，原来的和式就可以展开成下面这样的形式：
```math
\begin{aligned} 
\lfloor\frac{x}{m}\rfloor &+ \lfloor\frac{0}{m}\rfloor -& \lfloor\frac{0\mod m}{m}\rfloor \\
+\lfloor\frac{x + n\mod n}{m}\rfloor &+ \lfloor\frac{n}{m}\rfloor -& \lfloor\frac{n\mod m}{m}\rfloor \\
+\lfloor\frac{x + 2n\mod n}{m}\rfloor &+ \lfloor\frac{2n}{m}\rfloor -& \lfloor\frac{2n\mod m}{m}\rfloor \\
\vdots & \vdots  & \vdots \\
+\lfloor\frac{x + (m-1)n\mod n}{m}\rfloor &+ \lfloor\frac{(n-1)n}{m}\rfloor -& \lfloor\frac{(m-1)n\mod m}{m}\rfloor 
\end{aligned}
```

当我们用较小的 $m$ 做试验时，这三列分别对应得到了：$a\lfloor\frac{x}{a}\rfloor, bn, c$。

尤其是，我们能看出 $b$ 是怎么来的。第二列是一个等差数列，它的和我们是知道的 —— 等于首项与末项的平均值，再乘以项数：
```math
\frac{1}{2}(0 + frac{(m-1)n}{m})\cdot m = \frac{(m-1)n}{2}.
```

于是我们之前猜测的 $b=(m−1)/2$ ​就得到了验证。

第一列和第三列似乎更难；要确定 $a$ 和 $c$，我们必须仔细研究数字序列:
```math
0\mod m, n\mod m, 2n\mod m,\cdots, (m-1)n\mod m
```

假设，例如， $m = 12$ 且 $n = 5$。如果我们把这一序列看作钟表上的时间，那么这些数字就是 $0$ 点（我们把 $12$ 点视为 0$ 点），接着是 $5$ 点、 $10$ 点、 $3$ 点（$= 15$ 点）、 $8$ 点，以此类推。结果发现，我们恰好每个小时都碰上一次。

现在假设 $m = 12$，且 $n = 8$。这些数字分别是 $0$点、 $8$点、$4$点（$= 16$点），但随后 $0, 8, 4$会重复出现。由于 $8, 12$ 都是 $4$ 的倍数，而且这些数字从 $0$ 开始（这也是 $4$ 的倍数），因此根本无法打破这一规律——它们必定都是 $4$ 的倍数。

在上述两种情况下，我们有 $\gcd(12, 5) = 1$ 和 $\gcd(12, 8) = 4$。下一章我们将证明的一般规律是：如果 $d = \gcd(m, n)$，那么我们会按某种顺序得到数字 $0, d, 2d,\cdots, m-d$，接着是 $d − 1$ 的相同序列的更多副本。例如，当 $m = 12$ 且 $n = 8$ 时，模式 $0, 8, 4$ 就会出现四次。

我们求和的第一列现在完全说得通了。它包含 $d$ 个项的副本： $\lfloor x/m\rfloor, \lfloor (x+d)/m\rfloor,\cdots, \lfloor (x+m-d)/m\rfloor$，顺序不一，因此其总和为:
```math
\begin{aligned} 
d(\lfloor\frac{x}{m}\rfloor&+\lfloor\frac{x+d}{m}\rfloor+\cdots+\lfloor\frac{x+m-d}{m}\rfloor) \\
&=d(\lfloor\frac{x/d}{m/d}\rfloor+\lfloor\frac{x/d+1}{m/d}\rfloor+\cdots+\lfloor\frac{x/d+m/d-1}{m/d}\rfloor) \\
&=d\lfloor\frac{x}{d}\rfloor
\end{aligned}
```

这最后一步是(3.26)的又一应用。我们对 $a$ 的猜测已得到验证：
```math
a = d = \gcd(m, n).
```

而且正如我们猜测的那样，现在也可以算出 $c$ 了，因为第三列已经变得很容易理解。它包含了 $d$ 段等差数列 $0/m, d/m, 2d/m, \cdots, (m−d)/m$，所以它的和是：
```math
d(\frac{1}{2}(0+\frac{m-d}{m})\cdot\frac{n}{d}) = \frac{m-d}{2};
```

事实上，第三列是要减去，而不是加上，因此我们得到：
```math
c = \frac{d-m}{2}
```

谜团解开，探索结束。我们想要的闭式就是：
```math
\sum_{0\le<m} \lfloor\frac{nk+x}{m}\rfloor = d\lfloor\frac{x}{d}\rfloor + \frac{m-1}{2}\cdot n + \frac{d-m}{2},
```

其中 $d=\gcd(m,n)$。作为验证，我们可以用之前已知的特殊情况 $n=0$ 和 $n=1$ 来检验：当 $n=0$ 时，有 $d=\gcd(m,0)=m$；公式中最后两项都为 $0$，因此公式正确给出 $m\lfloor x/m\rfloor$。当 $n=1$ 时，有 $d=\gcd(m,1)=1$；最后两项正好抵消，和式就等于 $\lfloor x\rfloor $。

只要对这个闭式稍作整理，我们就能让它在 $m$ 和 $n$ 之间呈现出对称性：
```math
\begin{aligned} 
\sum_{0\le<m} \lfloor\frac{nk+x}{m}\rfloor &= d\lfloor\frac{x}{d}\rfloor + \frac{m-1}{2}\cdot n + \frac{d-m}{2} \\
&= d\lfloor\frac{x}{d}\rfloor + \frac{(m-1)(n-1)}{2} + \frac{(m-1)}{2} + \frac{d-m}{2} \\
&= d\lfloor\frac{x}{d}\rfloor + \frac{(m-1)(n-1)}{2} + \frac{(d-1)}{2}. \tag{3.32}
\end{aligned}
```

这结果简直令人惊叹，因为从代数形式上，我们完全没有理由预料到这个和式会具有这样的对称性。我彻底被折服了。没错，我们就此证明了一条互反律。
```math
\sum_{0\le<m} \lfloor\frac{nk+x}{m}\rfloor = \sum_{0\le<n} \lfloor\frac{mk+x}{n}\rfloor, integers\ m, n>0.
```

例如，当 $m=41, n=127$ 时，左边的和只有 $41$ 项，右边的和却有 $127$ 项，但对任意实数 $x$，它们的值仍然完全相等。


