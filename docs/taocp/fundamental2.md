### 1.2.11 *渐进表示
为了把一个量同其他量做比较，时常想要知道它的近似值而不是精确值。例如，当 n 是大数时， n! 的斯特林近似式就是这一类表示。也已经利用过 $`H_n\approx\ln n+\gamma`$ 这个结果。这种渐进式的推导一般要涉及高等数学。

### 1.2.11.1 *大 O 记号
保罗巴赫曼在其《解析数论》一书发明了一种非常方便的近似值记号 大 O 记号，它使可以用 = 代替 $`\approx`$，还能定量计算精确度。例如
```math
H_n=\ln n+\gamma + O\binom{1}{n}. \qquad (1)
```
一般而言，只要 f(n) 为正整数 n 的函数，就可以使用记号 O(f(n))。它代表一个 _显式表示未知_ 的量，只知道它的值不是太大。O(f(n)) 的准确含义是：存在正常数 M 和 $`n_0`$，使得对于所有正整数 $`n\geq n_0`$，由 O(f(n)) 代表的数 $`x_n`$ 满足条件 $`|x_n|\leq M|f(n)|`$。不说明 M 和 $`n_0`$ 是多少，其实在不同情况下出现大 O 时，这两个常数通常有不同的值。

例如等式(1)意味着当 $`n\geq n_0`$ 时，$`|H_n-\ln n-\gamma|\leq M/n`$ 。虽然对常数 M 和 $`n_0`$ 未加说明，但是可以肯定，如果 n 足够大，那么 O(1/n) 这个量将任意的小。
让我们再多考察几个例子。知道
```math
1^2+2^2+\cdots+n^2=\frac{1}{3}n(n+\frac{1}{2})(n+1) = \frac{1}{3}n^3+\frac{1}{2}n^2+\frac{1}{6}n
```
由此推出
```math
1^2+2^2+\cdots+n^2=O(n^4) \qquad (2)
```
```math
1^2+2^2+\cdots+n^2=O(n^3) \qquad (3)
```
```math
1^2+2^2+\cdots+n^2=\frac{1}{3}n^3 + O(n^2) \qquad (4)
```
等式(2)是相当粗略的，然而并非不正确；等式(3)更强；等式(4)则进一步加强。为了证实这几个等式，将要证明，如果 $`P(n)=a_0+a_1n+\cdots+a_mn^m`$ 是次数小于或等于 m 的任意多项式，那么 $`P(n)=O(n^m)`$。推出这个结果，是因为当 $`n\geq 1`$ 时，
```math
|P(n)|\leq|a_0|+|a_1|n+ \cdots+|a_m|n^m=(|a_0|/n^m+|a_1|/n^{m-1}+\cdots+|a_m|)n^m \\
\leq (|a_0|+|a_1|+\cdots+|a_m|)n^m.
```
所以，可以取 $`M=|a_0|+|a_1|+\cdots+|a_m|`$ 和 $`n_0=1`$。也可以取其他值，比如 $`M=|a_0|/2^m+|a_1|/2^m+\cdots+|a_m|/2^m`$ 和 $`n_0=2`$

大 O 记号对于近似值处理有很大帮助，因为它能简要描述一个经常出现的概念，同时又略去往往无关的详细信息。此外，它可以按照常见的方式进行代数计算，尽管需要记住某些重大的差别。最重要一点是 单向相等性：可以写出等式 $`\frac{1}{2}n^2+n=O(n^2)`$，但是绝对不会把它写成 $`O(n^2)=\frac{1}{2}n^2+n`$。不然由于 $`\frac{1}{4}n^2=O(n^2)`$，会得出荒谬的关系 $`\frac{1}{4}n^2=\frac{1}{2}n^2+n`$。始终约定：一个等式的右端不会给出比左端更多的信息量；等式右端是其左端的一种 “粗略表示”。

