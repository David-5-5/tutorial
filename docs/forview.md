## 6.5 BERNOULLI NUMBERS 伯努利数
我们接下来要介绍的一类重要数列以雅各布·伯努利（Jakob Bernoulli，1654–1705）的名字命名。他在推导 $m$ 次幂和公式的过程中发现了一系列奇妙的关系式 [26]。我们记：
$$
S_m(n) = 0^m + 1^m + \cdots + (n-1)^m  = \sum_{k=0}^{n-1} k^m = \sum_0^n x^m \delta x. \tag{6.77}
$$

（因此，当 $m>0$ 时，在广义调和数的记号下有 $S_m(n)=H_{n-1}^{(-m)}$。）伯努利研究了下面这组公式，并从中发现了一个规律：

$$
\begin{aligned}
S_0(n) &= n \\
S_1(n) &= \frac12n^2 - \frac12n \\
S_2(n) &= \frac13n^3 - \frac12n^2 + \frac16n \\
S_3(n) &= \frac14n^4 - \frac12n^3 + \frac14n^2 \\
S_4(n) &= \frac15n^5 - \frac12n^4 + \frac13n^3 - \frac1{30}n \\
S_5(n) &= \frac16n^6 - \frac12n^5 + \frac5{12}n^4 - \frac1{12}n^2 \\
S_6(n) &= \frac17n^7 - \frac12n^6 + \frac12n^5 - \frac16n^3 + \frac1{42}n \\
S_7(n) &= \frac18n^8 - \frac12n^7 + \frac7{12}n^6 - \frac7{24}n^4 + \frac1{12}n^2 \\
S_8(n) &= \frac19n^9 - \frac12n^8 + \frac23n^7 - \frac7{15}n^5 + \frac29n^3 - \frac1{30}n \\
S_9(n) &= \frac1{10}n^{10} - \frac12n^9 + \frac34n^8 - \frac7{10}n^6 + \frac12n^4 - \frac3{20}n^2 \\
S_{10}(n) &= \frac1{11}n^{11} - \frac12n^{10} + \frac56n^9 - n^7 + n^5 - \frac12n^3 + \frac5{66}n
\end{aligned}
$$

你也能看出这个规律吗？$S_m(n)$ 中 $n^{m+1}$ 的系数永远是 $\frac{1}{m+1}$。 $n^m$ 的系数永远是 $-\dfrac12$。$n^{m-1}$ 的系数永远是……看一下……$\frac{m}{12}$。$n^{m-2}$ 的系数永远是 $0$。$n^{m-3}$ 的系数永远是……嗯……没错，是 $-\frac{m(m-1)(m-2)}{720}$。$n^{m-4}$ 的系数永远是 $0$。这个规律似乎会一直延续下去，$n^{m-k}$ 的系数总是某个常数乘以 $\binom{m}{k}$。

这就是伯努利的经验性发现（他并未给出证明）。用现代记号，我们将系数写成如下形式：
$$
\begin{aligned}
S_m(n) &= \frac1{m+1}\left(
            B_0 n^{m+1}
          + \binom{m+1}{1} B_1 n^m
          + \cdots
          + \binom{m+1}{m} B_m n
         \right) \\
       &= \frac1{m+1} \sum_{k=0}^m \binom{m+1}{k} B_k n^{m+1-k}.
\end{aligned} \tag{6.78}
$$

伯努利数由如下隐式递推关系定义：
$$
\sum_{j=0}^m \binom{m+1}{j} B_j = [m=0], \quad \text{对所有 } m \ge 0. \tag{6.79}
$$
例如，$\binom{2}{0}B_0 + \binom{2}{1}B_1 = 0$。
前几项的值为：

$$
\begin{array}{c|rrrrrrrrrrrrr}
n & 0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 10 & 11 & 12 \\
\hline
B_n & 1 & -\frac12 & \frac16 & 0 & -\frac1{30} & 0 & \frac1{42} & 0 & -\frac1{30} & 0 & \frac5{66} & 0 & -\frac{691}{2730}
\end{array}
$$

（奇怪的分数 $-\dfrac{691}{2730}$ 的出现，让所有关于 $B_n$ 存在简单闭式的猜想都破灭了。）

