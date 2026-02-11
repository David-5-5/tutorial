# 3. Integer Functions 整数函数

整数构成了离散数学的基石，我们经常需要将分数或任意实数转换为整数。本章的目标是熟悉并熟练掌握此类转换，并了解它们的一些显著性质。


## 3.1 FLOORS AND CEILINGS

我们首先介绍下取整（最大整数）和上取整（最小整数）整数函数，其定义域为所有实数 $x$ ，如下所示：
```math
\lfloor x\rfloor = 小于或等于x的最大整数 \\
\lceil x\rceil = 大于或等于x的最小整数         \tag{3.1}
```

Kenneth E. Iverson 在20世纪60年代初引入了这种记法，以及 floor 和 ceiling 这两个名称[191，第12页]。他发现排版人员可以通过削减 [ 和 ] 的顶部和底部来处理这些符号。他的记法已变得足够流行，以至于在技术论文中现在可以直接使用 floor 和 ceiling 括号，而无需解释其含义。直到最近，人们大多习惯用 [x] 来表示不大于 x 的最大整数，却很少有针对最小整数函数的良好等价表示。一些作者甚至尝试使用 ']x[' ，但收效甚微。

除了表示法上的差异，函数本身也存在差异。例如，一些袖珍计算器具有 $INT$ 函数，其定义为：当 $x$ 为正时，$\lfloor x\rfloor$；当 $x$ 为负时， $\lceil x\rceil$。这些计算器的设计者可能希望他们的 $INT$ 函数满足恒等式 $INT(−x) = −INT(x)$。不过，我们还是坚持使用我们的地板函数和天花板函数，因为它们比这个恒等式具有更优的性质。

通过凝视这张插图，我们可以观察到关于 floors 和 ceilings 的几个事实。首先，由于 $floor$ 函数位于或低于对角线 $f(x) = x$ 之下，我们有 $\lfloor x\rfloor\le x$；同样地， $\lceil x\rceil\ge x$。（当然，这一点从定义中就已十分明显。）这两个函数在整数点上完全相等：
```math
\lfloor x\rfloor=x\iff x\ is\ an\ integer\iff\lceil x\rceil=x 
```

我们使用符号 $\iff$ 表示“当且仅当”。此外，当它们不同时，天花板恰好比地板高 1：
```math
\lfloor x\rfloor-\lceil x\rceil= [x\ is\ not\ an\ integer] \tag{3.2}
```

如果我们把对角线向下平移一个单位，它将完全位于地板函数下方，因此 $x − 1 < \lfloor x\rfloor$；同样 $x + 1 > \lceil x\rceil$。综合这些观察结果，我们得到:
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
我们现在已经了解了处理 $floor$ 和 $ceil$ 的基本工具。让我们开始用它们解决一个简单的问题：$\lceil \lg 35\rceil$ 是多少？（根据爱德华·M·莱因戈尔德的建议，我们用 $\lg$ 表示以2为底的对数。）嗯，由于 $2^5<35\le 26$，我们可以取对数得到 $5<\lg 35\le 6$；因此，关系式(3.5(c))告诉我们 $\lceil \lg 35\rceil = 6$.

请注意，数字 $35$ 用基数 $2$ 表示时是 $6$ 位长：$35 = (100011)_2$。那么，是否总是成立 $\lceil \lg n\rceil = 6$ 是 $n$ 用二进制表示时的位数呢？并不完全正确。我们还需要六位来表示 $32 = (100000)_2$。因此，$\lceil \lg n\rceil = 6$ 并不是这个问题的正确答案。（它仅在 $n$ 是 $2$ 的幂时出错，但这种情况有无穷多。）我们可以通过认识到每个数 $n$ 需要 $m$ 位来写，使得 $2^{m−1}\le n < 2^m$；从而（3.5(a)）告诉我们 $m-1 = \lfloor \lg n\rfloor$，所以 $m = \lfloor \lg n\rfloor +1$。也就是说，对于所有 $n > 0$，我们需要 $\lfloor\lg n\rfloor +1$ 位来用二进制表示 $n$。或者，类似的推导也可以得到答案 $\lceil\lg(n+1)\rceil$；如果愿意承认写 $n = 0$ 用二进制表示需要零位，那么这个公式对 n = 0 也成立。

接下来我们来看一下包含多个向上取整或向下取整的表达式。$\lceil\lfloor x\rfloor\rceil$ 是什么？很简单 | 因为 $\lfloor x\rfloor$ 是一个整数， $\lceil\lfloor x\rfloor\rceil$ 就等于 $\lfloor x\rfloor$。因此，任何最内层是 $\lfloor x\rfloor$，并被任意数量的向上取整或向下取整包围的表达式也是如此。

