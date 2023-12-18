算法分析的数学基础

$
\exists c, n_0, 使得当 N\geq n_0时, T(N) \leq cf(N), 则即为T(N) = O(f(N))$

$\exists c, n_0, 使得当 N\geq n_0时, T(N) \geq cg(N), 则即为T(N) = \Omega(g(N)) $

$当T(N) = O(h(N)), T(N) = \Omega(h(N)), 记为T(N) = \Theta(h(N))$

$\exists c, n_0, 使得当 N\geq n_0时, T(N) < cf(N), 则即为T(N) = o(f(N)) $

$\exists c, n_0, 使得当 N\geq n_0时, T(N) > cg(N), 则即为T(N) = \omega(g(N)) $

$如果T_1(N) = O(f(N))且T_2(N) = O(g(N)), 那么: \\
(1) T_1(N) + T_2(N) = max(O(f(N)), O(g(N))) \\
(2) T_1(N) * T_2(N) = O(f(N) * g(N))
$