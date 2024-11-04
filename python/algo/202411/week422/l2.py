from bisect import bisect_left
from cmath import inf
from functools import cache
import heapq
from typing import List


class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        # 比赛时自行解答，二分 + dfs 不是正确的思路
        n , m = len(moveTime), len(moveTime[0])

        def check(mx:int) -> bool:
            dis = [[0] * m for _ in range(n)]
            @cache
            def dfs(u:int, v:int, limit:int) :
                
                if u == 0 and v == 0: 
                    return True

                dis[u][v] = limit
                if limit <= moveTime[u][v]: 
                    return False
                for x, y in [(u+1,v), (u-1,v), (u,v-1), (u,v+1)]:
                    if 0<=x<n and 0<=y<m and limit > dis[x][y] and dfs(x, y, limit-1):
                        return True
                return False
            return dfs(n-1,m-1,mx)
        r = max(max(row) for row in moveTime) + n + m + 1
        return bisect_left(range(r), True, key=check)


    def minTimeToReach2(self, moveTime: List[List[int]]) -> int:
        # 参考题解，使用 Dijkstra 最短距离
        n, m = len(moveTime), len(moveTime[0])
        dist = [inf] * (n*m)
        visited = [False] * (n*m)

        dist[0] = 0
        # The element in pr is truple (weight, vertex)
        pr = []
        heapq.heappush(pr, (0, 0,0)) 
        while pr:
            _, r, c = heapq.heappop(pr)
            if visited[r*m+c]:
                continue
            visited[r*m+c] = True
            for nr, nc in [(r-1, c),(r+1, c),(r, c-1),(r, c+1)]:
                if 0<=nr<n and 0<=nc<m and not visited[nr*m+nc] and dist[nr*m+nc] > max(dist[r*m+c],moveTime[nr][nc])+1:
                    dist[nr*m+nc] = max(dist[r*m+c],moveTime[nr][nc])+1
                    heapq.heappush(pr, (dist[nr*m+nc], nr, nc))

        return dist[-1]

if __name__ == "__main__":
    sol = Solution()
    moveTime = [[0,4],[4,4]]
    print(sol.minTimeToReach2(moveTime))