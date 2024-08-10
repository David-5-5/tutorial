from collections import deque
from typing import List

# 周赛 322 参考题解 使用二分图判定是否奇数环
class Solution:
    def magnificentSets(self, n: int, edges: List[List[int]]) -> int:

        g = [[] for _ in range(n)]
        for u, v in edges: # 边的节点从1开始表示，需要-1转换回0开始
            g[u-1].append(v-1)
            g[v-1].append(u-1)

        vis = [0] * n
        clock = 0
        def bfs(start: int) -> int:
            nonlocal clock
            clock += 1
            mx = base
            q = deque([(start, base)])
            while q:
                u, c = q.popleft()
                mx = max(mx, c)
                vis[u] = clock # 访问当前节点
                for v in g[u]:
                    if vis[v] < clock:
                        vis[v]= clock
                        q.append((v, c+1))
            return mx

        color = [0] * n # 0 未染色，1 染红色 -1 染蓝色
        def dfs(u: int, c:int) -> bool:
            # dfs 寻找奇数环
            nodes.append(u) # 记录连通块中的节点
            color[u] = c
            for v in g[u]:
                if color[v] == c:
                    return True # 同色的相邻节点，表示奇数环
                if color[v] == -c:
                    continue # 不同色的相邻节点，跳过
                if dfs(v, -c): return True
            return False

        ans = 0
        for i, c in enumerate(color):
            if c: continue # 上一个连通块
            nodes = []
            if dfs(i, 1):
                return -1
            base = ans + 1
            for x in nodes:
                ans = max(ans, bfs(x))
        return ans

if __name__ == "__main__":
    sol = Solution()
    n, edges = 6, [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
    print(sol.magnificentSets(n, edges)) 
