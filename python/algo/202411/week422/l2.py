from bisect import bisect_left
from functools import cache
from typing import List


class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
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

if __name__ == "__main__":
    sol = Solution()
    moveTime = [[0,4],[4,4]]
    print(sol.minTimeToReach(moveTime))