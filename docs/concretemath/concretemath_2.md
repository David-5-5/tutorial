# 2 SUM 总和

求和在数学中无处不在，因此我们需要基本的工具来处理它们。本章将介绍使求和更易于使用的符号表示法和通用技巧。


## 2.1 符号
在第1章中，我们遇到了前 n 个整数的和，它我们写成 $1 + 2 + 3 + \cdots + (n − 1) + n$。这种公式中的 $\cdots$ 告诉我们，要补全由周围项所确立的模式。当然，我们必须留意像 $1 + 7 + \cdots + 41.7$ 这样的求和，如果没有适当的上下文，这些求和是毫无意义的。另一方面，加入诸如 3 和 $(n − 1)$ 这样的项未免有些过度；如果只写成 $1 + 2 + \cdots + n$，这个模式想必也会很清晰。有时我们甚至可以大胆一些，直接写成 $1 + \cdots + n$。


我们将处理一般形式的和
```math
a_1 + a_1 + \cdots + a_n, \tag{2.1}
```
其中每个 $a_k$ 都是某种已定义的数字。这种表示法的优点在于，如果我们想象力足够丰富，几乎可以像完整写出一样“看到”整个求和式。

每个求和项 $a_k$ 都称为一个项。这些项通常以易于识别的模式所遵循的公式形式隐式指定，在这种情况下，我们有时必须将其写成展开形式，以便清楚地表达其含义。例如，如果
```math
1 + 2 + \cdots + 2^{n-1}
```

应表示 $n$ 项的和，而不是 $2^{n-1}$，我们应更明确地写成
```math
2^0 + 2^1 + \cdots + 2^{n-1}.
```

三点表示法用途广泛，但可能含糊不清且略显冗长。其他替代方案也已出现，尤其是分隔形式。
```math
\sum_{k=1}^n a_k, \tag{2.2}
```

这种记法被称为西格玛记号，因为它使用了希腊字母 $\sum$（大写西格玛）。这种记法告诉我们，求和时要精确地包含那些项 $a_k$，其下标 $k$ 是一个整数，且该整数位于下限 $1$ 和上限 $n$ 之间，包括这两个端点。换句话说，我们对 $k$ 从 $1$ 到 $n$ 进行求和。约瑟夫·傅里叶于1820年引入了这种带限定的 $\sum-$ 记号，很快便在数学界掀起了一股热潮。 

顺带一提，求和号 $\sum$ 后方的表达式（此处为 $a_k$​）称作求和项。

在式 (2.2) 中，指标变量 $k$ 被称为被求和号约束的变量，因为 $a_k$ ​中的 $k$ 与求和记号 $\sum$ 外部出现的 $k$ 互不相关。此处将 $k$ 替换为其他任何字母，都不会改变式 (2.2) 的含义。字母 $i$ 也常被使用（或许是因为它对应英文 index 一词），但我们通常会选用 $k$ 作为求和指标，将 $i$ 留给虚数单位 $\sqrt{-1}$ ​是更稳妥的做法。

事实证明，广义的 Sigma 符号甚至比带限定符的形式更有用：我们只需在 $\sum$ 下方写上一个或多个条件，即可指定求和所涉及的下标集合。例如，(2.1)和(2.2)中的求和也可以写成
```math
\sum_{1\le k\le n}a_k, \tag{2.3}
```

在这个特定的例子中，新形式与(2.2)之间并没有太大差异，但一般形式允许我们对不限于连续整数的索引集求和。例如，我们可以如下表示小于 100 的所有奇正整数的平方之和：
```math
\sum_{\substack{1\le k< 100\\ k\ odd}}k^2 .
```

此求和的分隔等价物，
```math
\sum_{k=0}^{49}(2k+1)^2 ,
```

更加繁琐且不够清晰。同样，从 $1$ 到 $N$ 之间所有质数的倒数之和是
```math
\sum_{\substack{p\le N\\ p\ prime}}\frac{1}{p} ;
```

分隔形式将要求我们编写
```math
\sum_{k=1}^{\pi(N)} \frac{1}{p_k} ;
```

其中 $p$ 表示第 $k$ 个素数， $\pi(N)$ 是不大于 $N$ 的素数个数。(顺便一提，这个求和给出了接近 $N$ 的随机整数的 distinct 素因子的平均数量的近似值，因为大约 $1/p$ 的这些整数能被 $p$ 整除。对于较大的 $N$，其值约为 $\ln\ln N + M$，其中 $M\approx 0.2614972128476427837554268386086958590515666$ 是梅滕斯常数[271]；$\ln x$ 表示 $x$ 的自然对数，$\ln\ln x$ 表示 $\ln(\ln x)$。)

一般求和符号的最大优势在于，我们能比带限定符的形式更方便地对其进行操作。例如，假设我们要将索引变量 $k$ 改为 $k+1$。使用一般形式，我们有
```math
\sum_{1\le k\le n}a_k = \sum_{1\le k+1\le n}a_{k+1} ;
```

很容易看出发生了什么，我们几乎不用思考就能进行替换。但采用分隔形式后，我们有
```math
\sum_{k=1}^n a_k = \sum_{k=0}^{n-1} a_{k+1};
```
更难看清发生了什么，我们更有可能犯错。

另一方面，带分隔符的形式并非完全无用。它整洁美观，而且我们能快速书写，因为(2.2)只有七个符号，而(2.3)却有八个。因此，在陈述问题或展示结果时，我们常常会使用带上下分隔符的 $\sum$，但在处理需要变换索引变量的求和时，我们更倾向于使用 $\sum$ 下的关系。

$\sum$ 符号在本书中出现了1000多次，因此我们应该是确保我们确切地知道它的含义。正式地，我们写：
```math
\sum_{P(k)}a_k \tag{2.4}
```

作为所有项之和的缩写 $a_k$，使得 $k$ 是满足给定性质 $P(k)$ 的整数。 (“性质 $P(k)$”是指关于 $k$ 的任何可为真或假的陈述。) 暂时我们假设，只有有限个满足 $P(k)$ 的整数 $k$ 具有 $a_k\ne 0$；否则，将会有无限多个非零数相加，情况可能会变得有点棘手。在另一个极端，如果对于所有整数 $k，P(k)$ 为假，那么我们就得到一个“空”和；空和的值被定义为零。

