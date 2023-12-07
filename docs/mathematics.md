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
- 展示长公式
$
\begin{multiline}
px
\end{multiline}
$