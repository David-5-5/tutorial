from collections import deque
from itertools import combinations
from typing import List

class Solution:
    def maxPartitionFactor(self, points: List[List[int]]) -> int:
        # 自行解答，bfs, 二分图
        n = len(points)
        if n == 2: return 0

        def check(mx: int) -> bool:
            rb = [-1] * n
            vis = [False] * n
            q = deque()
            for c in range(n):
                if not vis[c]:
                    q.append(c)
                    if rb[c] == -1: rb[c] = 0
                    vis[c] = True
                while q:
                    i = q.popleft()
                    x1, y1 = points[i][0], points[i][1]
                    for j in range(n):
                        if i == j: continue
                        x2, y2 = points[j][0], points[j][1]
                        if abs(x1-x2) + abs(y1-y2) < mx:
                            if rb[i] == rb[j]: return False
                            else:
                                rb[j] = rb[i] ^ 1
                                if not vis[j]:
                                    q.append(j)
                                    vis[j] = True
            
            return True            

        l, r = -1, 4 * 10 ** 8 + 1
        while l + 1 < r:
            mid = (l + r) // 2
            if check(mid):
                l = mid
            else: r = mid

        return l


    def maxPartitionFactor2(self, points: List[List[int]]) -> int:
        # 自行解答，dfs 二分图
        n = len(points)
        if n == 2: return 0

        def check(mx: int) -> bool:
            rb = [-1] * n
            vis = [False] * n
            
            def dfs(i: int) -> bool:
                x1, y1 = points[i][0], points[i][1]
                for j in range(n):
                    if i == j: continue
                    x2, y2 = points[j][0], points[j][1]
                    if abs(x1-x2) + abs(y1-y2) < mx:
                        if rb[i] == rb[j]: return False
                        else:
                            rb[j] = rb[i] ^ 1
                            if not vis[j]:
                                vis[j] = True
                                if not dfs(j): return False
                return True              
            for i in range(n):
                if not vis[i]:
                    rb[i], vis[i] = 0, True
                    if not dfs(i): return False
            return True
        
        l, r = -1, 4 * 10 ** 8 + 1
        while l + 1 < r:
            mid = (l + r) // 2
            if check(mid):
                l = mid
            else: r = mid

        return l

if __name__ == "__main__":
    print(Solution().maxPartitionFactor2([[95922,-85190],[25931,81942],[-31245,-30278],[34636,-69149],[2662,-57718]]))