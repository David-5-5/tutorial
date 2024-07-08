from math import inf
from typing import List

# use bfs not dfs to reduce the time complexity
class Solution:
    def maximumMinutes(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        min_fire = [[inf] * n for _ in range(m)]
        # bfs search the minimum time to fire
        def fire() -> int:
            q = []
            for x in range(m):
                for y in range(n):
                    if grid[x][y] == 1:
                        min_fire[x][y] = 0
                        q.append((x,y))            
            time = 1
            while q:
                tmp = q
                q = []
                for x, y in tmp:
                    for u,v in [(x+1,y), (x-1,y), (x, y+1), (x, y-1)]:
                        if 0 <= u < m and 0 <= v < n and grid[u][v] == 0 and min_fire[u][v]==inf:
                            min_fire[u][v] = time
                            q.append((u,v))
                time += 1

        fire()

        # use bfs check whether not reach safehouse it stay in (0,0) for "threshold" minutes
        def check(threshold: int) -> bool:
            visited = [[False] * n for _ in range(m)]
            q = [(0,0)]
            visited[0][0] = True
            time = 1
            while q:
                tmp = q
                q = []
                for x, y in tmp:
                    for u,v in [(x+1,y), (x-1,y), (x, y+1), (x, y-1)]:
                        if 0 <= u < m and 0 <= v < n and grid[u][v] == 0 and not visited[u][v]:
                            visited[u][v] = True
                            if u == m-1 and v == n-1:
                                if  min_fire[u][v] - time >= threshold: return True
                                else:return False
                            if min_fire[u][v] - time > threshold:
                                q.append((u,v))
                time += 1
            return False
        
        # 使用开区间 (left, right) 进行二分搜索
        right = m * n + 1
        left = -1
        while left + 1 < right:  # 区间不为空

            mid = (left + right) // 2
            if check(mid):
                left = mid  # 范围缩小到 [mid, right]
            else:
                right = mid  # 范围缩小到 [left, mid]
    
        return left if left < m * n else 10 ** 9


if __name__ == "__main__":
    sol = Solution()
    grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
    grid = [[0,0,0,0],[0,1,2,0],[0,2,0,0]]
    print(sol.maximumMinutes(grid))