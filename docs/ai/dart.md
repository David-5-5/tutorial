How it works
In \(m\)-th training round, suppose \(k\) trees are selected to be dropped.

Let \(D = \sum_{i \in \mathbf{K}} F_i\) be the leaf scores of dropped trees and \(F_m = \eta \tilde{F}_m\) be the leaf scores of a new tree.

The objective function is as follows:

\[\mathrm{Obj} = \sum_{j=1}^n L \left( y_j, \hat{y}_j^{m-1} - D_j + \tilde{F}_m \right) + \Omega \left( \tilde{F}_m \right).\]
\(D\) and \(F_m\) are overshooting, so using scale factor

\[\hat{y}_j^m = \sum_{i \not\in \mathbf{K}} F_i + a \left( \sum_{i \in \mathbf{K}} F_i + b F_m \right) .\]
