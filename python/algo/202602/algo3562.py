from cmath import inf
from functools import cache
from typing import List


class Solution:
    def maxProfit(self, n: int, present: List[int], future: List[int], hierarchy: List[List[int]], budget: int) -> int:
        # 参考题解 树上背包 + 状态机
        g = [[] for _ in range(n)]
        for u, v in hierarchy:
            g[u-1].append(v-1)

        def dfs(u: int)  -> List[List[int]]:
            # 树上背包计算 u 的各子树
            sub_f = [[0, 0] for _ in range(budget+1)]
            for v in g[u]:
                fv = dfs(v)
                for j in range(budget, -1, -1): # j 包括 v 及之前的子树的所有预算
                    # 枚举子树 v 的预算为 jv
                    for jv in range(j+1):
                        for k in range(2):
                            sub_f[j][k] = max(sub_f[j][k], sub_f[j-jv][k] + fv[jv][k])
            # 计算 u 和 子树的最大值
            f = [[0, 0] for _ in range(budget+1)]
            for j in range(budget, -1, -1):
                for k in range(2):
                    cost = present[u] // (k+1)
                    if j >= cost:
                        f[j][k] = max(sub_f[j][0], sub_f[j-cost][1] + future[u]-cost)
                    else:
                        f[j][k] = sub_f[j][0]
            
            return f


        return dfs(0)[budget][0]
    
    def maxProfit2(self, n: int, present: List[int], future: List[int], hierarchy: List[List[int]], budget: int) -> int:
        # 参考题解 - 性能优化
        fmax = lambda a, b: b if b > a else a

        g = [[] for _ in range(n)]
        for u, v in hierarchy:
            g[u - 1].append(v - 1)

        def dfs(u: int) -> List[List[int]]:
            # 计算从 x 的所有儿子子树 y 中，能得到的最大利润之和
            sub_f = [[0] + [-inf] * budget for _ in range(2)]
            for v in g[u]:
                fy = dfs(v)
                for k, fvk in enumerate(fy):
                    nf = [0] + [-inf] * budget
                    for jv, res_v in enumerate(fvk):
                        if res_v < 0:  # 重要优化：物品价值为负数，一定不选
                            continue
                        for j in range(jv, budget + 1):
                            nf[j] = fmax(nf[j], sub_f[k][j - jv] + res_v)
                    sub_f[k] = nf

            f = [None] * 2
            for k in range(2):
                # 不买 x，转移来源为 sub_f[0]，因为对于子树来说，父节点一定不买
                f[k] = sub_f[0].copy()
                cost = present[u] // (k + 1)
                # 买 x，转移来源为 sub_f[1]，因为对于子树来说，父节点一定买
                for j in range(cost, budget + 1):
                    f[k][j] = fmax(f[k][j], sub_f[1][j - cost] + future[u] - cost)
            return f

        return max(dfs(0)[0])
