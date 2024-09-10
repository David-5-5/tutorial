from math import inf
from typing import List

# 周赛 304
class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        # 自行解答 基环树
        n = len(edges)
        level = [[inf] * 2 for _ in range(n)]
        
        def dfs(u:int, l:int, t:int) :
            visited[u] = True
            level[u][t] = l
            v = edges[u]
            if v != -1 and not visited[v]:
                dfs(v, l+1, t)
        
        visited = [False] * n
        dfs(node1, 0, 0)

        visited = [False] * n
        dfs(node2, 0, 1)

        res, minl = -1, inf
        for i in range(n):
            mxl = max(level[i])
            if mxl < minl:
                minl = mxl
                res = i
        return res
    
    def closestMeetingNode2(self, edges: List[int], node1: int, node2: int) -> int:
        # 改为非递归
        n = len(edges)
        
        def calculate(u:int) -> List[int]:
            res = [inf] * n
            l = 0
            while u != -1 and res[u] == inf:
                res[u] = l
                u = edges[u]
                l += 1
            return res
        
        level1 = calculate(node1)
        level2 = calculate(node2)

        res, minl = -1, inf
        for i in range(n):
            mxl = max(level1[i], level2[i])
            if mxl < minl:
                minl = mxl
                res = i
        return res

if __name__ == "__main__":
    sol = Solution()
    edges, node1, node2 = [2,2,3,-1], 0, 1
    print(sol.closestMeetingNode(edges, node1, node2))
    print(sol.closestMeetingNode2(edges, node1, node2))