关于 = 用法的这种约定可更确切的表述如下：不妨把包含 O(f(n)) 记号的表达式看成 n 的函数集合。符号 O(f(n)) 代表所有以整数为自变量且满足下述条件的函数 g 的集合：存在常数 M 和 $`n_0`$，使得 $|g(n)|\leq M|f(n)|`$ 对于所有整数 $`n\geq n_0`$ 成立。如果 S 和 T 是函数的集合，那么 S+T 表示集合 {$`g+h|g\in S and h\in T`$}；类似的，定义 $`S+c,S_T,S.T,logS,\cdots`$ 如果 $`\alpha(n)`$ 和 $`\beta(n)`$ 是包含大 O 记号的表达式，那么记号 $`\alpha(n)=\beta(n)`$ 意味着由 $`\alpha(n)`$ 表示的函数集合 _包含于_ 由 $`\beta(n)`$ 表示的函数集合。

因此，可以执行习惯上用 = 进行的大部分运算；如果 $`\alpha(n)=\beta(n)`$ 且 $`\beta(n)=\gamma(n)`$ ，那么 $`\alpha(n)=\gamma(n)`$。如果 $`\alpha(n)=\beta(n)`$，$`\delta(n)`$ 是用 $`\beta(n)`$ 替换 $`\gamma(n)`$ 式中的 $`\alpha(n)`$ 得到的公式，那么 $`\gamma(n)=\delta(n)`$。从这两个结果可以推出其他结论，例如 $`g(x_1,x_2,\cdot,x_m)`$ 是实函数，而 $`\alpha_k(n)=\beta_k(n)`$ 对 $`1\leq k\leq m`$ 成立，那么
```math
g(\alpha_1(n),\alpha_2(n),\cdot,\alpha_m(n))=g(\beta_1(n),\beta_2(n),\cdot,\beta_m(n))
```
下面是可以用大 O 记号进行的一些简单运算：
```math
f(n)=O(f(n)), \qquad (5)
```
```math
c.O(f(n))=O(f(n)), \qquad (6)
```
```math
O(f(n))+O(f(n))=O(f(n)), \qquad (7)
```
```math
O(O(f(n)))=O(f(n)), \qquad (8)
```
```math
O(f(n))O(g(n))=O(f(n)g(n)), \qquad (9)
```
```math
O(f(n)g(n))=f(n)O(g(n)). \qquad (10)
```
大 O 记号也经常用在关于复变量 z 的函数中，用在 z=0 的邻域内。 O(f(z))代表所有满足下述条件的量 g(z)：只要 |z|< r ， 就有 $`|g(z)|\leq M|f(z)|`$。同样，M 和 r 是未定的常数，尽管再需要时可以指定它们的值。大 O 记号的上下文应该指明相应的变量名称及其范围。当变量名是 n 时，隐含假定 O(f(n)) 是关于大整数 n 的函数；当变量名是 z 时，，隐含假定 O(f(z)) 是关于小复数 z 的函数。

假定 g(z) 是由无穷幂级数
```math
g(z)=\sum_{k\geq 0} a_kz^k
```
给出的函数，这个级数在 $`z=z_0`$ 时收敛。那么只要 $`|z|<|z_0|`$，绝对值之和 $`\sum_{k\geq 0} a_kz^k`$ 也必然收敛。因此如果 $`z_0\neq 0`$ 总是可以写
```math
g(z)=a_0+a_1z+\cdots+a_mz^m+O(z^{m+1}). \qquad (11)
```
因为 $`g(z)=a_0+a_1z+\cdots+a_mz^m+z^{m+1}(a_{m+1}+a_{m+2}z+\cdots)`$；仅需证明，存在正数 r，使得 $`|z|\leq r`$ 时括号中的量有界；容易看出，只要 $`|z|\leq r<|z_0|`$，$`|a_{m+1}|+|a_{m+2}|r+|a_{m+3}|r^2+\cdots)`$ 就是一个上界。

例如，在1.2.9节列出的那些生成函数给出了很多当 z 足够小时成立的重要渐进式，包括：
```math
e^z=1+z+\frac{1}{2!}z^2+\cdots+\frac{1}{m!}z^m+ O(z^{m+1}). \qquad (12)
```
```math
\ln(1+z)=z-\frac{1}{2}z^2+\cdots+\frac{(-1)^{m+1}}{m}z^m + O(z^{m+1}). \qquad (13)
```
```math
(1+z)^\alpha=1+\alpha z + \binom{\alpha}{2}z^2 + \cdots+ \binom{\alpha}{m}z^m + O(z^{m+1}). \qquad (14)
```
```math
\frac{1}{(1+z)}\ln\frac{1}{(1+z)}=z+H_2z^2 + \cdots+ H_mz^m + O(z^{m+1}). \qquad (15)
```
其中 m 为非负整数。任何具体的大 O 记号都隐含一对常数 M 和 r，两者彼此相关。例如，对于任何固定的 r，当 $`|z|\leq r`$ 时，$`e^z`$ 显然是 O(1)，因为 $`|e^z|\leq e^{|z|}`$；但是不存在对于一切 z 值都满足 $`|e^z|\leq M`$ 的常数 M。所以当范围 r 增加时，上界 M 也要增大。

有时一个渐进级数虽然不对应一个收敛的无穷级数，但也是正确的。例如，通过普通的幂表示阶乘幂的两个基本公式：
```math
n^{\overline r}=\sum_{k=0}^m\begin{bmatrix}r \\ r-k\end{bmatrix}n^{r-k}+O(n^{r-m-1}). \qquad (16)
```
```math
n^{\underline r}=\sum_{k=0}^m(-1)^k\begin{bmatrix}r\\r-k\end{bmatrix}n^{r-k}+O(n^{r-m-1}). \qquad (17)
```
对于任何实数 r 和任何固定的整数 都是渐进成立的，然而无限和
```math
\sum_{k=0}^\infty\begin{bmatrix}1/2 \\ 1/2-k\end{bmatrix}n^{1/2-k}
```
对于所有 n 发散。当然，但 r 为非负整数时，$`n^{\overline r}`$ 和 $`n^{\underline r}`$ 都只是 r 次多项式，式(17) 实际上即是1.2.6-(44)。当 r 是负整数且 |n|>|r| 时，无限和 $`\sum_{k=0}^\infty\begin{bmatrix}r \\ r-k\end{bmatrix}n^{r-k}`$ 确实收敛到 $`n^{\overline r} = 1/(n-)^{\underline {-r}}`$；利用等式1.2.6-(58)，还可以把这个和写成更自然的形式 $`\sum_{k=0}^\infty\begin{Bmatrix}k-r \\ -r\end{Bmatrix}n^{r-k}`$。

举一个简单的例子来说明至今所介绍的概念。考虑 $`\sqrt[n]{n}`$ 这个量：当 n 增大时，求 n 次根的运算使其值有减少的趋势，但是 $`\sqrt[n]{n}`$ 究竟是减少还是增大，并不是一目了然的。实际上， 会减少到 1 。再考虑稍微复杂一些的量 $`n(\sqrt[n]{n}-1)`$ 。当 n 变大时，现在知道 $`(\sqrt[n]{n}-1)`$ 却会变小，那么 $`n(\sqrt[n]{n}-1)`$ 会怎样变化？

应用上面的公式，这个问题迎刃而解，有
```math
\sqrt[n]{n}= e^{\ln n/n} = 1 + (\ln n/n) + O(\ln n/n)^2, \qquad (18)
```
因为当 $`n\Leftarrow \infty `$ 时，$`\ln n/n \Leftarrow 0`$。这个等式证明现前的论断，即 $`\sqrt[n]{n}\Leftarrow 1`$。此外
```math
n(\sqrt[n]{n}-1) = n(\ln n/n + O((\ln n/n)^2)) = \ln n + O((\ln n)^2/n). \qquad (19)
```
还句话说， $`n(\sqrt[n]{n}-1)`$ 近似等于 $`\ln n`$；两者之差为 $`O((\ln n)^2/n)`$，当 n 趋近无穷大时，它趋近于 0。

人们时常滥用大 O 记号，以为它表示确切的增长量级。有些人在使用它的时候，以为它不仅说明上界，还限定下界。例如，对 n 个数排序的一种算法有可能被斥为效率过低，理由是运行时间为 $`O(n^2)`$。但是 $`O(n^2)`$ 的运行时间并非一定意味着它不是 $`O(n)`$ 的。还有另外一个大 $`\Omega`$ 记号，它是用来表示下界的：
```math
g(n) = \Omega(f(n)). \qquad (20)
```
意味着存在两个正常数 L 和 $`n_0`$ 使得
```math
|g(n)| \geq L|f(n)| \forall n \geq n_0 . \qquad (20)
```
使用这个记号，能够正确的断定，如果 n 足够大，那么运行时间为 $`\Omega(n^2)`$ 的排序算法不如运行时间为 $`O(n\log n)`$ 的算法高效，但是如果不知道大 O 和 大 $`\Omega`$ 中隐含的常数因子，就完全不知道 $`O(n\log n)`$ 的算法将从多么大的 n 开始表现出优势。

最后，如果要说明严格的增长量级，但不想指明常数大小，那么可以使用大 $`\Theta`$：
```math
g(n) = \Theta(f(n)) \iff g(n) = O(f(n)) and g(n) = \Omega(f(n)). \qquad (21)
```


### 1.2.11.2 *欧拉求和公式
欧拉提出了一种极有用的求和方法，能获得令人满意的近似值。它的方法是用积分逼近有限和，在许多情况下，利用这种手段可以不断改进近似值。

当函数 可微，欧拉给出了计算 $`\int_1^n f(x)dx`$ 和 $`\sum_{k=1}^{n-1}f(k)`$ 这两个公式之差的有用的公式 。

为方便起见，将使用记号
```math
{x} = x \mod 1 = x -  \lfloor x\rfloor . \qquad (1)
```
推导将从下述恒等式开始：
```math
\int_k^{k+1}({x}-\frac{1}{2})f'(x)dx = (x-k-\frac{1}{2})f(x)\big|_k^{k+1} - \int_k^{k+1}f(x)dx \\
= \frac{1}{2}(f(k+1)+f(k)) -  \int_k^{k+1}f(x)dx . \qquad (2)
```
等式的两端都对 $`1\leq k < n`$ 求和，得到
```math
\int_1^n({x}-\frac{1}{2})f'(x)dx = \sum_{1\leq k < n}f(k)+\frac{1}{2}(f(n)-f(1)) - \int_1^nf(x)dx 
```
即
```math
\sum_{1\leq k < n}f(x) = \int_1^nf(x)dx - \frac{1}{2}(f(n)-f(1)) + \int_1^n B_1({x})f'(x)dx, \qquad (3)
``` 
其中 $`B_1(x)`$ 是多项式 $`x-\frac{1}{2}`$。这便是所求的有限和与积分之间的联系。

如果继续分部积分，可以进一步求近似值。但是在此之前，先来讨论 伯努利数，即下述无穷级数的系数：
```math
\frac{z}{e^z-1}= B_0 + B_1z + \frac{B_2z^2}{2!} + ... = \sum_{k\geq 0}\frac{B_kz^k}{k!}. \qquad (4)
``` 
几个级数的系数出现在形形色色的应用问题中。雅各布伯努利去世后出版的著作《猜度术》将它介绍给了欧洲数学家。无独有偶，日本的关孝和也发现了这类数。

前几个伯努利数是
```math
B_0=1, B_1 = -\frac{1}{2}, B_2 = \frac{1}{6}, B_3 = 0, B_4 = -\frac{1}{30}. \qquad (5)
``` 
附录A的表3中列出了接下去的一些数值。由于
```math
\frac{z}{e^z-1} + \frac{z}{2} = \frac{z}{2}\frac{e^z+1}{e^z-1}=-\frac{z}{2}\frac{e^{-z}+1}{e^{-z}-1}
``` 
是一个偶函数，因此
```math
B_3 = B_5 = B_7 = B_9 = \cdots = 0.  \qquad (6)
``` 
如果伯努利数的定义式 (4) 两端同事乘以 ，并令 z 的同次幂的系数相等，便等到公式
```math
\sum_k\binom{n}{k}B_k = B_n + \delta_{n1}. \qquad (7)
``` 
现在定义的 _伯努利多项式_
```math
B_m(x)=\sum_k\binom{m}{k}B_kx^{m-k}. \qquad (8)
``` 
如果 m=1，那么 $`B_1(x)=B_0+B_1=x-\frac{1}{2}`$，对应于上面 (3) 中使用的多项式。如果 m>1，那么由 (7) 有 $`B_m(1)=B_m=B_m(0)`$；还句话说，$`B_m({x})`$ 在整数点 x 处不间断。


讲了伯努利多项式和伯努利数，它们与我们的问题之间有什么关系？答案立即揭晓。对等式 (8) 求导，得到
```math
B_m'(x)=\sum_k\binom{m}{k}(m-k)B_kx^{m-k-1} \\
= m\sum_k\binom{m-1}{k}B_kx^{m-k-1} 
= mB_{m-1}(x). \qquad (9)
``` 
因此，当 $`m\geq 1`$ 时，可以分部积分如下：
```math
\frac{1}{m!}\int_1^n B_m({x})f^{(m)}(x)dx = \frac{1}{(m+1)!}(B_{m+1}(1)f^{(m)}(n)-B_{m+1}(0)f^{(m)}(1)) \\
- \frac{1}{(m+1)!}\int_1^n B_{m+1}({x})f^{(m+1)}(x)dx.
``` 
据此可以继续改进式 (3) 的近似值，并且利用式 (6) 得到欧拉的一般公式：
```math
\sum_{1\leq k < n}f(k) = \int_1^nf(x)dx - \frac{1}{2}(f(n)-f(1)) + \frac{B_2}(f'(n)-f'(1)) + \cdots \\
+ \frac{(-1)^mB_m}{m!}(f^{(m-1)}(n)-f^{(m-1)}(1)) + R_{mn}
= \int_1^n f(x)dx + \sum_{k=1}^m\frac{B_k}{k!}(f^{(k-1)}(n)-f^{(k-1)}(1)) + R_{mn}, \qquad (10)
``` 
其中
```math
R_{mn} = \frac{(-1)^{m+1}}{m!}\int_1^n B_m({x})f^{(m)}(x)dx. \qquad (11)
```
当 $`B_m({x})f^{(m)}(x)/m!`$ 非常小的时候，余项 $`R_{mn}`$ 是很小的。事实上，可以证明，当 m 为偶数时，
```math
\left| \frac{B_m({x})}{m!}\right| \leq \frac{B_m}{m!} < \frac{4}{(2\pi)^m}. \qquad (12)
``` 
另外，当 m 增加时，$`f^{(m)}(x)`$ 通常随之变大。所以对于给定的 n，存在 m 的“最佳”值，使 $`|R_{mn}|`$ 取最小值。

已经知道，当 m 为偶数时，存在数 $`\theta`$ 满足：只要 $`f^{(m+2)}(x)f^{(m+4)}(x) > 0`$ 对于 成立，就有
```math
R_{mn} = \theta \frac{B_{m+2}}{(m+2)!}(f^{(m+1)}(n)-f^{(m+1)}(1)), 0 < \theta < 1. \qquad (13)
```
所以此时余项与第一个舍弃项符号相同，而绝对值更小。这个结果有一种更简单的形式，将在习题 3 证明。

现在把欧拉公式应用到两个重要的例子中。首先，置 f(x)=1/x。它的 m 阶导数为 $`f^{(m)}(x)=(-1)^mm!/x^{m+1}`$，所以由式 (10) 得到
```math
H_{n-1} = \ln n + \sum_{k=1}^m\frac{B_k}{k}(-1)^{k-1}(\frac{1}{n^k}-1) + R_{mn}. \qquad (14)
```
现在求出
```math
\gamma = \lim_{n\to \infty}(H_{n-1}-\ln n) = \sum_{k=1}^\frac{B_k}{k}(-1)^k + \lim_{n\to \infty}R_{mn}. \qquad (15)
```
由于 $`\lim_{n\to \infty}R_{mn}=-\int_1^n B_m({x})dx/x^{m+1}`$ 存在，证明确实存在常数 $`\gamma`$ 。因此可以结合式 (14) 和 (15)，推出调和数的一般近似值：
```math
H_{n-1} = \ln n + \gamma + \sum_{k=1}^m\frac{(-1)^{k-1}B_k}{kn^k} + \int_n^\infty \frac{B_m({x})}{x^{m+1}}dx.
= \ln n + \gamma + \sum_{k=1}^m\frac{(-1)^{k-1}B_k}{kn^k} + O(\frac{1}{n^m}).
```
把 m 换成 m+1 ，得出
```math
H_{n-1} = \ln n + \gamma + \sum_{k=1}^m\frac{(-1)^{k-1}B_k}{kn^k} + O(\frac{1}{n^{m+1}}). \qquad (16)
```
此外，从等式 (13) 看出，误差小于第个舍弃项。可以得到一个特例，对两端加 1/n：

这就是式1.2.7-(3) 看出，对于很大的 k，伯努利数 $`B_k`$ 将变得非常大，当 k 为偶数时近似等于 $`(-1)^{1+k/2}2(k!/(2\pi)^k)`$，所以式 (16) 对于任何固定的 n 值，不可能扩展为一个收敛的无穷级数。

可以用同样的方式推导出斯特林近似公式。这一次置 $`f(x)=\ln x`$，由式 (10) 得到
```math
\ln (n-1)! = n\ln n - n + 1 - \frac{1}{2}\ln n + \sum_{k=1}^m\frac{B_k(-1)^{k-1}}{k(k-1)}(\frac{1}{n^k}-1) + R_{mn}. \qquad (17)
```
沿用上面的做法，发现极限
```math
\lim_{n\to \infty}(\ln n! - n\ln n + n - \frac{1}{2}\ln n) = 
1 + \sum_{k=1}^m\frac{B_k(-1)^{k-1}}{k(k-1)} + \lim_{n\to \infty}R_{mn}. 
```
存在；暂且把它称为 “斯特林常数”，得到斯特林的结果
```math
\ln n!=(n+\frac{1}{2})\ln n - n + \sigma + \sum_{k=1}^m\frac{B_k(-1)^{k-1}}{k(k-1)n^{k-1}} + O(\frac{1}{n^m}). \qquad (18)
```
特别地，令 m=5，得到
```math
\ln n!=(n+\frac{1}{2})\ln n - n + \sigma + \frac{1}{12n} - \frac{1}{360n^3} + O(\frac{1}{n^5}). 
```
为两端为指数，求 e 的幂
```math
n!=e^\sigma\sqrt{n}(\frac{n}{e})^n exp(\frac{1}{12n}-\frac{1}{360n^3} + O(\frac{1}{n^5}))
```
利用 $`e^\sigma=sqrt{2\pi}`$，展开指数部分，获得最终结果
```math
n!=\sqrt{2\pi n}(\frac{n}{e})^n(1+\frac{1}{12n} + \frac{1}{288n^2} - \frac{139}{51840n^3} -\frac{571}{2488320n^4} + O(\frac{1}{n^5})). \qquad (19)
```


### 1.2.11.3 *若干渐进计算式
这一节研究下面三个令人感兴趣的和，目的在于推导它们的近似值：
```math
P(n) = 1 + \frac{n-1}{n} + \frac{n-2}{n}\frac{n-2}{n-1} + \cdots = \sum_{k=0}^{n} \frac{(n-k)^k(n-k)!}{n!} . \qquad (1)
```
```math
Q(n) = 1 + \frac{n-1}{n} + \frac{n-1}{n}\frac{n-2}{n} + \cdots = \sum_{k=0}^{n} \frac{n!}{(n-k)!n^k} . \qquad (2)
```
```math
R(n) = 1 + \frac{n}{+1n} + \frac{n}{n+1}\frac{n}{n+2} + \cdots = \sum_{k\geq 0} \frac{n!n^k}{(n+k)!} . \qquad (3)
```
这三个函数出现在后面将要遇到的若干算法中，它们的形式相似而内在性质不同。P(n) 和 Q(n) 为有限和，而 R(n) 是无限和。当 n 为很大的数时，这三个函数看上去近乎相等，不过不能明显看出它们当中的任何一个近似值是什么。探讨这三个函数的近似值，将带来很多富有启发性的附带结果。

首先，注意 P(n) 和 Q(n) 之间的了一个重要联系：
```math
Q(n)+R(n) = \frac{n!}{n^n}((1+n+\cdots+\frac{n^{n-1}}{(n-1)!})+(\frac{n^n}{n!}+\frac{n^{n+1}}{(n+1)!})) = \frac{n!e^n}{n^n} . \qquad (4)
```
斯特林公式告诉，$`n!e^n/n^n`$ 近似等于 $`\sqrt{2\pi n}`$，所以可以推测 Q(n) 和 R(n) 都粗略地等于 $`\sqrt{\pi n/2}`$。

下一步，必须考虑 的级数的部分和。利用带余项的泰勒公式
```math
f(x) = f(0) + f'(0)x + \cdots + \frac{f^{(n)}(0)x^n}{n!} + \int_0^x \frac{t^n}{n!} f^{(n+1)}(x-t)dt. \qquad (5)
```
立即导出一个重要的函数
```math
\gamma(a,x) = \int_0^x e^{-t}t^{a-1}dt . \qquad (6)
```
这个函数称为 _不完全 $`\gamma(a,x)`$ 函数_。假定 a>0。 有 $`\gamma(a,\infty)=\Gamma(a)`$；这就是 “不完全 $`\gamma(a,x)`$ 函数” 这个名称的由来。它有两个很有用的按 x 展开的级数:
```math
\gamma(a,x) = \frac{x^a}{a} - \frac{x^{a+1}}{a+1} + \frac{x^{a+2}}{a+2} - \cdots . = \sum_{k\geq 0}  \frac{(-1)^kx^{a+k}}{k!(a+k)} \qquad (7)
```
```math
e^{x}\gamma(a,x) = \frac{x^a}{a} + \frac{x^{a+1}}{a(a+1)} + \frac{x^{a+2}}{a(a+1)(a+2)} + \cdots . = \sum_{k\geq 0} \frac{x^{a+k}}{a(a+1)\cdots(a+k)} \qquad (8)
```
从第二个公式看出它同 R(n) 的联系：
```math
R(n) = \frac{n!e^n}{n^n}(\frac{\Gamma(n,n)}{(n-1)!})  \qquad (9)
```
这里特意不把这个等式写成最简形式，因为 $`\gamma(n,n)`$ 是 $`\gamma(n,\infty)=\Gamma(n)=(n-1)!`$ 的一部分，而 $`n!e^n/n^n`$ 是关系式 (4) 右端的量。

求近似值问题于是归结为求 $`\gamma(n,n)/(n-1)!`$ 的理想估计。现在假定 y 是固定的，x 取很大的值，来确定 $`\gamma(x=1,x+y)/\Gamma(x+1)`$ 的近似值。下面使用的方法比将要获得的结果更为重要。

按照定义有
```math
\frac{\gamma(x+1,x+y)}{\Gamma(x+1)} = \frac{1}{\Gamma(x+1)}\int_0^{x+y} e^{-t}t^{x}dt \\
= 1 - \frac{1}{\Gamma(x+1)}\int_x^\infty e^{-t}t^{x}dt + \frac{1}{\Gamma(x+1)}\int_x^{x+y} e^{-t}t^{x}dt \qquad (10)
```
置
```math
I_1 = \int_x^\infty e^{-t}t^{x}dt, \\
I_1 = \int_x^{x+y} e^{-t}t^{x}dt, \\
```
依次考察这两个积分。


$`I_1`$ 的估计：代入 t=x(1+u) ，把 $`I_1`$ 转换成从 0 到无穷大的积分；进一步代入 v=u-ln(1+u) 和 dv = (1 - 1/(1+u))du，
```math
I_1 = e^{-x}x^x\int_0^\infty xe{-xu}du = e^{-x}x^x\int_0^\infty xe^{-xv}(1+\frac{1}{u})dv. \qquad (11)
```
在最后这个积分中，用 的一个幂级数替换 。得到
```math
v = \frac{1}{2}u^2 - \frac{1}{3}u^3 + \frac{1}{4}u^4 - \frac{1}{5}u^5 + \cdots = 
(u^2/2)(1-\frac{2}{3}u+\frac{1}{2}u^2-\frac{2}{5}u^3+\cdots) .
```
置 $`w=\sqrt{2v}`$，因此有
```math
w = u(1-\frac{2}{3}u+\frac{1}{2}u^2-\frac{2}{5}u^3+\cdots)^\frac{1}{2} = u - \frac{1}{3}u^2 + \frac{7}{36}u^3 - \frac{73}{540}u^4 + \frac{1331}{12960}u^5 + O(u^6).
```
这个展开式可以通过二项式定理获得。，现在可以把 u 作为 w 的幂级数求解：
```math
u = w + \frac{1}{3}w^2 + \frac{1}{36}w^3 - \frac{1}{270}w^4 + \frac{1}{4320}w^5 + O(w^6).
```
```math
1 + \frac{1}{u} = 1 + \frac{1}{w} - \frac{1}{3} + \frac{1}{12}w - \frac{2}{135}w^2 + \frac{1}{864}w^3 + O(w^4)\\
= \frac{1}{\sqrt{2}}v^{-1/2} + \frac{2}{3} + \frac{\sqrt{2}}{12}v^{1/2} - \frac{4}{135}v + \frac{\sqrt{2}}{432}v^{3/2} + O(v^2) \qquad (12)
```
在所有这些公式中，大 O 记号都是指很小的变量值，就是说，对于足够小的正数 r，有 $`|u|\leq r,|v|\leq r,|w|\leq r`$。这样足以令人满意吗？在等式 (11) 中，用 v 代换 1+1/u 的时候，应当对于 $`0\leq x <\infty`$ 成立，而不仅对于 $`|v|\leq r`$ 成立。幸好，对于这个积分，从 0 到 $`\infty`$ 的积分值几乎完全依赖于被积函数在自变量接近零时的取值。事实上，对于任意固定的 r>0 以及很大的 x，有
```math
\infty xe^{-xv}(1+\frac{1}{u})dv = O(e^{-rx}) \qquad (13)
```
感兴趣的是一直到 $`O(x^{-m})`$ 项的近似值；由于对于任意正数 r 和 m，$`O((1/e^r)^x)`$ 都远远小于 $`O(x^{-m})`$，仅需要从 0 到任何固定的正数 r 积分。因此取足够小的 r，就可以保证上面对幂级数的所有处理都是正确的。
```math
\int_r^\infty xe^{-xv}(1+\frac{1}{u})dv = O(e^{-rx}) \qquad (13)
```
现在有
```math
\int_0^\infty xe^{-xv}v^\alpha dv = \frac{1}{x^\alpha}\int_0^\infty e^{-q}q^\alpha dq = \frac{1}{x^\alpha}\Gamma(\alpha+1) , where \alpha > -1, \qquad (14)
```
所以，通过把级数 (12) 插入积分 (11)，终于得到
```math
I_1 = e^{-x}x^x(\sqrt{\frac{\pi}{2}}x^{1/2} + \frac{2}{3} + \frac{\sqrt{2\pi}}{24}x^{-1/2} - \frac{4}{135}x^{-1} + \frac{\sqrt{2\pi}}{576}x^{-3/2} + O(x^{-2})) \qquad (15)
```
$`I_2`$ 的估计：在积分 中代入 t=u+x，得到
```math
I_2 = e^{-x}x^x\int_0^ye{-u}(1+\frac{u}{x})^x du \qquad (16)
```
于是有
```math
e{-u}(1+\frac{u}{x})^x = exp(-u + x\ln(1+\frac{u}{x})) = exp(\frac{-u^2}{2x} + \frac{x^3}{2x^2} + O(x^{-3})) \\
= 1 - \frac{u^2}{2x} + \frac{u^4}{8x^2} + \frac{u^3}{3x^2} + O(x^{-3})
```
其中 $`0\leq u\leq y`$，x 很大。因此求出
```math
I_2 = e^{-x}x^x(y-\frac{y^3}{6}x^{-1}+(\frac{y^4}{12} +\frac{y^5}{40})x^{-2} + O(x^{-3})) \qquad (17)
```
最后在分析式 (10) 中用因式 $`1/\Gamma(x+1)`$ 乘式 (15) 和 (17) 时出现的系数 $`e^{-x}x^x/\Gamma(x+1)`$。斯特林近似式对于 $`\Gamma`$ 函数成立；由此可得
```math
\frac{e^{-x}x^x}{\Gamma(x+1)}=\frac{e^{-1/12x+O(x^{-3})}}{\sqrt{2\pi x}} \\
= \frac{1}{\sqrt{2\pi}}x^{-1/2} - \frac{1}{12\sqrt{2\pi}}x^{-3/2} + \frac{1}{288\sqrt{2\pi}}x^{-5/2} + O(x^{-7/2}) \qquad (18)
```
现在集 (10)(15)(17)(18) 之大成，隆重推出 --

__定理 A.__ 对于很大的 x 和固定的 y，
```math
\frac{\gamma(x+1,x+y)}{\Gamma(x+1)} = \frac{1}{2} + \frac{y-2/3}{\sqrt{2\pi}}x^{-1/2} + 
\frac{1}{\sqrt{2\pi}}(\frac{23}{270}-\frac{y}{12}-\frac{y^3}{6})x^{-3/2} + O(x^{-5/2}) \qquad (19)
```
上面的方法已经表明，这个近似式可以扩展到想达到的任意阶 x 幂。

利用等式 (4) 和 (9)，可以用 __定理 A__ 求 R(n) 和 Q(n) 的近似值，但是此项计算以后再做。现在研究 P(n)，它似乎需要采用不同的方法。有
```math
P(n) = \sum_{k=0}^n\frac{k^{n-k}k!}{n!} = \frac{\sqrt{2\pi}}{n!}\sum_{k=0}^nk^{n+1/2}e{-k}(1+\frac{1}{12k}+O(k^{-2})) \qquad (20)
```
因此，为了得到 P(n) 的值，必须研究形如
```math
\sum_{k=0}^nk^{n+1/2}e{-k}
```
的和。

令 $`f(x)=x^{n+1/2}e{-x}`$，应用欧拉求和公式
```math
\sum_{k=0}^nk^{n+1/2}e{-k}=\int_0^n x^{n+1/2}e{-x} + \frac{1}{2}n^{n+1/2}e{-n} + \frac{1}{24}n^{n-1/2}e{-n} - R. qquad (21)
```
对余式的粗略分析表明，$`R=O(n^ne{-n})`$；又由于积分是一个不完全 $`\gamma`$ 函数，有
```math
\sum_{k=0}^nk^{n+1/2}e{-k}=\gamma(n+\frac{2}{3},n) + \frac{1}{2}n^{n+1/2}e{-n} + O(n^ne{-n}). qquad (22)
```
式 (20) 还需要估计和式
```math
\sum_{k=0}^nk^{n-1/2}e{-k}=\sum_{0\leq k\leq n-1}k^{(n-1)+1/2}e{-k} n^{n-1/2}e{-n},
```
这个估计也可以通过式 (22) 获得。

现在有足够的公式来确定 P(n) Q(n) R(n) 的近似值，只剩下代入和乘法等运算要做了。在这个过程中，将利用展开式
```math
(n+\alpha)^{n+\beta} = n^{n+\beta}e^\alpha(1+\alpha(\beta-\frac{\alpha}{2})\frac{1}{n} + O(n^{-2})) \qquad (23)
```
对于 P(n)，式 (21) 的方法仅产生渐进级数的前面两项，汇集上面的全部的计算结果，得到要求的渐进式：
```math
P(n) = \sqrt{\frac{\pi n}{2}} - \frac{2}{3} + \frac{11}{24}\sqrt{\frac{\pi}{2n}} + \frac{4}{135n} - \frac{71}{1152}\sqrt{\frac{\pi}{2n^3}}+ O(n^{-2})  \qquad (24)
```
```math
Q(n) = \sqrt{\frac{\pi n}{2}} - \frac{1}{3} + \frac{1}{12}\sqrt{\frac{\pi}{2n}} + \frac{4}{135n} - \frac{1}{288}\sqrt{\frac{\pi}{2n^3}}+ O(n^{-2})  \qquad (24)
```
```math
R(n) = \sqrt{\frac{\pi n}{2}}+\frac{1}{3} + \frac{1}{12}\sqrt{\frac{\pi}{2n}} + \frac{4}{135n}+\frac{1}{288}\sqrt{\frac{\pi}{2n^3}}+ O(n^{-2})  \qquad (25)
```
公开发表的文献对这里研究的三个函数只做了轻描淡写的讨论。 展开式中的第一项 有霍华德德姆斯在博士论文中给出。

同 Q(n) 和 R(n) 的渐进值的等价的公式是由自学成才的杰出印度数学家拉马努金首先确定的，他提出估计
```math
n!e^n/2n^n - Q(n)
```
的问题。他在解答中给出了渐进级数
```math
\frac{1}{3} + \frac{4}{135}n^{-1} - \frac{8}{2835}n^{-3} + \cdots
```
这个结果大大超过等式 (25) 的精度。他的推导比上面的描述的方法更为精巧：为了估计 $`I_1`$，他代入 $`t=x+u\sqrt{2x}`$，把被积函数表示成形如
```math
c_{jk}\int_0^\infty exp(-u^2)u^jx^{-k/2} du
```
的项的和。积分 $`I_2`$ 完全可以不推导，因为当 a > 0 时，
```math
\gamma(a,x) = x^ae^{-x} + \gamma(a+1,x)
```
求 Q(n) 的渐进表示还有一个更简单的方法，就是习题20。我们采用的推导方法尽管比较复杂，但是具有启示作用，作者是罗伯特弗兹，他主要关心满足
```math
\gamma(x+1,x+y) = \Gamma(x+1)/2
```
的 y 值。不完全 $`\gamma`$ 函数的渐进性质后来又由弗朗西斯科特里格米扩充到复变量函数。


