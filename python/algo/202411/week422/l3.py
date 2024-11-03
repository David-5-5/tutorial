from bisect import bisect_left
from functools import cache
from typing import List


class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        n , m = len(moveTime), len(moveTime[0])

        def check(mx:int) -> bool:
            dis = [[0] * m for _ in range(n)]
            @cache
            def dfs(u:int, v:int, limit:int, step:int, time:int) :
                
                if u == n-1 and v == m-1: 
                    if moveTime[u][v] + step < limit: return True
                    else: return False

                dis[u][v] = moveTime[u][v] + step
                if dis[u][v] >= limit: 
                    return False
                for x, y in [(u+1,v), (u-1,v), (u,v-1), (u,v+1)]:
                    if 0<=x<n and 0<=y<m and moveTime[x][y]+step+time >dis[u][v] and dfs(x, y, limit, step + time , time+1):
                        return True
                return False
            return dfs(0,0,mx,0, 1)
        r = max(max(row) for row in moveTime) + n + m + 1
        return bisect_left(range(r), True, key=check)
