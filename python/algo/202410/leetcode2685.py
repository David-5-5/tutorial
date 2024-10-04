from typing import List

# 周赛 344
class Solution:
    def countCompleteComponents(self, n: int, edges: List[List[int]]) -> int:
        # 参考题解，求解完全连通分量 模板题
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        vis = [False] * n

        # dfs 求解每个连通图中点和边的数量
        def dfs(u:int):
            nonlocal v_cnt, e_cnt
            vis[u] = True
            v_cnt += 1
            e_cnt += len(g[u])
            for v in g[u]:
                if vis[v]: continue
                dfs(v)

        ans = 0
        for i in range(n):
            if not vis[i]:
                v_cnt = e_cnt = 0
                dfs(i)
                # 当 点和边数量满足 C(v,2) = e 时，为完全连通图，由于每条边计算两次，因此
                # 比较 2 * C(v,2) = 2*(V-1)*V = E , 其中 V 为点的数量， E 为边的数量
                if (v_cnt-1) * v_cnt == e_cnt : ans += 1

        return ans

