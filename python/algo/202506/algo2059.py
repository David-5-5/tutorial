from cmath import inf
from typing import List

# 动态规划 - 专题：把 X 变成 Y
class Solution:
    def minimumOperations(self, nums: List[int], start: int, goal: int) -> int:
        # 参考题解 广度优先搜索
        ops = [lambda x, y: x + y, lambda x, y: x - y, lambda x, y: x ^ y]    
        depth, q, vis = 0, [start], [False] * 1001
        vis[start] = True
        while q:
            depth += 1
            tmp = q
            q = []
            for u in tmp:
                for v in nums:
                    for op in ops:
                        val = op(u, v)
                        if val == goal: return depth
                        elif 0<=val<=1000 and not vis[val]:
                            q.append(val)
                            vis[val] = True
        
        return -1