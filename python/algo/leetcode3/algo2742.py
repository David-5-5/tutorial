from cmath import inf
from functools import lru_cache
from typing import List

# refer to https://www.bilibili.com/video/BV1Hj411D7Tr/?spm_id_from=333.880.my_history.page.click
# # https://leetcode.cn/problems/painting-the-walls/solutions/2312808/xuan-huo-bu-xuan-de-dian-xing-si-lu-by-e-ulcd/
class Solution:
    def paintWalls(self, cost: List[int], time: List[int]) -> int:
        n = len(cost)
        # 前 i 面墙, j 所需时间
        # 返回值为最小 cost
        @lru_cache(maxsize=None)
        def dfs(i:int, j:int) -> int:
            # 下面注释代码内存溢出
            # if i < 0: 
            #     if j >= 0:
            #         return 0
            #     else:
            #         return inf
            if j > i: return 0 # 优化 j >= i+1
            if i < 0: return inf
            
            # 动态规划 选或不选
            return min(dfs(i-1, j-1), dfs(i-1, j+time[i]) + cost[i])
        ans = dfs(n-1, 0)
        # dfs.cache_clear()
        return ans
    
    
    # 装换成 0-1背包，使用 c++ 实现