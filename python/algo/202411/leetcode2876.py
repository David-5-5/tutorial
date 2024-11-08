from collections import deque
from typing import List

# 周赛 365
class Solution:
    def countVisitedNodes(self, edges: List[int]) -> List[int]:
        # 基环树 参考题解
        n = len(edges)
        rg = [[] for _ in range(n)] # 反图
        deg = [0] * n

        for u, v in enumerate(edges):
            rg[v].append(u)
            deg[v] += 1


        # 拓扑排序 剪掉 g 上的所有树枝
        # 拓扑排序后，deg 值为 1 的点必定在基环上，为 0 的点必定在树枝上
        q = deque(i for i, d in enumerate(deg) if d == 0) # 初始化 deg = 0 的点
        while q:
            u = q.popleft()
            v = edges[u]
            deg[v] -= 1
            if deg[v] == 0: q.append(v)
        
        ans = [0] * n
        # 在反图上遍历树枝
        def rdfs(u:int, depth:int) -> None:
            ans[u] = depth
            for v in rg[u]:
                if deg[v] == 0: rdfs(v, depth+1)
        
        # 基环树上找环
        for i, d in enumerate(deg):
            if d<=0: continue
            ring = []
            u = i
            while True:
                deg[u] = -1 # 避免重复访问
                ring.append(u)
                u = edges[u]
                if u == i: break # 找到环
            for u in ring: rdfs(u, len(ring))
        return ans

if __name__ == "__main__":
    sol = Solution()
    edges = [6,3,6,1,0,8,0,6,6]
    print(sol.countVisitedNodes(edges))