我们可以对 $m$ 归纳证明伯努利公式 (6.78)，使用扰动法（第 2 章中求 $S_2(n)$ 的方法之一）：
$$
\begin{aligned}
S_{m+1}(n) + n^{m+1}
&= \sum_{k=0}^{n-1} (k+1)^{m+1} \\
&= \sum_{k=0}^{n-1} \sum_{j=0}^{m+1} \binom{m+1}{j} k^j
 = \sum_{j=0}^{m+1} \binom{m+1}{j} S_j(n). \tag{6.80}
\end{aligned}
$$

设 $\hat{S}_m(n)$ 为式 (6.78) 的右端；我们想要证明 $S_m(n)=\hat{S}_m(n)$，并假设当 $0\le j<m$ 时已有 $S_j(n)=\hat{S}_j(n)$。仿照第 2 章对 $m=2$ 的做法，我们先从 (6.80) 两边同时减去 $S_{m+1}(n)$。然后用 (6.78) 展开每一个 $S_j(n)$，并重新整理，把右端 $n$ 的各次幂系数合并化简：
$$
\begin{aligned}
n^{m+1} &= \sum_{j=0}^m \binom{m+1}{j} S_j(n) \\
&= \sum_{j=0}^m \binom{m+1}{j} \hat{S}_j(n) + \binom{m+1}{m} \Delta \\
&= \sum_{j=0}^m \binom{m+1}{j} \frac{1}{j+1} \sum_{k=0}^j \binom{j+1}{k} B_k n^{j+1-k} + (m+1)\Delta \\
&= \sum_{0\le k\le j\le m}
   \binom{m+1}{j}\binom{j+1}{k}\frac{B_k}{j+1} n^{j+1-k} + (m+1)\Delta \\
&= \sum_{0\le k\le j\le m} \binom{m+1}{j}\binom{j+1}{j-k}\frac{B_{j-k}}{j+1} n^{k+1}+ (m+1)\Delta \\
&= \sum_{0\le k\le j\le m} \binom{m+1}{j}\binom{j+1}{k+1}\frac{B_{j-k}}{j+1} n^{k+1} + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \sum_{k\le j\le m} \binom{m+1}{j}\binom{j}{k} B_{j-k} + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \binom{m+1}{k+1} \sum_{k\le j\le m} \binom{m-k}{j-k} B_{j-k}  + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \binom{m+1}{k+1} \sum_{0\le j\le m-k} \binom{m-k}{j} B_j + (m+1)\Delta \\
&= \sum_{0\le k\le m} \frac{n^{k+1}}{k+1} \binom{m+1}{k+1} [m-k=0] + (m+1)\Delta \\
&= \frac{n^{m+1}}{m+1} \binom{m+1}{m+1} + (m+1)\Delta \\
&= n^{m+1} + (m+1)\Delta, \quad\text{其中 }\Delta = S_m(n)-\hat{S}_m(n).
\end{aligned}
$$

（这一推导很好地复习了我们在第 5 章学过的标准运算技巧。）因此 $\Delta=0$，即 $S_m(n)=\hat{S}_m(n)$，证毕。

在第 7 章中，我们将利用生成函数给出式 (6.78) 一个简洁得多的证明。核心思路是证明伯努利数是幂级数的系数
$$
\frac{z}{e^z-1} = \sum_{n\ge0}\frac{B_n z^n}{n!} \tag{6.81}
$$

现在我们暂且假定式 (6.81) 成立，由此推导它的一些奇妙推论。如果在两边加上 $-\dfrac{z}{2}$，就可以消去右端的 $B_1 z/1! = -\dfrac{z}{2}$ 项，得到：
$$
\frac{z}{e^z-1} + \frac{z}{2}
= \frac{z}{2}\cdot\frac{e^z+1}{e^z-1}
= \frac{z}{2}\cdot\frac{e^{z/2}+e^{-z/2}}{e^{z/2}-e^{-z/2}}
= \frac{z}{2}\coth\frac{z}{2}. \tag{6.82}
$$
这里 $\coth$ 是**双曲余切**函数，微积分教材中也写作 $\cosh z/\sinh z$；我们有
$$
\sinh z = \frac{e^z-e^{-z}}{2},\quad \cosh z = \frac{e^z+e^{-z}}{2}. \tag{6.83}
$$

