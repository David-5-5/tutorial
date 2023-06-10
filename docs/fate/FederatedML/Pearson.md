## Heterogeneous Pearson Correlation Coefficient

### Introduction

Pearson Correlation Coefficient is a measure of the linear correlation between two variables, 
X and Y, defined as,
皮尔逊相关系数是衡量两个变量之间线性相关性的指标，X 和 Y，定义为，

$$
\begin{equation}
\rho_{X,Y} = \frac{cov(X, Y)}{\sigma_X\sigma_Y} = \frac{E[(X-\mu_X)(Y-\mu_Y)]}{\sigma_X\sigma_Y} = E\left[\left(\frac{X-\mu_X}{\sigma_X}\cdot\frac{Y-\mu_Y}{\sigma_Y}\right)\right]
\end{equation}
$$

Let
$$
\begin{equation}
\tilde{X} = \frac{X-\mu_X}{\sigma_X}, \tilde{Y}=\frac{Y-\mu_Y}{\sigma_Y}
\end{equation}
$$

Implementation Detail

We use an MPC protocol called SPDZ for Heterogeneous Pearson Correlation Coefficient calculation. For more details, one can refer
我们使用称为 SPDZ 的 MPC 协议来计算异构 Pearson 相关系数。 有关更多详细信息，可以参考