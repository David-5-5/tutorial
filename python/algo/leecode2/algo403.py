from typing import List
from functools import lru_cache
from bisect import bisect_right
class Solution:
    def canCross(self, stones: List[int]) -> bool:
        n = len(stones)
        # 由于每次的单元是上次的 k + [-1,0,1]，因此采用递归
        # 状态转移方程 dp[i][k] 表示从 i 下标开始 k + [-1,0,1] 是否可以到达终点
        # 边界条件：
        #   1）初始 i = 0, k = 0
        #   2）若 i = n - 1，则返回True
        # 状态转移方程 dp[i][k] 
        #   = True      若 dp[j1][k-1], dp[j2][k], dp[j3][k+1], 都存在一条路径能到达终点
        #   = False     反之
        # j1,j2,j3, 表示 stones[i] 分别加上 k-1, k, k+1 等于 stones[j1], stones[j2], stones[j3]
        # 若 stones[i] + k + * 的值在stones中不存在，则忽略
        @lru_cache(maxsize = None)
        def cross(begin :int, k:int) -> bool:
            if begin == n - 1: return True
            for i in [k-1,k,k+1]:
                if i > 0:
                    # 使用 bisect_right 二分查找跳到的下一个stones的位置
                    inx = bisect_right(stones, stones[begin]+i, begin+1)
                    if stones[inx-1] == stones[begin]+i:
                        if cross(inx-1, i): return True
            return False
        
        return cross(0, 0)
