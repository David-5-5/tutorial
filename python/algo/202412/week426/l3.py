from bisect import bisect_left
from itertools import accumulate
from typing import List


class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]], k: int) -> List[int]:
        # 思路同 l4 换根 DP
        n, m = len(edges1) + 1, len(edges2) + 1
        
        g1, g2 = [[] for _ in range(n)], [[] for _ in range(m)]
        for u, v in edges1:
            g1[u].append(v)
            g1[v].append(u)

        for u, v in edges2:
            g2[u].append(v)
            g2[v].append(u)

        # 记录以 u 根节点的到各节点的的距离计数
        # 第一次遍历以 0 为根节点各节点到子节点的距离计数
        # 第二次遍历换根，计算以每个节点为根节点的距离计数
        ans1 = [[0] * (k+1) for _ in range(n)]
        ans2 = [[0] * (k+1) for _ in range(m)]

        def dfs(g:List[List[int]], u:int, fa:int, ans: List[List[int]]) :
            ans[u][0] = 1

            for v in g[u]:
                if v == fa:continue
                dfs(g, v, u, ans)
                for i in range(k):
                    if ans[v][i] == 0:break
                    ans[u][i+1] += ans[v][i]
        
        dfs(g1, 0, -1, ans1)
        dfs(g2, 0, -1, ans2)

        mx_odd = sum(ans2[0][0:k])
        def reroot(g:List[List[int]], u:int, fa:int, need_mx:bool, ans: List[List[int]]):
            nonlocal mx_odd
            if fa != -1:
                fa_tmp = [0] * (k+1)
                fa_tmp[0] = 1
                for i in range(k):
                    fa_tmp[i+1] = ans[fa][i+1] - ans[u][i]
                
                for i in range(k):
                    ans[u][i+1] += fa_tmp[i]
                    
                if need_mx and sum(ans[u][0:k]) > mx_odd : mx_odd = sum(ans[u][0:k])

            for v in g[u]:
                if v == fa: continue
                reroot(g, v, u, need_mx, ans)

        reroot(g2, 0, -1, True, ans2)
        reroot(g1, 0, -1, False, ans1)
        return [sum(dis) + mx_odd for dis in ans1]
    
if __name__ == "__main__":
    sol = Solution()
    # edges1, edges2, k = [[0,1],[0,2],[2,3],[2,4]], [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], 2
    edges1, edges2, k = [[0,1],[0,2],[0,3],[0,4]], [[0,1],[1,2],[2,3]], 1

    print(sol.maxTargetNodes(edges1, edges2, k))