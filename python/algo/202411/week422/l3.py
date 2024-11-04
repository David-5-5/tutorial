from bisect import bisect_left
from cmath import inf
from functools import cache
import heapq
from typing import List


class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
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
                if 0<=nr<n and 0<=nc<m and not visited[nr*m+nc] and dist[nr*m+nc] > max(dist[r*m+c],moveTime[nr][nc])+1+(r+c)%2:
                    dist[nr*m+nc] = max(dist[r*m+c],moveTime[nr][nc])+1+(r+c)%2
                    heapq.heappush(pr, (dist[nr*m+nc], nr, nc))

        return dist[-1]

if __name__ == "__main__":
    sol = Solution()
    moveTime = [[0,4],[4,4]]
    print(sol.minTimeToReach(moveTime))