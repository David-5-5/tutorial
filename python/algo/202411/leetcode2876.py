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
            rg[v].append[u]
            deg[v] += 1


        # 拓扑排序 剪掉 g 上的所有树枝
        # 拓扑排序后，deg 值为 1 的点必定在基环上，为 0 的点必定在树枝上
        q = deque(i for i, d in enumerate(deg) if d == 0) # 初始化 deg = 0 的点
        while q:
            u = q.popleft()
            v = edges[u]
            deg[v] -= 1
            if deg[v] == 0: q.append(v)
        

if __name__ == "__main__":
    sol = Solution()
    edges = [6,3,6,1,0,8,0,6,6]
    print(sol.countVisitedNodes(edges))
