# Markdown数学公式表


## 插入公式块

在符号$之间插入公式内容

- 示例1: 靠右显示
$
x^2 + y^2 = z^2
$


- 示例2: 居中显示
$$
x^2 + y^2 = z^2
$$


## 括号
- 圆括号Parentheses- round brackets
$
(x+y)
$

- 方括号Brackets- square brackets
$
[x+y]
$

- 花括号Braces- curly brackets
$
\{x+y\}
$

- 尖括号 Angle brackets
$
\langle x+y \rangle
$

- 绝对值 Pipes Vertical bars
$
|x+y|
$

- Double pipes
$
\|x+y\|
$

- 上限值 Ceil
$
\lceil x+y \rceil
$

- 下限值 Floor
$
\lfloor x+y \rfloor
$


## 放大括号
- 放大圆括号
$
\Bigg( \bigg(  \Big( \big( () \big) \Big) \bigg) \Bigg)
$

- 放大上限值
$
\Bigg\lceil \bigg\lceil  \Big\lceil \big\lceil \lceil\rceil \big\rceil \Big\rceil \bigg\rceil \Bigg\rceil
$

> 其他括号类似


## 矩阵
- Plain
$
\begin{matrix}
1 & 2 & 3\\
a & b & c
\end{matrix}
$

- 圆括号矩阵
$
\begin{pmatrix}
1 & 2 & 3\\
a & b & c
\end{pmatrix}
$

- 方括号矩阵
$
\begin{bmatrix}
1 & 2 & 3\\
a & b & c
\end{bmatrix}
$

- 花括号矩阵
$
\begin{Bmatrix}
1 & 2 & 3\\
a & b & c
\end{Bmatrix}
$

- Pipe单线矩阵
$
\begin{vmatrix}
1 & 2 & 3\\
a & b & c
\end{vmatrix}
$

- 双线矩阵
$
\begin{Vmatrix}
1 & 2 & 3\\
a & b & c
\end{Vmatrix}
$

- 行内矩阵
$
\begin{smallmatrix}
1 & 2 & 3\\
a & b & c
\end{smallmatrix}
$
一个矩阵可以嵌套到其他矩阵



## 分式和二项式
- 除式
$
\frac{x}{y}
$
$
\frac{x+1}{y+\frac{1}{2}}
$

- 二项式
$
\binom{n}{k}
$



## 对齐
- 拆分对齐方程(以等号对齐)
$$
 \begin{align*} 
 x &= y & w &= z & a &= b+c \\
 2x &=-y & 3w &= \frac{1}{2} & a &= b \\
 -4 + 5x &=2+ y & w+2 &= -1 + w & ab &= cb 
 \end{align*} 
$$

- 居中显示方程(不以等号对齐)
$$
 \begin{gather*} 
 x = y & w = z & a = b+c \\
 2x =-y & 3w = \frac{1}{2} & a = b \\
 -4 + 5x =2+ y & w+2 = -1 + w & ab = cb \\
 2x - 5y = 8 \\
 3x^2 + 9y = 3a + c
 \end{gather*} 
$$


## 运算符
$
\cos,  \tan, \csc,  \lim, \exp, \dim, \min, \max \\
\arcsin, \sin, \lg, \tanh, \ln, \arg, \log \\
\ker, \limsup, \Pr, \hom, \liminf
$