将 $z$ 换为 $-z$ 可得 $\dfrac{-z}{2}\coth\dfrac{-z}{2} = \dfrac{z}{2}\coth\dfrac{z}{2}$，因此 $\dfrac{z}{2}\coth\dfrac{z}{2}$ 中所有**奇次项系数均为 0**，从而
$$
B_3 = B_5 = B_7 = B_9 = B_{11} = B_{13} = \cdots = 0. \tag{6.84}
$$

此外，由 (6.82) 可直接得到 $\coth$ 展开式的闭式：
$$
z\coth z
= \frac{2z}{e^{2z}-1} + z
= \sum_{n\ge0} B_{2n}\frac{(2z)^{2n}}{(2n)!}
= \sum_{n\ge0} 4^n B_{2n}\frac{z^{2n}}{(2n)!}. \tag{6.85}
$$

不过双曲函数并不那么常用，人们更关心普通三角函数。利用关系式
$$
\sin z = -i\sinh iz,\quad \cos z = \cosh iz \tag{6.86}
$$
可以把三角函数用双曲函数表示。对应的幂级数为：
$$
\begin{aligned}
\sin z &= \frac{z^1}{1!} - \frac{z^3}{3!} + \frac{z^5}{5!} - \cdots,
& \sinh z &= \frac{z^1}{1!} + \frac{z^3}{3!} + \frac{z^5}{5!} + \cdots,\\
\cos z &= \frac{z^0}{0!} - \frac{z^2}{2!} + \frac{z^4}{4!} - \cdots,
& \cosh z &= \frac{z^0}{0!} + \frac{z^2}{2!} + \frac{z^4}{4!} + \cdots.
\end{aligned}
$$

因此 $\cot z = \cos z/\sin z = i\cosh iz/\sinh iz = i\coth iz$，于是有
$$
z\cot z = \sum_{n\ge0} B_{2n}\frac{(2iz)^{2n}}{(2n)!}
         = \sum_{n\ge0} (-4)^n B_{2n}\frac{z^{2n}}{(2n)!}. \tag{6.87}
$$

欧拉还发现了 $z\cot z$ 的另一个优美公式（见习题 73）：
$$
z\cot z = 1 - 2\sum_{k\ge1}\frac{z^2}{k^2\pi^2 - z^2}. \tag{6.88}
$$

将欧拉的公式按 $z^2$ 的幂次展开，可得
$$
\begin{aligned}
z\cot z
&= 1 - 2\sum_{k\ge1}\left( \frac{z^2}{k^2\pi^2} + \frac{z^4}{k^4\pi^4} + \frac{z^6}{k^6\pi^6} + \cdots \right) \\
&= 1 - 2\left(\frac{z^2}{\pi^2}H_\infty^{(2)} + \frac{z^4}{\pi^4}H_\infty^{(4)} + \frac{z^6}{\pi^6}H_\infty^{(6)} + \cdots \right).
\end{aligned}
$$

将上式与式 (6.87) 中 $z^{2n}$ 的系数对应相等，我们就得到了无穷级数求和的惊人闭式：
$$
\zeta(2n) = H_\infty^{(2n)}
         = (-1)^{n-1}\frac{2^{2n-1}\pi^{2n}B_{2n}}{(2n)!},
\quad \text{整数 } n>0. \tag{6.89}
$$

例如：
$$
\zeta(2) = H_\infty^{(2)} = 1+\frac14+\frac19+\cdots
         = \frac{\pi^2 B_2}{1} = \pi^2/6; \tag{6.90}
$$
$$
\zeta(4) = H_\infty^{(4)} = 1+\frac1{16}+\frac1{81}+\cdots
         = -\frac{\pi^4 B_4}{3} = \pi^4/90. \tag{6.91}
$$

公式 (6.89) 不仅给出了 $H_\infty^{(2n)}$ 的闭式，还揭示了 $B_{2n}$ 的大致量级——当 $n$ 很大时，$H_\infty^{(2n)}$ 非常接近 1。
同时它也说明：对所有 $n>0$，有 $(-1)^{n-1}B_{2n}>0$，即非零伯努利数的符号正负交替。





