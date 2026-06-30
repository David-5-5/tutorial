from bisect import bisect_left, bisect_right
from cmath import inf
from functools import cache
from typing import List


class Solution:
    def maxWalls(self, robots: List[int], distance: List[int], walls: List[int]) -> int:
        # 自行解答 难度分 2525
        rob = list(zip(robots, distance))
        rob.sort()
        walls.sort()
        n, m = len(rob), len(walls)

        @cache
        def dfs(i: int, prd: bool) -> int:
            if i < 0: return 0

            l_limit , r_limit = 0, inf
            if i + 1 < n: r_limit = rob[i+1][0]
            if i: l_limit = rob[i-1][0]

            # 未避免重复计算，当墙和机器人重复时，会导致重复计算墙壁
            # 因此规则是仅包含当前机器人所在墙壁，不包括左边或右边机器人所在墙壁
            l_l = bisect_left(walls, max(l_limit, rob[i][0] - rob[i][1]))
            # 因此当 walls[l_l] == rob[i-1][0] 包含左边机器人所在墙壁右移一位
            if i and l_l < m and walls[l_l] == rob[i-1][0]: l_l += 1
            l_p = bisect_right(walls, rob[i][0])

            r_p = bisect_left(walls, rob[i][0])
            r_r = bisect_right(walls, min(r_limit, rob[i][0] + rob[i][1]))
            # 因此当 walls[r_r] == rob[i+1][0] 包含右边机器人所在墙壁左移一位
            if i + 1 < n and walls[r_r-1] == rob[i+1][0]: r_r -= 1

            res = l_p - l_l + dfs(i-1, True)
            if not prd:
                res = max(res, r_r - r_p + dfs(i-1, False))
            else:
                pre_l = bisect_left(walls, max(rob[i+1][0]-rob[i+1][1], rob[i][0]))
                remain = pre_l - r_p
                res = max(res, min(r_r - r_p, remain) + dfs(i-1, False))

            return res
        
        return dfs(n-1, False)