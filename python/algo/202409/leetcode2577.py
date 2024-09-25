from cmath import inf
import heapq
from typing import List

# 周赛 334
class Solution:
    def minimumTime(self, grid: List[List[int]]) -> int:
        # 参考题解
        m, n = len(grid), len(grid[0])

        if grid[0][1]>1 and grid[1][0]>1 : return -1

        # dis[i][j] 与 i+j 同奇偶，边权与 grid 和 dis[i][j] 奇偶相关
        dis = [[inf] * n for _ in range(m)]
        dis[0][0] = 0
        q = [(0,0,0)]

        while q:

            d, x, y = heapq.heappop(q)
            if x == m - 1 and y == n - 1 : return d
            for i, j in (x+1,y), (x-1,y), (x,y+1), (x,y-1):
                if 0<=i<m and 0<=j<n:
                    nd = max(d+1, grid[i][j])
                    nd += (nd - i - j) % 2
                    if nd < dis[i][j]:
                        dis[i][j] = nd
                        heapq.heappush(q, (nd, i, j))

        return dis[-1][-1]

if __name__ == "__main__":      
    sol = Solution()
    grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
    print(sol.minimumTime(grid))