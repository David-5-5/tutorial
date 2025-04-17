from functools import cache
from typing import List


class Solution:
    def maxStudents(self, seats: List[List[str]]) -> int:
        # 自行解答
        m, n = len(seats), len(seats[0])

        def check(top:int, left, pos:int) -> bool:
            x, y = pos // n, pos % n
            if seats[x][y] == '#': return False
            
            if y and (top>>(y-1)&1) : return False # left of top
            if y<n-1 and (top>>(y+1)&1): return False # right of top
            if y and (left>>(y-1)&1): return False # left
            
            return True

        @cache
        def dfs(top:int, left:int, pos:int) ->int:
            if pos == m * n: return 0
            
            # 不坐
            res = dfs(top, left, pos + 1) if (pos+1) % n else dfs(left, 0, pos + 1)
            # 坐
            if check(top, left, pos):
                left |= 1<<(pos%n)
                res = max(res, (dfs(top, left, pos + 1) if (pos+1) % n else dfs(left, 0, pos + 1))+1)
            return res

        return dfs(0, 0, 0)        