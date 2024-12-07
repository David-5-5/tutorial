from typing import List

# 双周赛 136
class Solution:
    def timeTaken(self, edges: List[List[int]]) -> List[int]:
        # 自行解答，换根 DP
        # 在比赛规定的时间内，完成代码的难度很大
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        # 记录离顶点最大的两个 time 时刻
        taken = [[0,-1,0,-1] for _ in range(n)] 
        
        def dfs(u:int, fa:int) -> int:

            for v in g[u]:
                if v == fa:continue
                dis = dfs(v, u)
                if dis >= taken[u][0]:
                    taken[u] = [dis, v] + taken[u][0:2]
                elif dis >= taken[u][2]:
                    taken[u] = taken[u][0:2] + [dis, v]
            
            return taken[u][0] + (1 if u % 2 else 2)
        dfs(0, -1)

        ans = [0] * n
        def reroot(u:int, fa:int):
            ans[u] = taken[u][0]
            for v in g[u]:
                if v == fa:continue
                newd = taken[u][0] if v != taken[u][1] else taken[u][2]
                newd += (1 if u % 2 else 2)
                if newd >= taken[v][0]:
                    taken[v] = [newd, u] + taken[u][0:2]
                elif newd >= taken[v][2]:
                    taken[v] = taken[v][0:2] + [newd, u]
                reroot(v, u)
        
        reroot(0, -1)
        return ans