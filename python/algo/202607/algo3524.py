from typing import List

# 七、其他线性 DP - 7.3 子数组 DP
class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        # 自行解答
        n  = len(nums)
        ans = [[0] * k for _ in range(n+1)]
        for i, v in enumerate(nums):
            for x in range(k):
                ans[i+1][x * v % k] += ans[i][x]
            ans[i+1][v % k] += 1
        
        return  [sum(col) for col in zip(*ans)]