这里有一道难度更高的问题：证明或证伪该断言：
```math
\lfloor\sqrt{\lfloor x\rfloor}\rfloor = \lfloor\sqrt{x}\rfloor, real\ x\ge 0 \tag{3.9}
```

当 $x$ 是整数时，显然等式成立，因为 $x=\lfloor x\rfloor$。在特殊情况下也存在等式： $\pi=3.14159\cdots$， $e=2.71828\cdots$，以及 ($\phi= (1 + \sqrt{5})/2 = 1.61803\cdots$)，因为我们得到 $1 = 1$。我们未能找到反例，这表明等式一般情况下成立，那么让我们试着证明它吧。

顺便说一下，当我们面对“证明或反驳”时，通常最好先尝试用反例来反驳，原因有两点：首先，反驳可能更容易（我们只需要一个反例）；其次，吹毛求疵能激发我们的创造力。即使给定的命题是正确的，我们在寻找反例的过程中往往也会自然而然地找到证明，一旦我们意识到为什么反例不可能存在。此外，保持怀疑态度也是有益健康的。

如果我们试图借助微积分证明 $\lfloor\sqrt{\lfloor x\rfloor}\rfloor = \lfloor\sqrt{x}\rfloor$，我们可能会先将 x分解成整数部分和小数部分： $\lfloor x\rfloor+\{x\}=n+\theta$ ，然后利用二项式定理展开平方根： $(n+\theta)^{1/2} = n^{1/2} + n^{−1/2}\theta/2 − n^{−3/2}\theta^2/8 +\cdots$。但这种方法会变得相当复杂。

使用我们开发的工具要容易得多。这里有一个可能的策略：某种方式下，先去掉外层的 $floor$ 函数和平方根 $\lfloor\sqrt{\lfloor x\rfloor}\rfloor$，再移除内层的 $floor$ 函数，然后把外层的值加回去，得到 $\lfloor\sqrt{x}\rfloor$。好的。我们令 $m=\lfloor\sqrt{\lfloor x\rfloor}\rfloor$，并调用(3.5(a))，得到 $m\le \lfloor\sqrt{x}\rfloor<m+1$。这样就去掉了外层的 $floor$ 括号，且没有丢失任何信息。由于这三个表达式都是非负的，我们对两边同时平方，得到 $m^2\le\sqrt{x}<(m + 1)^2$。这一步消除了平方根。接下来，我们利用(3.7(d))处理左边不等式，用(3.7(a))处理右边不等式，从而去掉 $floor$ 函数： $m^2\le x<(m + 1)^2$。现在，只需简单地反向推导，取平方根即可得到 $m\le \sqrt{x}<m+1$，再调用(3.5(a))，得到 $m=\lfloor\sqrt{x}\rfloor$。因此，$\lfloor\sqrt{\lfloor x\rfloor}\rfloor = m = \lfloor\sqrt{x}\rfloor$；该断言成立。类似地，我们也可以证明
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

无论何时，当 $f(x), f(如果 m 和 n 是整数，且分母 n 为正数。例如，令 m = 0；我们有 ⌊⌊bx/10c/10⌋/10⌋ = bx/1000c。连续三次除以 10 并舍弃小数部分，等同于除以 1000 并丢弃余数。) , f(\lceil x\rceil)$ 都有定义时，我们来证明这一关于向上取整的一般性质。由于我们之前已经讨论过向下取整，而且向下取整的证明几乎相同，因此我们先证明这一性质。如果 $x = \lceil x\rceil$，则无需证明。否则， $x < \lceil x\rceil$，并且由于 $f$ 是递增的，所以 $f(x) < f(\lceil x\rceil)$。因此， $\lceil f(x)\rceil\le \lceil f(\lceil x\rceil)\rceil$，因为 $\lceil\rceil$ 是非递减的。如果 $\lceil f(x)\rceil< \lceil f(\lceil x\rceil)\rceil$，则必然存在一个数 $y$，使得 $x \le y < \lceil x\rceil$ 且 $f(y) = \lceil f(x)\rceil$，这是因为 $f$ 是连续的。根据 $f$ 的特殊性质，这个 $y$ 必然是整数。然而，$x$ 和 $\lceil x\rceil$ 之间不可能存在严格介于二者之间的整数。这种矛盾表明，我们必须有 $\lceil f(x)\rceil = \lceil f(\lceil x\rceil)\rceil$。

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