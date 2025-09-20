from functools import cache
from typing import List

# 回溯 - 4.7 搜索 
class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        # 参考题解
        if (sum(nums) < k): return -1
        ans = -1
        n = len(nums)
        
        @cache
        def dfs(i: int, alt: int, even:int, prod:int, sel:bool):
            '''
            i: 当前的元素索引
            alt : 交错和
            even : 当前选择奇数或偶数个元素
            prod : 选择的元素的乘积
            sel : 是否包含已选择元素, 空元素不合法
            ''' 

            nonlocal ans
            if ans == limit or (ans >= 0 and prod > limit): # 剪枝
                return
            if i == n:
                if alt == k and prod <= limit and sel: ans = max(ans, prod)
                return
            
            # 不选择当前元素
            dfs(i + 1, alt, even, prod, sel)
            # 选择当前元素
            next_sum = alt + (nums[i] if even == 0 else -nums[i])
            # min(prod * nums[i], limit + 1) ！！！！最关键点，压缩状态空间 
            dfs(i + 1, next_sum, even ^ 1, min(prod * nums[i], limit + 1), True)
        
        dfs(0, 0, 0, 1, False)
        
        return ans