当一个求和出现在段落正文内而非显示方程中时，会使用(2.4)的稍作修改的形式：我们写作'$\sum_{P(k)} a_k$'，并将性质 $P(k)$ 作为 $\sum$ 的下标，以使公式不会显得过于突兀。同样地，`$\sum_{k=1}^n a_k$ 是一种便捷的替代方案，适用于当我们希望将记号限制在单行时使用(2.2)。

人们常常会忍不住写
```math
\sum_{k=2}^{n-1}k(k-1)(n-k) \quad \text{ instead of } \quad \sum_{k=0}^{n}k(k-1)(n-k)
```

因为这个求和式中 $k = 0,1$ 和 $n$ 这些项的值均为零。不知为何，似乎将 $n-2$ 项相加比 $n+1$ 项相加更有效率。但这种诱惑应当抵制；计算的效率并不等同于理解的效率！我们发现，将求和指标的上下界保持尽可能简单是有利的，因为当上下界简单时，求和式可以更容易地进行操作。事实上，形式 $\sum_{k=2}^{n-1}$ 甚至可能产生危险的歧义，因为当 $n=0$ 或 $n=1$ 时（参见练习1），它的含义完全不明确。值为零的项并不会造成任何损害，而且往往能省去很多麻烦。

到目前为止，我们所讨论的符号都相当标准，但现在我们将要彻底背离传统。肯尼斯·E·艾弗森在他的编程语言APL中提出了一种绝妙的想法[191，第11页；另见220]，我们将会看到，这一想法极大地简化了我们在本书中想要完成的许多工作。这个想法很简单：将一个真或假的陈述用方括号括起来，并规定：如果该陈述为真，则结果为 1；如果该陈述为假，则结果为 0。例如，
```math
[p\ prime] = 
\begin{cases}
1, & \text{if p is a prime number}    \\
0, & \text{if p is not a prime number};
\end{cases}
```

伊维森约定允许我们用任意索引表示求和，因为我们可以将(2.4)重写为
```math
\sum_k a_k[P(k)] \tag{2.5}
```
如果 $P(k)$ 为假，则项 $a_k[P(k)]$ 为零，因此我们可以安全地将其包含在求和项中。这使得调整求和指标变得容易，因为我们无需费心处理边界条件。


需要提及一个细微的技术问题：有时 $k$ 并不是对所有整数 $k$ 都定义的。我们通过假设当 $P(k)$ 为假时，$[P(k)]$ 是“非常强烈的零”来规避这一困难；它几乎是零，以至于使得 $a_k[P(k)]$ 等于零，即使 $a_k$ 未定义。例如，如果我们使用伊维森约定来书写互反素数之和 $\le N$，则为
```math
\sum_p [p\ prime][p\le N]/p,
```

当 $p = 0$ 时，不存在除以零的问题，因为我们的约定告诉我们 $[0\ prime][0\le N]/0=0$.

让我们总结一下到目前为止我们所讨论的关于求和的内容。表达项之和有两种很好的方式：一种方式使用 '$\cdots$'，另一种方式使用 '$\sum$'。三点形式通常会提示一些有用的变换，尤其是相邻项的组合，因为如果我们让整个求和结果清晰地呈现在眼前，就可能发现一些简化的规律。但过多的细节也可能让人难以把握。而求和符号表示法简洁明了，能让家人和朋友刮目相看，而且常常暗示出在三点形式中并不明显的变换技巧。当我们使用求和符号表示法时，零项通常并无害处；事实上，零项往往能使 $\sum$ 的变换更加容易。


## 2.2 和以及递归
我们现在明白了如何用花哨的符号表示求和。但是，一个人究竟该如何求得一个和的值呢？一种方法是观察到，和与递推之间存在着密切的关系。这个和
```math
S_n = \sum_{k=0}^n a_k
```

等价于递归
```math
\begin{aligned}
S_0 &= a_0; \\
S_n &= S_{n-1} + a_n, \quad \text { for }n>0. \tag{2.6}
\end{aligned}
```

因此，我们可以利用我们在第 $1$ 章中学到的方法，通过求解递归式来以闭式形式评估求和。

例如，如果 $a_n$ 等于一个常数加上 $n$ 的倍数，那么求和递推式 (2.6) 就具有以下一般形式：
```math
\begin{aligned}
R_0 &= \alpha; \\
R_n &= R_{n-1} + \beta + \gamma n,\quad \text{ for }n>0. \tag{2.7}
\end{aligned}
```

按照第 $1$ 章所述的方法，我们发现 $R_1 = \alpha + \beta + \gamma，R_2 = \alpha + 2\beta + 3\gamma$，依此类推；一般地，解可以写成的形式
```math
R_n = A(n)\alpha + B(n)\beta + C(n)\gamma,  \tag{2.8}
```

其中 $A(n), B(n), C(n)$ 是对一般参数 $\alpha, \beta, \gamma$ 的依赖系数。

构造库方法告诉我们，尝试将 $n$ 的简单函数代入 $R_n$，希望能找到常数参数 $\alpha, \beta, \gamma$，使解特别简单。令 $R_n = 1$，则有 $\alpha=1, \beta=0, \gamma=0$；因此
```math
A(n) = 1.
```
设置 $R_n = n$ 表示 $\alpha=0, \beta=1, \gamma=0$；因此
```math
B(n) = n.
```

设置 $R_n = n^2$ 意味着 $\alpha=0, \beta=-1, \gamma=2$；因此
```math
2C(n) - B(n) = n^2.
```

而且我们有 $C(n) = (n^2 + n)/2$。简单得像吃蛋糕一样。

因此，若我们想要计算
```math
\sum_{k=0}^n(a+bk),
```
求和递推式 (2.6) 可化简为 (2.7)，其中 $\alpha=\beta=a, \gamma=b$，答案为 $aA(n) + aB(n) + bC(n) = a(n + 1) + b(n + 1)n/2$.

相反，许多递归关系可以转化为求和；因此，我们在本章稍后将学习的专门用于求和的方法，将有助于我们解决原本可能很困难的递归关系。汉诺塔递归关系就是一个典型的例子：
```math
\begin{aligned}
T_0 &= 0; \\
T_n &= 2T_{n-1} + 1, \quad \text{ for }n > 0.
\end{aligned}
```

如果我们将两边都除以 $2^n$:，它就可以被转化为特殊形式 (2.6)。
```math
\begin{aligned}
T_0/2^0 &= 0; \\
T_n/2^n &= T_{n-1}/2^{n-1} + 1/2^n, \quad \text{ for }n > 0.
\end{aligned}
```

现在我们可以设置 $S_n = T_n/2^n$，我们有
```math
\begin{aligned}
S_0 &= 0; \\
S_n &= S_{n-1} + =2^{-n}, \quad \text{ for }n > 0.
\end{aligned}
```
由此可知
```math
S_n = \sum_{k=1}^n 2^{-k},
```

请注意，我们已将 $k = 0$ 这一项排除在该求和之外。几何级数 $2^{−1}+2^{−2}+\cdots+2^{−n} = (\frac{1}{2})^1 +(\frac{1}{2})^2+\cdots+(\frac{1}{2})^n$，将在本章稍后推导出来；结果是 $1 − (\frac{1}{2})^n$。因此 $T_n = 2^nS_n = 2^n − 1$.

我们已将 $T_n$ 转换为 $S_n$，这是通过注意到递归可以被 $2_n$ 整除而实现的。这一技巧是通用技术的一个特例，该技术几乎可将任何形式的递归简化为:
```math
a_nT_n = b_nT_{n-1} + c_n \tag{2.9}
```
的任何递归化为和的一般技巧的特殊情形，用*求和因子* $s_n$ 乘两边：
```math
s_na_nT_n = s_nb_nT_{n-1} + s_nc_n 
```

巧妙的选择因子 $s_n$ 可使：
```math
s_nb_n = s_{n-1}a_{n-1}
```

记 $S_n = s_na_nT_n$，则得到一个和的递归：
```math
S_n = S_{n-1} + s_nc_n
```
因此
```math
S_n = s_0a_0T_0 + \sum_{k=1}^{n}s_kc_k = s_1b_1T_0 + \sum_{k=1}^{n}s_kc_k
```
原来递归 (2.9) 的解为：
```math
T_n = \frac{1}{s_na_n}(s_1b_1T_0 + \sum_{k=1}^{n}s_kc_k)  \tag{2.10}
```

例如，当 $n=1$ 时有 $T_1=(s_1b_1T_0+s_1c_1)/s_1a_1=(b_1T_0+c_1)/a_1$。但我们要如何巧妙求出合适的 $s_n$？方法很简单：
将关系式 $s_n = s_{n-1}a_{n-1}/b_n$ 展开，即可得到该分式
```math
s_n = \frac{a_{n-1}a_{n-2}\cdots a_1}{b_nb_{n-1}\cdots b_2} \tag{2.11}
```
或该值任意合适的常数倍，都可以作为恰当的求和因子。例如汉诺塔递推中满足 $a_n=1$，$b_n=2$；按刚才推导的通用方法可知，若想将递推式化简为求和形式，取 $s_n=2^{-n}$ 作为乘子十分合适。我们无需灵光一现，就能直接求出该乘子。

和往常一样，必须注意避免除零。只要所有 $a_n$ 与 $b_n$ 均不为零，求和因子法就始终适用。

快速排序是计算机领域最重要的数据排序算法之一。对随机无序的 $n$ 个元素执行快速排序时，其平均比较次数满足下述递推关系：
```math
\begin{aligned}
C_0 &= 0 \\
C_n &= n + 1 + \frac{2}{n}\sum_{k=0}^{n-1}C_k, \quad \text{ for }n > 0.\tag{2.12}
\end{aligned}
```

首先把除法去掉，两边乘以 $n$，得到关系式：
```math
nC_n = n^2 + n + 2\sum_{k=0}^{n-1}C_k , \quad \text{ for }n > 0.;
```

用 $n-1$ 来代替 $n$，则
```math
(n-1)C_{n-1} = (n-1)^2 + (n-1) + 2\sum_{k=0}^{n-2}C_k , \quad \text{ for }n-1 > 0;
```
两式相减，$\sum$ 符号不再出现，得到：

```math
nC_n - (n-1)C_{n-1} = 2n + 2C_n ,\quad \text{ for }n > 0.;
```

可以发现该递推关系在 $n=1$ 时同样成立，因为 $C_1=2$。因此 $C_n$ 原本的递推式可以化简为一个形式简洁得多的递推关系：
```math
\begin{aligned}
C_0 &= 0 \\
nC_n &= (n + 1)C_{n-1} + 2n, \quad \text{ for }n > 0.;
\end{aligned}
```

有了关键进展。该递推符合式(2.9)的标准形式：$a_n=n$，$b_n=n+1$，$c_n=2n$，现已可以使用求和因子法。根据上一页给出的通用方法，只需给递推式整体乘以某一倍数的
```math
s_n = \frac{a_{n-1}a_{n-2}\cdots a_1}{b_nb_{n-1}\cdots b_2} = 
\frac{(n-1)\cdot(n-2)\cdots\cdot 1}{(n+1)\cdot n\cdots\cdot 3} = 
\frac{2}{(n+1)n}
```

依照式 (2.10) ，解就是：
```math
C_n = 2(n+1)\sum_{k=1}^n\frac{1}{k+1}
```

余下的这个和式与应用中频繁出现的一个量形式十分相似。事实上它出现得极其频繁，我们为此赋予它专门的名称和记号：
$$
H_n = 1 + \frac12 + \cdots + \frac1n = \sum_{k=1}^n \frac1k \tag{2.13}$$
字母 $H$ 代表“调和”；$H_n$ 被称作调和数，之所以这样命名，是因为小提琴琴弦发出的第 $k$ 阶泛音，对应弦长为基音弦长的 $1/k$ 倍。

我们可以将 $C_n$ 写成闭式形式，以此完成对快速排序递推式 (2.12) 的分析；只要能把 $C_n$ 用 $H_n$ 表示出来，就能实现这一点。$C_n$ 表达式中的和式为
$$\sum_{k=1}^n \frac{1}{k + 1} = \sum_{1\le k\le n} \frac{1}{k + 1}$$

只需做变量替换 $k$ 换为 $k-1$ 并调整求和上下限，就能轻松将其与 $H_n$ 关联起来：
$$
\begin{aligned}
\sum_{1\le k\le n}\frac{1}{k+1} &=\sum_{1\le k-1\le n}\frac1k \\
& =\sum_{2\le k\le n+1}\frac1k \\
&=\left(\sum_{1\le k\le n}\frac1k\right)-1+\frac{1}{n+1} = H_n - \frac{n}{n+1}
\end{aligned}
$$

很好！我们已经求出求解递推式 $(2.12)$ 所需的和式：对 $n$ 个随机排列的数据元素进行快速排序时，平均比较次数为
```math
C_n = 2(n+1)H_n - 2n \qquad (2.14)
```
照例验证小规模取值是否正确：$C_0 = 0$，$C_1 = 2$，$C_2 = 5$


## 2.3 和的操作
掌握求和运算的关键，是能够把一个 $\sum$ 变换为另一个更简洁、或更贴近求解目标的求和形式。只需熟记几条基本变换规则并多加练习，就能轻松做到这一点。

设 $K$ 为任意有限整数集。对集合 $K$ 中元素求和，可通过三条简单规则进行变换：
```math
\sum_{k\in K}ca_k = c\sum_{k\in K}a_k; \qquad \qquad \text{(distributive law)} \tag{2.15}
```
```math
\sum_{k\in K}(a_k + b_k) = \sum_{k\in K}a_k + \sum_{k\in K}b_k ;\quad\text{(distributive law)} \tag{2.16}
```
```math
\sum_{k\in K}a_k = \sum_{p(k)\in K}a_{p(k)}; \qquad\qquad\text{(commutative law)} \tag{2.17}
```

分配律允许我们将常数移入或移出 $\sum$。结合律可以把一个 $\sum$ 拆成两部分，也能将两个 $\sum$ 合并为一个。交换律表明我们可以任意重排求和项的顺序；其中 $p(k)$ 是全体整数集合上的任意一个排列。

例如，若 $K=\{-1,0,+1\}$ 且 $p(k)=-k$，这三条定律分别给出：
$c a_{-1} + c a_0 + c a_1 = c(a_{-1} + a_0 + a_1) \qquad \text{distributive law}$
$(a_{-1}+b_{-1})+(a_0+b_0)+(a_1+b_1) \\
\qquad = (a_{-1}+a_0+a_1)+(b_{-1}+b_0+b_1)\qquad \text{associative law}$
$a_{-1}+a_0+a_1 = a_1+a_0+a_{-1}\qquad \text{commutative law}$

第一章中的高斯求和技巧，便可看作这三条基本定律的应用。假设我们要求解等差数列的一般和式
```math
S = \sum_{0\le k\le n}(a + bk)
```

根据交换律，用 $n-k$ 替代 $k$，得到
```math
S = \sum_{0\le n-k\le n}(a + b(n-k)) = \sum_{0\le k\le n}(a + bn - bk)
```

利用交换律可把这两个方程相加：
```math
2S = \sum_{0\le k\le n}((a + bk)+(a + bn - bk)) = \sum_{0\le k\le n}(2a + bn) \\
```

此时我们便可运用分配律，并计算一个平凡和式：
```math
2S = (2a+bn) \sum_{0\le k\le n} 1 = (2a + bn) (n+1)
```

两边各除以 2, 证明了：
```math
\sum_{k=0}^n(a + bk) = (a+\frac{1}{2}bn)(n+1) \tag{2.18}
```
等式右侧可以记忆为首项与末项的平均值 $\dfrac12\big(a+(a+bn)\big)$ 乘以项数 $n+1$。

需要重点注意，通用交换律 $(2.17)$ 中的函数 $p(k)$ 必须是全体整数上的一个排列。也就是说，对任意整数 $n$，有且仅有一个整数 $k$ 满足 $p(k)=n$。如若不然，交换律可能不再成立；习题3给出了极具说服力的例证。形如 $p(k)=k+c$ 或 $p(k)=c-k$（其中 $c$ 为整数常数）的变换恒为排列，因此始终适用。

另一方面，我们可以略微放宽排列的限制条件：仅要求当 $n$ 属于下标集 $K$ 时，有且仅有一个整数 $k$ 使得 $p(k)=n$。若 $n\notin K$（即 $n$ 不在集合 $K$ 中），$p(k)=n$ 出现多少次都无关紧要，因为这类 $k$ 并不参与求和。

例如由此可以推导：
$$
\sum_{k\in K\atop k\text{ even}} a_k=\sum_{n\in K\atop n\text{ even}} a_n=\sum_{2k\in K\atop 2k\text{ even}} a_{2k}=\sum_{2k\in K} a_{2k} \tag{2.19}
$$
原因是当 $n\in K$ 且 $n$ 为偶数时，有且仅有一个 $k$ 满足 $2k=n$。

艾弗森约定可以在公式中间通过逻辑语句得到 $0$ 或 $1$ 的值，将它与分配律、结合律、交换律配合使用，能够推导出求和运算的更多性质。例如有一条合并不同下标集的重要规则：若 $K$ 与 $K'$ 为任意整数集合，则
```math
\sum_{k\in K}^na_k + \sum_{k\in K'}^na_k = \sum_{k\in K\cap K'}^na_k + \sum_{k\in K\cup K'}^na_k \tag{2.20}
```

这是根据下列的一般公式
```math
\sum_{k\in K}^na_k = \sum_ka_k[k\in K] \tag{2.21}
```
和
```math
[k\in K] + [k\in K] = [k\in K\cap K'] +  [k\in K\cup K'] \tag{2.22}
```

得出的。典型的把规则 (2.20) 用到结合两个几乎不相交的指标集合，如同：
```math
\sum_{k=1}^ma_k + \sum_{k=m}^na_k = a_m + \sum_{k=1}^na_k, \qquad \text{ for } 1\le m\le n;
```

或者从和中分出一项：
```math
\sum_{0\le k\le n}a_k = a_0 + \sum_{1\le k\le n}a_k, \qquad \text{ for }  n\ge 0; \tag{2.23}
```

这种拆分单项的运算，是*扰动法*(perturbation method)的基础，该方法常可求出和式的闭式表达式。思路为先设未知和式为 $S_n$：
$$S_n = \sum_{0\le k\le n} a_k$$
随后用两种方式改写 $S_{n+1}$，分别拆分其末项与首项：
```math
\begin{aligned}
S_n + a_{n+1} = \sum_{0\le k\le n+1}a_k &= a_0 + \sum_{1\le k\le n+1}a_k \\
              &= a_0 + \sum_{1\le k+1\le n+1}a_{k+1} \\
              &= a_0 + \sum_{0\le k\le n}a_{k+1} \tag{2.24}
\end{aligned}
```

现在在此最后和上处理，且尝试由 $S_n$ 表达它。若成功，则可获得一个方程，它的解是我们所要找的和。例如，用此方法来求出一般几何级数的和，
```math
S_n = \sum_{0\le k\le n}ax^k .
```

式 (2.24) 中的一般摄动方法
```math
S_n + ax^{n+1} = ax^0 + \sum_{0\le k\le n}ax^{k+1} .
```

根据分配律，右边的和是 $x\sum_{0\le k\le n}ax^k = xS_n$，因此 $S_n + ax^{n+1} = a + xS_n$，这样解出 $S_n$ 得到
```math
\sum_{k=0}^nax^k = \frac{a-ax^{n+1}}{1-x},  \qquad \text{ for } x\ne 1 \tag{2.25}
```

（当 $x = 1$ 时，该和式显然就是 $(n + 1)a$。）等式右侧可以记作：求和包含的首项减去末尾之后被舍去的首项，再除以 $1$ 减去公比。

这一过程显得格外简便。我们再用扰动法求解一个稍复杂的和式，
```math
S_n = \sum_{0\le k\le n}k2^k .
```

本例中有 $S_0 = 0$，$S_1 = 2$，$S_2 = 10$，$S_3 = 34$，$S_4 = 98$；其通项公式是什么？由式 $(2.24)$ 可得
```math
S_n + (n+1)2^{n+1} = \sum_{0\le k\le n}(k+1)2^{k+1} .
```

于是我们希望把右侧的和式用 $S_n$ 表示。借助结合律，可将其拆分为两个和式，
```math
\sum_{0\le k\le n}k2^{k+1} + \sum_{0\le k\le n}2^{k+1} 
```
第一个和是 $2S_n$。另一个和是几何级数，根据式 (2.25)，它等于 $(2-2^{n+2})/(1-2) = 2^{n+2} - 2$。所以我门得到 $S_n + (n+1)2^{n+1} = 2S_n + 2^{n+2} - 2$，而代数计算得到：
```math
\sum_{0\le k\le n}k2^k = (n-1)2^{n+1} + 2 .
```

现在就能理解为何 $S_3 = 34$：它等于 $32 + 2$，而非 $2\cdot 17$。

将推导中的 $2$ 替换为 $x$，同理可得方程 $S_n + (n + 1)x^{n+1} = xS_n + (x - x^{n+2})/(1 - x)$ 因此我们能推出
```math
\sum_{0\le k\le n}kx^k = \frac{x- (n+1)x^{n+1} + nx^{n+2}}{(1-x) ^2}, \qquad \text{ for } x\ne 1. \tag{2.26}
```

值得一提的是，我们完全可以用另一种截然不同的方式推导出该闭式，利用初等微积分知识即可。若从等式
```math
\sum_{k=0}^nx^k = \frac{1-x^{n+1}}{1-x} .
```

开始，且两边对 x 求导，得到
```math
\sum_{k=0}^nkx^{k-1} = \frac{(1-x)(-(n+1)x^n)+1-x^{n+1}}{(1-x)^2} = \frac{1-(n+1)x^n+nx^{n+1}}{(1-x)^2} .
```
因为和的求导是它各项求导的和。


## 2.4 多重和
和式的项可以由两个或多个下标来定义，而不仅限于单个下标。例如，下面是由下标 $j$ 与 $k$ 共同确定、包含九项的二重和：
```math
\begin{aligned}
\sum_{1\le j,k\le 3}a_jb_k &= a_1b_1 + a_1b_2 + a_1b_3\\
              &+ a_2b_1 + a_2b_2 + a_2b_3 \\
              &+ a_3b_1 + a_3b_2 + a_3b_3 
\end{aligned}
```

对于多重和，我们沿用单重和的记号与方法。设 $P(j,k)$ 为关于 $j$ 和 $k$ 的条件性质，所有满足 $P(j,k)$ 成立的 $a_{j,k}$ 之和有两种表达方式，其中一种借助艾弗森约定，对所有整数数对 $j,k$ 进行求和：
```math
\sum_{P(j,k)}a_jb_k = \sum_{j,k}a_jb_k[P(j,k)].
```
即便存在多个求和下标，也只需使用一个 $\sum$ 符号；$\sum$ 表示对所有符合条件的下标组合进行求和。

当处理和式的和时，我们也会用到两个 $\sum$ 符号。例如，
```math
\sum_j\sum_ka_jb_k[P(j,k)] 
```
的简写形式是：
$$\sum_j\left(\sum_k a_{j,k}\,[P(j,k)]\right)$$


即为对所有整数 $j$，求 $\sum_k a_{j,k}\,[P(j,k)]$ 的和，后者表示对所有整数 $k$，求取满足 $P(j,k)$ 成立的全部 $a_{j,k}$ 之和。此时称该二重和「先对 $k$ 求和」。含有多个下标的和式，可以任选其中一个下标作为优先求和对象。

对此有一条基本法则，称为交换求和次序，它是前文结合律 $(2.16)$ 的推广：
```math
\sum_j\sum_ka_jb_k[P(j,k)] = \sum_{P(j,k)}a_jb_k = \sum_k\sum_ja_jb_k[P(j,k)] . \tag{2.27}
```

该法则中间项为双下标求和。左侧 $\sum_j\sum_k$ 代表先对 $k$ 求和，再对 $j$ 求和；右侧 $\sum_k\sum_j$ 代表先对 $j$ 求和，再对 $k$ 求和。实际求解二重和的闭式时，通常优先选择某一个下标先计算会更加简便，我们可以任选更便捷的求和次序。

多重和式无需畏难，但初学者容易感到费解，因此我们再举若干实例。开篇提及的九项和式，是二重和运算变换的典型示例，该和式可以进行化简，其化简过程也是处理二重求和 $\sum\sum$ 的常规思路：
```math
\begin{aligned}
\sum_{1\le j,k\le 3}a_jb_k &= \sum_{j,k}a_jb_k[1\le j,k\le 3] \\
    &= \sum_{j,k}a_jb_k[1\le j\le 3][1\le k\le 3] \\
    &= \sum_j\sum_ka_jb_k[1\le j\le 3][1\le k\le 3] \\
    &= \sum_ja_j[1\le j\le 3]\sum_kb_k[1\le k\le 3] \\
    &= \sum_ja_j[1\le j\le 3](\sum_kb_k[1\le k\le 3]) \\
    &= (\sum_ja_j[1\le j\le 3])(\sum_kb_k[1\le k\le 3]) \\
    &= (\sum_{j=1}^3a_j)(\sum_{k=1}^3b_k) 
\end{aligned}
```

第一行表示无序排列的九项求和。第二行将其每三项分为一组：$(a_1b_1+a_1b_2+a_1b_3)+(a_2b_1+a_2b_2+a_2b_3)+(a_3b_1+a_3b_2+a_3b_3)$。第三行利用分配律提取 $a_j$，由于 $a_j$ 与 $[1\le j\le 3]$ 均和 $k$ 无关，可得：$a_1(b_1+b_2+b_3)+a_2(b_1+b_2+b_3)+a_3(b_1+b_2+b_3)$。第四行与第三行等价，只是额外添加了一对冗余括号，让第五行的变换更易理解。第五行对每个 $j$ 提取公因子 $(b_1+b_2+b_3)$，得到：$(a_1+a_2+a_3)(b_1+b_2+b_3)$。最后一行仅是上一行的另一种写法。该推导方式可用于证明一般形式的*分配律*，
```math
\sum_{j\in J,k\in K}a_jb_k = (\sum_{j\in J}a_j)(\sum_{k\in K}b_k). \tag{2.28}
```
对所有指标集 $J$ 和 $K$ 成立。

交换求和次序的基本法则 $(2.27)$ 存在多种变式，这类变式多用于限定下标取值范围，而非对所有整数 $j,k$ 全域求和。变式主要分为两种形式：常规形式与复杂形式。首先介绍常规形式：
```math
\sum_{j\in J}\sum_{k\in K}a_{j,k} = \sum_{j\in J, k\in K}a_{j,k} = \sum_{k\in K}\sum_{j\in J}a_{j,k} . \tag{2.29}
```

这只是式 $(2.27)$ 的另一种写法，因为艾弗森示性因子 $[j\in J,k\in K]$ 可分解为 $[j\in J][k\in K]$。当下标 $j$ 与 $k$ 的取值范围相互独立时，均可使用这种常规形式的法则。

交换次序的复杂形式公式会更巧妙一些，适用于内层求和的取值范围依赖外层求和下标变量的情形：
```math
\sum_{j\in J}\sum_{k\in K(j)}a_{j,k} = \sum_{k\in K'}\sum_{j\in J'(k)}a_{j,k}.  \tag{2.30}
```

其中集合 $J,K(j),K',J'(k)$ 必须满足如下关联关系：
```math
[j \in J][k\in K(j)] = [k\in K'][j\in J'(k)]
```

这类分解原则上总是可以实现的，我们只需令 $J=K'$ 为全体整数集，同时令 $K(j)=J'(k)$ 为约束二重和的基础性质 $P(j,k)$ 即可。但存在若干重要特例，使得集合 $J,K(j),K',J'(k)$ 具备简洁形式，这类特例在实际应用中频繁出现。下面给出一种极具实用价值的分解形式：
```math
[1\le j\le n][j\le k\le n] = [1\le j\le k\le n] = [1\le k\le n][1\le j\le k]. \tag{2.31}
```

这个艾弗森(Iverson)方程允许写成：
```math
\sum_{j=1}^n\sum_{k=j}^na_{j,k} = \sum_{1\le j\le k\le n}a_{j,k}  = \sum_{k=1}^n\sum_{j=1}^ka_{j,k}. \tag{2.32}
```

这两种累次和中，通常总有一种更便于计算；我们可以借助 $(2.32)$ 从难计算的形式转换为易计算的形式。

下面结合一个实用例子应用上述思路，考虑数阵
```math
\begin{bmatrix}
a_1a_1 & a_1a_2 & a_1a_3 & \cdots & a_1a_n \\
a_2a_1 & a_2a_2 & a_2a_3 & \cdots & a_2a_n \\
a_3a_1 & a_3a_2 & a_3a_3 & \cdots & a_3a_n \\
\vdots & \vdots & \vdots &  & \vdots \\
a_na_1 & a_na_2 & a_na_3 & \cdots & a_na_n \\
\end{bmatrix}
```
由 $n^2$ 个乘积项 $a_j a_k$ 构成。我们的目标是求出
```math
S_\triangle = \sum_{1\le j\le k\le n}a_ja_k,
```
数阵主对角线及其上方所有元素的和。由于 $a_j a_k = a_k a_j$，该数阵关于主对角线对称；因此 $S$ 的值约为全体元素和的一半（需额外计入主对角线的修正项）。

基于上述分析，我们可以进行如下推导变换：
```math
S_\triangle = \sum_{1\le j\le k\le n}a_ja_k =  \sum_{1\le k\le j\le n}a_ka_j = \sum_{1\le k\le j\le n}a_ja_k  = S_\triangledown,
```

这是因为我们可以将下标 $(j,k)$ 重命名为 $(k,j)$。此外，由于
$$[1\le j\le k\le n] + [1\le k\le j\le n] = [1\le j,k\le n] + [1\le j=k\le n]$$

于是可得
```math
\begin{aligned}
2S_\triangle &= S_\triangle + S_\triangledown =  \sum_{1\le k, j\le n}a_ja_k  +  \sum_{1\le k=j\le n}a_ja_k  .
\end{aligned}
```

由一般分配律 $(2.28)$ 可得，第一个和式等于 $\big(\sum_{j=1}^n a_j\big)\big(\sum_{k=1}^n a_k\big) = \big(\sum_{k=1}^n a_k\big)^2$。 第二个和式为 $\sum_{k=1}^n a_k^2$。因此有
```math
S_\triangle =\sum_{1\le j\le k\le n}a_ja_k  = \frac{1}{2}\left(\left(\sum_{k=1}^na_k\right)^2 + \sum_{k=1}^na_k^2\right) \tag{2.33}
```

由此得到用上三角和式表示为最简单重和的表达式。受此推导启发，我们再来看另一个二重和：
```math
S = \sum_{1\le j< k\le n}(a_k-a_j)(b_k-b_j) 
```

同样，将 $j$ 与 $k$ 互换后具有对称性：
```math
S = \sum_{1\le k< j\le n}(a_j-a_k)(b_j-b_k) = \sum_{1\le k< j\le n}(a_k-a_j)(b_k-b_j)
```

于是我们可以将 $S$ 自身相加，并利用恒等式
```math
[1\le j< k\le n] + [1\le k< j\le n] = [1\le j, k\le n] - [1\le j=k\le n]
```
得出：
```math
2S= \sum_{1\le j,k\le n}(a_j-a_k)(b_j-b_k) - \sum_{1\le j=k\le n}(a_j-a_k)(b_j-b_k)
```

上式中，第二项的和为 0；第一项可以分为四个和：
```math
\begin{aligned}
& \sum_{1\le j,k\le n}a_jb_j - \sum_{1\le j,k\le n}a_jb_k - \sum_{1\le j,k\le n}a_kb_j + \sum_{1\le j,k\le n}a_kb_k \\
&= 2\sum_{1\le j,k\le n}a_kb_k - 2\sum_{1\le j,k\le n}a_jb_k \\
&= 2n\sum_{1\le k\le n}a_kb_k - 2\left(\sum_{k=1}^na_k\right)\left(\sum_{k=1}^nb_k\right) 
\end{aligned}
```

最后一步中，两个和式均依据一般分配律 $(2.28)$ 完成化简。若第一个和式的变换不易理解，下面分步重新推导一遍：
$$
\begin{aligned}
2\sum_{1\le j,k\le n} a_kb_k
&= 2\sum_{1\le k\le n}\sum_{1\le j\le n} a_kb_k \\
&= 2\sum_{1\le k\le n} a_kb_k \sum_{1\le j\le n} 1 \\
&= 2\sum_{1\le k\le n} a_kb_k \cdot n
= 2n\sum_{1\le k\le n} a_kb_k .
\end{aligned}
$$

若求和式中未出现某个下标变量（此处为 $j$），只需将剩余部分乘以该下标变量取值集合的元素个数（此处为 $n$），便可直接消去该求和下标。
回到之前的推导步骤，现将等式两边同除以 $2$ 并整理变形，即可得到一个精巧的公式：
```math
(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) = n\sum_{1\le k\le n}a_kb_k - \sum_{1\le j< k\le n}(a_k-a_j)(b_k-b_j) \tag{2.34}
```
此等式产生了作为一种特殊情形的切比雪夫单调不等式(Chebyshev's monotonic inequalities):

```math
(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) \le n\sum_{k=1}^na_kb_k, \text{ if } a_1\le\cdots\le a_n \text{ and } b_1\le\cdots\le b_n;
```
```math
(\sum_{k=1}^na_k)(\sum_{k=1}^nb_k) \ge n\sum_{k=1}^n a_kb_k, \text{ if } a_1\le\cdots\le a_n \text{ and } b_1\gt\cdots\gt b_n;
```
（一般地，若 $a_1 \le \cdots \le a_n$，且 $p$ 是集合 $\{1,\dots,n\}$ 的一个排列，则不难证明：$\sum_{k=1}^n a_k b_{p(k)}$ 的最大值在 $b_{p(1)} \le \cdots \le b_{p(n)}$ 时取得，最小值在 $b_{p(1)} \ge \cdots \ge b_{p(n)}$ 时取得。）

多重求和与*单重*求和中变换求和下标的一般运算有着有趣的关联。由交换律可知
```math
\sum_{k\in K}a_k = \sum_{p(k)\in K}a_{p(k)},
```

若 $p(k)$ 是整数的任意排列。但当我们把 $k$ 替换为 $f(j)$，其中 $f$ 为任意函数时，又会发生什么呢？
```math
f: J\to K
```

将整数 $j \in J$ 映射为整数 $f(j) \in K$ 时，下标替换的通用公式为
```math
\sum_{j\in J}a_{f(j)} = \sum_{k\in K}a_k\#f^-(k), \tag{2.35}
```

其中 $\#f^-(k)$ 表明集合：
```math
f^-(k) = \{j|f(j) = k\}
```
即满足 $f(j)$ 等于 $k$ 且 $j \in J$ 的取值个数。

通过交换求和次序，不难证明式 $(2.35)$ 。
```math
\sum_{j\in J}a_{f(j)} = \sum_{j\in J, k\in K}a_k[f(j)=k] = \sum_{k\in K}a_k\sum_{j\in J}[f(j)=k]
```

由于 $\sum_{j\in J} [f(j)=k] = \#f^{-1}(k)$。在 $f$ 是集合 $J$ 与 $K$ 之间一一映射的特殊情形下，对任意 $k$ 都有 $\#f^{-1}(k)=1$，此时通用公式 $(2.35)$ 可化简为
```math
\sum_{j\in J}a_{f(j)} = \sum_{f(j)\in K}a_{f(j)} = \sum_{k\in K}a_k
```
这正是我们之前见过的交换律 $(2.17)$，只是形式稍有变换。

至此我们接触的多重和示例，通项均为 $a_k$，$b_k$ 这类一般形式。但本书侧重具体实例，下面来看一个含有具体数值的多重和：
```math
S_n = \sum_{1\le j < k \le n}\frac{1}{k-j}
```
例如  $S_1=0; S_2=1; S_3=\frac{1}{2-1}+\frac{1}{3-1}+\frac{1}{3-2} = \frac{5}{2} $

计算一个双重和的标准方法是先对 j 或先对 k 求和，所有讨论两种选取
```math
\begin{aligned}
S_n &=  \sum_{1\le k \le n}\sum_{1\le j < k}\frac{1}{k-j}  & & \text {summing first on j} \\
&=  \sum_{1\le k \le n}\sum_{1\le k-j < k}\frac{1}{j}   & & \text {replacing j by k − j} \\
&=  \sum_{1\le k \le n}\sum_{0< j\le k-1}\frac{1}{j}  & & \text {simplifying the bounds on j}\\
&=  \sum_{1\le k \le n}H_{k-1}  & & \text {by (2.13), the definition of } H_{k−1} \\
&=  \sum_{1\le k+1 \le n}H_k   & & \text {replacing k by k + 1} \\
&=  \sum_{0\le k < n}H_k & & \text {simplifying the bounds on k} \\
\end{aligned}
```

但是我们不知道如何得到调和数的和的闭形式。若尝试先对 $k$ 求和，则得到：
```math
\begin{aligned}
S_n &=  \sum_{1\le j \le n}\sum_{j< k \le n}\frac{1}{k-j}  & & \text {summing first on k} \\
&=  \sum_{1\le j \le n}\sum_{j\le k+j \le n}\frac{1}{k} & & \text {replacing k by k + j} \\
&=  \sum_{1\le j \le n}\sum_{0< k\le n-j}\frac{1}{k}& & \text {simplifying the bounds on k} \\
&=  \sum_{1\le j \le n}H_{n-j} & & \text {by (2.13), the definition of } H_{n−j}\\
&=  \sum_{1\le n-j \le n}H_j  & & \text {replacing j by n − j} \\
&=  \sum_{0\le j < n}H_j  & & \text {simplifying the bounds on j}
\end{aligned}
```
又回到相同的绝境。

还有另一种推导思路：在将 $S_n$ 化为多重和之前，先把 $k$ 替换为 $k+j$。
```math
\begin{aligned}
S_n &=  \sum_{1\le j < k \le n}\frac{1}{k-j} & & \text {recopying the given sum} \\
&=  \sum_{1\le j < k+j \le n}\frac{1}{k} & & \text {replacing k by k + j} \\
&=  \sum_{1\le k\le n}\sum_{1\le j\le n-k}\frac{1}{k} & & \text {summing first on j} \\
&=  \sum_{1\le k \le n}\frac{n-k}{k} & & \text {the sum on j is trivial} \\
&=  \sum_{1\le k \le n}\frac{n}{k} - \sum_{1\le k \le n}1 & & \text {by the associative law} \\
&=  n\left(\sum_{1\le k \le n}\frac{1}{k}\right) - n & & \text {by gosh} \\
&=  nH_n - n & & \text {by (2.13), the definition of }H_n
\end{aligned}
```
我们找到了 $S_n$。把它和冒失的开端结合起来，作为一个额外的结果：
```math
\sum_{0\le k < n}H_k = nH_n - n. \tag{2.36}
```

我们可以从代数和几何两个角度理解这里用到的技巧。（1）代数角度：若二重和的通项含有 $k+f(j)$，其中 $f$ 为任意函数，本例说明可尝试将 $k$ 换为 $k-f(j)$ 再对 $j$ 求和。（2）几何角度：以 $n=4$ 为例，可将该和式 $S_n$ 表示为如下形式：
```math
\begin{aligned}
 && k=1 \qquad k=2 \qquad k=3 \qquad k=4 \\
j=1 &&\frac{1}{1} \quad + \quad \frac{1}{2}\quad + \quad\frac{1}{3} \\
j=2 && \frac{1}{1}\quad+ \quad\frac{1}{2} \\
j=3 && \frac{1}{1}  \\
j=4 &&
\end{aligned}
```
最初按列先对 $j$ 求和、或按行先对 $k$ 求和，得到 $H_1+H_2+H_3=H_3+H_2+H_1$。而更巧妙的做法本质是沿对角线求和，得到 $\dfrac{3}{1}+\dfrac{2}{2}+\dfrac{1}{3}$。


## 2.5 一般的方法
我们将尝试找前 n 个平方和的一个闭形式，称它为 $\Box_n$
```math
\Box_n = \sum_{0\le k\le n}k^2,\ for\ n \ge 0 \tag{2.37}
```
将看到至少有 7 种不同的方法来解这个问题。

```math
\Box_n = \frac{n(n+1)(2n+1)}{6} ,\ for\ n \ge 0 \tag{2.38}
```

- 方法1：猜测解答，用归纳法证明

等价的公式是：
```math
\Box_n = \frac{n(n+1)(n+\frac{1}{2})}{3} ,\ for\ n \ge 0 \tag{2.39}
```

对于归纳法来说，假设 n > 0,且设当 n-1 替换 n 时，公式 (2.39) 成立，由于
```math
\Box_n = \Box_{n-1} + n^2 ,
```

得到：
```math
\begin{aligned}
3\Box_n &= n(n+1)(n+\frac{1}{2}) + 3n^2  \\
        &= (n^3 - \frac{3}{2}n^2 + \frac{1}{2}n) + 3n^2 \\
        &= (n^3 + \frac{3}{2}n^2 + \frac{1}{2}n) \\
        &= n(n+1)(n+\frac{1}{2})
\end{aligned}
```
所以无疑对所有 $n\ge 0$，公式(2.39) 确实成立。



- 方法2：摄动和
按照式 (2.24) 摄动方程：
```math
\begin{aligned}
\Box_n + (n+1)^2 &= \sum_{0\le k\le n}(k+1)^2  \\
    &= \sum_{0\le k\le n}(k^2+2k+1)\\
    &= \sum_{0\le k\le n}k^2 + 2\sum_{0\le k\le n}k \sum_{0\le k\le n}1 \\
    &= \Box_n + 2\sum_{0\le k\le n}k \sum_{0\le k\le n}1
\end{aligned}
```

$\Box_n$ 彼此消去了。偶尔摄动法产生像 $\Box_n = \Box_n$ 的结果，我们的工作白费了。另一方面，这个推导的结果并不是一点用没有，它展示了一种方法，把前 n 个整数相加为闭形式，
```math
2\sum_{0\le k\le n}k = (n+1)^2 - (n+1) ,
```

如果从整数立方的和开始，称它为 $\Box^3_n$，能否取的整数平方的一个表达式？让我们试试看。
```math
\begin{aligned}
\Box^3_n+ (n+1)^3 &= \sum_{0\le k\le n}(k+1)^3  \\
    &= \sum_{0\le k\le n}(k^3+3k^2+3k+1)\\
    &= \Box^3_n + 3\Box_n + 3\frac{(n+1)n}{2} + (n+1).
\end{aligned}
```
确实被消去，且有足够的资料来确定 $\Box_n$，而不依赖于归纳法：
```math
\begin{aligned}
3\Box_n  &= (n+1)^3 - 3\frac{(n+1)n}{2} - (n+1)  \\
    &= (n+1)(n^2 + 2n + 1 - \frac{3}{2}n - 1) \\
    &= (n+1)(n+\frac{1}{2})n.
\end{aligned}
```

- 方法3 建立所有组合部分
对于涉及 $n^2$ 的被加数，稍加推广递归式 (2.7) 也就够了。
```math
\begin{aligned}
R_0 &=  \alpha  \\
R_n &= R_{n-1} + \beta + \gamma n + \delta n^2, for\ n > 0, \tag{2.40}
\end{aligned}
```

的解将是一般形式的解：
```math
R_n = A(n)\alpha + B(n)\beta + C(n)\gamma + D(n)\delta; \tag{2.41}
```
且我们以及确定了 A(n) B(n) C(n)，因为当 $\delta=0$ 时，式 (2.41) 和 (2.7) 相同。若现在插入 $R_n = n^3$，发现当 $\alpha=0, \beta=1, \gamma=-3$ 时 $n^3$ 是解。因此
```math
3D(n) - 3C(n) + B(n) = n ^ 3
```
这样就确定了 D(n)。

我们对和 $\Box_n$ 感兴趣，它等于 $\Box_{n-1} + n^2$。于是，如果在式 (2.41) 中置 $\alpha=\beta=\gamma=0, \delta=1$，则取得 $\Box_n = R_n$，所以 $\Box_n = D(n)$。不需要从 B(n) 和 C(n) 计算 D(n) 的代数运算，因为已经知道了解答是什么，但是找到：
```math
3D(n) = n^3 + 3C(n) - B(n) = n^3 + 3\frac{(n+1)n}{2} - n = (n+1)(n+\frac{1}{2})n
```
将使怀疑者消除疑虑。


- 方法4 用积分替换和
在微积分中，积分可视为曲线下的面积，把接触曲线的长的小矩形加起来近似此面积。$\Box_n$ 是大小为 $1\times 1, 1\times 4, \cdots, 1\times n^2$ 的矩形面积之和，它近似等于 0 和 n 之间曲线 $f(x)=x^2$ 之下的面积。此曲线下的面积为 $\int_0^nx^2dx=n^3/3$，所有我们知道 $\Box_n$ 近似为 $n^3/3$。

用这个事实的一个方法是研究近似的误差 $E_n = \Box_n - n^3/3$。由于 $\Box_n$ 满足递归式 $\Box_n = \Box_{n-1} + n^2$ ，发现 $E_n$ 满足较简单的递归
```math
\begin{aligned}
E_n &=  \Box_n - n^3/3 =  \Box_{n-1} + n^2 - n^3/3\\
    &= E_{n-1} + (n-1)^3 + n^2 - n^3/3 \\
    &= E_{n-1} + n - 1/3
\end{aligned}
```

寻找积分近似的另一种方法是通过相加楔形误差项来找 $E_n$ 的公式。得到
```math
\begin{aligned}
\Box_n - \int_0^nx^2dx &=  \sum_{k=1}^n(k^2 - \int_{k-1}^kx^2dx)\\
    &= \sum_{k=1}^n(k^2 - \frac{k^3-(k-1)^3}{3}) = \sum_{k=1}^n(k-1/3)\\
\end{aligned}
```
不管用那一种方法，能找出 $E_n$，然后求得 $\Box_n$。


- 方法5 伸展和收缩
还有另外一种方式来找 $\Box_n$ 的闭形式，用看来较复杂的双重和来替换原来的和，如果适当的来回处理双重和，则实际上能简化它：
```math
\begin{aligned}
\Box_n &= \sum_{1\le k\le n}k^2 = \sum_{1\le j\le k\le n}k \qquad too\ abstract. \\ 
    &= \sum_{1\le j\le n}\sum_{j\le k\le n}k \\
    &= \sum_{1\le j\le n} \frac{j+n}{2} (n-j+1) \\
    &= \frac{1}{2} \sum_{1\le j\le n} (n(n+1) + j - j^2) \\
    &= \frac{1}{2}n^2(n+1) + \frac{1}{4}n(n+1) - \frac{1}{2}\Box_n \\
    &= \frac{1}{2}n(n+1)(n + \frac{1}{2})- \frac{1}{2}\Box_n \\
\end{aligned}
```
将单重求和转化为双重求和，乍看之下似乎是一种倒退，但实际上却是一种进步，因为它能产生更易于处理的求和形式。我们不能指望仅通过不断地化简、再化简来解决所有问题：毕竟，仅靠一味向上攀登是无法征服最高峰的。


- 方法6 用有限演算

- 方法7 用母函数


## 2.6 有限与无限微积分
现在以更高的高度来看求和问题，来学习更为广泛的观点的时候了。数学家们构建了一套有限微积分理论，它与更为传统的无限微积分相类似，借助这套理论，我们能够以简洁且系统化的方式处理求和问题。

无限微积分以*微分算子* $D$ 的性质为基础，该算子的定义为
```math
Df(x) = \lim_{h\to 0} \frac{f(x+h)-f(x)}{h}
```

有限微积分以*差分算子* $\Delta$ 的性质为基础，其定义为
```math
\Delta f(x) = f(x+1) - f(x).  \tag{2.42}
```
这便是导数的有限对应形式—— 在这种形式中，我们将 $h$ 的取值限定为正整数。因此，$h=1$ 是我们所能取到的、最接近（极限状态下 $h\to 0$）的取值。


符号 $D$ 和 $\Delta$ 被称为算子，因为它们作用于函数并生成新的函数；二者是作用于函数的函数，其运算结果仍为函数。若 $f$ 是从实数到实数的适当光滑函数，那么 $Df$ 同样是从实数到实数的函数。而若 $f$ 是任意一个从实数到实数的函数，$\Delta$ f也同样如此。函数 $Df$ 和 $\Delta$$f$ 在点 $x$ 处的取值均由上述定义给出。

在微积分的入门阶段，我们便学习了微分算子 $D$ 对幂函数 $f(x)=x^m$ 的作用规则，此时有 $Df(x)=mx^{m−1}$。我们可省略函数 $f$，将这一规则简记为
```math
D(x^m) = mx^{m-1} .
```

倘若差分算子 $\Delta$ 也能得出同样简洁优美的结果，那就再好不过了；遗憾的是，事实并非如此。例如，我们有
```math
\Delta(x^3) = (x+1)^3 - x^3 = 3x^2 + 3x + 1.
```

但存在一种 $m$ 次阶乘幂，其在差分算子 $\Delta$ 的作用下能呈现出简洁的变换规律，而这一点也正是有限微积分的精妙所在。这种新式的 $m$ 次幂，其定义规则为
```math
x^{\underline{m}} = \begin{matrix} m\ factors \\ \overbrace{x(x-1)\cdots(x-m-1)} \end{matrix}, m\ge 0. \tag{2.43}
```

注意看 $m$ 下方的短横线，它表示这 $m$ 个因子需依次递减；我们也有对应的定义，用以表示因子依次递增的情形：
```math
x^{\overline{m}} = \begin{matrix} m\ factors \\ \overbrace{x(x+1)\cdots(x+m-1)} \end{matrix}, m\ge 0. \tag{2.44}
```

当 $m=0$ 时，有 $x^{\underline{0}}​=x^{\overline{0}}=1$ ，因为按数学惯例，零个因子的乘积取 1（正如零个项的和按惯例取 0）。

若需口头读出 $x^{\underline{m}}$ ​，称其为 “x 的 m 次下降幂”；同理，$x^{\overline{m}}$ 为 “x 的 m 次上升幂”。这类函数也被称作**下降阶乘幂**和**上升阶乘幂**，因其与阶乘函数 $n!=n(n−1)…(1)$ 联系紧密。事实上，$n!=n^{\underline{n}}​=1^{\overline{n}}$。

数学文献中还出现了阶乘幂的其他几种记法，其中最常见的是珀赫哈默尔符号 $(x)_m$​，该符号可表示 $x^{\underline{m}}$ ​或 $x^{\overline{m}}$；也能见到 $(x)^m$ 这类记法被用来表示 $x^{\underline{m}}$ ​。而这种下划线上划线的记法正逐渐得到普及，因为它书写简便、易于记忆，且不存在冗余括号。

下降阶乘幂 $x^{\underline{m}}$ ​在差分算子 $\Delta$ 的作用下性质尤为优良，于是有
```math
\begin{aligned}
\Delta(x^{\underline{m}}) &= (x+1)^{\underline{m}} - x^{\underline{m}} \\ 
    &= (x+1)x\cdots(x-m+2) - x\cdot(x-m+2)(x-m+1) \\
    &= mx(x-1)\cdots(x-m+2)
\end{aligned}
```
因此有限的微积分也有简便的运算规则，与 $D(x^m) = mx^{m-1} $ 相呼应：
```math
\Delta(x^{\underline{m}}) = mx^{\underline{m-1}}. \tag{2.45}
```
这是基本的阶乘事实。

无限微积分中的微分算子 D 存在逆算子，即反导数（或积分）算子 $\int$ 。微积分基本定理建立了算子 D 与 $\int$ 之间的关联:
```math
g(x) = Df(x) \quad \text{if and only if } \quad \int g(x)dx = f(x) + C.
```

其中 $\int g(x)dx$ 为 $g(x)$ 的不定积分，指所有导数为 $g(x)$ 的函数所构成的函数类。与之类似，差分算子 $\Delta$ 也存在逆算子，即反差分（或求和）算子 $\sum$;并且有限微积分中也有对应的一条基本定理。
```math
g(x) = \Delta f(x) \quad \text{if and only if } \quad \sum g(x)\delta x = f(x) + C. \tag{2.46}
```

$\sum g(x)\delta x$ 为 $g(x)$ 的不定和，指所有差分等于 $g(x)$ 的函数所构成的函数类。（注意小写的 $\delta$ 与大写的 $\Delta$ 的对应关系，恰如小写的 d 与大写的 D 的对应关系。）不定积分中的 C 为任意常数；而不定和中的 C 则是满足 $p(x+1)=p(x)$ 的任意函数。例如，C 可以是周期函数 $a+b\sin2\pi x$; 这类函数在取差分时会被消去，正如常数在求导时会被消去一样。当 x 取整数值时，函数 C 为常数。

接下来我们就要揭晓核心结论了。无限微积分中还定义了定积分：若 $g(x)=Df(x)$，则
```math
\int_a^b g(x)dx = f(x)\bigg|_a^b = f(b) - f(a) .
```

因此，有限微积分 —— 向来效仿这位更为知名的 “同门兄长”—— 也有定和的概念：若 $g(x)=\Delta f(x)$，则
```math
\sum_a^b g(x)\delta x = f(x)\bigg|_a^b = f(b) - f(a) . \tag{2.47}
```

直观上，$\sum_a^b g(x)\delta x$ 究竟代表什么含义？我们对它的定义源于类比，而非实际的必然需求。我们希望这一类比关系能够成立，这样便能轻松记住有限微积分的运算法则；但倘若无法理解其背后的含义，这套记法便毫无实用价值。不妨先从一些特例入手，推导它的具体含义，我们先做出如下假设： $g(x) = \Delta f(x) = f(x+1) - f(x) $, 如果 $b=a$，有：
```math
\sum_a^a g(x)\delta x = f(a) - f(a) = 0. 
```

接下来，如果 $b=a+1$，结果是：
```math
\sum_a^{a+1} g(x)\delta x = f(a+1) - f(a) = g(a). 
```

更一般地，若 b 增加 1，则有
```math
\begin{aligned}
\sum_a^{b+1} g(x)\delta x - \sum_a^{b} g(x)\delta x &= (f(b+1) - f(a)) - (f(b) -f(a)) \\
&= f(b+1) - f(b) = g(b). 
\end{aligned}
```

结合这些结论与数学归纳法，便能精确推导出：当满足 $b\ge a$ 的且为整数时，$\sum_a^b g(x)\delta x$ 的一般含义：
```math
\sum_a^b g(x)\delta x = \sum_{k=a}^{b-1} g(k) = \sum_{a\le k < b}g(k), for\ int\ b\ge a. \tag{2.48}
```

换言之，定和与带上下限的普通求和含义一致，只是排除了上限处的函数值。

我们换一种稍许不同的方式来梳理这一结论。假设我们遇到一个待求闭式解的未知求和式，且能将其写成 $\sum_{a\le k<b} g(k)= \sum_a^b g(x)\delta x$ 的形式。有限微积分的理论表明，只要我们能找到一个满足 $g(x)=f(x+1)−f(x)$ 的不定和（即反差分）函数 $f$，就能将该求和式的结果表示为 $f(b)−f(a)$ 。要理解这一原理，一种方法是利用省略号记法，将 $\sum_{a\le k<b} g(k)$ 完全展开：
```math
\begin{aligned}
\sum_{a\le k< b} (f(k+1) - f(k)) &= (f(a+1) - f(a)) + (f(a+2) - f(a+1)) + \cdots \\
        & + (f(b-1) - f(b-2) + (f(b) - f(b-1))).
\end{aligned}
```

右侧所有项均相互抵消，仅保留 $f(b) − f(a)$；因此 $f(b) − f(a)$ 即为该和式的值。(形如 $\sum_{a\le k< b} (f(k+1) - f(k))$) 的求和通常被称为链式 (telescoping) 求和，其命名源于伸缩式望远镜的原理：伸缩式望远镜的总厚度完全由最外层管的外半径与最内层管的内半径决定。）

但规则(2.48)仅在 $b\ge a$ 时适用；如果 $b < a$，会怎样呢？ (2.47)指出我们必须有
```math
\begin{aligned}
\sum_a^b g(x)\delta x &= (f(b) - f(a)) \\
    &= - (f(a) - f(b)) = - \sum_b^a g(x)\delta x
\end{aligned}
```

这与定积分的相应方程类似。完整地表述出来:
```math
\sum_a^b g(x)\delta x + \sum_b^c g(x)\delta x = \sum_a^c g(x)\delta x. \tag{2.49}
```

此时，我们当中可能有些人开始怀疑，这些平行和类比到底能给我们带来什么？首先，定积分为我们提供了一种简单的方法来计算下降幂的和：基本法则(2.45)、(2.47) 和 (2.48) 推导出了普遍法则:
```math
\sum_{0\le k<n} k^{\underline{m}} = \frac{k^{\underline{m+1}}}{m+1}\bigg|_0^n = \frac{n^{\underline{m+1}}}{m+1}, m, n\ge 0. \tag{2.50}
```

这个公式很容易记住，它与熟悉的公式很类似：
```math
\int_0^n x^mdx = n^{m+1}/(m+1).
```

特别是，当 $m = 1$ 时，我们有 $k^{\underline{1}} = k$，因此有限微积分的原理为我们提供了一种轻松记忆这一事实的方法:
```math
\sum_{0\le k<n} k = \frac{n^{\underline{2}}}{2} = n(n-1)/2 .
```

定积分方法还让我们隐约意识到，对范围 $0\le k < n$ 求和往往比对  $1\le k\le n$ 求和更简单；前者恰好是 $f(n) − f(0)$，而后者则必须计算为 $f(n + 1) − f(1)$。

如果我们将普通幂首先用下降幂表示，也可以用这种新方法求和。例如，
```math
k^2 = k^{\underline{2}} + k^{\underline{1}} .
```

因此
```math
\sum_{0\le k<n} k^2 = \frac{n^{\underline{3}}}{3} + \frac{n^{\underline{2}}}{2} = \frac{1}{3}n(n-1)(n-2+\frac{3}{2}) =  \frac{1}{3}n(n-\frac{1}{2})(n-1).
```
将 n 替换为 n + 1，为我们提供了另一种计算我们老朋友 $\Box_n = \sum_{0\le k\le n} k^2$ 的闭式表达的方法。

这可真简单。事实上，它比上一节中那些把这一公式讲得烂熟的无数种方法还要简单。那么，让我们试着再进一步，从平方到立方：一个简单的计算表明
```math
k^3 = k^{\underline{3}} + 3k^{\underline{2}} + k^{\underline{1}} .
```

(通过使用斯特林数，总是可以实现普通幂与阶乘幂之间的转换，我们将在第6章中研究这些数。) 因此
```math
\sum_{a\le k<b} k^3 = \frac{k^{\underline{4}}}{4} + k^{\underline{3}} + \frac{k^{\underline{2}}}{2} \bigg|_a^b .
```

因此，下降幂非常适合求和。但它们还有其他可取之处吗？我们是否必须先将熟悉的普通幂转换为下降幂，然后再转回，才能进行其他操作？其实不然，很多时候可以直接处理阶乘幂，因为它们具有额外的性质。例如，正如我们有 $(x + y)^2 = x^2 + 2xy + y^2$ 一样，事实证明 $(x + y)^{\underline{2}} = x^{\underline{2}} + 2x^{\underline{1}}y^{\underline{1}} + y^{\underline{2}}$ ，同样的类比也适用于 $(x + y)^m 和 $(x + y)^{\underline{m}}$。（这一“阶乘二项式定理”在练习5.37中得到证明。）

到目前为止，我们只考虑了具有非负指数的下降幂。为了将与普通幂的类比扩展到负指数，

我们需要一个合适的定义 $x^{\underline{m}}$ ，其中 $m < 0$。查看该序列
```math
\begin{aligned}
x^{\underline{3}} &= x(x-1)(x-2), \\
x^{\underline{2}} &= x(x-1), \\
x^{\underline{1}} &= x, \\
x^{\underline{0}} &= 1
\end{aligned}
```

我们注意到，要从 $x^{\underline{3}}$ 到 $x^{\underline{2}}$，再到 $x^{\underline{1}}$，最后到 $x^{\underline{0}}$，我们需要依次除以 $x-2$，然后除以 $x-1$，再除以 $x$。似乎合理（即使不是必须的）的是，接下来我们应该除以 $x+1$，从而将 $x^{\underline{0}}$ 转化为$x^{\underline{-1}}$，进而得到 $x^{\underline{-1}}=1/(x+1)$。继续下去，前几个负指数下降幂是
```math
\begin{aligned}
x^{\underline{-1}} &= \frac{1}{x+1}, \\
x^{\underline{-2}} &= \frac{1}{(x+1)(x+2)}, \\
x^{\underline{-3}} &= \frac{1}{(x+1)(x+2)(x+3)},
\end{aligned}
```

我们对负下降幂的一般定义是
```math
x^{\underline{-m}} = \frac{1}{(x+1)(x+2)\cdots(x+m)}, for\ m>0. \tag{2.51}
```

(也可以为实数甚至复数 m定义下降幂，但我们将在第5章之前暂不讨论。)
有了这个定义，下降幂还具有其他一些优良性质。其中也许最重要的是一个一般的指数法则，类似于该法则
```math
x^{m+n} = x^mx^n
```

对于普通幂。下降幂版本是
```math
x^{\underline{m+n}} = x^{\underline{m}}(x-m)^{\underline{n}}. \tag{2.52}
```

例如， $x^{\underline{2+3}} = x^{\underline{2}}(x-2)^{\underline{3}}$；对于负的 n，我们有
```math
x^{\underline{2-3}} = x^{\underline{2}}(x-2)^{\underline{-3}} = x(x-1)\frac{1}{(x-1)x(x+1)} = \frac{1}{x+1}  = x^{\underline{-1}}. 
```

如果我们选择将 $x^{\underline{-1}}$ 定义为 $1/x$，而不是定义为 $1/(x+1)$，那么指数法则(2.52)在诸如 $m = −1$ 和 $n = 1$ 的情况下就会失效。事实上，我们完全可以用 (2.52) 来精确地告诉我们，在负指数的情况下，下降幂究竟应该如何定义，只需设定 $m = −n$ 即可。当一种现有的记号被扩展以涵盖更多情形时，最好总是以这样一种方式来给出定义，使得一般的法则能够继续成立。

现在，让我们确保新定义的下降幂满足关键的差分性质。当 $m<0$ 时，是否 $\Delta x^{\underline{m}} = mx^{\underline{m-1}}？$ 例如，如果 $m = −2$，则差分为
```math
\begin{aligned}
\Delta x^{\underline{-2}} &= \frac{1}{(x+2)x(x+3)} - \frac{1}{(x+1)(x+2)}  \\
        &= \frac{(x+1)-(x+3)}{(x+1)(x+2)x(x+3)} \\
        &= -2x^{\underline{-3}}. 
\end{aligned}
```
是的，它有效！类似的论证适用于所有 $m < 0$.

因此，求和性质（2.50）对于负下降幂以及正下降幂均成立，只要不出现除以零的情况：
```math
\sum_a^bx^{\underline{m}}\delta x = \frac{x^{\underline{m+1}}}{m+1}\bigg|_a^b, for\ m\ne -1.
```

但是，当 $m = −1$ 时又如何呢？请记住，对于积分，我们使用
```math
\int_0^n x^{-1}dx = \ln x\bigg|_a^b.
```

当 $m = −1$ 时，我们希望得到 $\ln x$ 的有限模拟；换句话说，我们寻找一个函数 $f(x)$，使得
```math
x^{\underline{-1}} = \frac{1}{x+1} = \Delta f(x) = f(x+1) - f(x) .
```

不难看出，
```math
f(x) = \frac{1}{1} + \frac{1}{2} + \cdots + \frac{1}{x} .
```

是一种这样的函数，当 $x$ 为整数时，该量恰好是 (2.13) 的调和数 $H_x$。因此，$H_x$ 是连续对数 $\ln x$ 的离散模拟。（我们将在第6章中定义非整数 $x$ 的 $H_x$，但就目前目的而言，整数值已足够。我们还将在第9章中看到，对于较大的 $x$， $H_x-\ln x$ 的值大约等于 $0.577 + 1/(2x)$。因此， $H_x$ 与 $\ln x$ 不仅具有相似性，它们的值通常相差不到 1。）

我们现在可以完整地描述下降幂的和：
```math
\sum_a^bx^{\underline{m}}\delta x = 
\begin{cases} 
\frac{x^{\underline{m+1}}}{m+1}\bigg|_a^b, & for\ m\ne -1; \\
H_x\bigg|_a^b, & for\ m=-1. \tag{2.53}
\end{cases} 
```

这个公式表明，为什么调和数会频繁出现在诸如快速排序分析之类的离散问题的解中，正如所谓的自然对数会自然而然地出现在连续问题的解中一样。

现在我们已经找到了 $\ln x$ 的类比，让我们来看看是否有 $e^x$ 的类比。哪个函数 $f(x)$ 具有性质 $\Delta f(x) = f(x)$，对应于恒等式 $De^x=e^x$？很简单：
```math
f(x+1) - f(x) = f(x) \iff f(x+1) = 2f(x) ;
```

因此，我们处理的是一个简单的递归关系，我们可以将 $f(x) = 2^x$ 视为离散指数函数。

$c^x$ 的差值也相当简单，对于任意 $c$，即
```math
\Delta(c^x) = c^{x+1} - c^x = (c-1)c^x.
```

因此， $c^x$ 的反差分(anti-difference)为 $c^x/(c − 1)$，如果 $c\ne 1$。这一事实，连同基本定律 (2.47) 和 (2.48)，为我们提供了一种简洁的方法来理解等比数列求和的一般公式：
```math
\sum_{a\le k<b} c^k = \sum_a^b c^x\delta x = \frac{c^x}{c-1}\bigg|_a^b = \frac{c^b-c^a}{c-1}, for\ c\ne 1.
```

每次我们遇到一个可能以封闭形式表示的函数 $f$，我们都可以计算它的差分 $\Delta f = g$；然后我们就得到了一个函数 $g$，其不定和 $\sum g(x) \delta x$ 是已知的。表55是用于求和的差分/反差分对表的开头。

尽管连续数学和离散数学之间存在诸多相似之处，但某些连续概念却并无对应的离散版本。例如，无穷微积分中的链式法则对于复合函数的导数非常方便；然而，在有限微积分中并不存在相应的链式法则，因为 $\Delta f(g(x))$ 并没有一个简洁的表达形式。离散变量替换较为困难，除非在某些特殊情况下，比如用 $c\pm x$ 代替 $x$。

然而， $\Delta(f(x)g(x))$ 具有相当优美的形式，它为我们提供了一种分部求和的规则，这是无穷微积分中称为分部积分的有限版本。让我们回顾一下这个公式
```math
D(uv) = uDv + vDu
```

在无限微积分中，则导出了分部积分法则，
```math
\int uDv = uv - \int vDu,
```

在整合并重新排列各项之后，我们可以在有限微积分中做类似的事情。

我们首先对两个函数的乘积应用差分算子 $u(x)$ 和 $v(x)$:
```math
\begin{aligned}
\Delta (u(x)v(x)) &= u(x+1)v(x+1) - u(x)v(x)  \\
        &= u(x+1)v(x+1) - u(x)v(x+1)  \\
        & + u(x)v(x+1) - u(x)v(x)  \\
        &= u(x)\Delta v(x) + v(x+1)\Delta u(x) . \tag{2.54}
\end{aligned}
```

此公式可利用 *移位运算符* $E$ 以便捷形式表示，该运算符由定义
```math
Ef(x) = f(x+1).
```

将 $Ev(x)$ 替换为 $v(x+1)$，可得到乘积差的紧凑规则：
```math
\Delta(uv) = u\Delta v + Ev\Delta u.\tag{2.55}
```

(E有点麻烦，但它使等式成立。) 对该等式两边取不定和，并重新排列各项，即可得到所宣传的分部求和法则：
```math
\sum u\Delta v = uv - \sum Ev\Delta u.\tag{2.56}
```

与无穷微积分一样，可以对所有三个项施加限制，从而使不定和变为定和。

当左侧的求和比右侧更难计算时，这条规则很有用。我们来看一个例子。函数 $\int xe^xdx$ 通常采用分部积分法进行计算；它的离散类似物是 $\sum x2^x\delta x$，我们在本章前面已经遇到过这种形式 $\sum_{k=0}^n k2^k$。为了对这个求和进行分部积分，我们令 $u(x) = x$ 且 $\Delta v(x)=2^x$；因此 $\Delta u(x)=1, v(x)=2^x$，且 $Ev(x)=2^{x+1}$。代入(2.56) 得
```math
\sum x2^x\delta x = x2^x - \sum 2^{x+1}\delta x = x2^x - 2^{x+1} + C.
```

我们可以用这个来评估我们之前所做的求和，方法是附加限制：
```math
\begin{aligned}
\sum_{k=0}^n k2^k &= \sum_0^{n+1} x2^x\delta x \\
    &= x2^x - 2^{x+1}\bigg|_0^{n+1} \\
    &= ((n+1)2^{n+1} - 2^{n+2}) - (0\cdot 2^0 - 2^1) \\
    &= (n-1)2^{n+1} + 2.
\end{aligned}
```

用这种方法求和比用微扰法更容易，因为我们不用动脑筋。

我们偶然发现了一个公式，用于 $\sum_{0\le k<n} H_k$ 在本章前面，并且自认为很幸运。但如果我们知道分部求和法，本可以更系统地找到我们的公式(2.36)。让我们通过解决一个看似更难的求和问题来证明这一断言： $\sum_{0\le k<n} kH_k$。如果我们以 $\int x\ln xdx$ 为类比，这个解题过程并不困难。我们设 $u(x) = H_x, \Delta v(x) = x = x^{\underline{1}}$，因此 $\Delta u(x) = x^{\underline{-1}}，v(x) = x^{\underline{2}}/2，Ev(x) = (x+1)^{\underline{2}}/2$，于是我们得到
```math
\begin{aligned}
\sum xH_x\delta x &= \frac{x^{\underline{2}}}{2}H_x - \sum\frac{(x+1)^{\underline{2}}}{2}x^{\underline{-1}}\delta x \\
    &= \frac{x^{\underline{2}}}{2}H_x - \frac{1}{2}\sum x^{\underline{1}}\delta x \\
    &= \frac{x^{\underline{2}}}{2}H_x - \frac{x^{\underline{2}}}{4} + C.
\end{aligned}
```

从第一行到第二行，我们利用指数法则(2.52)，将两个下降的幂 $(x+1)^{\underline{2}}x^{\underline{-1}}$ 合并起来，其中 $m=−1$ 且 $n=2$。现在我们可以加上极限，并得出结论
```math
\sum_{a\le k<n} kH_k = \sum_0^n xH_x \delta x = \frac{n^{\underline{2}}}{2}(H_n-\frac{1}{2}). \tag{2.57}
```


## 2.7 无穷级数
当我们定义本章开头的 $\sum$ 符号表示，通过以下方式回避了无穷级数的问题： “等等再谈。目前，我们可以假设我们遇到的所有级数都只有有限个非零项。” 但清算的时刻终于到来了；我们必须面对求和可以是无限的这一事实。事实上，无限求和既带来好消息，也带来坏消息。

首先，坏消息是：我们用于操作 $\sum$ 的方法，在涉及无穷级数时，并不总是有效的。但接下来，好消息是：有一大类易于理解的无穷级数，我们之前所做的一切运算都是完全合法的。在更深入地探讨求和的本质含义之后，这两条消息背后的缘由便会变得清晰明了。

每个人都知道什么是有限求和：我们一个接一个地把一堆项加起来，直到全部加完。但无限求和需要更仔细地定义，否则我们可能会陷入悖论般的境地。

例如，似乎很自然地定义事物，使无穷级数
```math
S = 1 + \frac{1}{2} + \frac{1}{4} + \frac{1}{8} + \frac{1}{16} + \frac{1}{32} + \cdots
```
等于 2，因为如果我们把它加倍，就得到
```math
2S = 2 + 1 + \frac{1}{2} + \frac{1}{4} + \frac{1}{8} + \frac{1}{16} + \frac{1}{32} + \cdots = 2 + S.
```

另一方面，同样的推理表明，我们应当定义
```math
T = 1 + 2 + 4 + 8 + 16 + 32 + \cdots
```

结果为 −1，因为如果我们把它加倍，就会得到
```math
2T = 2 + 4 + 8 + 16 + 32 + 64 + \cdots = T - 1
```

有些奇怪的事情正在发生；我们怎么可能通过求和正数得到一个负数呢？看起来，最好还是不定义 $T$；或者，也许我们应该说 $T=\infty$，因为 $T$ 中的项会变得比任何固定的有限数都大。（请注意，$\infty$ 是方程 $2T = T − 1$ 的另一个“解”；它也“解”了方程 2S = 2 + S。）

让我们试着为一般求和的值制定一个良好的定义 $\sum_{k\in K} a_k$，其中 $K$ 可能是无限的。首先，我们假设所有项 $a_k$ 都是非负的。那么，一个合适的定义并不难找到：如果存在一个上界常数 $A$，使得
```math
\sum_{k\in K} a_k \le A
```

对于所有有限子集 $F\subset K$，我们定义 $\sum_{k\in K} a_k$ 是*最小*的 $A$。(根据实数的已知性质，所有此类 $A$ 的集合总是包含一个最小元素。)但如果不存在有界常数 $A$，我们就说 $\sum_{k\in K} a_k=\infty$；这意味着，如果 $A$ 是任意实数，总存在有限个项 $a_k$，其和超过 $A$。

前一段中的定义经过了仔细制定，因此它不依赖于索引集可能存在的任何顺序 $K$。因此，我们即将提出的论点适用于具有多个索引的多重求和 $k_1, k_2,\cdots$，而不仅仅适用于对整数集合的求和。

在特殊情况下，当 $K$ 是非负整数集时，我们对非负项的定义 $a_k$ 意味着
```math
\sum_{k\ge 0} a_k = \lim_{n\to\infty}\sum_{k=0}^n a_k.
```

原因如下：任何实数的非递减序列都有一个极限（可能为 $\infty$）。如果该极限是 $A$，且若 $F$ 是任意有限的非负整数集合，其元素均满足 $\le n$，则有 $\sum_{k\in K} a_k\le \sum_{k=0}^n a_k \le A$；因此 $A=\infty$ 或 $A$ 是一个界常数。若 $A'$ 是小于所述极限 $A$ 的任意数，则存在一个 $n$，使得 $\sum_{k=0}^n a_k > A'$；因此，有限集合 $ F=\{0, 1,\cdots,n\}$ 证明了 $A'$ 不是界常数。

现在，根据刚才给出的定义，我们可以轻松地计算某些无穷级数的值。例如，如果 $a_k = x^k$，那么
```math
\sum_{k\ge 0} x_k = \lim_{n\to\infty}\frac{1-x^{n+1}}{1-x} = 
\begin{cases} 
1/(1-x), & if\ 0\le x <1; \\
\infty, & if\ x\ne 1.
\end{cases} 
```

特别是，刚才考虑的无穷级数 $S$ 和 $T$ 分别具有值 2 和 $\infty$，正如我们所怀疑的那样。另一个有趣的例子是
```math
\begin{aligned}
\sum_{k\ge 0} \frac{1}{(k+1)(k+2)} &= \sum_{k\ge 0}k^{\underline{-2}} \\
    &= \lim_{n\to\infty}\sum_0^nk^{\underline{-2}} = \lim_{n\to\infty}\frac{k^{\underline{-1}}}{-1}\bigg|_0^n=1.
\end{aligned}
```

现在，让我们考虑一下，总和中可能既有负项，也有非负项的情况。例如，它的值应该是什么？
```math
\sum_{k\ge 0} (-1)k = 1 - 1 + 1 - 1 + 1 - 1 + \cdots?
```

如果我们把术语两两分组，我们会得到
```math
(1 - 1) + (1 - 1) + (1 - 1) + \cdots = 0 + 0 + 0 + \cdots
```
因此，总和为零；但如果我们从后一步开始配对，我们
```math
1 - (1 - 1) - (1 - 1) - (1 - 1) - \cdots = 1 - 0 - 0 - 0 + \cdots
```
总和是 1.

我们也可以尝试在公式 $\sum_{k\ge 0} (x)k = 1/(1−x)$ 中设置 $x = −1$，因为我们已经证明了当 $0\le x <1$ 时，该公式成立；但这样一来，我们不得不得出结论：无穷级数的和是 $\frac{1}{2}$，尽管它是由整数组成的求和公式。

另一个有趣的例子是双向无限的 $\sum_ka_k$ 其中 $a_k=1/(k+1)$ 对于 $k\ge 0$ 和 $a_k=1/(k-1)$ 对于 $k<0$。我们可以将其写成
```math
\cdots + (-\frac{1}{4}) + (-\frac{1}{3}) + (-\frac{1}{2}) + 1 + \frac{1}{2} + \frac{1}{3} + \frac{1}{4} + \cdots.\tag{2.58}
```

如果我们从“中心”元素开始向外围求和，
```math
\cdots + (-\frac{1}{4} + (-\frac{1}{3} + (-\frac{1}{2} + (1) + \frac{1}{2}) + \frac{1}{3}) + \frac{1}{4}) + \cdots,
```

我们得到值 1；如果我们把所有括号向左移动一步，我们会得到相同的值 1，
```math
\cdots + (-\frac{1}{5} + (-\frac{1}{4} + (-\frac{1}{3} + (-\frac{1}{2}) + 1) + \frac{1}{2}) + \frac{1}{3}) + \cdots,
```

因为最内层 $n$ 括号内所有数字的和是
```math
-\frac{1}{n+1} - \frac{1}{n} - \cdots -\frac{1}{2} +  1 + \frac{1}{2} + \cdots + \frac{1}{n-1} = 1 - \frac{1}{n} - \frac{1}{n+1},
```

类似的论证表明，如果将这些括号向左或向右移动任意固定数量，该值为 1；这促使我们相信，该和确实为 1。另一方面，如果我们以如下方式分组项，
```math
\cdots + (-\frac{1}{4} + (-\frac{1}{3} + (-\frac{1}{2} + 1 + \frac{1}{2}) + \frac{1}{3} + \frac{1}{4})  + \frac{1}{5} + \frac{1}{6}) + \cdots,
```

第 n 对括号从里向外包含数字
```math
-\frac{1}{n+1} - \frac{1}{n} - \cdots -\frac{1}{2} +  1 + \frac{1}{2} + \cdots + \frac{1}{2n-1} + \frac{1}{2n} = 1 + H_{2n} - H_{n+1},
```

我们在第 9 章将证明，当 $n$ 趋于无穷大时，$\lim_{n\to\infty}(H_{2n}−H_{n+1})=\ln 2$；因此，这种分组表明，这个双向无限的实际上应等于 $1+\ln 2$.

有些求和方式，即使其项以不同顺序相加，也会得出不同的值。关于分析的高级教材提供了多种定义，可为这类病态求和赋予有意义的值；但如果我们采用这些定义，就无法像之前那样自由地使用 $\sum -$ 符号。对于本书的目的而言，我们并不需要“条件收敛”这种精细的修正；因此，我们将坚持使用一种能够保持本章中所有运算有效性的无穷级数定义。

事实上，我们对无穷级数的定义相当简单。设 $K$ 为任意集合，且对于每个 $k\in K$，都定义了一个实数值项 $a_k$。（这里 $'k'$ 实际上可能代表多个下标 $k_1, k_2,\cdots,$ 因此 $K$ 可能是多维的。）任何实数 $x$ 都可以表示为其正部分与负部分之差，
```math
x = x^+ - x^-, where\ x^+=x\cdot[x>0] and\ x^-=-x\cdot[x<0].
```

(要么 $x^+= 0\ or\ x^−= 0$。) 我们已经解释了如何为无穷级数 $\sum_{k\in K} a_k^+$ 和 $\sum_{k\in K} a_k^-$ 定义值，因为 $a_k^+$ 和 $a_k^-$ 都是非负的。因此，我们的通用定义是
```math
\sum_{k\in K} a_k = \sum_{k\in K} a_k^+ - \sum_{k\in K} a_k^-, \tag{2.59}
```
除非右侧的和都等于 $\infty$。在后一种情况下，我们保留 $\sum_{k\in K} a_k$ 未定义。

让 $A^+=\sum_{k\in K} a_k^+$ 和  $A^-=\sum_{k\in K} a_k^-$ 。如果 $A^+$ 和 $A^-$ 都是有限的，求和 $\sum_{k\in K} a_k$ 被称为*绝对收敛*到值 $A=A^+-A^-$。如果 $A^+=\infty$，但 $A^-$ 是有限的，则求和 $\sum_{k\in K} a_k$ 被称为*发散*到 $+\infty$。类似地，如果 $A^-=\infty$，但 $A^+$ 是有限的，则求和 $\sum_{k\in K} a_k$ 被称为*发散*到 $-\infty$。如果 $A^+=A^-=\infty$，则一切皆休。

我们首先给出一个适用于非负项的定义，然后将其推广到实数值项。如果项 $a_k$ 是复数，我们还可以以显而易见的方式再次扩展该定义：求和 $\sum_{k\in K} a_k$ 被定义为 $\sum_{k\in K} \Re a_k +i\sum_{k\in K} \Im a_k$，其中 $\Re a_k $ 和 $\Im a_k$ 分别是 $a_k$ 的实部和虚部，只要这两个求和都已定义。否则 $\sum_{k\in K} a_k$ 未定义。（参见练习18）

正如前面所述，坏消息是，某些无穷级数必须保持未定义状态，因为我们所进行的运算在所有此类情况下都会导致不一致。（参见练习34。）好消息是，只要我们处理的是如前所述绝对收敛的级数，本章中所有的运算都是完全有效的。

我们可以通过证明我们的每个变换规则都保持所有绝对收敛级数的值来验证这一好消息。更明确地说，这意味着我们必须证明分配律、结合律和交换律，以及先对一个索引变量求和的规则；我们所做的一切其他内容都是从这四个关于级数的基本运算中推导出来的。

分配律(2.15)可以更精确地表述如下：如果 $\sum_{k\in K} a_k$ 绝对收敛于 $A$，且 $c$ 是任意复数，则 $\sum_{k\in K} ca_k$ 绝对收敛于 $cA$。我们可以通过将求和分解为实部与虚部、正部分与负部分来证明这一点，如上所述，并通过证明当 $c > 0$ 且每个项 $a_k$ 非负时的特殊情况来完成证明。在这种特殊情况下，证明成立，因为 $\sum_{k\in F} ca_k=c\sum_{k\in F} a_k$  对于所有有限集 $F$ 成立；后一个事实可通过归纳法，根据 $F$ 的大小来证明。

结合律（2.16）可表述如下：如果 $\sum_{k\in K} a_k$ 和 $\sum_{k\in K} b_k$ 绝对收敛于 $A$ 和 $B$，则 $\sum_{k\in K} (a_k+b_k)$ 绝对收敛于 $A+B$。这实际上是稍后我们将证明的一个更一般定理的特例。

交换律(2.17)其实无需证明，因为在(2.35)之后的讨论中，我们已经展示了如何将其作为求和顺序互换的一般规则的特例推导出来。

我们需要证明的主要结果是多重求和的基本原理： *绝对收敛*(Absolutely convergent)的多重求和总是可以先对任意一个索引进行求和。 形式上，我们将证明，如果 $J$ 且 $\{K_j|j\in J\}$ 的元素是任意索引集合，那么
```math
\sum_{j\in J, k\in K_j} a_{j,k}, 绝对收敛于 A,
```

那么，对于每个 $j\in J$，都存在复数 $A_j$，使得
```math
\sum_{k\in K_j} a_{j,k}, 绝对收敛于 A_j,
```
```math
\sum_{j\in J} A_j, 绝对收敛于 A,
```

当所有项均为非负时，证明此断言就足够了，因为我们可以像之前那样，将所有内容分解为实部和虚部、正部和负部，从而证明一般情况。因此，我们假设 $a_{j,k}\ge 0$ 对于所有对 $(j, k)\in M$ 成立，其中 $M$ 是主索引集 $\{(j, k)|j\in J, k\in K_j\}$。

我们已知 $\sum_{(j,k)\in M} a_{j,k}$ 是有限的，即
```math
\sum_{(j, k)\in F} a_{j,k} \le A
```

对于所有有限子集 $F\subseteq M$，且 $A$ 是最小的此类上界。如果 $j$ 是 $J$ 中的任意元素，则形如 $\sum_{k\in F_j} a_{j,k}$ 的每个求和式中， $F_j$ 是 $K_j$ 的一个有限子集，其上界为 $A$。因此，这些有限求和式具有最小上界 $A_j\ge 0$，并且根据定义， $\sum_{k\in K_j} a_{j,k}=A_j$。

我们仍需证明:对于所有有限子集 $G\subseteq J$, $\sum_{j\in G} A_j$ 最小上界是 $A$。假设 $G$ 是 $J$ 的一个有限子集，且满足 $\sum_{j\in G} A_j =A'> A$。我们可以找到有限子集 $F_j\subseteq K_j$，使得对于每个 $j\in G$，且 $A_j > 0$，有 $\sum_{k\in F_j} a_{j,k}>(A/A')A_j$。至少存在一个这样的 $j$。但此时 $\sum_{j\in G, k\in F_j} a_{j,k}>(A/A')\sum_{j\in G}A_j = A$，这与下述事实矛盾： 对所有有限子集 $F\subseteq M$, $\sum_{(j,k)\in F} a_{j,k}\le A$ 成立。因此对于所有有限子集 $G\subseteq J$，必有 $\sum_{j\in G} A_j\le A$。

最后，设 $A'$ 为任意一个小于 $A$ 的实数。如果我们能找到一个有限集 $G\subseteq J$，使得 $\sum_{j\in G} A_j>A'$，那么我们的证明就完成了。我们知道，存在一个有限集 $F\subseteq M$，使得 $\sum_{(j,k)\in F} a_{j,k} > A'$；令 $G$ 为该 $F$ 中所有 j 的集合，并令 $F_j = \{k|(j, k)\in F\}$。于是 $\sum_{j\in G}A_j \ge \sum_{j\in G}\sum_{k\in F_j} a_{j,k} = \sum_{(j,k)\in F} a_{j,k}>A'$；证毕。

好的，我们现在是合法的了！只要各项绝对值的有限和都有一个有限上界，我们之前对无穷级数所做的一切都是合理的。由于双重无穷级数(2.58)以两种不同的方式求值时给出了两个不同的答案，那么它的正项 $1 + \frac{1}{2} + \frac{1}{3} + \cdots$ 必须发散到 $\infty$；否则，无论我们如何分组，都会得到相同的答案。



